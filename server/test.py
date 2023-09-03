import socket

clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientsocket.connect(('localhost', 3321))
clientsocket.send(bytes('holis!!!!', 'UTF-8'))
print(clientsocket.recv(1024))
