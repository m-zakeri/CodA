# in the name of allah

from gen.CFGListener import CFGListener
from gen.CPP14Lexer import CPP14Lexer
from gen.CPP14Parser import CPP14Parser

from antlr4 import *

input_path=input("please write the source code path:\n")
f=open(input_path,'r')
source=f.read()

stream = InputStream(source)

lexer = CPP14Lexer(stream)

token_stream = CommonTokenStream(lexer)

parser = CPP14Parser(token_stream)

pars_tree = parser.translationunit()

cfg_listener = CFGListener()
walker = ParseTreeWalker()

walker.walk(cfg_listener,pars_tree)