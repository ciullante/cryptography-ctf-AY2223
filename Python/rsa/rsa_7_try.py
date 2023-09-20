import os
os.environ['PWNLIB_NOTERM'] = 'True'  # Configuration patch to allow pwntools to be run inside of an IDE
os.environ['PWNLIB_SILENT'] = 'True'
from pwnlib.tubes.remote import remote
from Crypto.Util.number import bytes_to_long, getPrime, long_to_bytes
import decimal

server = remote("130.192.5.212", 6647)

n = int(server.recvline().decode())
c = int(server.recvline().decode())
e = 65537

n_bit = n.bit_length()

lower_bound = 0
upper_bound = n
m = 0
for i in range(n_bit):
    c =( c * pow(2, e, n)) %n
    server.sendline(str(c).encode())
    bit = int(server.recvline().decode())
    if  bit == 1:
        print("111")
        lower_bound = (upper_bound + lower_bound) // 2
    else:
        print("000")
        upper_bound = (upper_bound + lower_bound) // 2

print(int(upper_bound))
print(int(lower_bound))
u = int(upper_bound)
l = int(lower_bound)
print(long_to_bytes(u))
print(long_to_bytes(l))