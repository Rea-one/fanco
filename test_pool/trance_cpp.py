import numpy as np

if __name__ == "__main__":
    target = input("输入要打开的文件名: ")
    data = []
    file = open(target)
    for line in file:
        for elem in line.split():
            data.append(elem)
            
            
    change_sign = False
    string_pool = []
    _subject = []
    action = []
    _object = []
    for elem in data:
        for tar in elem:
            if tar == '.':
                if _subject.__len__() == 0:
                    _subject = string_pool
                    string_pool = []
                elif action.__len__() == 0:
                    action = string_pool
                    string_pool = []
                elif _object.__len__() == 0:
                    _object = string_pool
                    string_pool = []
                    
                    