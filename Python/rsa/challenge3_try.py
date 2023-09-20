from Crypto.Util.number import bytes_to_long, getPrime, long_to_bytes

#kth root of the number n
def iroot(k, n):
    u, s = n, n+1
    while u < s:
        s = u
        t = (k-1) * s + n // pow(s, k-1)
        u = t // k
    return s

n = 1002377325462265193999966239331938420043855910747382013931673
e = 3
ct = 3239652861114474176617817642126683102816200405503678601991

## testiamo low exponent
x = iroot(e, ct)
print(long_to_bytes(x))


p = 934637197090526256706525222709
q = 1072477458186567150192511962197

phi = (p - 1 ) * (q - 1)
d = pow(e, -1 , phi)

m = pow(ct, d, n)
print(long_to_bytes(m))