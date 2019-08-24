"""
    在建立明星人脸数据库的过程中，通过爬虫爬取了大量明星图片之后，需要对图片进行过滤。
本脚本会对传入的图片路径列表文件中的所有文件，进行人脸检测，对于不能检测到人脸的图片，将其
路径保存到输出文件中。方便后续的图片过滤或删除操作。
    本脚本通过Dlib的正脸检测进行人脸检测，使用了多线程技术。
"""
import dlib
import cv2
import os
import sys
import threading
import time

dir=[]
if(len(sys.argv) == 1):
    print("You dont input the folder path that you want to list file name, dir will be default to ./!\n")
    dir="./"
else:
    dir=sys.argv[1]

savefilename=sys.argv[2]

# 创建dlib人脸检测器对象
detector = dlib.get_frontal_face_detector()
filenames=[]

def DetectFace(imgpath):
    """
        对输入imgpath图像进行人脸检测，当图片中有且仅有1张人脸时，
    返回True,否则返回False.
    """
    img = cv2.imread(imgpath) # 图片读取
    if(img is None):
        return False
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    dets = detector(gray, 1) # dlib进行人脸检测
    return len(dets)==1 # 图片中有且仅有一张人脸

def DetectFace1(imgpath):
    """
        对输入imgpath图像进行人脸检测，当图片中有且仅有1张人脸时，
    返回True,否则返回False.
    """
    img = cv2.imread(imgpath) # 图片读取
    if(img is None):
        return False
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    dets = detector(gray, 1) # dlib进行人脸检测
    return dets 

def ReadImgFileList(imglistfilepath):
    """
        读取文件列表文件的内容，按行存储为list，并返回该list
    """
    lines = []
    with open(imglistfilepath, 'r') as file_to_read:
        while True:
            line = file_to_read.readline()
            if not line:
                break
            line = line.strip('\n')
            lines.append(line)
    return lines

def GetAFileName(filenames):
    """
        从输入的文件名列表中获取第一个文件名。考虑了多线程环境下的操作，
    通过定义的threading.Lock()进行多线程同步。获取了文件名后，会将该
    文件名从list中删除。
        当传入的文件名列表为空时，返回None.
    """
    threadLock.acquire()
    if len(filenames)>0:
        fn = filenames[0]
        del filenames[0]
        threadLock.release()
        return fn
    threadLock.release()
    return None

def ThreadFunc(filenames,f):
    """
        线程函数，在这里进行人脸检测，并计时。
    """
    filename = GetAFileName(filenames)
    esptime = time.clock()-starttime
    processedimg = totalnum - len(filenames)
    if processedimg % 10 == 0:
        print(str(processedimg)  + " average time : "+str(esptime/processedimg)+" "+str(processedimg/totalnum*100)+'%')
    if filename != None:
        #dets = DetectFace1(filename)
        #for index, d in enumerate(dets):
        #    info="{} {} L: {} T: {} R: {} B: {}".format(filename,index, d.left(), d.top(), d.right(), d.bottom())
        #    f.write(info)
        #    f.write("\n")
        #    f.flush()
        if not DetectFace(filename):
            f.write(filename)
            f.write("\n")
            f.flush()


class facedetectthread(threading.Thread):
    """
        人脸检测线程类，对threading.Thread的继承，完成对人脸检测函数的调用
    """
    def __init__(self, filenames, f):
        threading.Thread.__init__(self)
        self.filenames = filenames
        self.f = f
    def run(self):
        """
            线程需要执行的功能
        """
        ThreadFunc(filenames,f)

dir = dir.replace("\\\\",'/')
dir = dir.replace("\\",'/')
f = open(savefilename, 'a+')# 打开输出文件
filenames=ReadImgFileList(dir)# 读取所有文件名
threadLock = threading.Lock()# 创建获取文件名时的线程同步对象
threads = []# 记录当前已经创建的线程
starttime = time.clock()# 计时起点
totalnum = len(filenames)# 总的图像数目

while len(filenames) > 0 :# 当还有文件未处理时
    if len(threads) < 8:# 当前创建的线程总数小于8，CPU: i7-9700K
        func = facedetectthread(filenames,f)# 创建人脸检测线程对象
        func.start()# 开始执行线程
        threads.append(func)# 记录已创建的线程对象
    else:
        runfuncs=threading.enumerate()# 当前正在运行状态的线程
        for t in threads:
            if t not in runfuncs:# 对于已经结束的线程，改变其状态，并从已创建线程对象列表中去除
                t.join()
                threads.remove(t)
for t in threads:# 等待所有线程结束
    t.join()
f.close()# 关闭输出文件