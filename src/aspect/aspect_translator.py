from lark import Transformer

from aspect.aspect import Aspect


class AspectTranslator(Transformer):
    def aspect(self, tree):
        advice, pointcut, body = tree[0], tree[1], tree[2]
        print(
            "aspect)",
            "\n\tadvice:",
            advice,
            "\n\tpointcut:",
            pointcut,
            "\n\tbody:",
            body,
        )
        return Aspect(advice, pointcut, body)

    ######################## advice ########################
    def advice(self, tree):
        return tree[0]

    def before(self, tree):
        # TODO return Before()
        return "before"

    def after(self, tree):
        return "after"

    def around(self, tree):
        return "around"

    def body(self, tree):
        return [t.value for t in tree]

    ######################## pointcut ########################
    def pointcut(self, tree):
        print("pointcut:", *tree)
        return [*tree]

    def primitive_pointcut(self, tree):
        return tree[0]

    def call(self, tree):
        return {"name": "call", "arg": tree[0]}

    def execution(self, tree):
        return {"name": "execution", "arg": tree[0]}

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
        return {"type": str(tree[0]), "name": tree[1], "args": tree[2]}

    def func_args(self, tree):
        """
        return:
            e.g.) ['int', 'float', 'char']
        """
        return [str(t) for t in tree]
