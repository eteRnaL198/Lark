def are_lists_equal(l1: list, l2: list):
    if len(l1) != len(l2):
        return False
    return all(x == y and type(x) == type(y) for x, y in zip(l1, l2))
