from antlr4 import CommonTokenStream

from src.antlr.gen.CPP14_v2Parser import CPP14_v2Parser
from src.antlr.gen.CPP14_v2Visitor import CPP14_v2Visitor
from src.cfg_extractor.lang_structures import (embed_in_function_structure, embed_in_do_while_structure,
                                               embed_in_for_structure,
                                               embed_in_switch_structure, embed_in_if_structure,
                                               embed_in_if_else_structure,
                                               embed_in_while_structure, embed_in_try_catch_structure)
from src.graph.utils import (build_single_node_graph, concat_graphs, build_isolated_node_graph)


class CFGExtractorVisitor(CPP14_v2Visitor):
    def __init__(self, common_token_stream: CommonTokenStream):
        self.token_stream = common_token_stream
        self.functions = {}

    def visitFunctiondefinition(self, ctx: CPP14_v2Parser.FunctiondefinitionContext):
        gin = self.visit(ctx.functionbody())
        self.functions[ctx.declarator()] = embed_in_function_structure(gin)

    def visitCompoundstatement(self, ctx: CPP14_v2Parser.CompoundstatementContext):
        return self.visit(ctx.statementseq())

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

    def visitSelectionstatement3(self, ctx: CPP14_v2Parser.Selectionstatement3Context):
        condition = ctx.condition()
        gin = self.visit(ctx.statement())
        return embed_in_switch_structure(gin, condition)

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

    def visitTryblock(self, ctx: CPP14_v2Parser.TryblockContext):
        g_body = self.visit(ctx.compoundstatement())
        g_handler_seq = self.visit(ctx.handlerseq())
        return embed_in_try_catch_structure(g_body, g_handler_seq)

    def visitHandlerseq(self, ctx: CPP14_v2Parser.HandlerseqContext):
        g_handler = self.visit(ctx.handler())
        g = g_handler.copy()
        if ctx.handlerseq():
            g_handler_seq = self.visit(ctx.handlerseq())
            g = concat_graphs(g, g_handler_seq)
        return g

    def visitHandler(self, ctx: CPP14_v2Parser.HandlerContext):
        return self.visit(ctx.compoundstatement())

    def visitThrowexpression(self, ctx: CPP14_v2Parser.ThrowexpressionContext):
        return build_single_node_graph(ctx)

    def visitJumpstatement1(self, ctx: CPP14_v2Parser.Jumpstatement1Context):
        return build_single_node_graph(ctx)

    def visitJumpstatement2(self, ctx: CPP14_v2Parser.Jumpstatement2Context):
        return build_single_node_graph(ctx)

    def visitJumpstatement3(self, ctx: CPP14_v2Parser.Jumpstatement3Context):
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

    def visitLabeledstatement2(self, ctx: CPP14_v2Parser.Labeledstatement2Context):
        return build_isolated_node_graph(ctx.constantexpression(), ctx.statement())

    def visitLabeledstatement3(self, ctx: CPP14_v2Parser.Labeledstatement3Context):
        return build_isolated_node_graph(ctx.Default(), ctx.statement())
