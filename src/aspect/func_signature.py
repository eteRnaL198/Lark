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
