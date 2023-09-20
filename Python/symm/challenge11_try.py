from Crypto.Util.number import long_to_bytes, bytes_to_long
import pwn

server = pwn.remote("130.192.5.212", 6532)


challenge = server.recvline().decode()
print(challenge)

tosend = b"a" * 32

for i in range(128):
    server.sendline(tosend.hex().encode())
    ct1 = server.recvline().decode().strip().split(" ")[-1]
    server.sendline(tosend.hex().encode())
    ct2 = server.recvline().decode().strip().split(" ")[-1]
    if ct1 == ct2:
        server.sendline(b"ECB")
    else:
        server.sendline(b"CBC")

    print(server.recvline())
    print(server.recvline())
    print(server.recvline())

server.close()