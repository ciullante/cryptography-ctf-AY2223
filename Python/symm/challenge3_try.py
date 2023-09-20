import pwn
from Crypto.Cipher import AES
import string

server = pwn.remote("130.192.5.212", 6541)
b_size = AES.block_size
secret_len = 36 + len("CRYPTO23{}")
blocks = (secret_len // b_size + 1) * b_size

secret = ''

for i in range(secret_len):

    pad = "A" * (blocks - 1 - i)
    if (i < b_size):
        myblock = "A" * (b_size - 1 - i)
    else:
        myblock = secret[-(b_size - 1):]
    for letter in string.printable:
        if i < b_size:
            tosend = myblock + secret + letter + pad
        else:
            tosend = myblock + letter + pad
        server.recvlines(4)
        server.sendline(b"enc")
        server.sendline(tosend.encode().hex().encode())

        res = server.recvline().decode().strip()
        ct = bytes.fromhex(res.split("> ")[2])

        if ct[0:16] == ct[blocks: blocks + 16]:
            secret += letter
            print(secret)
            break

server.close()
