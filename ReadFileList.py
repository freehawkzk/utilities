"""
读取filelist文件，返回其中所有文件名组成的列表
"""

def ReadFileList(filelistpath):
    """
        读取文件列表文件的内容，按行存储为list，并返回该list
    """
    lines = []
    with open(filelistpath, 'r') as file_to_read:
        while True:
            line = file_to_read.readline()
            if not line:
                break
            line = line.strip('\n')
            lines.append(line)
    return lines