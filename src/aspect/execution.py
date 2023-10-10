from base.func_def_visitor import FuncDefVisitor


class Execution:
    def __init__(self):
        self.visitor = FuncDefVisitor()

    def visit(self, ast):
        self.visitor.visit(ast)
