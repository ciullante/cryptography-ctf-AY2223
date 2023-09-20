import os
os.environ['PWNLIB_NOTERM'] = 'True'  # Configuration patch to allow pwntools to be run inside of an IDE
os.environ['PWNLIB_SILENT'] = 'True'
from pwnlib.tubes.remote import remote
from Crypto.Util.number import bytes_to_long, getPrime, long_to_bytes

server = remote("130.192.5.212", 6645)


n = server.recv(1024).decode()
c = server.recv(1024).decode()

n = int(n)
c = int(c)
e = 65537

bait = (pow(2, e, n) * c) %n

#print(str(bait).encode())
server.send(b'd' + str(bait).encode() + b'\n')

x = server.recvline(2000).decode()

x = int(x)
x = x // 2

print(long_to_bytes(x))

