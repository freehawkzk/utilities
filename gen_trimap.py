import os
import sys
from tools.mytools import ReadImgFileList
import cv2
import numpy as np

imglist = ReadImgFileList(sys.argv[1])
triDir = 'E:/datasets/AutoPortraitMatting/trimap/'
alpDir = 'E:/datasets/AutoPortraitMatting/alpha/'

def generate_trimap(alpha):
    fg = np.array(np.equal(alpha, 255).astype(np.float32))
    # fg = cv.erode(fg, kernel, iterations=np.random.randint(1, 3))
    
    unknown = np.array(np.not_equal(alpha, 0).astype(np.float32))
    
    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (10, 10))
    #unknown = cv2.dilate(unknown, kernel, iterations=np.random.randint(1, 10))
    unknown = cv2.dilate(unknown, kernel, iterations=1)
    trimap = fg * 255 + (unknown - fg) * 128
    return trimap.astype(np.uint8)

for imgname in imglist:
    img = os.path.basename(imgname)
    alpha = cv2.imread(alpDir+img)
    trimap = generate_trimap(alpha)
    cv2.imwrite(triDir+img,trimap)
    print(img)