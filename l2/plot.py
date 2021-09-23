import sys
from pylab import plot, show

x = []
y = []


f = open(sys.argv[1], "rt")
z = f.read().split('\n')
for i in z:
    if("(" in i):
        x.append(eval(i)[0])
        y.append(eval(i)[1])

plot(x, y)
show()
