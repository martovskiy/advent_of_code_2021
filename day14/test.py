from collections import defaultdict

rules = {}
with open("data.txt") as f:
  for l in f:
    l = l.strip()
    if "->" in l:
      a, b = l.split(" -> ")
      rules[a] = b
    elif l:
      tmpl = l

def run(steps):
  pc = defaultdict(int)
  for i in range(len(tmpl) - 1):
    pc[tmpl[i:i+2]] += 1
  pc[tmpl[-1]] += 1

  for step in range(steps):
    pcn = defaultdict(int)
    for p, c in pc.items():
      if p in rules:
        pcn[p[0] + rules[p]] += c
        pcn[rules[p] + p[1]] += c
      else:
        pcn[p] += c
    pc = pcn

  freq = defaultdict(int)
  for p, c in pc.items():
    freq[p[0]] += c
  freq = list(freq.items())
  freq.sort(key=lambda t: t[1])
  print(freq[-1][1] - freq[0][1])

run(10)
run(40)