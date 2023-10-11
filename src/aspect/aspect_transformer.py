from lark import Transformer

from aspect.aspect import Aspect
from aspect.execution import Execution
from aspect.func_signature import FuncSignature


class AspectTransformer(Transformer):
    def start(self, tree):
        return [*tree]

    def aspect(self, tree):
        advice_type, pointcut, advice_body = tree[0], tree[1], tree[2]
        return Aspect(advice_type, pointcut, advice_body)

    ######################## advice ########################
    def advice_type(self, tree):
        return tree[0]

    def before(self, tree):
        # TODO return Before()
        return "before"

    def after(self, tree):
        return "after"

    def around(self, tree):
        return "around"

    def advice_body(self, tree):
        return [t.value for t in tree]

    ######################## pointcut ########################
    def pointcut(self, tree):
        return [*tree]

    def primitive_pointcut(self, tree):
        return tree[0]

    def call(self, tree):
        return {"name": "call", "arg": tree[0]}

    def execution(self, tree):
        return Execution(tree[0])

    def infunc(self, tree):
        return {"name": "infunc", "arg": tree[0]}

    ######################## func ########################

    def func_name(self, tree):
        """
        e.g.) set_foo
        """
        return str(tree[0])

    def func_signature(self, tree):
        """
        e.g.) tree[int, foo, char] -> int foo(char)
        """
        type, name, args = str(tree[0]), tree[1], tree[2]
        return FuncSignature(type, name, args)

    def func_args(self, tree):
        """
        return:
            e.g.) ['int', 'float', 'char']
        """
        return [str(t) for t in tree]
