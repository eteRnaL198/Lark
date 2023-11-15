from lark import Transformer


class InheritanceTransformer(Transformer):
    def constructor(self, tree):
        print("constructor", tree)

    def abstract_method(self, tree):
        print("abstract_method", tree)

    def block(self, tree):
        print("block", tree)
