from lark import Transformer


class AccTranslator(Transformer):
    def __init__(self):
        self.aspects = []

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

    ######################## advice ########################
    def advice(self, tree):
        return tree[0]

    def before(self, tree):
        return "befeore"

    def after(self, tree):
        return "after"

    def around(self, tree):
        return "around"

    def body(self, tree):
        return [t.value for t in tree]

    ######################## pointcut ########################
    def pointcut(self, tree):
        return [*tree]

    def primitive_pointcut(self, tree):
        return tree[0]

    def call(self, tree):
        return {"name": "call", "arg": tree[0]}

    def infunc(self, tree):
        return {"name": "infunc", "arg": tree[0]}

    def function_name(self, tree):
        """
        e.g.) foo_bar
        """
        return str(tree[0])

    def function_signature(self, tree):
        """
        e.g.) tree[void, foo, int] -> void foo(int)
        """
        return tree[0] + " " + tree[1] + "(" + tree[2] + ")"
