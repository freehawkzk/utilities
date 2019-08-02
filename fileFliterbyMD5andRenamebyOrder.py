#coding:utf-8
import os
import hashlib
import shutil
import sys

dir=[]
if(len(sys.argv) == 1):
    print("You dont input the folder path that you want to list file name, dir will be default to ./!\n")
    dir="./"
    savefilename = "default_file_name.txt"
else:
    dir=sys.argv[1]

dir = dir.replace("\\\\",'/')
dir = dir.replace("\\",'/')
if not dir.endswith('/'):
    dir = dir + '/'

A = dir
md5dict={}
nCount = 1
for filename in os.listdir(A):
    print(filename)
    hashvalue = hashlib.md5(open(os.path.join(A,filename),'rb').read()).hexdigest()
    if hashvalue in md5dict:
        os.remove(A+filename)
        print("  delete")
    else:
        md5dict[hashvalue]=os.path.join(A,filename)
    shutil.move(os.path.join(A,filename),os.path.join(A,"%05d.jpg")% nCount)
    nCount =nCount + 1


