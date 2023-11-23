from typing import List

from pycparser.c_ast import NodeVisitor, ParamList

from src.base.visitor.function import Function


class FuncVisitor(NodeVisitor):
    def __init__(self):
        self.functions: list[Function] = []

    def visit(self, node):
        super().visit(node)
        return self.functions

    def visit_FuncDef(self, node):
        """関数の定義を取得
        Note:
            メソッドの命名規則: visit_XXX
        """
        params: List[str] = (
            [param.type.type.names[0] for param in node.decl.type.args]
            if type(node.decl.type.args) == ParamList
            else []
        )

        self.__add(
            Function(
                node.decl.name,
                params,
                node.decl.type.type.type.names[0],
                node.decl.coord.line,
                node.body.block_items[-1].coord.line,
            )
        )
        self.generic_visit(node)

    def visit_Return(self, node):
        self.functions[-1].add_return_lines(node.coord.line)
        self.generic_visit(node)

    def __add(self, func):
        return self.functions.append(func)
