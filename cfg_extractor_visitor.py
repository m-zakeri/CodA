from enum import Enum, auto
from itertools import takewhile
import networkx as nx
from antlr4 import *

from gen.CPP14_v2Parser import CPP14_v2Parser
from gen.CPP14_v2Visitor import CPP14_v2Visitor


class StackAlphabet(Enum):
    IF_OPEN = auto()
    IF_CLOSE = auto()
    ELSE_OPEN = auto()
    ELSE_CLOSE = auto()


class CFGExtractorVisitor(CPP14_v2Visitor):
    def __init__(self, common_token_stream: CommonTokenStream):
        self.token_stream = common_token_stream
        self.stack = []
        self.cfg = nx.DiGraph()

    def extract_exact_text(self, rule: ParserRuleContext):
        return self.token_stream.getText(rule.start.tokenIndex, rule.stop.tokenIndex)

    def visitExpressionstatement(self, ctx:CPP14_v2Parser.ExpressionstatementContext):
        self.stack.append(self.extract_exact_text(ctx))
        return self.visitChildren(ctx)

    def visitDeclarationstatement(self, ctx: CPP14_v2Parser.DeclarationstatementContext):
        self.stack.append(self.extract_exact_text(ctx))
        return self.visitChildren(ctx)

    def visitSelectionstatement1(self, ctx: CPP14_v2Parser.Selectionstatement1Context):
        self.stack.append(f"condition({self.extract_exact_text(ctx.condition())})")
        if_body = ctx.statement()

        self.stack.append(StackAlphabet.IF_OPEN)
        self.visit(if_body)
        self.stack.append(StackAlphabet.IF_CLOSE)

    def visitSelectionstatement2(self, ctx: CPP14_v2Parser.Selectionstatement2Context):
        self.stack.append(f"condition({self.extract_exact_text(ctx.condition())})")
        if_body = ctx.statement(0)
        else_body = ctx.statement(1)

        self.stack.append(StackAlphabet.IF_OPEN)
        self.visit(if_body)
        self.stack.append(StackAlphabet.IF_CLOSE)

        self.stack.append(StackAlphabet.ELSE_OPEN)
        self.visit(else_body)
        self.stack.append(StackAlphabet.ELSE_CLOSE)


def partition_on_last(l: list, element):
    right = list(reversed(list(takewhile(lambda e: e != element, reversed(l)))))
    left = l[:-len(right)]
    return left, right
