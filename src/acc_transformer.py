from lark import Transformer


class AccTransformer(Transformer):
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

    # advice
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

    # pointcut
    def pointcut(self, tree):
        print("pointcut:", tree[0].children)
        return tree

    def call(self, tree):
        # print("call:", tree[0].value)
        return ("call:", tree)

    def function_signature(self, tree):
        return tree[0] + " " + tree[1] + "(" + tree[2] + ")"
