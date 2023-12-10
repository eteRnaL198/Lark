from pycparser.c_ast import NodeVisitor

from src.base.visitor.variable import Variable


class VarVisitor(NodeVisitor):
    def __init__(self):
        self.vars: dict[str, list[int]] = {}

    def visit(self, node):
        super().visit(node)
        return [Variable(k, v) for k, v in self.vars.items()]

    def visit_Assignment(self, node):
        """代入文を取得
        Note:
            メソッドの命名規則: visit_XXX
        """
        try:
            self.__add(node.lvalue.name, node.coord.line)
        except AttributeError:
            pass

    def __add(self, name: str, num: int):
        if name not in self.vars:
            self.vars[name] = [num]
            return
        self.vars[name].append(num)
