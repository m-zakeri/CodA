# in the name of allah

from .CPP14Listener import CPP14Listener
from .CPP14Parser import  CPP14Parser
from .CPP14Lexer import CPP14Lexer as lexer

class CFGListener(CPP14Listener):
    block_dict = {}
    block_name = 0
    block_start = 0
    block_stop = 0
    domain_name = ""
    junction_stack = []
    decision_stack = []
    def addNode(self):
        self.block_dict[self.domain_name]["Nodes"].append((self.block_name, self.block_start, self.block_stop))

    def addJunctionEdge(self):
        source_node = self.junction_stack.pop()
        dest_node = self.block_name
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addDecisionEdge(self):
        source_node = self.decision_stack.pop()
        dest_node = self.block_name
        self.block_dict[self.domain_name]["Edges"].append((source_node, dest_node))
        self.CFG_file.write(str(source_node) + ' ' + str(dest_node) + '\n')

    def addJunc(self):
        self.junction_stack.append(self.block_name)

    def addDecision(self):
        self.decision_stack.append(self.block_name)

    def enterFunctiondefinition(self, ctx:CPP14Parser.FunctiondefinitionContext):
        self.block_name = 1
        self.block_start = ctx.functionbody().start.line
        self.domain_name = ctx.declarator().getText().split('(')[0]
        self.block_dict[self.domain_name] = {
            "Nodes" : [],
            "Edges" : []
        }
        self.CFG_file = open('CFGS/' + self.domain_name + '.txt' , 'w')
        self.CFG_file.write("initial nodes: " +str(self.block_name) + '\n')

    def enterSelectionstatement(self, ctx:CPP14Parser.SelectionstatementContext):
        self.block_stop = ctx.start.line
        self.addNode()
        if self.block_name in self.junction_stack:
            self.junction_stack.remove(self.block_name)
        if ctx.getToken(lexer.Else,0) is None:
            self.addDecision()
            self.addJunc()
        else:
            self.addDecision()
            self.addDecision()

    def enterStatement(self, ctx:CPP14Parser.StatementContext):
        if isinstance(ctx.parentCtx,CPP14Parser.SelectionstatementContext):
            self.block_name += 1
            self.addDecisionEdge()
            self.block_start = ctx.start.line
            self.addJunc()

    def exitStatement(self, ctx:CPP14Parser.StatementContext):
        if isinstance(ctx.parentCtx, CPP14Parser.SelectionstatementContext):
            self.block_stop = ctx.stop.line
            self.addNode()


    def exitSelectionstatement(self, ctx:CPP14Parser.SelectionstatementContext):
        self.block_name += 1
        self.block_start = ctx.stop.line
        self.addJunctionEdge()
        self.addJunctionEdge()
        self.addJunc()

    def exitFunctiondefinition(self, ctx:CPP14Parser.FunctiondefinitionContext):
        self.block_stop = ctx.stop.line
        self.addNode()
        self.CFG_file.write("final nodes: " + str(self.block_name) + '\n')
        print(self.block_dict)
        self.CFG_file.close()

    def enterDeclarator(self, ctx:CPP14Parser.DeclaratorContext):
        pass
        #print(ctx.parentCtx.parentCtx.parentCtx.getText())
