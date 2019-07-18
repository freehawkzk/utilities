# 将指定路径下的所有文件的绝对路径保存到指定的txt文件中
# Usage: python.exe listfilename.py  path  savefile.txt

import os
import sys

dir=[]
savefilename = []
if(len(sys.argv) == 1):
    print("You dont input the folder path that you want to list file name, dir will be default to ./!\n")
    dir="./"
    savefilename = "default_file_name.txt"
else:
    dir=sys.argv[1]

if(len(sys.argv) <= 2):
    print("You dont input the save txt file name, information will be saved in default_file_name.txt!\n")
    savefilename = "default_file_name.txt"
else:
    savefilename = sys.argv[2]

dir = dir.replace("\\\\",'/')
dir = dir.replace("\\",'/')
filenames=os.listdir(dir)
for file in filenames:
    file = dir+file
    print(file)
    cmd='Dlib_68ptsx.exe '+file+' '+savefilename
    print(cmd)
    os.system(cmd)