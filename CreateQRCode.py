from MyQR import myqr
import os
words=b"\x01\x01\x12\x34\x56"
version, level, qr_name = myqr.run(
	words,
    version=1,
    level='H',
    picture=None,
    colorized=False,
    contrast=1.0,
    brightness=1.0,
    save_name="myqr.jpg",
    save_dir=os.getcwd()
	)