import os
import sys
from tools.mytools import ReadImgFileList
from shutil import copyfile

imgnamesfile = sys.argv[1]

imgdir ='E:/datasets/AutoPortraitMatting/image/'
alpdir='E:/datasets/AutoPortraitMatting/alpha/'

imglist = ReadImgFileList(imgnamesfile)

for imgname in imglist:
    bn = os.path.basename(imgname)
    #print(os.path.split(imgname)[-2][-4])
    l=[]
    if os.path.split(imgname)[-2][-4]=='n':
        l='0'
    else:
        l='1'
    print(bn.strip()[-5])
    if bn.strip()[-5]=='e':
        continue
    else:
        copyfile(imgname,imgdir+l+bn)
        copyfile(imgname.strip()[:-4]+'_matte.png',alpdir+l+bn)
    print(bn)