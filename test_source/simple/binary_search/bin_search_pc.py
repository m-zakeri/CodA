def simple_bin_search_pc1(n, search):
    return (0 < n) and \
    (1 < n) and \
    (2 < n) and \
    (3 < n) and \
    (4 < n) and \
    not(5 < n) and \
    (0 <= (n - 1)) and \
    (3 < search) and \
    ((((0 + (n - 1)) / 2) + 1) <= (n - 1)) and \
    not(4 < search) and \
    not(4 == search)