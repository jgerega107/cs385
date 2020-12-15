import random

count = 100
print(str(count))

r = 1
wg = count*count
while r <= count:
    c = 1
    while c <= count:
        if c > r:
            print(str(r) + "," + str(c) + "," +str(wg) + ",r" + str(r) + str(c))
            wg-=1
        c+=1
    r+=1
