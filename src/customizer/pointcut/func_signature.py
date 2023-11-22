from util.list_util import are_lists_equal


class FuncSignature:
    """関数シグネチャ"""

    def __init__(self, type, name, args):
        """
        Args:
            type (str): 関数の戻り値の型
            name (str): 関数名
            args (list[str]): 引数の型のリスト
        """
        self.type: str = type
        self.name: str = name
        self.args: list[str] = args

    def __repr__(self):
        return "{} {}({})".format(self.type, self.name, ", ".join(self.args))

    def __eq__(self, other):
        if not type(other) == FuncSignature:
            return False
        return self.name == other.name and are_lists_equal(self.args, other.args)
