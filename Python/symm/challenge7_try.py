from Crypto.Util.number import long_to_bytes, bytes_to_long
import pwn
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad

cookie = "username={aaaaaa + true+pad fino a block size + aaaaaa}&admin=false"
fixed1 = b"username="
fixed2 = b"&admin="

server = pwn.remote("130.192.5.212", 6552)

p1 = b"a" * (AES.block_size - len(fixed1))
p2 = pad(b"true", AES.block_size)
p3 = b"a" * (AES.block_size - len(fixed2))
bait = p1 + p2 + p3

print(bait)
server.sendline(bait)

res = int(server.recvline().decode().split(" ")[-1])
cookie = long_to_bytes(res)
print(len(cookie))
print(cookie)
 
ptrue = cookie[16:32]
new_cookie = cookie[:48] + ptrue

print(new_cookie)

print(len(cookie), len(new_cookie))
for message in server.recvlines(4):
    print(message)

server.sendline(b"flag")

server.sendline(str(bytes_to_long(new_cookie)).encode())
for message in server.recvlines(4):
    print(message)


server.close()