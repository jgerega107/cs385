def get_ways_1(num_stairs):
    ways = []
    if num_stairs <= 0:
        ways.append([])
    else:
        for i in range(1, 4):
            if num_stairs >= i:
                result = get_ways_1(num_stairs - i)
                for j in range(len(result)):
                    result[j].insert(0, i)
                ways += result
    return ways