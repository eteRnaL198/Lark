from pycparser import c_ast


class FuncDefVisitor(c_ast.NodeVisitor):
    def visit_FuncDef(self, node):
        print("FuncDef: ", node.decl.name, node.decl.coord)
        return node.decl.name
        # self.generic_visit(node)

    # def visit_FuncDecl(self, node):
    #     print("FuncDecl: ", node.args, node.coord)

    # def visit_FuncCall(self, node):
    #     print("FuncCall: ", node.name.name, node.name.coord)
