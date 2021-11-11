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
    g.add_node(0, data=data)
    return g


def concat_graphs(gin1, gin2):
    gin2 = shift_node_labels(gin2, len(gin1))
    g: nx.DiGraph = nx.compose(gin1, gin2)
    g.add_edge(last_node(gin1), head_node(gin2))
    return g


def embed_in_if_else_structure(gin_true, gin_false):
    g = nx.DiGraph()
    gin_true = shift_node_labels(gin_true, 2)
    gin_false = shift_node_labels(gin_false, len(gin_true) + 2)

    gin_true_start = head_node(gin_true)
    gin_true_end = last_node(gin_true)
    gin_false_start = last_node(gin_false)
    gin_false_end = last_node(gin_false)

    g_start = 0
    g_cond = 1
    g_end = gin_false_end + 1

    g.add_nodes_from([g_start, g_cond, g_end, gin_true_start, gin_false_start])
    g.add_edges_from([(g_start, g_cond),
                      (g_cond, gin_false_start, {"state": "False"}),
                      (g_cond, gin_true_start, {"state": "True"}),
                      (gin_true_end, g_end),
                      (gin_false_end, g_end)])
    g = nx.compose(g, gin_true)
    g = nx.compose(g, gin_false)
    return g


def embed_in_if_structure(gin) -> nx.DiGraph:
    g = nx.DiGraph()
    gin = shift_node_labels(gin, 2)

    gin_start = head_node(gin)
    gin_end = last_node(gin)

    g_start = 0
    g_cond = 1
    g_end = gin_end + 1

    g.add_nodes_from([g_start, g_cond, g_end, gin_start])
    g.add_edges_from([(g_start, g_cond),
                      (g_cond, g_end, {"state": "False"}),
                      (g_cond, gin_start, {"state": "True"}),
                      (gin_end, g_end)])
    g = nx.compose(g, gin)
    # x = nx.contracted_nodes(x, "cond", "start", self_loops=False)
    # x = nx.contracted_nodes(x, "end", "temp_end", self_loops=False)
    # x = nx.relabel_nodes(x, {"temp_start": "start"})
    return g


def draw_CFG(graph):
    top_down_pos = graphviz_layout(graph, prog="dot")

    nx.draw(graph,
            pos=top_down_pos,
            with_labels=True,
            font_weight="bold",
            node_size=800,
            font_color="black",
            alpha=0.9,
            edgecolors="tab:gray")

    edge_labels = {(i[0], i[1]): i[2]["state"] for i in graph.edges.data() if i[2].get("state")}

    nx.draw_networkx_edge_labels(graph,
                                 pos=top_down_pos,
                                 edge_labels=edge_labels,
                                 font_weight="bold")

    plt.show()
