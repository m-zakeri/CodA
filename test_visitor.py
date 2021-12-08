import argparse

from antlr4 import *

from cfg_extractor_visitor import CFGExtractorVisitor
from gen.CPP14_v2Lexer import CPP14_v2Lexer
from gen.CPP14_v2Parser import CPP14_v2Parser
from visual import draw_CFG
import networkx as nx

def main(args):
    file_name = f"test_source/{args.file}"
    # Step 1: load the input source into a stream
    stream = FileStream(file_name, encoding="utf8")
    # Step 2: create an instance of CPP14_v2Lexer
    lexer = CPP14_v2Lexer(stream)
    # Step 3: tokenize the input source into a list of tokens
    token_stream = CommonTokenStream(lexer)
    # Step 4: create an instance of CPP14_v2Parser
    parser = CPP14_v2Parser(token_stream)
    # step 5: create a parse tree
    parse_tree = parser.translationunit()
    # Step 6: create an instance of CFGExtractorVisitor
    cfg_extractor = CFGExtractorVisitor(token_stream)
    # Step 7: extract the cfg by visiting the parse_tree
    cfg = cfg_extractor.visit(parse_tree)
    cfg: nx.DiGraph
    nodes = list(cfg.nodes.data())
    edges = list(cfg.edges.data())
    print(nodes)
    print(edges)
    # draw_CFG(cfg, args.file, token_stream)


if __name__ == '__main__':
    arg_parser = argparse.ArgumentParser()
    arg_parser.add_argument(
        '-n', '--file',
        help='Input source', default="sample.cpp")
    args = arg_parser.parse_args()
    main(args)
