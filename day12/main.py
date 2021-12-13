from collections import defaultdict


def search(nodeSearch, path, part2=False):
    if nodeSearch == 'end':
        routes.add(tuple(path))
        return
    for node in data[nodeSearch]:
        if node == 'start':
            continue
        if node.islower() and node in path:
            if not part2:
                continue
            else:
                if any(path.count(y) > 1 for y in path if y.islower()):
                    continue
        search(node, path + [node], part2)
    return len(routes)


with open("data.txt", 'r') as file:
    data = defaultdict(list)
    for x in file.read().splitlines():
        a, b = x.split('-')
        data[a] += [b]
        data[b] += [a]
    routes = set()
    print(search('start', ['start']))
    print(search('start', ['start'], True))
