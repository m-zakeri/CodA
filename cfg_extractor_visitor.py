from antlr4 import *

from gen.CPP14_v2Parser import CPP14_v2Parser
from gen.CPP14_v2Visitor import CPP14_v2Visitor
from graph_utils import build_single_node_graph, concat_graphs, solve_null_nodes
from lang_structures import *


class CFGExtractorVisitor(CPP14_v2Visitor):
    def __init__(self, common_token_stream: CommonTokenStream):
        self.token_stream = common_token_stream

    def visitTranslationunit(self, ctx: CPP14_v2Parser.TranslationunitContext):
        gin = self.visit(ctx.declarationseq())
        return solve_null_nodes(gin)

    # todo: implement seq2 as well
    def visitDeclarationseq1(self, ctx: CPP14_v2Parser.Declarationseq1Context):
        return self.visit(ctx.declaration())

    def visitFunctiondefinition(self, ctx: CPP14_v2Parser.FunctiondefinitionContext):
        return self.visit(ctx.functionbody())

    def visitCompoundstatement(self, ctx: CPP14_v2Parser.CompoundstatementContext):
        return self.visit(ctx.statementseq())

    # todo: add conditions
    def visitSelectionstatement1(self, ctx: CPP14_v2Parser.Selectionstatement1Context):
        condition = ctx.condition()
        if_body = ctx.statement()
        gin = self.visit(if_body)
        return embed_in_if_structure(gin, condition)

    def visitSelectionstatement2(self, ctx: CPP14_v2Parser.Selectionstatement2Context):
        condition = ctx.condition()
        if_body = ctx.statement(0)
        else_body = ctx.statement(1)
        gin_if = self.visit(if_body)
        gin_else = self.visit(else_body)
        return embed_in_if_else_structure(gin_if, gin_else, condition)

    def visitIterationstatement1(self, ctx: CPP14_v2Parser.Iterationstatement1Context):
        condition = ctx.condition()
        gin = self.visit(ctx.statement())
        return embed_in_while_structure(gin, condition)

    def visitIterationstatement2(self, ctx: CPP14_v2Parser.Iterationstatement2Context):
        condition = ctx.expression()
        gin = self.visit(ctx.statement())
        return embed_in_do_while_structure(gin, condition)

    def visitIterationstatement3(self, ctx: CPP14_v2Parser.Iterationstatement3Context):
        init = ctx.forinitstatement()
        condition = ctx.condition()
        successor = ctx.expression()
        gin = self.visit(ctx.statement())
        return embed_in_for_structure(gin, init, condition, successor)

    def visitJumpstatement1(self, ctx: CPP14_v2Parser.Jumpstatement1Context):
        return build_single_node_graph(ctx)

    def visitStatementseq1(self, ctx: CPP14_v2Parser.Statementseq1Context):
        return self.visit(ctx.statement())

    def visitStatementseq2(self, ctx: CPP14_v2Parser.Statementseq2Context):
        gin1 = self.visit(ctx.statementseq())
        gin2 = self.visit(ctx.statement())
        return concat_graphs(gin1, gin2)

    def visitExpressionstatement(self, ctx: CPP14_v2Parser.ExpressionstatementContext):
        return build_single_node_graph(ctx)

    def visitDeclarationstatement(self, ctx: CPP14_v2Parser.DeclarationstatementContext):
        return build_single_node_graph(ctx)
