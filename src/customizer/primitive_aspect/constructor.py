from src.customizer.primitive_aspect.super_constructor import SuperConstructor


class Constructor:
    """コンストラクタ"""

    def __init__(self, args):
        self.args: list[str] = args

    def get_called_format(self, i):
        return "this." + self.args[i]
