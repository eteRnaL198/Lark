from lark import Transformer


class AccTransformer(Transformer):
    def __init__(self):
        self.variables = {}

    # advice
    def before(self, tree):
        print("before")

    def after(self, tree):
        pass

    def around(self, tree):
        pass

    def body(self, tree):
        print("body:", tree)

    # pointcut
    def pointcut(self, tree):
        return
