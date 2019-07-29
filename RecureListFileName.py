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
path = dir #文件夹目录
datas = []

def eachFile(filepath):
    fileNames = os.listdir(filepath)  # 获取当前路径下的文件名，返回List
    for file in fileNames:
        newDir = filepath + '/' + file # 将文件命加入到当前文件路径后面
        # print(newDir)
        # if os.path.isdir(newDir): # 如果是文件夹
        if os.path.isfile(newDir):  # 如果是文件
            f = open(savefilename, 'a+')
            print(newDir)
            if os.path.splitext(file)[-1] == ".jpg" or os.path.splitext(file)[-1] == ".png"or os.path.splitext(file)[-1] == ".bmp":
                newDir = newDir.replace("\\\\", '/')
                newDir = newDir.replace("\\", '/')
                datas.append(newDir)
                f.write(newDir)
                f.write("\n")
                f.flush()
            elif os.path.splitext(file)[-1] == ".feat" :
                os.remove(newDir)
            f.close()
        else:
            eachFile(newDir)                #如果不是文件，递归这个文件夹的路径



if __name__ == "__main__":
    eachFile(path)
    print(datas)