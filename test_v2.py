# in the name of allah

from gen.CFGListener_v2 import CFGInstListener
from gen.CPP14_v2Lexer import CPP14_v2Lexer
from gen.CPP14_v2Parser import CPP14_v2Parser

from antlr4 import *
from pathlib import Path
import os
# input_path=input("please write the source code path:\n")
input_path = 'test_source/student_projects/memory game.cpp'
f = open(input_path, 'r')
name = Path(f.name).stem
cfg_path = 'CFGS/v2/' + name
instrument_path = 'Instrument/v2/' + name
try:
    os.mkdir(cfg_path)
except:
    pass
try:
    os.mkdir(instrument_path)
except:
    pass

source = f.read()

stream = InputStream(source)

lexer = CPP14_v2Lexer(stream)

token_stream = CommonTokenStream(lexer)

parser = CPP14_v2Parser(token_stream)

pars_tree = parser.translationunit()
lexer.reset()
number_of_tokens = len(lexer.getAllTokens())
cfg_listener = CFGInstListener(token_stream , number_of_tokens , name)
walker = ParseTreeWalker()

walker.walk(cfg_listener, pars_tree)