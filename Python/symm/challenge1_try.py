from Crypto.Util.number import long_to_bytes, bytes_to_long
import pwn

server = pwn.remote("130.192.5.212", 6531)


for i in range(128):
    challenge = server.recvline().decode()
    print(challenge)
    otp = server.recvline().decode().strip().split(': ')[1]
    print("otp is: " + otp)
        
    server.sendline(otp.encode())
    c = server.recvline().decode().strip().split(": ")[2]
    print(c)

    res = server.recvline().decode()
    print(res)

    c1 = c[0:32]
    c2 = c[32:]
    print(c1)
    print(c2)

    if c1 == c2:
        print("ECB")
        server.sendline("ECB".encode())
    else:
        print("ECB")
        server.sendline("CBC".encode())

    print(server.recvline().decode())


print(server.recvline().decode())

server.close()