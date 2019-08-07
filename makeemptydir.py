import os
import sys

def MakeEmptyDir(dir,num):
    if os.path.isdir(dir):
        index=0
        while index < num:
            str = '{:0>4d}'.format(index)
            print(str)
            index=index+1
            dirpath = dir+'/'+str+'/'
            if not os.path.exists(dirpath):
                os.mkdir(dirpath)

if __name__ == "__main__":
    dir=sys.argv[1]
    print(dir)
    MakeEmptyDir(dir,200)
