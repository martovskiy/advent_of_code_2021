
with open('data.txt', 'r') as file:
    content = file.read()
    part1, part2 = content.strip().split("\n\n")

    coords = [[int(x) for x in ln.split(",")] for ln in part1.strip().split("\n")]
    instructions = [ln.split() for ln in part2.strip().split("\n")]


for no, fold in enumerate(instructions):
    dire, loc = fold[-1].split("=")
    loc = int(loc)

    map = set()

    for (x, y) in coords:
        if dire == "y":
            assert y != loc
            if y < loc:
                map.add((x, y))
            else:
                map.add((x, loc - (y - loc)))

        elif dire == "x":
            assert x != loc

            if x < loc:
                map.add((x, y))
            else:
                map.add((loc - (x - loc), y))

    coords = map

    if no == 0:
        print(len(coords))

grid = []
for n in range(6):
    grid.append(list("."*39))

for (x, y) in coords:
    grid[y][x] = "#"

print("\n".join("".join(ln) for ln in grid))
