class Method:
    """メソッド"""

    def __init__(self, type, name, args, body):
        """
        Args:
            type (str): メソッドの戻り値の型
            name (str): メソッド名
            args (list[str]): 引数の型のリスト
            body (list[str]): メソッドの中身
        """
        self.type: str = type
        self.name: str = name
        self.args: list[str] = args
        self.body: list[str] = body
