from Crypto.Util.number import bytes_to_long, getPrime
from secret import flag
p,q = getPrime(512), getPrime(512)
n = p*q
e = [31,71]
print(n)
m = bytes_to_long(flag)
print([pow(m,ee,n) for ee in e])

#111878026273294712018949370082518406506467116464661087967903317117790970179818521119422308743681165884714839229753890422498552439520129622400568291815662926856630054784957931276200669797960936574848652747695782006122165594815679174819420383236808427232190128494689592724885735557527546428352182955381438785243
#[21365530875222365408089590558277238868519093933679499573497796382318945735947363698250642292840163358661364502253675860875211930996586768348569665478478302557406023024198667549479713330995843573763779070287302925904249605248951539103766577720910916531156397290524711147190481250436303310833158551883065477802, 109923888150185132599133699920603647442125549267027925740547534185752534805190798828307763381282846183424731748817774041530111780035727732554883987972291399485218808912252904736687336430001558802685702179071045835397443328638586205728310934592265615642632264557052739379247258809601876089426321324712936017041]