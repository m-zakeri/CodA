"""

The script instrument CPP files

"""

__version__ = '0.1.0'
__author__ = 'Morteza Zakeri'

from antlr4 import TokenStreamRewriter
from coda.antlr_gen.cpp_parser.CPP14_v2Lexer import *
from coda.antlr_gen.cpp_parser.CPP14_v2Parser import *
from coda.antlr_gen.cpp_parser.CPP14_v2Listener import *


class InstrumentationListener(CPP14_v2Listener):
    def __init__(self, common_token_stream: CommonTokenStream):
        """

        :param common_token_stream:

        """
        self.branch_number = 0
        self.has_return_statement = False
        # Move all the tokens in the source code in a buffer, token_stream_rewriter.
        if common_token_stream is not None:
            self.token_stream_rewriter = TokenStreamRewriter.TokenStreamRewriter(common_token_stream)
        else:
            raise TypeError('common_token_stream is None')

    def enterTranslationunit(self, ctx: CPP14_v2Parser.TranslationunitContext):
        """

        Creating and open a text file for logging the instrumentation result
        :param ctx:
        :return:

        """
        new_code = '#include <fstream>\nstd::ofstream logFile("log_file.txt");\n\n'
        self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex, new_code)

    def enterStatement(self, ctx: CPP14_v2Parser.StatementContext):
        """

        DFS traversal of a statement subtree, rooted at ctx.
        If the statement is a branching condition insert a prob.
        :param ctx:
        :return:

        """

        if isinstance(ctx.parentCtx,
                      (CPP14_v2Parser.SelectionstatementContext, CPP14_v2Parser.IterationstatementContext)):
            # if there is a compound statement after the branchning condition:
            if isinstance(ctx.children[0], CPP14_v2Parser.CompoundstatementContext):
                self.branch_number += 1
                new_code = '\nlogFile << "p' + str(self.branch_number) + '" << std::endl;\n'
                self.token_stream_rewriter.insertAfter(ctx.start.tokenIndex, new_code)
            # if there is only one statement after the branchning condition then create a block.
            elif not isinstance(ctx.children[0],
                                (CPP14_v2Parser.SelectionstatementContext, CPP14_v2Parser.IterationstatementContext)):
                self.branch_number += 1
                new_code = '{'
                new_code += '\nlogFile << "p' + str(self.branch_number) + '" << std::endl;\n'
                new_code += ctx.getText()
                new_code += '\n}'
                self.token_stream_rewriter.replaceRange(ctx.start.tokenIndex, ctx.stop.tokenIndex, new_code)

    def enterFunctionbody(self, ctx: CPP14_v2Parser.FunctionbodyContext):
        """
        Insert a prob at the beginning of the function
        :param ctx:
        :return:
        """
        self.branch_number += 1
        new_code = '\nlogFile << "p' + str(self.branch_number) + '" << std::endl;'
        self.token_stream_rewriter.insertAfter(ctx.start.tokenIndex, new_code)

    def exitFunctionbody(self, ctx: CPP14_v2Parser.FunctionbodyContext):
        """

         Insert a prob at the end of the function only if the function is void.
        :param ctx:
        :return:

        """
        if not self.has_return_statement:
            self.branch_number += 1
            new_code = '\n logFile << "p' + str(self.branch_number) + '" << std::endl;\n'
            self.token_stream_rewriter.insertBeforeIndex(ctx.stop.tokenIndex, new_code)

    def enterJumpstatement(self, ctx: CPP14_v2Parser.JumpstatementContext):
        """

        Insert a prob at the end of the function with return statement.
        :param ctx:
        :return:

        """
        if ctx.getChild(0).getText() == 'return':
            self.branch_number += 1
            new_code = '\n logFile << "p' + str(self.branch_number) + '" << std::endl;\n'
            self.token_stream_rewriter.insertBeforeIndex(ctx.start.tokenIndex, new_code)
            self.has_return_statement = True
