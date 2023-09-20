from Crypto.Util.number import long_to_bytes, bytes_to_long
import pwn
import random

server = pwn.remote("130.192.5.212", 6561)

def encrypt(pt: bytes) -> bytes:
    server.sendline(b'y')
    server.sendline(pt)
    res = server.recvline().decode().strip()
    ct = res.split("? ")[2]
    ct = bytes.fromhex(ct)
    return ct


print(server.recvline().decode())

server.sendline(str(1).encode())

print(server.recvline().decode())
ct1 = bytes.fromhex(server.recvline().decode().strip())
print(ct1)
print(len(ct1))


pt2 = b"a" * len(ct1)
ct2 = encrypt(pt2)

keystream = bytearray()
for p, c in zip(pt2, ct2):
    keystream.append(p ^ c)

pt1 = bytearray()
for k, c in zip (keystream, ct1):
    pt1.append(k ^ c)
print(pt1)

