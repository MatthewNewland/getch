import _getch
def getchb():
    return _getch.getch()

def getcheb():
    return _getch.getche()

def getch():
    return _getch.getch().decode()

def getche():
    return str(_getch.getche().decode())
