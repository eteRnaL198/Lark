class SuperConstructor:
    """スーパーコンストラクタ"""

    def __init__(self, args):
        self.args: list[str] = args

    def replace(self, current: str, new: str):
        for i in range(len(self.args)):
            self.args[i] = self.args[i].replace(current, new)
