from Crypto.Util.number import long_to_bytes, bytes_to_long
import pwn
from Crypto.Cipher import AES
import string
from Crypto.Util.Padding import pad, unpad

server = pwn.remote("130.192.5.212", 6543)
b_size = AES.block_size
length = 36 + len("CRYPTO23{}")
blocks = (length // b_size + 1) * b_size
print(length)

server_pad_len = 5
secret = ''


tosend = b""#b"a" * (b_size - 10) + b"a" * (0)
print(len(tosend))
server.recvlines(4)
server.sendline(b"enc")
server.sendline(tosend.hex().encode())

res = server.recvline().decode().strip()
ct = bytes.fromhex(res.split("> ")[2])
print(len(ct))




server.close()