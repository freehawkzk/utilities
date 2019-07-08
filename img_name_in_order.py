# 将指定路径下的所有文件的绝对路径保存到指定的txt文件中
# Usage: python.exe listfilename.py  path  savefile.txt

import os
import sys
import cv2
import shutil
dir=[]
savefilename = []
if(len(sys.argv) == 1):
    print("You dont input the folder path that you want to list file name, dir will be default to ./!\n")
    dir="./"
    savefilename = "default_file_name.txt"
else:
    dir=sys.argv[1]

dir = dir.replace("\\\\",'/')
dir = dir.replace("\\",'/')


for index in range(1,140):
    dir1=dir+"/"+str(index)+"/"
    filenames = os.listdir(dir1)
    j=0
    for file in filenames:
        file = dir1+file
        print(file)
        f2 = dir1 + str(index)+"-"+str(j)+".bmp"
        j = j+1
        print (f2)
        shutil.move(file,f2)
