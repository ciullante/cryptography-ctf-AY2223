
import pwn
from Crypto.Cipher import AES
import string
from Crypto.Util.Padding import pad

server = pwn.remote("130.192.5.212", 6544)
b_size = AES.block_size
secret_len = 36 + len("CRYPTO23{}")

for j in range(1, 7):
    len_pad1 = j
    len_pad2 = 10 - j
    secret = ''
    for i in range(secret_len):
        back_block = b"A" * (b_size - len_pad1)
        front_block1 = b"A" * (b_size - len_pad2)
        front_block2 = b"A" * (b_size - (secret_len % b_size))
        pusher = b"A" * (i + 1)

        if (i < b_size):
            myblock = "A" * (b_size - 1 - i)
        else:
            myblock = secret[-(b_size - 1):]
        found = False
        for letter in string.printable:
            if i < b_size - 1:
                tosend = back_block + \
                    pad((letter + secret).encode(), b_size) + \
                    pusher + front_block1 + front_block2
            else:
                tosend = back_block + letter.encode() + \
                    secret[:15].encode() + pusher + front_block1 + front_block2
            server.recvlines(4)
            server.sendline(b"enc")
            server.sendline(tosend.hex().encode())

            res = server.recvline().decode().strip()
            ct = bytes.fromhex(res.split("> ")[2])

            if ct[16:32] == ct[96: 112]:
                secret = letter + secret
                print(secret)
                found = True
                break
        if not found:
            break
    if len(secret) == secret_len:
        print(secret)
        break

server.close()
