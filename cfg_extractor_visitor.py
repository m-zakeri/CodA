from enum import Enum, auto
from itertools import takewhile

from antlr4 import *

from gen.CPP14_v2Parser import CPP14_v2Parser
from gen.CPP14_v2Visitor import CPP14_v2Visitor
from pprint import pprint as print


class StackAlphabet(Enum):
    IF_OPEN = auto()
    IF_CLOSE = auto()
    ELSE_OPEN = auto()
    ELSE_CLOSE = auto()


class CFGExtractorVisitor(CPP14_v2Visitor):
    def __init__(self, common_token_stream: CommonTokenStream):
        self.token_stream = common_token_stream
        self.stack = []
        self.packs = []

    def extract_exact_text(self, token: ParserRuleContext):
        return self.token_stream.getText(token.start.tokenIndex, token.stop.tokenIndex)

    def visitExpression(self, ctx: CPP14_v2Parser.ExpressionContext):
        self.stack.append(self.extract_exact_text(ctx))
        return self.visitChildren(ctx)

    def visitDeclarationstatement(self, ctx: CPP14_v2Parser.DeclarationstatementContext):
        self.stack.append(self.extract_exact_text(ctx))
        return self.visitChildren(ctx)

    def visitSelectionstatement2(self, ctx: CPP14_v2Parser.Selectionstatement2Context):
        if_body = ctx.statement(0)
        else_body = ctx.statement(1)

        if StackAlphabet.IF_OPEN not in self.stack:
            self.stack, right = partition_on_last(self.stack, StackAlphabet.IF_OPEN)
            self.packs.append((None, right))

        self.stack.append(StackAlphabet.IF_OPEN)
        self.visit(if_body)

        self.stack, right = partition_on_last(self.stack, StackAlphabet.IF_OPEN)
        self.packs.append((True, right))

        print("**** should be if open")
        print(self.stack)
        print(self.packs)
        print("**********************")

        self.stack.append(StackAlphabet.ELSE_OPEN)
        self.stack, right = partition_on_last(self.stack, StackAlphabet.ELSE_OPEN)
        self.packs.append(right)

        self.visit(else_body)

        self.stack, right = partition_on_last(self.stack, StackAlphabet.ELSE_OPEN)
        self.packs.append(right)

        self.stack.append(StackAlphabet.ELSE_CLOSE)


def partition_on_last(l: list, element):
    right = list(reversed(list(takewhile(lambda e: e != element, reversed(l)))))
    left = l[:-len(right)]
    return left, right
