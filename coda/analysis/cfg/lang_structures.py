import networkx as nx

from coda.antlr_gen.cpp_parser.CPP14_v2Parser import CPP14_v2Parser
from coda.antlr_gen.rule_utils import is_break
from coda.graph.utils import (
    shift_node_labels,
    head_node, last_node,
    split_on_break,
    split_on_continue,
    split_on_return,
    split_on_throw,
    compose,
    reorder_node_labels,
    solve_null_nodes
)


def embed_in_for_structure(gin, initializer, condition, successor):
    g, g_cond, g_head = build_for_initial_graph(condition, initializer)

    gin = shift_node_labels(gin, len(g))
    gin_head, gin_last = get_graph_label_range(gin)
    g_succ = gin_last + 1
    g_last = g_succ + 1
    g.add_edges_from([(g_head, g_cond),
                      (g_cond, gin_head, {"state": "True"}),
                      (g_cond, g_last, {"state": "False"}),
                      (gin_last, g_succ),
                      (g_succ, g_cond)])

    g.nodes[g_succ]["data"] = [successor]
    g.nodes[g_last]["data"] = []
    g = compose(g, gin)
    g = split_on_continue(g, g_succ)
    g = split_on_break(g)
    return g


def build_for_initial_graph(condition, initializer):
    g = nx.DiGraph()
    g_head, g_cond = 0, 1
    g.add_nodes_from([(g_head, {"data": [initializer]}),
                      (g_cond, {"data": [condition]})])
    return g, g_cond, g_head


def embed_in_do_while_structure(gin, condition):
    g, g_head = build_simple_initial_graph()
    gin = shift_node_labels(gin, len(g))
    gin_head, gin_last = get_graph_label_range(gin)
    g_cond = gin_last + 1
    g_last = g_cond + 1

    g.add_edges_from([(g_head, gin_head),
                      (gin_last, g_cond),
                      (g_cond, gin_head, {"state": "True"}),
                      (g_cond, g_last, {"state": "False"})])

    g.nodes[g_cond]["data"] = [condition]
    g.nodes[g_last]["data"] = []
    g = compose(g, gin)
    g = split_on_continue(g, g_cond)
    g = split_on_break(g)
    return g


def build_simple_initial_graph():
    g = nx.DiGraph()
    g_head = 0
    g.add_node(g_head, data=[])
    return g, g_head


def embed_in_while_structure(gin, condition):
    g, g_cond, g_head = build_initial_while_graph(condition)

    gin = shift_node_labels(gin, len(g))
    gin_head, gin_last = get_graph_label_range(gin)
    g_last = gin_last + 1

    g.add_edges_from([(g_head, g_cond),
                      (g_cond, gin_head, {"state": "True"}),
                      (g_cond, g_last, {"state": "False"}),
                      (gin_last, g_cond)])

    g.nodes[g_last]["data"] = []
    g = compose(g, gin)
    g = split_on_continue(g, g_cond)
    g = split_on_break(g)
    return g


def build_initial_while_graph(condition):
    g = nx.DiGraph()
    g_head, g_cond = 0, 1
    g.add_nodes_from([(g_head, {"data": []}),
                      (g_cond, {"data": [condition]})])
    return g, g_cond, g_head


def embed_in_if_else_structure(gin_true, gin_false, condition):
    g, g_head = build_initial_conditional_graph(condition)
    # shift both then and else parts to rearrange the basic block's label numbers
    gin_false, gin_true = shift_if_else_graphs(len(g), gin_true, gin_false)

    # retrieve then and else part head and ending node labels
    gin_true_head, gin_true_last = get_graph_label_range(gin_true)
    gin_false_head, gin_false_last = get_graph_label_range(gin_false)

    # calculate the last node label of the final if-else structure graph
    g_last = gin_false_last + len(g)

    # set if-else structure nodes, as well as the decision flows
    g.add_edges_from([(g_head, gin_false_head, {"state": "False"}),
                      (g_head, gin_true_head, {"state": "True"}),
                      (gin_true_last, g_last),
                      (gin_false_last, g_last)])
    # set the junction basic block as an empty block
    g.nodes[g_last]["data"] = []

    # compose then part, else part, and the new graph into a graph as the final result
    g = compose(g, gin_true, gin_false)
    return g


def get_graph_label_range(gin): return head_node(gin), last_node(gin)


def build_initial_conditional_graph(condition):
    g = nx.DiGraph()
    g_head = 0
    g.add_node(g_head, data=[condition])
    return g, g_head


def shift_if_else_graphs(n, gin_true, gin_false):
    gin_true = shift_node_labels(gin_true, n)
    gin_false = shift_node_labels(gin_false, len(gin_true) + n)
    return gin_false, gin_true


def embed_in_if_structure(gin, condition) -> nx.DiGraph:
    g, g_head = build_initial_conditional_graph(condition)
    gin = shift_node_labels(gin, len(g))

    gin_head, gin_last = get_graph_label_range(gin)

    g_last = gin_last + len(g)

    g.add_edges_from([(g_head, g_last, {"state": "False"}),
                      (g_head, gin_head, {"state": "True"}),
                      (gin_last, g_last)])

    g.nodes[g_last]["data"] = []
    g = compose(g, gin)
    return g


def embed_in_switch_structure(gin: nx.DiGraph, condition):
    g, g_head = build_initial_conditional_graph(condition)
    sub_graphs, cases = extract_case_sub_graphs(gin)
    g_last = sum([len(h) for h in sub_graphs]) + 1

    hs = shift_case_graphs(sub_graphs, len(g))
    g.add_edges_from([(g_head, head_node(h), {"state": case.getText()}) for h, case in zip(hs, cases)])

    with_breaks, trails = partition_graphs_on_break(hs)
    g.add_edges_from([(last_node(h), g_last) for h in with_breaks])
    g.add_edges_from([(last_node(h), head_node(hs[hs.index(h) + 1])) for h in trails])

    g.nodes[g_last]["data"] = []
    g = compose(g, *hs)
    g = split_on_break(g)
    return g


def shift_case_graphs(sub_graphs, n):
    lengths = [len(h) for h in sub_graphs]
    hs = [shift_node_labels(sub_graphs[i], sum(lengths[:i]) + n) for i in range(len(sub_graphs))]
    return hs


def partition_graphs_on_break(gs):
    contains_break = lambda g: any(is_break(ctx) for ctx in g.nodes[last_node(g)]["data"])
    with_breaks, trails = partition(contains_break, gs[:-1])
    with_breaks.append(gs[-1])
    return with_breaks, trails


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
    g = split_on_return(g)
    return solve_null_nodes(g)


def embed_in_try_catch_structure(g_body, g_handler_seq):
    g = nx.DiGraph()
    g_handler_seq = shift_node_labels(g_handler_seq, len(g_body))
    g_handler_seq_head, g_handler_seq_last = get_graph_label_range(g_handler_seq)
    g_body_last = last_node(g_body)

    g_last = g_handler_seq_last + 1
    g.add_edges_from([(g_body_last, g_last),
                      (g_handler_seq_last, g_last)])
    g = compose(g, g_handler_seq, g_body)
    g.nodes[g_last]["data"] = []

    g = split_on_throw(g, g_handler_seq_head)
    return g
