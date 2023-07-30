from lark import Transformer


class ToMyLang(Transformer):
    def __init__(self):
        self.variables = {}

    # Terminal Symbols
    def number(self, tree):
        token = tree[0].value
        return float(token)

    def var(self, tree):
        token = tree[0].value
        return str(token)

    # Nonterminal Symbols
    def assign(self, tree):
        print(tree)
        name = tree[0]
        value = tree[1]
        self.variables[name] = value

    def display(self, tree):
        target = tree[0]
        if type(target) == str:
            target = self.variables[target]
        elif type(target) == int:
            target = float(target)
        print("表示:", target)

    def add(self, tree):
        print(tree)
        left = float(tree[0])
        # right = float(tree[1].value)
        # print(left + right)
        print(left)
