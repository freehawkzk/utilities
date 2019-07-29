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
            name1 = newDir
            name1 = name1.replace('·',"")
            os.rename(newDir, name1)

if __name__ == "__main__":
    eachFile(path)
