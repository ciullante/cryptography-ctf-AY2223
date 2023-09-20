import pwn
from Crypto.Cipher import AES
import string

server = pwn.remote("130.192.5.212", 6542)
b_size = AES.block_size
secret_len = 36 + len("CRYPTO23{}")
blocks = (secret_len // b_size + 1) * b_size

server_pad_len = 5
secret = ''

for i in range(secret_len):

    new_block = "A" * (b_size - server_pad_len)
    pad = "A" * (blocks - 1 - i)
    if (i < b_size):
        myblock = "A" * (b_size - 1 - i)
    else:
        myblock = secret[-(b_size - 1):]
    for letter in string.printable:
        if i < b_size:
            tosend = new_block + myblock + secret + letter + pad
        else:
            tosend = new_block + myblock + letter + pad
        server.recvlines(4)
        server.sendline(b"enc")
        server.sendline(tosend.encode().hex().encode())

        res = server.recvline().decode().strip()
        ct = bytes.fromhex(res.split("> ")[2])

        if ct[16:32] == ct[blocks + 16: blocks + 32]:
            secret += letter
            print(secret)
            break

server.close()
