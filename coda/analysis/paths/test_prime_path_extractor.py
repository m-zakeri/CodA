import pytest
from io import StringIO
from coda.analysis.paths.prime_path_extractor import ControlFlowGraph

def test_control_flow_graph_init():
    graph_file_content = """1 2
2 3
3 4
4 5
init: 1
final: 5"""
    graph_file = StringIO(graph_file_content)
    cfg = ControlFlowGraph(graph_file)
    
    assert cfg.nodes == {1, 2, 3, 4, 5}
    assert cfg.edges == {1: [2], 2: [3], 3: [4], 4: [5]}
    assert cfg.inits == {1}
    assert cfg.finals == {5}

def test_reach_head():
    graph_file_content = """1 2
2 3
3 4
4 5
init: 1
final: 5"""
    graph_file = StringIO(graph_file_content)
    cfg = ControlFlowGraph(graph_file)
    
    assert cfg.reachHead([1, 2, 3]) == True
    assert cfg.reachHead([2, 3, 4]) == False

def test_reach_end():
    graph_file_content = """1 2
2 3
3 4
4 5
init: 1
final: 5"""
    graph_file = StringIO(graph_file_content)
    cfg = ControlFlowGraph(graph_file)
    
    assert cfg.reachEnd([1, 2, 3, 4, 5]) == True
    assert cfg.reachEnd([1, 2, 3]) == False

def test_extend():
    graph_file_content = """1 2
2 3
3 4
4 5
init: 1
final: 5"""
    graph_file = StringIO(graph_file_content)
    cfg = ControlFlowGraph(graph_file)
    
    assert cfg.extend([1, 2, 3]) == [[1, 2, 3, 4]]
    assert cfg.extend([1, 2, 3, 4, 5]) == []

def test_compute_prime_paths():
    graph_file_content = """1 2
2 3
3 4
4 5
init: 1
final: 5"""
    graph_file = StringIO(graph_file_content)
    cfg = ControlFlowGraph(graph_file)
    
    cfg.computePrimePaths()
    expected_prime_paths = [
        [1, 2, 3, 4, 5],
        [2, 3, 4, 5],
        [3, 4, 5],
        [4, 5]
    ]
    assert cfg.primePaths == expected_prime_paths
