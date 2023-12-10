from src.customizer.primitive_aspect.super_constructor import SuperConstructor


class Constructor(SuperConstructor):
    """コンストラクタ"""

    def __init__(self, args):
        super().__init__(args)

    def get_called_format(self, i):
        return "this." + self.args[i]
