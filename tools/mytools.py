import os
import sys
import hashlib

def ReadImgFileList(imglistfilepath):
    """
        读取文件列表文件的内容，按行存储为list，并返回该list
    """
    lines = []
    with open(imglistfilepath, 'r') as file_to_read:
        while True:
            line = file_to_read.readline()
            if not line:
                break
            line = line.strip('\n')
            lines.append(line)
    return lines

def CalcHashOfFile(filename):
    """计算文件的md5值
    
    Arguments:
        filename {[string]} -- [文件名路径]
    返回值：
        如果指定的filename是文件并且存在，那么返回该文件的md5值，否则，返回None
    """
    filename = os.path.abspath(filename)
    if os.path.exists(filename) and os.path.isfile(filename) :
        hashvalue = hashlib.md5(open(os.path.join(A,filename),'rb').read()).hexdigest()
        return hashvalue
    else :
        return None