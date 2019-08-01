'''
递归的删除目录下特定后缀名的文件，如果删除文件后文件夹为空，删除该文件夹
'''

import os
import sys

dir=[]
if(len(sys.argv) == 1):
    print("You dont input the folder path that you want to list file name, dir will be default to ./!\n")
    dir="./"
else:
    dir=sys.argv[1]

# 指定VS临时文件
tobecleanedfileexts=[".idb",".db",".ipdb",".pdb",".iobj",".ilk",".exp",".obj",".log",".tlog",".lastbuildstate",".opendb",".ipch",".pch","unsuccessfulbuild"]

dir = dir.replace("\\\\",'/')
dir = dir.replace("\\",'/')
path = dir #文件夹目录
datas = []

def CleanPath(filepath):
    fileNames = os.listdir(filepath)  # 获取当前路径下的文件名，返回List
    for file in fileNames:
        newDir = filepath + '/' + file # 将文件命加入到当前文件路径后面
        if os.path.isfile(newDir):  # 如果是文件
            fileext = os.path.splitext(file)[-1]
            if fileext in tobecleanedfileexts :
                newDir = newDir.replace("\\\\", '/')
                newDir = newDir.replace("\\", '/')
                try:
                    os.remove(newDir)
                    print("remove "+newDir)
                except PermissionError as identifier:
                    pass

        else:
            CleanPath(newDir)                #如果不是文件，递归这个文件夹的路径
                
            try:
                if not os.listdir(newDir):
                    os.removedirs(newDir)
                    print("removedir "+newDir)
            except FileNotFoundError as identifier:
                pass

if __name__ == "__main__":
    CleanPath(path)