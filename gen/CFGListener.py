# in the name of allah

from antlr4 import *
from antlr4 import TokenStreamRewriter
from gen.CPP14Listener import CPP14Listener
from gen.CPP14Parser import CPP14Parser
from gen.CPP14Lexer import CPP14Lexer as lexer


class CFGListener(CPP14Listener):

    def addNode(self):
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
        source_node = self.iterate_junction_stack.pop()
        dest_node = self.block_number
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addIterateEdge(self):
        source_node = self.block_number
        dest_node = self.iterate_stack[-1]
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addIterateJunc(self):
        self.iterate_junction_stack.append(self.block_number)

    def addIterate(self):
        self.iterate_stack.append(self.block_number)

    def insertAfter(self, ctx):
        new_code = '\nlogFile << "' + self.domain_name + str(self.block_number) + '" << std::endl;'
        self.token_stream_rewriter.insertAfter(ctx.start.tokenIndex, new_code)

    def __init__(self, common_token_stream: CommonTokenStream , number_of_tokens):
        """

        :param common_token_stream:
        """
        self.block_dict = {}
        self.block_number = 0
        self.block_start = 0
        self.block_stop = 0
        self.domain_name = ""
        self.select_junction_stack = []
        self.select_decision_stack = []
        self.iterate_junction_stack = []
        self.iterate_stack = []
        self.afterInsert = [''] * number_of_tokens
        self.beforeInsert = [''] * number_of_tokens
        self.has_return_statement = False
        self.has_jump = False
        print("ya_ali")
        # Move all the tokens in the source code in a buffer, token_stream_rewriter.
        if common_token_stream is not None:
            self.token_stream_rewriter = TokenStreamRewriter.TokenStreamRewriter(common_token_stream)
        else:
            raise TypeError('common_token_stream is None')

    def enterTranslationunit(self, ctx: CPP14Parser.TranslationunitContext):
        """
        Creating and open a text file for logging the instrumentation result
        :param ctx:
        :return:
        """
        self.instrumented_source = open('Instrument/instrumented_source.cpp', 'w')
        new_code = '\n//in the name of allah\n#include <fstream>\nstd::ofstream logFile("log_file.txt");\n\n'
        self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex, new_code)

    def enterFunctiondefinition(self, ctx: CPP14Parser.FunctiondefinitionContext):
        self.block_number = 1
        self.block_start = ctx.functionbody().start.line
        temp = ctx.declarator().getText().replace('~' , "destructor")
        self.domain_name = ''.join(c for c in temp if c.isalnum())
        self.block_dict[self.domain_name] = {
            "Nodes": [],
            "Edges": []
        }
        self.CFG_file = open('CFGS/' + self.domain_name + '.txt', 'w')
        self.CFG_file.write("initial nodes: " + str(self.block_number) + '\n')

    def enterFunctionbody(self, ctx: CPP14Parser.FunctionbodyContext):
        """
        Insert a prob at the beginning of the function
        :param ctx:
        :return:
        """
        self.has_return_statement = False
        self.insertAfter(ctx)

    def enterSelectionstatement(self, ctx: CPP14Parser.SelectionstatementContext):
        self.block_stop = ctx.start.line
        self.addNode()
        if self.block_number in self.select_junction_stack:
            self.select_junction_stack.remove(self.block_number)
        if ctx.getToken(lexer.Else, 0) is None:
            self.addDecision()
            self.addJunc()
        else:
            self.addDecision()
            self.addDecision()

    def enterIterationstatement(self, ctx: CPP14Parser.IterationstatementContext):
        self.block_stop = ctx.start.line
        self.addNode()
        if ctx.getToken(lexer.Do, 0) is None:
            self.addDecision()

        source_node = self.block_number
        dest_node = source_node + 1
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

        self.block_number += 1
        self.addIterate()
        self.block_start = ctx.start.line

    def enterStatement(self, ctx: CPP14Parser.StatementContext):
        """
        DFS traversal of a statement subtree, rooted at ctx.
        If the statement is a branching condition insert a prob.
        :param ctx:
        :return:
        """
        if isinstance(ctx.parentCtx,
                      CPP14Parser.IterationstatementContext):
            # if there is a compound statement after the branchning condition:
            if isinstance(ctx.children[0], CPP14Parser.CompoundstatementContext):
                self.insertAfter(ctx)
            # if there is only one statement after the branchning condition then create a block.
            else:
                new_code = '{'
                new_code += '\nlogFile << "' + self.domain_name + str(self.block_number) + '" << std::endl;\n'
                self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex , new_code)

        elif isinstance(ctx.parentCtx,
                      (CPP14Parser.SelectionstatementContext)):
            self.block_number += 1
            self.addDecisionEdge()
            self.block_start = ctx.start.line
            # if there is a compound statement after the branchning condition:
            if isinstance(ctx.children[0], CPP14Parser.CompoundstatementContext):
                self.insertAfter(ctx)
            # if there is only one statement after the branchning condition then create a block.
            else:
                new_code = '{'
                new_code += '\nlogFile << "' + self.domain_name + str(self.block_number) + '" << std::endl;\n'
                self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex, new_code)

    def exitStatement(self, ctx: CPP14Parser.StatementContext):
        if isinstance(ctx.parentCtx, CPP14Parser.IterationstatementContext):
            self.addIterateEdge()
            self.block_stop = ctx.stop.line
            self.addNode()
            if not isinstance(ctx.children[0], CPP14Parser.CompoundstatementContext):
                new_code = '\n}'
                self.afterInsert[ctx.stop.tokenIndex] += new_code
        if isinstance(ctx.parentCtx, CPP14Parser.SelectionstatementContext):
            self.block_stop = ctx.stop.line
            self.addNode()
            if not self.has_jump:
                self.addJunc()
            self.has_jump = False
            if not isinstance(ctx.children[0], CPP14Parser.CompoundstatementContext):
                new_code = '\n}'
                self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitSelectionstatement(self, ctx: CPP14Parser.SelectionstatementContext):
        self.block_number += 1
        self.block_start = ctx.stop.line
        self.addJunctionEdge()
        self.addJunctionEdge()

        new_code = '\nlogFile << "' + self.domain_name + str(self.block_number) + '" << std::endl;\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitIterationstatement(self, ctx: CPP14Parser.IterationstatementContext):
        self.addIterateJunc()
        self.iterate_stack.pop()
        self.block_number += 1
        self.block_start = ctx.stop.line
        if ctx.getToken(lexer.Do, 0) is None:
            self.addDecisionEdge()
        while True:
            try:
                self.addIterateJunctionEdge()
            except:
                break
        new_code = '\nlogFile << "' + self.domain_name + str(self.block_number) + '" << std::endl;\n'
        self.afterInsert[ctx.stop.tokenIndex] += new_code

    def exitFunctionbody(self, ctx: CPP14Parser.FunctionbodyContext):
        """
         Insert a prob at the end of the function only if the function is void.
        :param ctx:
        :return:
        """
        if not self.has_return_statement:
            pass
            #new_code = '\n logFile << "' + self.domain_name + str(self.block_number) + '" << std::endl;\n'
            #self.token_stream_rewriter.insertBeforeIndex(ctx.stop.tokenIndex, new_code)

    def enterJumpstatement(self, ctx: CPP14Parser.JumpstatementContext):
        """
        Insert a prob at the end of the function with return statement.
        :param ctx:
        :return:
        """
        if ctx.getChild(0).getText() == 'break':
            self.has_jump = True
            self.addIterateJunc()

        if ctx.getChild(0).getText() == 'continue':
            self.has_jump = True
            self.addIterateEdge()

        if ctx.getChild(0).getText() == 'return':
            #new_code = '\n logFile << "' + self.domain_name + str(self.block_number) + '" << std::endl;\n'
            #self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex, new_code)
            self.has_return_statement = True

    def exitFunctiondefinition(self, ctx: CPP14Parser.FunctiondefinitionContext):
        self.block_stop = ctx.stop.line
        self.addNode()
        self.CFG_file.write("final nodes: " + str(self.block_number) + '\n')
        print(self.block_dict)
        self.CFG_file.close()

    def exitTranslationunit(self, ctx: CPP14Parser.TranslationunitContext):
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

    def enterDeclarator(self, ctx: CPP14Parser.DeclaratorContext):
        pass
        # print(ctx.parentCtx.parentCtx.parentCtx.getText())
