import dlib
import cv2
import os


import os
import sys
import threading
dir=[]
if(len(sys.argv) == 1):
    print("You dont input the folder path that you want to list file name, dir will be default to ./!\n")
    dir="./"
else:
    dir=sys.argv[1]

savefilename=sys.argv[2]

detector = dlib.get_frontal_face_detector()
filenames=[]

def DetectFace(imgpath):
    #print(imgpath)
    img = cv2.imread(imgpath)
    if(img is None):
        return False
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY);
    #img = dlib.load_rgb_image(imgpath)
    dets = detector(gray, 1)
    return len(dets)>0

def ReadImgFileList(imglistfilepath):
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
    threadLock.acquire()
    if len(filenames)>0:
        fn = filenames[0]
        del filenames[0]
        threadLock.release()
        return fn
    threadLock.release()
    return None

def ThreadFunc(filenames,f):
    filename = GetAFileName(filenames)

    if filename != None:
        if not DetectFace(filename) :
            #os.remove(file)
            print("remove "+filename)
            f.write(filename)
            f.write("\n")
            f.flush()


class facedetectthread(threading.Thread):
    def __init__(self, filenames, f):
        threading.Thread.__init__(self)
        self.filenames = filenames
        self.f = f
    def run(self):                   #把要执行的代码写到run函数里面 线程在创建后会直接运行run函数 
        ThreadFunc(filenames,f)


dir = dir.replace("\\\\",'/')
dir = dir.replace("\\",'/')

f = open(savefilename, 'a+')
filenames=ReadImgFileList(dir)
threadLock = threading.Lock()
threads = []
while len(filenames) > 0 :
    if len(threads) < 8:
        func = facedetectthread(filenames,f)
        func.start()
        threads.append(func)
    else:
        for t in threads:
            t.join()
            threads.remove(t)
            break
for t in threads:
    t.join()
f.close()



