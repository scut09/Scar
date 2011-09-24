import socket
import thread

x = 0.0
y = 0.0
z = 0.0

posLock = thread.allocate_lock()
goLock = thread.allocate_lock()

host = '127.0.0.1'
port = 1000
BUF_SIZE = 1024

theID = 0
sock = None

def SetPos(newx, newy, newz):
    global x, y, z, posLock
    posLock.acquire()
    x, y, z = newx, newy, newz
    posLock.release()


def Connect():
    global host, port, BUF_SIZE, sock, theID
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((host, port))
    theID = sock.recv( BUF_SIZE )
    return theID
    
def Run():
    global sock, theID
    allpos = sock.recv(2048)
    return allpos

def Send():
    global sock, theID
    pos = "<user id=" + theID + ">"
    posLock.acquire()
    pos += "<pos x=" + str(x) + " y=" + str(y) + " z=" + str(z) + "/>"
    posLock.release()
    pos += "</user>"
    sock.send(pos)
    
    


#if __name__=="__main__":
#   locks = []
#    
#    lock = thread.allocate_lock()
#    lock.acquire()
#    locks.append(lock)
#    thread.start_new_thread( mailLoop, (lock, ) )
#    
#    for i in range( len(locks) ):
#        while locks[ i ].locked() : pass
    
    
    
        
