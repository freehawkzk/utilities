import os
import sys
import shutil
import cv2
import numpy as np

def RotateClockWise90(img):
    trans_img = cv2.transpose( img )
    new_img = cv2.flip(trans_img, 1)
    return new_img

dir="D:/Work/XiongDi/pokerOCR/res/lab/action/uninsruance/"
filenames=os.listdir(dir)
dstdir="D:/Work/XiongDi/pokerOCR/res/lab/action/uninsruance/"
ncount = 0
for fn in filenames:
    print(dir+fn)
    dst=dstdir+str(ncount)+".png"
#    img = cv2.imread(dir+fn,cv2.IMREAD_COLOR)
#    h,w,c = img.shape
#    if h < w:
#        img = RotateClockWise90(img)
#    img=cv2.resize(img,(720,1280))
#    cv2.imwrite(os.path.join(dstdir,"%06d.png")% ncount,img)
    shutil.move(os.path.join(dir,fn),os.path.join(dstdir,"%06d.png")% ncount)
    ncount = ncount +1