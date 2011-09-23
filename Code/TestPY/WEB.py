import socket
import emb

host = ''
port = 54321

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

s.bind((host, port))

s.listen(5)

while 1:
    client_sock, client_addr = s.accept()
    emb.hello( "Got " + str(client_sock.getpeername()) )
    client_sock.close()
