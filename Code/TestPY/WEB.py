import socket
import thread
import xml.etree.ElementTree as ET

theID = 0
Lock = thread.allocate_lock()
dictLock = thread.allocate_lock()

posDic = dict()

def GetAllInfo():
    global posDic

    dictLock.acquire()
    allpos = "<all>"
    for node in posDic:
        allpos += posDic[ node ]
    allpos += "</all>"
    dictLock.release()

    return allpos


def Handler(sock):
    global theID, posDic
    global allpos, posLock

    Lock.acquire()    
    theID += 1
    tempId = theID
    Lock.release()

    sock.send(str(tempId))
    ##
    
    data = ''
    while data != 'end':
        info = GetAllInfo()
        print info
        sock.send(info)
        user = sock.recv( 1024 )
        
        dictLock.acquire()
        posDic[ tempId ] = user
        dictLock.release()        
        
    print end
        

HOST = ''
PORT = 1000

s = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
s.bind((HOST, PORT))
s.listen( 50 )

id = 1

while 1:
    sock, addr = s.accept()

    print sock.getpeername()

    thread.start_new_thread( Handler, (sock,) )


    
    
    
