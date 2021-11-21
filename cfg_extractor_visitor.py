from antlr4 import *

from gen.CPP14_v2Parser import CPP14_v2Parser
from gen.CPP14_v2Visitor import CPP14_v2Visitor
from graph_utils import (build_single_node_graph, concat_graphs)
from lang_structures import *


class CFGExtractorVisitor(CPP14_v2Visitor):
    def __init__(self, common_token_stream: CommonTokenStream):
        self.token_stream = common_token_stream

    def extract_exact_text(self, rule: ParserRuleContext):
        return self.token_stream.getText(rule.start.tokenIndex, rule.stop.tokenIndex), rule.start.line

    def visitTranslationunit(self, ctx: CPP14_v2Parser.TranslationunitContext):
        return self.visit(ctx.declarationseq())

    # todo: implement seq2 as well
    def visitDeclarationseq1(self, ctx: CPP14_v2Parser.Declarationseq1Context):
        return self.visit(ctx.declaration())

    def visitFunctiondefinition(self, ctx: CPP14_v2Parser.FunctiondefinitionContext):
        return self.visit(ctx.functionbody())

    def visitCompoundstatement(self, ctx: CPP14_v2Parser.CompoundstatementContext):
        return self.visit(ctx.statementseq())

    # todo: add conditions
    def visitSelectionstatement1(self, ctx: CPP14_v2Parser.Selectionstatement1Context):
        if_body = ctx.statement()
        condition = self.extract_exact_text(ctx.condition())
        gin = self.visit(if_body)
        return embed_in_if_structure(gin, condition)

    def visitSelectionstatement2(self, ctx: CPP14_v2Parser.Selectionstatement2Context):
        if_body = ctx.statement(0)
        gin_if = self.visit(if_body)

        else_body = ctx.statement(1)
        gin_else = self.visit(else_body)

        condition = self.extract_exact_text(ctx.condition())
        return embed_in_if_else_structure(gin_if, gin_else, condition)

    def visitIterationstatement1(self, ctx: CPP14_v2Parser.Iterationstatement1Context):
        condition = self.extract_exact_text(ctx.condition())
        gin = self.visit(ctx.statement())
        return embed_in_while_structure(gin, condition)

    def visitIterationstatement2(self, ctx: CPP14_v2Parser.Iterationstatement2Context):
        condition = self.extract_exact_text(ctx.expression())
        gin = self.visit(ctx.statement())
        return embed_in_do_while_structure(gin, condition)

    def visitIterationstatement3(self, ctx: CPP14_v2Parser.Iterationstatement3Context):
        init = self.extract_exact_text(ctx.forinitstatement())
        condition = self.extract_exact_text(ctx.condition())
        successor = self.extract_exact_text(ctx.expression())
        gin = self.visit(ctx.statement())
        return embed_in_for_structure(gin, init, condition, successor)

    def visitStatementseq1(self, ctx: CPP14_v2Parser.Statementseq1Context):
        return self.visit(ctx.statement())

    def visitStatementseq2(self, ctx: CPP14_v2Parser.Statementseq2Context):
        gin1 = self.visit(ctx.statementseq())
        gin2 = self.visit(ctx.statement())
        return concat_graphs(gin1, gin2)

    def visitExpressionstatement(self, ctx: CPP14_v2Parser.ExpressionstatementContext):
        expression_text = self.extract_exact_text(ctx)
        return build_single_node_graph(expression_text)

    def visitDeclarationstatement(self, ctx: CPP14_v2Parser.DeclarationstatementContext):
        declaration_text = self.extract_exact_text(ctx)
        return build_single_node_graph(declaration_text)
