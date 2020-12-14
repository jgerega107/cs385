import random

count = 10
print(str(count))
wgs = []

r = 1
while r <= count:
    c = 1
    while c <= count:
        if c != r:
            wg = random.randint(1, 500)
            while wg in wgs:
                wg = random.randint(1, count*count)
            wgs.append(wg)
            print(str(r) + "," + str(c) + "," +str(wg) + ",r" + str(r) + str(c))
        c+=1
    r+=1
