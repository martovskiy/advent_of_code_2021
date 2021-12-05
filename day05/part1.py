#!/usr/bin/python3
from collections import defaultdict

f = open("data.txt", "r")
lines = f.readlines()
space = defaultdict(int)
for line in lines:
    x, y = line.split('->')
    x1, y1 = [int(s) for s in x.split(',')]
    x2, y2 = [int(s) for s in y.split(',')]
    # straight lines
    if x1 == x2:
        for y3 in range(min(y1, y2), max(y1, y2) + 1):
            space[x1, y3] += 1
        continue
    if y1 == y2:
        for x3 in range(min(x1, x2), max(x1, x2) + 1):
            space[x3, y1] += 1
        continue
    if x2 > x1 and y2 > y1:
        for y3 in range(min(y1, y2), max(y1, y2) + 1):
            space[min(x1,x2)+y3-min(y1,y2), y3] += 1
        continue
    if x2 < x1 and y2 < y1:
        for y3 in range(min(y1, y2), max(y1, y2) + 1):
            space[min(x1,x2)+y3-min(y1,y2), y3] += 1
        continue
    for y3 in range(min(y1, y2), max(y1, y2) + 1):
        space[max(x1,x2)-y3+min(y1,y2), y3] += 1

ans = sum(x > 1 for x in space.values())
print(ans)