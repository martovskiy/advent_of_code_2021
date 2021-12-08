#!/usr/bin/python3
from collections import defaultdict

f = open("data.txt", "r")
data = f.read().splitlines()
result = 0
for line in data:
    print(line)
    inp, out = line.strip().split(' | ')
    inp = inp.split()
    out = out.split()
    res = ''
    code = defaultdict(str)
    for d in inp:
        if len(d) == 2:
            code['1'] = d
        elif len(d) == 4:
            code['4'] = d
        elif len(d) == 3:
            code['7'] = d
        elif len(d) == 7:
            code['8'] = d
    for d in inp:
        if len(d) == 6:
            if len(''.join(set(code['4']).intersection(d))) == 4:
                code['9'] = d
            elif len(''.join(set(code['7']).intersection(d))) == 3:
                code['0'] = d
            else:
                code['6'] = d
        elif len(d) == 5:
            if len(''.join(set(code['7']).intersection(d))) == 3:
                code['3'] = d
            elif len(''.join(set(code['4']).intersection(d))) == 3:
                code['5'] = d
            else:
                code['2'] = d
    assert len(code) == 10
    for d in out:
        for k in code:
            if sorted(code[k]) == sorted(d):
                res += k
                break
    result += int(res, 10)

print(result)
