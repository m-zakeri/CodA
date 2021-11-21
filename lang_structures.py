import networkx as nx

from graph_utils import shift_node_labels, head_node, last_node, compose


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
    g.add_edges_from([(g_head, g_cond),
                      (g_cond, gin_head, {"state": "True"}),
                      (g_cond, g_last, {"state": "False"}),
                      (gin_last, g_succ),
                      (g_succ, g_cond)])
    g.nodes[g_head]["data"] = [initializer]
    g.nodes[g_cond]["data"] = [condition]
    g.nodes[g_succ]["data"] = [successor]
    g.nodes[g_last]["data"] = []
    g = compose(g, gin)
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
    g = compose(g, gin)
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
    g = compose(g, gin)
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

    g.add_edges_from([(g_head, gin_false_head, {"state": "False"}),
                      (g_head, gin_true_head, {"state": "True"}),
                      (gin_true_last, g_last),
                      (gin_false_last, g_last)])

    g.nodes[g_head]["data"] = [condition]
    g.nodes[g_last]["data"] = []
    g = compose(g, gin_true, gin_false)
    return g


def embed_in_if_structure(gin, condition) -> nx.DiGraph:
    g = nx.DiGraph()
    g_starting_nodes_len = 1
    gin = shift_node_labels(gin, g_starting_nodes_len)

    gin_head = head_node(gin)
    gin_last = last_node(gin)

    g_head = 0
    g_last = gin_last + g_starting_nodes_len

    g.add_edges_from([(g_head, g_last, {"state": "False"}),
                      (g_head, gin_head, {"state": "True"}),
                      (gin_last, g_last)])

    g.nodes[g_head]["data"] = [condition]
    g.nodes[g_last]["data"] = []
    g = compose(g, gin)
    return g
