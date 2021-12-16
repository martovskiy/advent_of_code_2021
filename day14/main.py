with open('data.txt', 'r') as file:
    content = file.read()
    polymer, part2 = content.strip().split("\n\n")

    instructions = dict([ln.split("->") for ln in part2.strip().split("\n")])

print(polymer)

polymerNew = ""
last = ''
for x in polymer:
    print ("" + last + x)
    key =    last + x
    if key in instructions:
        polymerNew = polymerNew + instructions[key]
    last = x
print(polymerNew)
