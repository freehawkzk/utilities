import dlib
import cv2
import os


import os
import sys

dir=[]
if(len(sys.argv) == 1):
    print("You dont input the folder path that you want to list file name, dir will be default to ./!\n")
    dir="./"
else:
    dir=sys.argv[1]

detector = dlib.get_frontal_face_detector()

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

dir = dir.replace("\\\\",'/')
dir = dir.replace("\\",'/')
savefilename="removedimglist.txt"
f = open(savefilename, 'a+')
filenames=ReadImgFileList(dir)
for file in filenames:
    #print(file)
    if not DetectFace(file) :
        #os.remove(file)
        print("remove "+file)

        f.write(file)
        f.write("\n")
        f.flush()
    #else:
        #print(file)
f.close()



