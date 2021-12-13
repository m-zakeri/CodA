from functools import reduce

import networkx as nx

from src.antlr.rule_utils import is_break, is_return, is_continue, is_throw


def split_on_continue(gin: nx.DiGraph, continue_return) -> nx.DiGraph:
    return direct_node_to_if(gin, continue_return, is_continue)


def split_on_break(gin: nx.DiGraph) -> nx.DiGraph:
    return direct_node_to_if(gin, last_node(gin), is_break)


def split_on_throw(gin: nx.DiGraph, throw_return) -> nx.DiGraph:
    return direct_node_to_if(gin, throw_return, is_throw)


def direct_node_to_if(gin: nx.DiGraph, direction_reference, predicate) -> nx.DiGraph:
    g = gin.copy()
    for label, data in gin.nodes(data="data"):
        for ctx in data:
            if predicate(ctx):
                g.remove_edges_from([(label, adj) for adj in gin.adj[label]])
                g.add_edge(label, direction_reference)
                g.nodes[label]["data"] = data[:data.index(ctx)]
                break
    return g


def split_on_return(gin: nx.DiGraph) -> nx.DiGraph:
    g = gin.copy()
    for label, data in gin.nodes(data="data"):
        for ctx in data:
            if is_return(ctx):
                g.remove_edges_from([(label, adj) for adj in gin.adj[label]])
                g.add_edge(label, last_node(gin))
                d = data[:data.index(ctx)]
                if ctx.expression():
                    d += [ctx.expression()]
                g.nodes[label]["data"] = d
                break
    return g


def solve_null_nodes(gin: nx.DiGraph) -> nx.DiGraph:
    g = remove_null_nodes(gin)
    g = reorder_node_labels(g)
    return g


def remove_null_nodes(gin: nx.DiGraph) -> nx.DiGraph:
    g = gin.copy()
    for label, ns in gin.adj.items():
        for n in ns:
            if is_node_null(gin, n) and n != last_node(gin):
                g = shrink_path(g, label, n)
    return g


def shrink_path(gin: nx.DiGraph, from_node: int, to_node: int) -> nx.DiGraph:
    g = gin.copy()
    edge_attrs = g.edges[(from_node, to_node)]
    g.add_edges_from([(from_node, grand_child, edge_attrs) for grand_child in g.adj[to_node]])
    g.remove_edge(from_node, to_node)
    if is_node_unreachable(g, to_node):
        g.remove_node(to_node)
    return g


def reorder_node_labels(gin: nx.DiGraph) -> nx.DiGraph:
    return nx.relabel_nodes(gin, {old: new for new, old in enumerate(sorted(gin.nodes))})


def shift_node_labels(gin: nx.DiGraph, n: int) -> nx.DiGraph:
    return nx.relabel_nodes(gin, {i: i + n for i in gin.nodes})


def is_node_unreachable(gin: nx.DiGraph, n: int) -> bool: return gin.in_degree[n] == 0


def is_node_null(gin: nx.DiGraph, n: int) -> bool: return gin.nodes[n]["data"] == []


def compose(*graphs) -> nx.DiGraph: return reduce(lambda acc, x: nx.compose(acc, x), graphs)


def head_node(gin: nx.DiGraph) -> int: return min(gin.nodes)


def last_node(gin: nx.DiGraph) -> int: return max(gin.nodes)


def build_single_node_graph(data=None):
    g = nx.DiGraph()
    g.add_node(0, data=[data] if data else [])
    return g


def concat_graphs(gin1: nx.DiGraph, gin2: nx.DiGraph):
    gin2 = shift_node_labels(gin2, len(gin1) - 1)

    gin1_last = last_node(gin1)
    gin2_head = head_node(gin2)
    data = gin1.nodes[gin1_last]["data"] + gin2.nodes[gin2_head]["data"]

    g = compose(gin1, gin2)
    g.nodes[gin1_last]["data"] = data
    return g


def build_isolated_node_graph(to_isolate, body):
    g = nx.DiGraph()
    g.add_nodes_from([(0, {"data": []}),
                      (1, {"data": [to_isolate]}),
                      (2, {"data": [body]})])
    g.add_edges_from([(0, 1), (1, 2)])
    return g
