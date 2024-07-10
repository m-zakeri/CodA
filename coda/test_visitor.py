import argparse

from antlr4 import FileStream, CommonTokenStream

from coda.antlr_gen.cpp_parser.CPP14_v2Lexer import CPP14_v2Lexer
from coda.antlr_gen.cpp_parser.CPP14_v2Parser import CPP14_v2Parser
from coda.analysis.cfg.cfg_extractor_visitor import CFGExtractorVisitor
from coda.graph.visual import draw_CFG


def main(args):
    file_name = f"../test_source/{args.file}"
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
    #cfg_extractor = CFGExtractorVisitor(token_stream)
    cfg_extractor = CFGExtractorVisitor(parse_tree)
    # Step 7: extract the cfg by visiting the parse_tree
    cfg_extractor.visit(parse_tree)
    funcs = cfg_extractor.functions
    for i, g in enumerate(funcs.values()):
        draw_CFG(g, f"../test_output/{args.file}{i}", token_stream)
    # pps = {extract_exact_text(token_stream, sig): {"nodes": list(cfg.nodes.data()), "edges": list(cfg.edges.data())} for sig, cfg in funcs.items()}
    # from pprint import pprint as print
    # print(pps)


if __name__ == '__main__':
    arg_parser = argparse.ArgumentParser()
    arg_parser.add_argument(
        '-n', '--file',
        help='Input source', default="if.cpp")
    args = arg_parser.parse_args()
    main(args)
