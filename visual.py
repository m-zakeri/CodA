import networkx as nx
import matplotlib.pyplot as plt
from networkx.drawing.nx_pydot import graphviz_layout


def parse_graph(path):
    with open(path, mode='r') as f:
        lines = list(map(str.strip, f.readlines()))

    edge_lines = lines[:-2]
    edges = [t.split(" ") for t in edge_lines]
    edges = [tuple(map(int, e)) for e in edges]

    node_state_lines = lines[-2:]
    node_states = [s.split(":") for s in node_state_lines]
    node_states = [(s[0], int(s[1])) for s in node_states]
    return edges, node_states


def build_graph_from_edges(edges):
    graph = nx.DiGraph()
    graph.add_edges_from(edges)
    return graph


def draw_CFG(graph, states):
    top_down_pos = graphviz_layout(graph, prog="dot")
    color_map = create_color_map(graph, states)

    nx.draw(graph,
            pos=top_down_pos,
            with_labels=True,
            font_weight="bold",
            node_color=color_map,
            node_size=800,
            font_color="black",
            alpha=0.9,
            edgecolors="tab:gray")

    plt.show()


def create_color_map(graph, states):
    color_map = ["white"] * len(graph)
    for state in states:
        if state[0] == "initial nodes":
            color_map[state[1] - 1] = "#c0ffc0"
        if state[0] == "final nodes":
            color_map[state[1] - 1] = "yellow"
    return color_map


def main():
    edges, states = parse_graph('CFGS/v2/5/1.txt')
    g = build_graph_from_edges(edges)
    draw_CFG(g, states)


if __name__ == '__main__':
    main()
