from antlr4 import *

from cfg_extractor_visitor import CFGExtractorVisitor
from gen.CPP14_v2Lexer import CPP14_v2Lexer
from gen.CPP14_v2Parser import CPP14_v2Parser
from graph_utils import draw_CFG

file_name = "if-else"
file_path = f'test_source/{file_name}.cpp'
with open(file_path, 'r') as f:
    source = f.read()

stream = InputStream(source)
lexer = CPP14_v2Lexer(stream)
token_stream = CommonTokenStream(lexer)
parser = CPP14_v2Parser(token_stream)
pars_tree = parser.translationunit()
visitor = CFGExtractorVisitor(token_stream)
g = visitor.visit(pars_tree)
draw_CFG(g)
