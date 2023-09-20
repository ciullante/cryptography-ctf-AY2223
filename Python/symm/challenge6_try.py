from Crypto.Util.number import long_to_bytes, bytes_to_long
import pwn
from Crypto.Cipher import AES

server = pwn.remote("130.192.5.212", 6523)

def encrypt(pt : bytes) -> bytes:
    for message in server.recvlines(5):
        print(message)

    server.sendline(b"enc")

    print(server.recvline().decode())

    server.sendline(pt.hex().encode())

    iv = bytes.fromhex( server.recvline().decode().strip().split(": ")[1] )
    ct = bytes.fromhex( server.recvline().decode().strip().split(": ")[1] )
    print(server.recvline().decode())
    return iv, ct

def decrypt(ct : bytes, iv: bytes) -> bytes:
    for message in server.recvlines(5):
        print(message)

    server.sendline(b"dec")

    print(server.recvline().decode())

    server.sendline(ct.hex().encode())

    print(server.recvline().decode())

    server.sendline(iv.hex().encode())
    res = server.recvline().decode()
    print(res)

    try:
        pt = bytes.fromhex( server.recvline().decode().strip().split(": ")[1] )
    except:
        print("BRAVO")
        return res.encode()
    return pt


leak = b"mynamesuperadmin"

pt1 = long_to_bytes(0, 16)

iv1, ct1 = encrypt(pt1)

ct1p = bytearray()
for i, p in zip(iv1, pt1):
    ct1p.append(i ^ p)

bait = bytearray()
for l, c in zip (leak, ct1p):
    bait.append(l ^ c)

pt = decrypt(ct1, bait)
server.close()