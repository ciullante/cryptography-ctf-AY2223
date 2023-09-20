from Crypto.Util.number import long_to_bytes, bytes_to_long
import pwn
import json, base64

server = pwn.remote("130.192.5.212", 6521)

bait = json.dumps({
    "admin" : True
})
bait = bait.encode()

print(server.recvline().decode())

server.sendline(b'alessandro')
pt = server.recvline().decode().strip().split("> ")[1]
pt = bytearray(pt.encode())

res = server.recvline().decode().strip().split(": ")[1]
nonce, token = res.split(".")
token = base64.b64decode(token)
print(res)

new_token = bytearray()
for t, b, p in zip(token, bait, pt):
    new_token.append(t ^ b ^ p)         #pt ^ token = key => key ^ bait = enc(bait)


for message in server.recvlines(4):
    print(message.decode())

server.sendline(b"flag")
print(server.recvline().decode())

token = base64.b64encode(new_token).decode()
print(token)
tosend = f"{nonce}.{token}"
server.sendline(tosend.encode())

for message in server.recvlines(3):
    print(message.decode())

server.close()