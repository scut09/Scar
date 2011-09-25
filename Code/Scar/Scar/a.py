import threading

lock = threading.Lock()
i = 0

def SetI( newi ):
    global i
    lock.acquire()
    i = newi
    lock.release()

def GetI():
    global i
    lock.acquire()
    temp = i
    lock.release()
    return temp

def Run():
    while 1:
        pass
