from lark import Token, Transformer

from customizer.method.method import Method
from customizer.pointcut.func_signature import FuncSignature


class BaseTransformer(Transformer):
    def start(self, tree):
        return tree

    ######################## method ########################
    def method(self, tree):
        """
        e.g.) tree[FuncSignature, list[str]]
        """
        signature, body = tree[0], "\n".join(tree[1])
        return Method(signature, body)

    ######################## func ########################

    def func_signature(self, tree):
        """
        e.g.) tree[int, foo, char] -> int foo(char)
        """
        type, name, args = str(tree[0]), tree[1], tree[2]
        return FuncSignature(type, name, args)

    def func_name(self, tree):
        """
        e.g.) set_foo
        """
        return str(tree[0])

    def func_args(self, tree):
        """
        return:
            e.g.) ['int', 'float', 'char']
        """
        return [str(t) for t in tree]

    def body(self, tree):
        """
        e.g.)
        foo();
        if() {
            bar();
        }
        → [foo();, if() {, bar();, }]
        """
        lines: list[str] = []
        for t in tree:
            if isinstance(t, Token):
                lines.append(t.value)
            else:
                lines += t
        return lines

    def block(self, tree):
        """
        e.g.)
        if() {
            if() {
                foo();
            }
         }
        →[if(), {, if(), foo();, }, }]
        """
        lines: list[str] = []
        for t in tree:
            if isinstance(t, Token):
                lines.append(t.value)
            else:
                lines += t
        return lines
