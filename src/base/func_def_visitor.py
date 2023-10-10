from pycparser import c_ast

from base.function import Function


class FuncDefVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.functions: list[Function] = []

    def visit_FuncDef(self, node):
        """関数の定義を取得
        Note:
            メソッドの命名規則: visit_XXX
        """
        self.__add(Function(node.decl.name, node.decl.coord.line))
        # self.generic_visit(node)

    # def visit_FuncDecl(self, node):
    #     print("FuncDecl: ", node.args, node.coord)

    # def visit_FuncCall(self, node):
    #     print("FuncCall: ", node.name.name, node.name.coord)

    def __add(self, func):
        return self.functions.append(func)
