alpha = ['@', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v' ,'w', 'x', 'y', 'z', '[', '/', ']', '.', '_']
inDec = []

code = 'oiytmmvk'
word = []
wordStr = ''

for i in code:
    pos = alpha.index(i)
    inDec.append(pos)

for j in range(0, 32):
    word = []
    for k in inDec:
        letter = j ^ k
        word.append(alpha[letter])
    print(''.join(word), bin(j))