import os
os.environ['PWNLIB_NOTERM'] = 'True'  # Configuration patch to allow pwntools to be run inside of an IDE
os.environ['PWNLIB_SILENT'] = 'True'
from pwnlib.tubes.remote import remote
from Crypto.Util.number import bytes_to_long, getPrime, long_to_bytes
from sys import set_int_max_str_digits

set_int_max_str_digits(100000)

server = remote("130.192.5.212", 6646)

c = server.recvline(1024).decode()

c = int(c)
e = 65537

c_2m = c * pow(2,e)


server.sendline(b'd' + str(c_2m).encode())

x = server.recvline(2000).decode()

x = int(x)
x = x // 2

print(long_to_bytes(x))


