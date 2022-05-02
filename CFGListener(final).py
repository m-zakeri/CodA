# in the name of allah

from antlr4 import *
from antlr4 import TokenStreamRewriter
from .CPP14_v2Listener import CPP14_v2Listener
from .CPP14_v2Parser import CPP14_v2Parser
from .CPP14_v2Lexer import CPP14_v2Lexer as lexer
import graphviz as gv

import networkx as nx
import pylab as plt

import matplotlib.pyplot as plt
import json
SWITCH_FOR = {
    "for_while" : 0,
    "range_for" : 1,
    "switch" : 2
}
class CFGInstListener(CPP14_v2Listener):

    def addNode(self):
        try:
            if not self.is_catch:
                self.try_stack[-1].add((self.block_number , 'exception'))
        except:
            pass

        temp = []
        temp = self.block_dict[self.domain_name]["Nodes"]
        if(len(temp) != 0):
            if(temp[-1][0]==self.block_number):
                return

        self.block_dict[self.domain_name]["Nodes"].append((self.block_number, self.block_start, self.block_stop))

    def addJunctionEdges(self):
        for source_node,Type  in self.select_junction_stack[-1]:
            dest_node = self.block_number
            self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node,Type))
            self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addJunctionEdges_for(self):
        for source_node,Type  in self.select_junction_stack[-1]:
            dest_node = self.block_number
            self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node,'Flow'))
            self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addDecisionEdge(self):
        source_node,Type = self.select_decision_stack.pop()
        dest_node = self.block_number
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node,Type))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addJunc(self , Type = 'flow'):
        self.select_junction_stack[-1].append((self.block_number , Type))

    def addDecision(self , Type = 'flow'):
        self.select_decision_stack.append((self.block_number , Type))

    def addIterateJunctionEdges(self):
        for source_node,Type in self.iterate_junction_stack[-1]:
            dest_node = self.block_number
            self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node,Type))
            self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')
    def addIterateJunctionEdges_dwhile(self ):
        for source_node,Type in self.iterate_junction_stack[-1]:
            dest_node = self.block_number
            self.block_dict[self.domain_name]["Edges"].append((dest_node, source_node+1,'flow'))
            self.CFG_file.write(str(dest_node) + ' ' + str(source_node+1) + '\n')

    def addIterateEdge(self):
        source_node = self.block_number
        dest_node,Type = self.iterate_stack[-1]
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node,Type))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addIterateEdge_dwhile(self):
        source_node = self.block_number
        dest_node,Type = self.iterate_stack[-1]
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node+1,Type))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node+1) + '\n')



    def addInitEdge(self , Type = 'flow'):
        source_node = self.block_number
        dest_node = source_node + 1
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node, Type))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addDoWhileInitEdge(self):
        source_node = self.block_number
        dest_node = source_node + 1
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node , 'flow'))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addIterateJunc(self , Type = 'flow'):
        self.iterate_junction_stack[-1].append((self.block_number , Type))

    def addIterateJunc1(self , Type = 'flow'):
        self.iterate_junction_stack[-1].append((self.block_number +1  , Type))

    def addIterate(self , Type = 'flow'):
        self.iterate_stack.append((self.block_number  , Type))

    def addSwitchEdge(self):
        source_node,Type = self.switch_stack[-1]
        dest_node = self.block_number
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node,Type))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')
    
    def addSwitchJunctionEdges(self):
        for source_node,Type in self.switch_junction_stack[-1]:
            dest_node = self.block_number
            self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node,Type))
            self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')


    def add_throwedges(self):
        for source_node,Type in self.throw_stack[-1]:
            dest_node = self.block_number
            self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node,Type))
            self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def add_throw(self , Type = 'Exception'):
        self.throw_stack.append((self.block_number, Type))


    def addSwitch(self , Type = 'switch'):
        self.switch_stack.append((self.block_number , Type))
    def addSwitchJunc(self , Type = 'flow'):
        self.switch_junction_stack[-1].append((self.block_number , Type))

    def addGotoEdge(self , label):
        source_node = self.block_number
        dest_node = self.label_dict[label]
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node , 'goto'))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def insertAfter(self, ctx):
        new_code = '\n' + self.logLine() + ';\n'
        self.token_stream_rewriter.insertAfter(ctx.start.tokenIndex, new_code)

    def logLine(self):
        return 'logFile << "' + str(self.domain_name) + ' ' + str(self.block_number) + '" << std::endl'

    def addTryJunc(self , Type = 'flow'):
        self.try_junction_stack[-1].append((self.block_number,Type))

    def addTryEdges(self):
        for source_node,Type in self.try_stack[-1]:
            dest_node = self.block_number
            self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node,Type))
            self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addTryJuncEdges(self):
        for source_node,Type in self.try_junction_stack[-1]:
            dest_node = self.block_number
            self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node,Type))
            self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def __init__(self, common_token_stream: CommonTokenStream, number_of_tokens , directory_name):
        """
        :param common_token_stream:
        """
        self.cfg_path = 'CFGS/' + directory_name + '/'
        self.instrument_path = 'Instrument/' + directory_name + '/'
        self.block_dict = {}
        self.block_number = 0

        self.block_start = 0
        self.block_stop = 0
        self.domain_name = 0
        self.function_dict = {}
        self.select_junction_stack = []
        self.select_decision_stack = []
        self.iterate_junction_stack = []
        self.iterate_stack = []
        self.switch_junction_stack = []
        self.temp=[]
        self.switch_stack = []
        self.switch_for_stack = []
        self.has_jump_stack = []
        self.is_for = []
        self.is_while = []
        self.is_doWhile = []
        self.has_default_stack = []
        self.has_case_stack = []
        self.try_stack = []
        self.try_junction_stack = []
        self.is_catch = False
        self.throw_stack = []
        self.afterInsert = [''] * number_of_tokens
        self.initial_nodes = set()
        self.final_nodes = set()
        self.label_dict = {}
        self.goto_dict = {}

        # Move all the tokens in the source code in a buffer, token_stream_rewriter.
        if common_token_stream is not None:
            self.token_stream_rewriter = TokenStreamRewriter.TokenStreamRewriter(common_token_stream)
        else:
            raise TypeError('common_token_stream is None')
        # create graph
        self.CFG_graph = nx.Graph()

    def enterTranslationunit(self, ctx: CPP14_v2Parser.TranslationunitContext):
        """
        Creating and open a text file for logging the instrumentation result
        :param ctx:
        :return:
        """
        self.instrumented_source = open(self.instrument_path + 'instrumented_source.cpp', 'w')
        log_path = self.instrument_path + "log_file.txt"
        new_code = '\n//in the name of allah\n#include <fstream>\nstd::ofstream logFile("log_file.txt");\n\n'
        self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex, new_code)
        self.domain_name = 0

    #function
    def enterFunctiondefinition(self, ctx: CPP14_v2Parser.FunctiondefinitionContext):
        self.initial_nodes = set()
        self.final_nodes = set()
        temp = ctx.declarator().getText().replace('~', "destructor")
        function_name = ''.join(c for c in temp if c.isalnum())
        self.domain_name += 1
        self.function_dict[self.domain_name] = (function_name , ctx.start.line)
        self.block_dict[self.domain_name] = {
            "Nodes": [],
            "Edges": []
        }
        self.CFG_file = open(self.cfg_path + str(self.domain_name) + '.txt', 'w')


    def enterFunctionbody1(self, ctx:CPP14_v2Parser.Functionbody1Context): #normal function
        self.block_number = 1
        self.block_start = ctx.start.line
        self.has_jump_stack.append(False)
        self.insertAfter(ctx)
        self.initial_nodes.add(self.block_number)

    def enterFunctiontryblock(self, ctx:CPP14_v2Parser.FunctiontryblockContext): #try function
        self.block_number = 1
        self.block_start = ctx.start.line
        self.has_jump_stack.append(False)
        body = ctx.compoundstatement()
        self.insertAfter(body)
        self.initial_nodes.add(self.block_number)
        self.try_stack.append(set())
        self.try_junction_stack.append(list())

    def enterTryblock(self, ctx:CPP14_v2Parser.TryblockContext):
        self.is_catch = True
        self.block_stop = ctx.start.line
        self.addNode()
        self.addInitEdge()
        self.is_catch = True
        self.has_jump_stack.append(False)
        self.try_stack.append(set())
        self.try_junction_stack.append(list())
        self.block_number += 1
        self.block_start = ctx.start.line + 1
        body = ctx.compoundstatement()
        self.insertAfter(body)

    def exitCompoundstatement(self, ctx:CPP14_v2Parser.CompoundstatementContext):
        if isinstance(ctx.parentCtx , CPP14_v2Parser.TryblockContext):
            self.is_catch = True

            self.has_jump_stack.pop() + 1
            self.block_stop = ctx.stop.line
            self.addNode()
            self.addTryJunc()


        elif isinstance(ctx.parentCtx , CPP14_v2Parser.FunctiontryblockContext):
            self.is_catch = True

            self.block_stop = ctx.stop.line
            self.addNode()

    def enterHandler(self, ctx:CPP14_v2Parser.HandlerContext):
        self.is_catch = True
        self.block_number += 1
        self.block_start = ctx.start.line

        body = ctx.compoundstatement()
        self.insertAfter(body)
        self.addTryEdges()
        self.has_jump_stack.append(False)
    def exitHandler(self, ctx:CPP14_v2Parser.HandlerContext):
        self.block_stop = ctx.stop.line
        self.addNode()
        self.addTryJunc()

        self.has_jump_stack.pop()
    def exitTryblock(self, ctx:CPP14_v2Parser.TryblockContext):

        self.is_catch = True
        self.block_number += 1
        self.block_start = ctx.stop.line + 1
        self.addTryJuncEdges()
        self.try_junction_stack.pop()
        self.try_stack.pop()
        self.is_catch = True

        new_code = '\n' + self.logLine() + ';\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code
    def exitFunctiontryblock(self, ctx:CPP14_v2Parser.FunctiontryblockContext):

        self.is_catch = True
        self.try_stack.pop()
    #selection

    def enterSelectionstatement1(self, ctx:CPP14_v2Parser.Selectionstatement1Context): #if
        self.block_stop = ctx.start.line
        self.addNode()

        self.select_junction_stack.append(list())


        self.addDecision('True')

        self.addJunc('False')



    def enterStatement(self, ctx:CPP14_v2Parser.StatementContext):
        """
        DFS traversal of a statement subtree, rooted at ctx.
        If the statement is a branching condition insert a prob.
        :param ctx:
        :return:
        """
        #do-while and range-for
        #line 342(CPP14_v2Parser.Iterationstatement4Context)
        if isinstance(ctx.parentCtx,
                      (CPP14_v2Parser.Iterationstatement2Context)):
            # if there is a compound statement after the branchning condition:


            body = ctx.compoundstatement()
            if body != None:
                self.insertAfter(body)
            # if there is only one statement after the branchning condition then create a block.
            else:
                new_code = '{'
                new_code += '\n'+ self.logLine() +';\n'
                self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex, new_code)

        #one line while and for
        elif isinstance(ctx.parentCtx , CPP14_v2Parser.IterationstatementContext):
            self.block_number += 1
            self.block_start = ctx.start.line

            # if there is a compound statement after the branchning condition:
            body = ctx.compoundstatement()
            if body != None:
                self.insertAfter(body)
            # if there is only one statement after the branchning condition then create a block.
            else:
                new_code = '{'
                new_code += '\n' + self.logLine() + ';\n'
                self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex, new_code)
        elif isinstance(ctx.parentCtx,
                      (CPP14_v2Parser.Selectionstatement1Context , CPP14_v2Parser.Selectionstatement2Context)):

            self.block_number += 1


            self.addDecisionEdge()

            self.block_start  = ctx.start.line

            self.has_jump_stack.append(False)

            # if there is a compound statement after the branchning condition:
            body = ctx.compoundstatement()
            if body != None:
                self.insertAfter(body)
            # if there is only one statement after the branchning condition then create a block.
            else:
                new_code = '{'
                new_code += '\n' + self.logLine() + ';\n'
                self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex, new_code)

        elif isinstance(ctx.parentCtx,
                        CPP14_v2Parser.Selectionstatement3Context):
            if ctx.compoundstatement() == None:
                new_code = '{\n'
                self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex, new_code)

    def exitStatement(self, ctx: CPP14_v2Parser.StatementContext):
        if isinstance(ctx.parentCtx, CPP14_v2Parser.IterationstatementContext): #loop

            if self.is_for.pop():
                self.addInitEdge("flow")
                self.block_stop = ctx.stop.line
                self.addNode()
                self.block_number += 1
                self.block_start = ctx.stop.line
                self.block_stop = self.block_start
                self.addNode()
                self.addIterateEdge()
            if self.is_while.pop():
                self.addIterateEdge()
                self.block_stop = ctx.stop.line
                self.addNode()

            if self.is_doWhile.pop():

                self.block_stop = ctx.stop.line + 1
                self.addNode()
                self.addIterateEdge_dwhile()
                self.addIterateJunc("False")

            if ctx.compoundstatement() == None:
                new_code = '\n}'
                self.afterInsert[ctx.stop.tokenIndex] += new_code


        elif isinstance(ctx.parentCtx,
                        (CPP14_v2Parser.Selectionstatement1Context, CPP14_v2Parser.Selectionstatement2Context)): # if
            if (ctx.getText()[0:2] == "if"):
                self.block_number -= 1
                return
            self.block_stop = ctx.stop.line
            self.addNode()



            if not self.has_jump_stack.pop():
                self.addJunc()

            if ctx.compoundstatement() == None:
                new_code = '\n}'
                self.afterInsert[ctx.stop.tokenIndex] += new_code

        elif isinstance(ctx.parentCtx,
                        CPP14_v2Parser.Selectionstatement3Context): # switch
            if ctx.compoundstatement() == None:
                new_code = '\n}'
                self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitSelectionstatement1(self, ctx: CPP14_v2Parser.Selectionstatement1Context):  # if

        self.block_number += 1

        self.block_start = ctx.stop.line + 1

        self.addJunctionEdges()

        self.select_junction_stack.pop()

        new_code = '\n' + self.logLine() + ';\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code


    def enterSelectionstatement2(self, ctx:CPP14_v2Parser.Selectionstatement2Context): #if-else

        self.block_stop = ctx.start.line
        self.addNode()
        self.select_junction_stack.append(list())

        # decision stack first if part pop True then else part pop False
        self.addDecision('False')
        self.addDecision('True')
    def enterSelectionstatement3(self, ctx:CPP14_v2Parser.Selectionstatement3Context): #switch
        self.block_stop = ctx.start.line
        self.addNode()
        self.addSwitch()
        self.has_jump_stack.append(True)
        self.has_default_stack.append(False)
        self.has_case_stack.append(False)
        self.switch_for_stack.append(SWITCH_FOR["switch"])
        self.switch_junction_stack.append(list())

    def enterLabeledstatement1(self, ctx:CPP14_v2Parser.Labeledstatement1Context): #label
        try:
            if not self.has_jump_stack[-1]:
                self.addInitEdge()
                self.block_stop = ctx.start.line
                self.addNode()
        except:
            self.addInitEdge()
            self.block_stop = ctx.start.line
            self.addNode()
        self.block_number += 1
        self.block_start = ctx.start.line
        label = ctx.Identifier().getText()
        self.label_dict[label] = self.block_number
        try:
            for source_node in self.goto_dict[label]:
                self.block_dict[self.domain_name]["Edges"].append((source_node, self.block_number))
                self.CFG_file.write(str(source_node) + ' ' + str(self.block_number) + '\n')
        except:
            pass
        index = ctx.statement().start.tokenIndex
        new_code = self.logLine() + ';\n'
        self.token_stream_rewriter.insertBeforeIndex(index , new_code)

    def enterLabeledstatement2(self, ctx:CPP14_v2Parser.Labeledstatement2Context): #case
        self.block_stop = ctx.start.line
        self.addNode()
        try:
            if not self.has_jump_stack.pop():
                self.addInitEdge()
        except:
            pass
        self.has_case_stack[-1] = True
        self.has_jump_stack.append(False)
        self.block_number += 1
        self.block_start = ctx.start.line
        if not self.has_default_stack[-1]:
            self.addSwitchEdge()
        index = ctx.statement().start.tokenIndex
        new_code = self.logLine() + ';\n'
        self.token_stream_rewriter.insertBeforeIndex(index, new_code)
    def enterLabeledstatement3(self, ctx:CPP14_v2Parser.Labeledstatement3Context): #default
        self.block_stop = ctx.start.line
        self.addNode()
        try:
            if not self.has_jump_stack.pop():
                self.addInitEdge()
        except:
            pass
        self.has_default_stack[-1] = True
        self.has_jump_stack.append(False)
        self.block_number += 1
        self.block_start = ctx.start.line
        self.addSwitchEdge()
        index = ctx.statement().start.tokenIndex
        new_code = self.logLine() + ';\n'
        self.token_stream_rewriter.insertBeforeIndex(index, new_code)


    #iteration
    def enterIterationstatement1(self, ctx:CPP14_v2Parser.Iterationstatement1Context): #while
        self.switch_for_stack.append(SWITCH_FOR["for_while"])
        self.has_jump_stack.append(False)
        self.is_for.append(False)
        self.is_while.append(True)
        self.is_doWhile.append(False)
        self.block_stop = ctx.start.line - 1
        self.addNode()
        self.addInitEdge()
        self.block_number += 1
        self.block_start = ctx.start.line
        self.block_stop = self.block_start
        self.addNode()


        self.iterate_junction_stack.append(list())
        self.addIterateJunc('False')
        self.addIterate()
        self.addInitEdge('True')

    def enterIterationstatement3(self, ctx:CPP14_v2Parser.Iterationstatement3Context): # for
        self.switch_for_stack.append(SWITCH_FOR["for_while"])
        self.has_jump_stack.append(False)
        self.is_for.append(True)
        self.is_while.append(False)
        self.is_doWhile.append(False)
        self.block_stop = ctx.start.line
        self.addNode()
        self.addInitEdge("flow")

        self.iterate_junction_stack.append(list())
        self.block_number += 1
        self.block_start = ctx.start.line
        self.block_stop = self.block_start
        self.addNode()
        self.addIterateJunc('False')
        self.addIterate()
        self.addInitEdge('True')

        if ctx.condition() == None:
            new_code = self.logLine() + ' '
            self.token_stream_rewriter.insertAfter(ctx.forinitstatement().stop.tokenIndex, new_code)

    def enterIterationstatement2(self, ctx:CPP14_v2Parser.Iterationstatement2Context): # do-while
        self.switch_for_stack.append(SWITCH_FOR["for_while"])
        self.has_jump_stack.append(False)
        self.is_while.append(False)
        self.is_for.append(False)
        self.is_doWhile.append(True)
        self.iterate_junction_stack.append(list())

        self.block_stop = ctx.start.line - 1
        self.addNode()
        self.temp.append(self.block_number)
        self.addInitEdge()
        self.addIterate("True")

        expression = ctx.expression()


        new_code = self.logLine()
        new_code += ' && ('
        self.token_stream_rewriter.insertBeforeIndex(expression.start.tokenIndex, new_code)
        new_code = ')'
        self.token_stream_rewriter.insertAfter(expression.stop.tokenIndex, new_code)

        self.block_number += 1
        self.block_start = ctx.start.line

    def enterIterationstatement4(self, ctx:CPP14_v2Parser.Iterationstatement4Context): #range-for
        self.switch_for_stack.append(SWITCH_FOR["range_for"])
        self.has_jump_stack.append(False)
        self.is_for.append(True)
        self.is_while.append(False)
        self.is_doWhile.append(False)
        self.block_stop = ctx.start.line
        self.addNode()
        self.addInitEdge("flow")

        self.iterate_junction_stack.append(list())
        self.block_number += 1
        self.block_start = ctx.start.line
        self.block_stop = self.block_start
        self.addNode()
        self.addIterateJunc('False')
        self.addIterate()
        self.addInitEdge('True')

        """if ctx.condition() == None:
            new_code = self.logLine() + ' '
            self.token_stream_rewriter.insertAfter(ctx.forinitstatement().stop.tokenIndex, new_code)"""

    def enterCondition(self, ctx:CPP14_v2Parser.ConditionContext): # for and while and if condition
        if not isinstance(ctx.parentCtx, CPP14_v2Parser.Selectionstatement3Context):
            new_code = self.logLine()
            new_code += ' && ('
            self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex, new_code)
            new_code = ')'
            self.token_stream_rewriter.insertAfter(ctx.stop.tokenIndex , new_code)





    def exitSelectionstatement2(self, ctx:CPP14_v2Parser.Selectionstatement2Context):#if-else

        self.block_number += 1

        self.block_start = ctx.stop.line + 1

        self.addJunctionEdges()
        self.select_junction_stack.pop()
        new_code = '\n' +  self.logLine() +';\n'
        self.afterInsert[ctx.stop.tokenIndex ] += new_code

    def exitSelectionstatement3(self, ctx:CPP14_v2Parser.Selectionstatement3Context): #switch
        self.block_stop = ctx.stop.line
        self.addNode()
        self.switch_for_stack.pop()
        if not self.has_default_stack.pop():
            self.switch_junction_stack[-1].append((self.switch_stack.pop()[0],'flow'))
            if not self.has_case_stack.pop():
                self.has_jump_stack.pop()
            elif not self.has_jump_stack.pop():
                self.addSwitchJunc()
        elif not self.has_jump_stack.pop():
            self.addSwitchJunc()

        self.block_number += 1
        self.block_start = ctx.stop.line + 1
        self.addSwitchJunctionEdges()
        self.switch_junction_stack.pop()
        new_code = '\n' +  self.logLine() +';\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitIterationstatement1(self, ctx:CPP14_v2Parser.Iterationstatement1Context): #while
        self.iterate_stack.pop()
        self.switch_for_stack.pop()
        self.has_jump_stack.pop()
        self.block_number += 1
        self.block_start = ctx.stop.line +1
        self.addIterateJunctionEdges()
        self.iterate_junction_stack.pop()
        new_code = '\n' +  self.logLine() +';\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitIterationstatement3(self, ctx:CPP14_v2Parser.Iterationstatement3Context): #for

        self.iterate_stack.pop()
        self.switch_for_stack.pop()
        self.has_jump_stack.pop()
        self.block_number += 1
        self.block_start = ctx.stop.line + 1
        self.addIterateJunctionEdges()
        self.iterate_junction_stack.pop()
        new_code = '\n' + self.logLine() + ';\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitIterationstatement2(self, ctx:CPP14_v2Parser.Iterationstatement2Context): #do-while
        self.iterate_stack.pop()
        self.switch_for_stack.pop()
        self.has_jump_stack.pop()
        self.block_number += 1
        self.block_start = ctx.stop.line +1
        self.addIterateJunctionEdges()

        self.iterate_junction_stack.pop()

        new_code = '\n' +  self.logLine() +';\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitIterationstatement4(self, ctx: CPP14_v2Parser.Iterationstatement4Context):  # range-for
        self.iterate_stack.pop()
        self.switch_for_stack.pop()
        self.has_jump_stack.pop()
        self.block_number += 1
        self.block_start = ctx.stop.line + 1
        self.addIterateJunctionEdges()
        self.iterate_junction_stack.pop()
        new_code = '\n' + self.logLine() + ';\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitFunctionbody1(self, ctx:CPP14_v2Parser.Functionbody1Context):
        """
         Insert a prob at the end of the function only if the function is void.
        :param ctx:
        :return:
        """
        if not self.has_jump_stack.pop():
            self.block_stop = ctx.stop.line
            self.addNode()
            self.final_nodes.add(self.block_number)

    def enterJumpstatement1(self, ctx:CPP14_v2Parser.Jumpstatement1Context): #break
        self.block_stop = ctx.stop.line
        self.addNode()
        try:
            self.has_jump_stack[-1] = True
        except:
            pass
        if self.switch_for_stack[-1] == SWITCH_FOR["switch"]:
             self.addSwitchJunc()
        else:
            self.addIterateJunc()

    def enterJumpstatement2(self, ctx: CPP14_v2Parser.Jumpstatement2Context):  # continue
        self.block_stop = ctx.stop.line
        self.addNode()
        try:
            self.has_jump_stack[-1] = True
        except:
            pass
        i = 1
        while (self.switch_for_stack[-i] == SWITCH_FOR["switch"]):
            i = i-1
        if self.switch_for_stack[-i] == SWITCH_FOR["range_for"]:
            self.addIterateJunc()
        self.addIterateEdge()

    def enterJumpstatement3(self, ctx:CPP14_v2Parser.Jumpstatement3Context): #return
        self.block_stop = ctx.stop.line
        self.addNode()

        try:
            self.has_jump_stack[-1] = True
        except:
            pass
        self.final_nodes.add(self.block_number)

    def enterJumpstatement4(self, ctx:CPP14_v2Parser.Jumpstatement4Context): #return
        self.block_stop = ctx.stop.line
        self.addNode()
        try:
            self.has_jump_stack[-1] = True
        except:
            pass
        self.final_nodes.add(self.block_number)

    def enterJumpstatement5(self, ctx:CPP14_v2Parser.Jumpstatement5Context): #goto
        self.block_stop = ctx.stop.line
        self.addNode()
        try:
            self.has_jump_stack[-1] = True
        except:
            pass
        label = ctx.Identifier().getText()
        try:
            self.addGotoEdge(label)
        except:
            try:
                self.goto_dict[label] += [self.block_number]
            except:
                self.goto_dict[label] = [self.block_number]

    def enterThrowexpression(self, ctx:CPP14_v2Parser.ThrowexpressionContext): #throw
        self.is_catch = False

        self.block_stop = ctx.stop.line

        self.addNode()

        try:
            self.has_jump_stack[-1] = True
        except:
            pass

        self.is_catch = True
    def exitFunctiondefinition(self, ctx: CPP14_v2Parser.FunctiondefinitionContext):
        initial_nodes_str = ' '.join(str(node) for node in self.initial_nodes)
        self.CFG_file.write("initial nodes:" + initial_nodes_str + '\n')
        self.final_nodes.add(self.block_number)
        final_nodes_str = ' '.join(str(node) for node in self.final_nodes)
        self.CFG_file.write("final nodes:" + final_nodes_str + '\n')

        self.CFG_file.close()
        temp = []
        temp_e = []
        func_graph = nx.DiGraph()
        func_graph.add_nodes_from([(str(n)) for n,s,e in self.block_dict[self.domain_name]["Nodes"]])
        func_graph.add_edges_from([(str(s),str(d)) for s,d,T in self.block_dict[self.domain_name]["Edges"]])
        temp.append([(str(s),str(d),str(T)) for s,d,T in self.block_dict[self.domain_name]["Edges"]])
        temp_e.append([(str(s),str(e)) for n,s,e in self.block_dict[self.domain_name]["Nodes"]])
        Nodes_list = [*func_graph.nodes]
        edge_labels = {}
        f_nodes = []
        for s,d,T in self.block_dict[self.domain_name]["Edges"]:
            edge_labels[(s,d)] = T
        graph = gv.Digraph(node_attr={'shape': 'none'})
        graph.node('start', style='filled', fillcolor='red', fontsize='22')
        graph.node('end', style='filled', fillcolor='red', fontsize='22')
        for node in func_graph:
            if func_graph.out_degree(node) == 0:
                f_nodes.append(node)

        for i,j in zip(func_graph,temp_e[0]):

            graph.node(str(Nodes_list[int(i)-1]),label= f'''<
<FONT POINT-SIZE="22">
               <TABLE BORDER="0" CELLBORDER="1" CELLSPACING="0">
                    <tr>
                         <td width="30" height="30" fixedsize="true">{i}</td>
                         <td width="9" height="9" fixedsize="true" style="invis"></td>
                         <td width="9" height="9" fixedsize="true" style="invis"></td>
                    </tr>
                    <tr>
                         <td width="30" height="40" fixedsize="true" sides="tlb"></td>
                         <td width="50" height="40" fixedsize="false" sides="bt" PORT="here">{int(j[0]) , int(j[1])}</td>
                         <td width="30" height="40" fixedsize="true" sides="brt"></td>
                    </tr>
            </TABLE>
            </FONT>>''')





        for items in f_nodes:


            graph.edge(f'{str(Nodes_list[int(items)-1])}:here:s', 'end')


        for x in temp[0]:
            graph.edge(f'{x[0]}:here:s',f'{x[1]}:here:n',x[2], fontsize='22')

        graph.edge('start', f'{str(Nodes_list[0])}:here:n')


        graph.render(f'{self.cfg_path}/{str(self.domain_name)}.gv', view=True)



        graph_json = open(self.cfg_path + str(self.domain_name) + '.json' , 'w')
        json.dump(self.block_dict[self.domain_name] , graph_json)


    def exitTranslationunit(self, ctx: CPP14_v2Parser.TranslationunitContext):
        """
        Creating and open a text file for logging the instrumentation result
        :param ctx:
        :return:
        """
        for i in range(len(self.afterInsert)):
            if self.afterInsert[i] != '':
                self.token_stream_rewriter.insertAfter(i , self.afterInsert[i])
        self.instrumented_source.write(self.token_stream_rewriter.getDefaultText())
        self.instrumented_source.close()

        functions_json = open(self.cfg_path + 'functions.json', 'w')
        json.dump(self.function_dict, functions_json)

    def enterDeclarator(self, ctx: CPP14_v2Parser.DeclaratorContext):
        pass
