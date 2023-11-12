class AbstractMethod:
    """メソッド"""

    def __init__(self, type, name, args):
        """
        Args:
            type (str): メソッドの戻り値の型
            name (str): メソッド名
            args (list[str]): 引数の型のリスト
        """
        self.type: str = type
        self.name: str = name
        self.args: list[str] = args
