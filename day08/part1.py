#!/usr/bin/python3

f = open("test.txt", "r")
data = f.read().splitlines()
print(sum(sum(len(d) in (2, 3, 4, 7) for d in line.split(" | ")[1].split(" ")) for line in data))


