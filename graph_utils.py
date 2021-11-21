import matplotlib.pyplot as plt
import networkx as nx
from networkx.drawing.nx_pydot import graphviz_layout


def head_node(gin):
    return min(gin.nodes)


def last_node(gin):
    return max(gin.nodes)


def shift_node_labels(gin, n):
    return nx.relabel_nodes(gin, {i: i + n for i in gin.nodes})


def build_single_node_graph(data):
    g = nx.DiGraph()
    g.add_node(0, data=[data])
    return g


def concat_graphs(gin1: nx.DiGraph, gin2: nx.DiGraph):
    gin2 = shift_node_labels(gin2, len(gin1) - 1)

    gin1_last = last_node(gin1)
    gin2_first = head_node(gin2)
    data = gin1.nodes[gin1_last]["data"] + gin2.nodes[gin2_first]["data"]

    g = nx.compose(gin1, gin2)
    g.nodes[gin1_last]["data"] = data
    return g


def draw_CFG(graph):
    pos = graphviz_layout(graph, prog="dot")
    node_labels = {node: args["data"] for node, args in graph.nodes.data()}
    edge_labels = {(f, t): args["state"] for f, t, args in graph.edges.data() if args.get("state")}
    nx.draw(graph,
            pos=pos,
            node_shape="s",
            node_size=100,
            node_color="white",
            font_color="black",
            edgecolors="tab:gray")
    nx.draw_networkx_labels(graph, pos=pos, labels=node_labels, horizontalalignment="left")
    nx.draw_networkx_edge_labels(graph, pos=pos, edge_labels=edge_labels, font_weight="bold")
    plt.show()
