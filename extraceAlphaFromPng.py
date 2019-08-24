import os
import sys
import cv2
from tools.mytools import ReadImgFileList

imglistfilepath=sys.argv[1]

imgs=ReadImgFileList(imglistfilepath)

for file in imgs:
    f = os.path.abspath(file)
    f=f.replace("\\",'/')
    s=f.split('/')
    s[3]="mask"
    dir = s[0:-1]
    d=s[0]+'/'
    for do in dir[1:]:
        d=d+do+'/'
    if not os.path.exists(d):
        os.makedirs(d)
    img = cv2.imread(file,cv2.IMREAD_UNCHANGED)
    b,g,r,alpha = cv2.split(img)
    rt ,mask = cv2.threshold(alpha,125,255,cv2.THRESH_BINARY)
    cv2.imwrite(d+s[-1],mask)
    print(file)

    