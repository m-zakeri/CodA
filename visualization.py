import networkx as nx
import matplotlib.pyplot as plt


def draw_cfg():
    with open(r'CFGS/main.txt', mode='r') as f:
        lines = f.readlines()
    lines = lines[1:-1]
    edges = list()
    for line_ in lines:
        ab = line_[:-1].split(' ')
        edges.append((ab[0], ab[1]))

    print(lines)
    G = nx.DiGraph(edges)
    print(G)

    color_map = []
    for node in G:
        if G.in_degree(node) == 0:
            color_map.append('green')
        elif G.out_degree(node) == 0:
            color_map.append('red')
        else:
            color_map.append('gray')

    pos = nx.kamada_kawai_layout(G=G)
    nx.draw(G, with_labels=True, node_size=1000, pos=pos, node_color=color_map)
    plt.show()


draw_cfg()