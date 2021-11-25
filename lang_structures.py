import networkx as nx

from gen.CPP14_v2Parser import CPP14_v2Parser
from graph_utils import (shift_node_labels,
                         head_node, last_node,
                         split_on_break, split_on_continue, split_on_return,
                         compose, reorder_node_labels)
from rule_utils import is_break


def embed_in_for_structure(gin, initializer, condition, successor):
    g = nx.DiGraph()
    g_head, g_cond = 0, 1
    g_starting_nodes_len = 2
    gin = shift_node_labels(gin, g_starting_nodes_len)
    gin_head = head_node(gin)
    gin_last = last_node(gin)
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
    g = split_on_continue(g, g_cond)
    g = split_on_break(g)
    return g


def embed_in_do_while_structure(gin, condition):
    g = nx.DiGraph()
    g_head = 0
    g_starting_nodes_len = 1
    gin = shift_node_labels(gin, g_starting_nodes_len)
    gin_head = head_node(gin)
    gin_last = last_node(gin)
    g_last = gin_last + 1
    g.add_nodes_from([g_head, g_last, gin_head])
    g.add_edges_from([(g_head, gin_head),
                      (gin_last, gin_head, {"state": "True"}),
                      (gin_last, g_last, {"state": "False"})])
    gin.nodes[gin_last]["data"] += [condition]
    g.nodes[g_head]["data"] = []
    g.nodes[g_last]["data"] = []
    g = compose(g, gin)
    g = split_on_continue(g, gin_last)
    g = split_on_break(g)
    return g


def embed_in_while_structure(gin, condition):
    g = nx.DiGraph()
    g_head, g_cond = 0, 1
    g_starting_nodes_len = 2
    gin = shift_node_labels(gin, g_starting_nodes_len)
    gin_head = head_node(gin)
    gin_last = last_node(gin)
    g_last = gin_last + 1
    g.add_edges_from([(g_head, g_cond),
                      (g_cond, gin_head, {"state": "True"}),
                      (g_cond, g_last, {"state": "False"}),
                      (gin_last, g_cond)])
    g.nodes[g_head]["data"] = []
    g.nodes[g_cond]["data"] = [condition]
    g.nodes[g_last]["data"] = []
    g = compose(g, gin)
    g = split_on_continue(g, g_cond)
    g = split_on_break(g)
    return g


def embed_in_if_else_structure(gin_true, gin_false, condition):
    g = nx.DiGraph()
    g_head = 0
    g_starting_nodes_len = 1
    gin_true = shift_node_labels(gin_true, g_starting_nodes_len)
    gin_false = shift_node_labels(gin_false, len(gin_true) + g_starting_nodes_len)

    gin_true_head = head_node(gin_true)
    gin_true_last = last_node(gin_true)
    gin_false_head = last_node(gin_false)
    gin_false_last = last_node(gin_false)

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
    g_head = 0
    g_starting_nodes_len = 1
    gin = shift_node_labels(gin, g_starting_nodes_len)

    gin_head = head_node(gin)
    gin_last = last_node(gin)

    g_last = gin_last + g_starting_nodes_len

    g.add_edges_from([(g_head, g_last, {"state": "False"}),
                      (g_head, gin_head, {"state": "True"}),
                      (gin_last, g_last)])

    g.nodes[g_head]["data"] = [condition]
    g.nodes[g_last]["data"] = []
    g = compose(g, gin)
    return g


def embed_in_switch_structure(gin: nx.DiGraph, condition):
    g = nx.DiGraph()
    g_head = 0
    g_starting_nodes_len = 1
    sub_graphs, cases = extract_case_sub_graphs(gin)
    lengths = [len(h) for h in sub_graphs]
    g_last = sum(lengths) + 1
    hs = [shift_node_labels(sub_graphs[i], sum(lengths[:i]) + g_starting_nodes_len) for i in range(len(sub_graphs))]
    g.add_edges_from([(g_head, head_node(h), {"state": case.getText()}) for h, case in zip(hs, cases)])

    with_breaks, trails = partition(lambda h: any(is_break(ctx) for ctx in h.nodes[last_node(h)]["data"]), hs[:-1])
    with_breaks.append(hs[-1])
    g.add_edges_from([(last_node(h), g_last) for h in with_breaks])
    g.add_edges_from([(last_node(h), head_node(hs[hs.index(h) + 1])) for h in trails])

    g.nodes[g_head]["data"] = [condition]
    g.nodes[g_last]["data"] = []
    g = compose(g, *hs)
    g = split_on_break(g)
    return g


def partition(predicate, iterator):
    yes, no = [], []
    for e in iterator:
        if predicate(e):
            yes.append(e)
        else:
            no.append(e)
    return yes, no


def case_indices(gin):
    return zip(*[(l, d[0]) for l, d in gin.nodes(data="data") if
                 d and (isinstance(d[0], CPP14_v2Parser.ConstantexpressionContext)
                        or d[0].getText() == "default")])


def extract_case_sub_graphs(gin):
    indices, cases = case_indices(gin)
    case_ranges = pair_case_indices(indices, last_node(gin))
    sub_graphs = [reorder_node_labels(gin.subgraph(range(f, t))) for f, t in case_ranges]
    return sub_graphs, cases


def pair_case_indices(iterator, ending):
    start_indices = map(lambda x: x + 1, iterator)
    end_indices = list(iterator)
    end_indices = end_indices[1:]
    end_indices.append(ending + 1)
    return list(zip(start_indices, end_indices))


def embed_in_function_structure(gin):
    g = gin.copy()
    g_last = last_node(gin) + 1
    g.add_node(g_last, data=[])
    g.add_edge(last_node(gin), g_last)
    return split_on_return(g)
