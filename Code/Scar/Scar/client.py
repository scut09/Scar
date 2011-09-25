import socket
import thread
import xml.etree.ElementTree as ET
import emb

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

def Parse(document):
    import xml.dom.minidom
    from xml.dom.minidom import Node
    dom = xml.dom.minidom.parseString(document)
    
    for name in dom.getElementsByTagName("user"):
        theID = name.getAttribute('id')
        children = name.getElementsByTagName("pos")        
        for child in children:
            if child.nodeType == Node.ELEMENT_NODE:
                emb.update_user(
                    int(theID),
                    float(child.getAttribute("x")),
                    float(child.getAttribute("y")),
                    float(child.getAttribute("z"))
                    )               



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
    return int(theID)
    
def Run():
    global sock, theID
    allinfo = sock.recv(2048)
    Parse(str(allinfo))
    return allinfo

def Send():
    global sock, theID
    pos = '<user id="' + theID + '">'
    posLock.acquire()
    pos += '<pos x="' + str(x) + '" y="' + str(y) + '" z="'+ str(z) + '"/>'
    posLock.release()
    pos += "</user>"
    sock.send(pos)
    
    


if __name__=="__main__":
    Connect()
    while 1:
        Run()
        Send()
#   locks = []
#    
#    lock = thread.allocate_lock()
#    lock.acquire()
#    locks.append(lock)
#    thread.start_new_thread( mailLoop, (lock, ) )
#    
#    for i in range( len(locks) ):
#        while locks[ i ].locked() : pass
    
    
    
        
