class StringifiedAspect:
    def __init__(self, *tokens: str):
        """
        Args:
            tokens (str): アスペクトを定義する文字列
                e.g.) "after():", "execution() {", "...", "}"
        """
        self.data = "\n".join(tokens)

    def __str__(self):
        return self.data

    def replace(self, current, new):
        self.data = self.data.replace(current, new)
