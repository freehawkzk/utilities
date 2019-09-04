import os
import sys
import chardet

def ReadImgFileList(imglistfilepath,encoding):
    """
        读取文件列表文件的内容，按行存储为list，并返回该list
    """
    lines = []
    with open(imglistfilepath, 'r',encoding=encoding) as file_to_read:
        while True:
            line = file_to_read.readline()
            if not line:
                break
            line = line.strip('\n')
            lines.append(line)
    return lines

def AddVersionNum(filepath,encoding):
    lines = ReadImgFileList(filepath,encoding)
    newlines=[]
    for line in lines:
        l = line[:line.rfind(' ')]
        if l=='int g_VersionLL =':
            curr = int(line[line.rfind(' '):-1])
            #print(curr)
            #print(l)
            curr = curr+1
            #print(l+' '+str(curr)+';')
            line = l+' '+str(curr)+';'
        newlines.append(line)
    f = open(filepath, 'w+',encoding=encoding)
    for line in newlines:
        f.write(line)
        f.write('\n')
        #print(line)
    f.close()

if __name__ == "__main__":

    result=[] 
    with open(sys.argv[1], "rb") as f:
        msg = f.read()
        result = chardet.detect(msg)
        print(result['encoding'])
    AddVersionNum(sys.argv[1],encoding=result['encoding'])