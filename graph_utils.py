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


# todo: merge gin1's last node with gin2's first node
def concat_graphs(gin1: nx.DiGraph, gin2: nx.DiGraph):
    gin2 = shift_node_labels(gin2, len(gin1) - 1)

    gin1_last = last_node(gin1)
    gin2_first = head_node(gin2)
    data = gin1.nodes[gin1_last]["data"] + gin2.nodes[gin2_first]["data"]

    g = nx.compose(gin1, gin2)
    g.nodes[gin1_last]["data"] = data
    return g


def embed_in_for_structure(gin, initializer, condition, successor):
    g = nx.DiGraph()
    g_starting_nodes_len = 2
    gin = shift_node_labels(gin, g_starting_nodes_len)
    gin_head = head_node(gin)
    gin_last = last_node(gin)
    g_head = 0
    g_cond = 1
    g_succ = gin_last + 1
    g_last = g_succ + 1
    g.add_nodes_from([g_head, g_cond, g_succ, g_last, gin_head])
    g.add_edges_from([(g_head, g_cond),
                      (g_cond, gin_head, {"state": "True"}),
                      (g_cond, g_last, {"state": "False"}),
                      (gin_last, g_succ),
                      (g_succ, g_cond)])
    g.nodes[g_head]["data"] = [initializer]
    g.nodes[g_cond]["data"] = [condition]
    g.nodes[g_succ]["data"] = [successor]
    g.nodes[g_last]["data"] = []
    g = nx.compose(g, gin)
    return g


def embed_in_do_while_structure(gin, condition):
    g = nx.DiGraph()
    g_starting_nodes_len = 1
    gin = shift_node_labels(gin, g_starting_nodes_len)
    gin_head = head_node(gin)
    gin_last = last_node(gin)
    g_head = 0
    g_last = gin_last + g_starting_nodes_len
    g.add_nodes_from([g_head, g_last, gin_head])
    g.add_edges_from([(g_head, gin_head),
                      (gin_last, gin_head, {"state": "True"}),
                      (gin_last, g_last, {"state": "False"})])
    gin.nodes[gin_last]["data"] += [condition]
    g.nodes[g_head]["data"] = []
    g.nodes[g_last]["data"] = []
    g = nx.compose(g, gin)
    return g


def embed_in_while_structure(gin, condition):
    g = nx.DiGraph()
    g_starting_nodes_len = 1
    gin = shift_node_labels(gin, g_starting_nodes_len)
    gin_head = head_node(gin)
    gin_last = last_node(gin)
    g_head = 0
    g_last = gin_last + g_starting_nodes_len
    g.add_nodes_from([g_head, g_last, gin_head])
    g.add_edges_from([(gin_last, g_head),
                      (g_head, gin_head, {"state": "True"}),
                      (g_head, g_last, {"state": "False"})])
    g.nodes[g_head]["data"] = [condition]
    g.nodes[g_last]["data"] = []
    g = nx.compose(g, gin)
    return g


def embed_in_if_else_structure(gin_true, gin_false, condition):
    g = nx.DiGraph()
    g_starting_nodes_len = 1
    gin_true = shift_node_labels(gin_true, g_starting_nodes_len)
    gin_false = shift_node_labels(gin_false, len(gin_true) + g_starting_nodes_len)

    gin_true_head = head_node(gin_true)
    gin_true_last = last_node(gin_true)
    gin_false_head = last_node(gin_false)
    gin_false_last = last_node(gin_false)

    g_head = 0
    g_last = gin_false_last + g_starting_nodes_len

    g.add_nodes_from([g_head, g_last, gin_true_head, gin_false_head])
    g.add_edges_from([(g_head, gin_false_head, {"state": "False"}),
                      (g_head, gin_true_head, {"state": "True"}),
                      (gin_true_last, g_last),
                      (gin_false_last, g_last)])

    g.nodes[g_head]["data"] = [condition]
    g.nodes[g_last]["data"] = []
    g = nx.compose(g, gin_true)
    g = nx.compose(g, gin_false)
    return g


# todo: if the node before condition
def embed_in_if_structure(gin, condition) -> nx.DiGraph:
    g = nx.DiGraph()
    g_starting_nodes_len = 1
    gin = shift_node_labels(gin, g_starting_nodes_len)

    gin_head = head_node(gin)
    gin_last = last_node(gin)

    g_head = 0
    g_last = gin_last + g_starting_nodes_len

    g.add_nodes_from([g_head, g_last, gin_head])
    g.add_edges_from([(g_head, g_last, {"state": "False"}),
                      (g_head, gin_head, {"state": "True"}),
                      (gin_last, g_last)])

    g.nodes[g_head]["data"] = [condition]
    g.nodes[g_last]["data"] = []
    g = nx.compose(g, gin)
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
