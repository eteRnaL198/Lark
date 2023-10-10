class Function:
    """関数の値オブジェクト
    Args:
        name (str): 関数名
        line (int): 関数が定義されている行
    """

    def __init__(self, name, line):
        self.name = name
        self.line = line
