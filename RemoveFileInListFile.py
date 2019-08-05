"""
    删除在filelist中指定的所有文件
    使用示例：
    python RemoveFileInListFile.py filelist.txt
"""
import sys
import os
from ReadFileList import ReadFileList

def RemoveFileInList(filelist):
    """
    删除在filelist中的所有文件名指定的文件，如果删除之后目录为空，则删除目录
    """
    # 遍历文件名，
    for file in filelist:
        if(os.path.isfile(file)):
            os.remove(file)# 删除文件
            print("remove "+file)
            ppath = os.path.dirname(file)
            if not os.listdir(ppath):# 删除空文件夹
                os.removedirs(ppath)

if __name__ == "__main__":
    filelistpath = []
    if(len(sys.argv) == 1):
        print("请指定要删除的文件列表集合文件!\n")
        exit()
    else:
        filelistpath=sys.argv[1]
    # 读取文件列表文件名
    filenames = ReadFileList(filelistpath)
    RemoveFileInList(filenames)