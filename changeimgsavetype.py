import os
import sys
import cv2


srcdir = sys.argv[1]
dstdir = sys.argv[2]
dsttype = sys.argv[3]

imgdir = srcdir.replace("\\\\",'/')
imgdir = imgdir.replace("\\",'/')
if imgdir.endswith('/'):
    imgdir = imgdir[:-1]
path = imgdir #文件夹目录

def ListPath(filepath):
    fileNames = os.listdir(filepath)  # 获取当前路径下的文件名，返回List
    for file in fileNames:
        newDir = filepath + '/' + file # 将文件命加入到当前文件路径后面
        if os.path.isfile(newDir):  # 如果是文件
            if os.path.splitext(file)[-1] == ".jpg" or os.path.splitext(file)[-1] == ".png"or os.path.splitext(file)[-1] == ".bmp":
                newDir = newDir.replace("\\\\", '/')
                newDir = newDir.replace("\\", '/')
                print(newDir)
                bn = os.path.basename(newDir)
                src = cv2.imread(newDir,cv2.IMREAD_UNCHANGED)
                cv2.imwrite(dstdir+bn.strip()[:-4]+dsttype,src)
        else:
            ListPath(newDir)                #如果不是文件，递归这个文件夹的路径



if __name__ == "__main__":
    ListPath(path)
