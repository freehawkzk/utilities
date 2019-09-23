import os
import sys
import cv2

dir = sys.argv[1]

fns = os.listdir(dir)

ncount = 0
dst='C:/Users/zk/Desktop/allaligned/m/'
for fn in fns:
    img = cv2.imread(dir+fn,cv2.IMREAD_COLOR)
    img = cv2.resize(img,(100,100))

    cv2.imwrite(os.path.join(dst+'%07d.jpg')%ncount,img)
    ncount = ncount+1
