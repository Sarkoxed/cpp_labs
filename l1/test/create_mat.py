from random import random, randint

def create_pal(x):
    return int(str(x) + str(x)[::-1])

n = randint(2, 10)
m = randint(3, 7)
l = [str(n), str(m), ]
for i in range(n):
    for j in range(m):
        if(random() < 0.2):
            if(random() < 0.5):
                l.append(str(create_pal(randint(1, 1000))))
            else:
                l.append(str(randint(100, 1000)))
        else:
            l.append('0')

l.append("rwegregr")

with open("test.txt", "wt") as f:
    f.write("\n".join(l))
