# in the name of allah

from gen.CFGListener_v2 import CFGInstListener
from gen.CPP14_v2Lexer import CPP14_v2Lexer
from gen.CPP14_v2Parser import CPP14_v2Parser
from graph import Graph
from antlr4 import *
from pathlib import Path
import os
# input_path=input("please enter the source code path:\n")
input_path = 'test_source/4.cpp'
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

function_prime_paths = {}
function_logs = {}
i = 1
while True:
    try:
        cfg_file = open(cfg_path + '/' + str(i) + '.txt', 'r')
        cfg = Graph(cfg_file)
        cfg.computePrimePaths()
        for j in range(len(cfg.primePaths)):
            print( j+1 , cfg.primePaths[j])

        function_prime_paths[i] = cfg.primePaths
        i += 1
    except Exception as e:
        break
print(function_prime_paths)
#input("please enter log file dir:")
