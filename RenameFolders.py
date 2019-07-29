from xpinyin import Pinyin
import os
import sys

pin = Pinyin()


nameDict={}

dir=[]
if(len(sys.argv) == 1):
    print("You dont input the folder path that you want to list file name, dir will be default to ./!\n")
    dir="./"
else:
    dir=sys.argv[1]


dir = dir.replace("\\\\",'/')
dir = dir.replace("\\",'/')
path = dir #文件夹目录
datas = []

def eachFile(filepath):
    fileNames = os.listdir(filepath)  # 获取当前路径下的文件名，返回List
    for file in fileNames:
        newDir = filepath + '/' + file # 将文件命加入到当前文件路径后面
        if os.path.isdir(newDir): # 如果是文件夹
            pinyinname = pin.get_pinyin(newDir,"")  # 默认分割符为-
            t = pinyinname.split();
            pinyinname = "".join(t)
            if not pinyinname in nameDict:
                nameDict[pinyinname]=1
            else :
                nameDict[pinyinname] = nameDict[pinyinname]+1

def renameFolder(filepath):
    fileNames = os.listdir(filepath)  # 获取当前路径下的文件名，返回List
    for file in fileNames:
        newDir = filepath + '/' + file # 将文件命加入到当前文件路径后面
        if os.path.isdir(newDir): # 如果是文件夹
            pinyinname = pin.get_pinyin(newDir,"")  # 默认分割符为-
            t = pinyinname.split();
            pinyinname = "".join(t)
            if nameDict[pinyinname] >= 1:
                pinyinname1 = pinyinname+str(nameDict[pinyinname])
                nameDict[pinyinname] = nameDict[pinyinname]-1
                os.rename(newDir,pinyinname1)


if __name__ == "__main__":
    eachFile(path)
    renameFolder(path)