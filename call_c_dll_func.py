# 将指定路径下的所有文件的绝对路径保存到指定的txt文件中
# Usage: python.exe listfilename.py  path  savefile.txt

import os
import sys
import cv2
import shutil
import ctypes
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

dll = ctypes.cdll.LoadLibrary( 'FaceVerificationDllx.dll' )
nRst = dll.GetFaceFeature(("E:/XiongDi/PMDataset/humans/1/1-1.bmp").encode()  , ("32223").encode())

