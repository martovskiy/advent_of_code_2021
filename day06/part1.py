#!/usr/bin/python3
from collections import defaultdict

f = open("data.txt", "r")
lines = f.readlines()
input = [int(s) for s in lines[0].split(',')]
data = defaultdict(int)
for i in input:
    data[i] = data[i] + 1
epoch = 256  #
for i in range(epoch):
    zerodata = data[0]
    data[0] = data[1]
    data[1] = data[2]
    data[2] = data[3]
    data[3] = data[4]
    data[4] = data[5]
    data[5] = data[6]
    data[6] = data[7] + zerodata
    data[7] = data[8]
    data[8] = zerodata

print(sum(data.values()))
