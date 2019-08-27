from cnocr import CnOcr
ocr = CnOcr()
res = ocr.ocr_for_single_line('1.JPG')
print("Predicted Chars:", res)