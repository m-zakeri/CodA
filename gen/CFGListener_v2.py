# in the name of allah

from antlr4 import *
from antlr4 import TokenStreamRewriter
from .CPP14_v2Listener import CPP14_v2Listener
from .CPP14_v2Parser import CPP14_v2Parser
from .CPP14_v2Lexer import CPP14_v2Lexer as lexer

import networkx as nx
import matplotlib.pyplot as plt
SWITCH_FOR = {
    "for_while" : 0,
    "range_for" : 1,
    "switch" : 2
}
class CFGInstListener(CPP14_v2Listener):

    def addNode(self):
        try:
            if not self.is_catch:
                self.try_stack[-1].add(self.block_number)
        except:
            pass
        self.block_dict[self.domain_name]["Nodes"].append((self.block_number, self.block_start, self.block_stop))

    def addJunctionEdge(self):
        try:
            source_node = self.select_junction_stack.pop()
            dest_node = self.block_number
            self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
            self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')
        except:
            pass

    def addDecisionEdge(self):
        source_node = self.select_decision_stack.pop()
        dest_node = self.block_number
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addJunc(self):
        self.select_junction_stack.append(self.block_number)

    def addDecision(self):
        self.select_decision_stack.append(self.block_number)

    def addIterateJunctionEdge(self):
        for source_node in self.iterate_junction_stack[-1]:
            dest_node = self.block_number
            self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
            self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addIterateEdge(self):
        source_node = self.block_number
        dest_node = self.iterate_stack[-1]
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addInitEdge(self):
        source_node = self.block_number
        dest_node = source_node + 1
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addDoWhileInitEdge(self):
        source_node = self.block_number
        dest_node = source_node + 2
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addIterateJunc(self):
        self.iterate_junction_stack[-1].append(self.block_number)

    def addIterate(self):
        self.iterate_stack.append(self.block_number)

    def addSwitchEdge(self):
        source_node = self.switch_stack[-1]
        dest_node = self.block_number
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')
    
    def addSwitchJunctionEdge(self):
        for source_node in self.switch_junction_stack[-1]:
            dest_node = self.block_number
            self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
            self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')
        
    def addSwitch(self):
        self.switch_stack.append(self.block_number)
    def addSwitchJunc(self):
        self.switch_junction_stack[-1].append(self.block_number)

    def addGotoEdge(self , label):
        source_node = self.block_number
        dest_node = self.label_dict[label]
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def insertAfter(self, ctx):
        new_code = '\n' + self.logLine() + ';\n'
        self.token_stream_rewriter.insertAfter(ctx.start.tokenIndex, new_code)

    def logLine(self):
        return 'logFile << "' + self.domain_name + ' ' + str(self.block_number) + '" << std::endl'

    def addTryJunc(self):
        self.try_junction_stack[-1].append(self.block_number)

    def addTryEdge(self):
        for source_node in self.try_stack[-1]:
            dest_node = self.block_number
            self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
            self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addTryJuncEdge(self):
        for source_node in self.try_junction_stack[-1]:
            dest_node = self.block_number
            self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
            self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def __init__(self, common_token_stream: CommonTokenStream, number_of_tokens , directory_name):
        """
        :param common_token_stream:
        """
        self.cfg_path = 'CFGS/v2/' + directory_name + '/'
        self.instrument_path = 'Instrument/v2/' + directory_name + '/'
        self.block_dict = {}
        self.block_number = 0
        self.block_start = 0
        self.block_stop = 0
        self.domain_name = ""
        self.select_junction_stack = []
        self.select_decision_stack = []
        self.iterate_junction_stack = []
        self.iterate_stack = []
        self.switch_junction_stack = []
        self.switch_stack = []
        self.switch_for_stack = []
        self.has_jump_stack = []
        self.has_default_stack = []
        self.has_case_stack = []
        self.try_stack = []
        self.try_junction_stack = []
        self.is_catch = False
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
        new_code = '\n//in the name of allah\n#include <fstream>\nstd::ofstream logFile("log_file.txt");\n\n'
        self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex, new_code)

    #function
    def enterFunctiondefinition(self, ctx: CPP14_v2Parser.FunctiondefinitionContext):
        self.initial_nodes = set()
        self.final_nodes = set()
        temp = ctx.declarator().getText().replace('~', "destructor")
        self.domain_name = ''.join(c for c in temp if c.isalnum())
        self.block_dict[self.domain_name] = {
            "Nodes": [],
            "Edges": []
        }
        self.CFG_file = open(self.cfg_path + self.domain_name + '.txt', 'w')


    def enterFunctionbody1(self, ctx:CPP14_v2Parser.Functionbody1Context): #normal function
        """
        Insert a prob at the beginning of the function
        :param ctx:
        :return:
        """
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
        self.has_jump_stack.append(False)
        self.try_stack.append(set())
        self.try_junction_stack.append(list())

    def exitCompoundstatement(self, ctx:CPP14_v2Parser.CompoundstatementContext):
        if isinstance(ctx.parentCtx , CPP14_v2Parser.TryblockContext):
            self.has_jump_stack.pop()
            self.block_stop = ctx.stop.line
            self.addNode()
            self.try_junction_stack[-1].append(self.block_number)
        elif isinstance(ctx.parentCtx , CPP14_v2Parser.FunctiontryblockContext):
            self.has_jump_stack.pop()
            self.block_stop = ctx.stop.line
            self.addNode()

    def enterHandler(self, ctx:CPP14_v2Parser.HandlerContext):
        self.is_catch = True
        self.block_number += 1
        self.block_start = ctx.start.line
        body = ctx.compoundstatement()
        self.insertAfter(body)
        self.addTryEdge()
        self.has_jump_stack.append(False)

    def exitHandler(self, ctx:CPP14_v2Parser.HandlerContext):
        self.block_stop = ctx.stop.line
        self.addNode()
        self.addTryJunc()
        self.has_jump_stack.pop()

    def exitTryblock(self, ctx:CPP14_v2Parser.TryblockContext):
        self.block_number += 1
        self.block_start = ctx.stop.line
        self.addTryJuncEdge()
        self.try_junction_stack.pop()
        self.try_stack.pop()
        self.is_catch = False
        new_code = '\n' + self.logLine() + ';\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitFunctiontryblock(self, ctx:CPP14_v2Parser.FunctiontryblockContext):
        self.is_catch = False
        self.try_stack.pop()
    #selection
    def enterSelectionstatement1(self, ctx:CPP14_v2Parser.Selectionstatement1Context): #if
        self.block_stop = ctx.start.line
        self.addNode()
        if self.block_number in self.select_junction_stack:
            self.select_junction_stack.remove(self.block_number)
        self.addDecision()
        self.addJunc()

    def enterSelectionstatement2(self, ctx:CPP14_v2Parser.Selectionstatement2Context): #if-else
        self.block_stop = ctx.start.line
        self.addNode()
        if self.block_number in self.select_junction_stack:
            self.select_junction_stack.remove(self.block_number)
        self.addDecision()
        self.addDecision()

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
        self.block_stop = ctx.start.line
        self.addNode()
        self.addInitEdge()
        self.iterate_junction_stack.append(list())
        self.block_number += 1
        self.block_start = ctx.start.line
        self.addIterateJunc()
        self.addIterate()

    def enterIterationstatement3(self, ctx:CPP14_v2Parser.Iterationstatement3Context): # for
        self.switch_for_stack.append(SWITCH_FOR["for_while"])
        self.has_jump_stack.append(False)
        self.block_stop = ctx.start.line
        self.addNode()
        self.addInitEdge()
        self.iterate_junction_stack.append(list())
        self.block_number += 1
        self.block_start = ctx.start.line
        self.addIterateJunc()
        self.addIterate()

        if ctx.condition() == None:
            new_code = self.logLine() + ' '
            self.token_stream_rewriter.insertAfter(ctx.forinitstatement().stop.tokenIndex , new_code)

    def enterIterationstatement2(self, ctx:CPP14_v2Parser.Iterationstatement2Context): # do-while
        self.switch_for_stack.append(SWITCH_FOR["for_while"])
        self.has_jump_stack.append(False)
        self.block_stop = ctx.start.line
        self.addNode()
        self.addDoWhileInitEdge()
        self.iterate_junction_stack.append(list())

        expression = ctx.expression()
        self.block_number += 1
        self.block_start = expression.start.line
        self.block_stop = expression.stop.line
        self.addNode()
        self.addIterate()
        self.addIterateJunc()
        self.addInitEdge()
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
        self.block_stop = ctx.start.line
        self.addNode()
        self.addDecision()
        self.addInitEdge()
        self.iterate_junction_stack.append(list())
        self.block_number += 1
        self.block_start = ctx.start.line
        self.addIterate()

    def enterCondition(self, ctx:CPP14_v2Parser.ConditionContext): # for and while condition
        if isinstance(ctx.parentCtx , CPP14_v2Parser.IterationstatementContext):
            new_code = self.logLine()
            new_code += ' && ('
            self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex, new_code)
            new_code = ')'
            self.token_stream_rewriter.insertAfter(ctx.stop.tokenIndex , new_code)


    def enterStatement(self, ctx:CPP14_v2Parser.StatementContext):
        """
        DFS traversal of a statement subtree, rooted at ctx.
        If the statement is a branching condition insert a prob.
        :param ctx:
        :return:
        """
        #do-while and range-for
        if isinstance(ctx.parentCtx,
                      (CPP14_v2Parser.Iterationstatement4Context,CPP14_v2Parser.Iterationstatement2Context)):
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
            if ctx.compoundstatement() == None:
                new_code = '{\n'
                self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex, new_code)

        elif isinstance(ctx.parentCtx,
                      (CPP14_v2Parser.Selectionstatement1Context , CPP14_v2Parser.Selectionstatement2Context)):
            self.block_number += 1
            self.addDecisionEdge()
            self.block_start = ctx.start.line
            self.has_jump_stack.append(False)
            # if there is a compound statement after the branchning condition:
            body = ctx.compoundstatement()
            if body != None:
                print(ctx.start.line)
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
            self.addIterateEdge()
            self.block_stop = ctx.stop.line
            self.addNode()
            if ctx.compoundstatement() == None:
                new_code = '\n}'
                self.afterInsert[ctx.stop.tokenIndex] += new_code

        elif isinstance(ctx.parentCtx,
                        (CPP14_v2Parser.Selectionstatement1Context, CPP14_v2Parser.Selectionstatement2Context)): # if
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

    def exitSelectionstatement1(self, ctx:CPP14_v2Parser.Selectionstatement1Context):#if
        self.block_number += 1
        self.block_start = ctx.stop.line
        self.addJunctionEdge()
        self.addJunctionEdge()

        new_code = '\n' +  self.logLine() +';\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitSelectionstatement2(self, ctx:CPP14_v2Parser.Selectionstatement2Context):#if-else
        self.block_number += 1
        self.block_start = ctx.stop.line
        self.addJunctionEdge()
        self.addJunctionEdge()

        new_code = '\n' +  self.logLine() +';\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitSelectionstatement3(self, ctx:CPP14_v2Parser.Selectionstatement3Context): #switch
        self.block_stop = ctx.stop.line
        self.addNode()
        self.switch_for_stack.pop()
        if not self.has_default_stack.pop():
            self.switch_junction_stack[-1].append(self.switch_stack.pop())
            if not self.has_case_stack.pop():
                self.has_jump_stack.pop()
            elif not self.has_jump_stack.pop():
                self.addSwitchJunc()
        elif not self.has_jump_stack.pop():
            self.addSwitchJunc()

        self.block_number += 1
        self.block_start = ctx.stop.line
        self.addSwitchJunctionEdge()
        self.switch_junction_stack.pop()
        new_code = '\n' +  self.logLine() +';\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitIterationstatement1(self, ctx:CPP14_v2Parser.Iterationstatement1Context): #while
        self.iterate_stack.pop()
        self.switch_for_stack.pop()
        self.has_jump_stack.pop()
        self.block_number += 1
        self.block_start = ctx.stop.line
        self.addIterateJunctionEdge()
        self.iterate_junction_stack.pop()
        new_code = '\n' +  self.logLine() +';\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitIterationstatement3(self, ctx:CPP14_v2Parser.Iterationstatement3Context): #for
        self.iterate_stack.pop()
        self.switch_for_stack.pop()
        self.has_jump_stack.pop()
        self.block_number += 1
        self.block_start = ctx.stop.line
        self.addIterateJunctionEdge()
        self.iterate_junction_stack.pop()
        new_code = '\n' +  self.logLine() +';\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitIterationstatement2(self, ctx:CPP14_v2Parser.Iterationstatement2Context): #do-while
        self.iterate_stack.pop()
        self.switch_for_stack.pop()
        self.has_jump_stack.pop()
        self.block_number += 1
        self.block_start = ctx.stop.line
        self.addIterateJunctionEdge()
        self.iterate_junction_stack.pop()
        new_code = '\n' +  self.logLine() +';\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitIterationstatement4(self, ctx: CPP14_v2Parser.Iterationstatement4Context):  # range-for
        self.addIterateJunc()

        self.iterate_stack.pop()
        self.switch_for_stack.pop()
        self.has_jump_stack.pop()
        self.block_number += 1
        self.block_start = ctx.stop.line
        self.addDecisionEdge()
        self.addIterateJunctionEdge()
        self.iterate_junction_stack.pop()
        new_code = '\n' +  self.logLine() +';\n'
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
        self.block_stop = ctx.stop.line
        self.addNode()
        try:
            self.has_jump_stack[-1] = True
        except:
            pass

    def exitFunctiondefinition(self, ctx: CPP14_v2Parser.FunctiondefinitionContext):
        initial_nodes_str = ' '.join(str(node) for node in self.initial_nodes)
        self.CFG_file.write("initial nodes:" + initial_nodes_str + '\n')
        self.final_nodes.add(self.block_number)
        final_nodes_str = ' '.join(str(node) for node in self.final_nodes)
        self.CFG_file.write("final nodes:" + final_nodes_str + '\n')
        print(self.block_dict)
        self.CFG_file.close()
        func_graph = nx.Graph(self.block_dict[self.domain_name]["Edges"])
        nx.draw(func_graph , with_labels=True)
        plt.savefig(self.cfg_path + self.domain_name + '.png')
        plt.close()

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

    def enterDeclarator(self, ctx: CPP14_v2Parser.DeclaratorContext):
        pass
        # print(ctx.parentCtx.parentCtx.parentCtx.getText())
