class StringifiedAspect:
    def __init__(self, *tokens: str):
        """
        Args:
            tokens (str): アスペクトを定義する文字列
                e.g.) "after():", "execution() {", "...", "}"
        """
        self.aspect = "\n".join(tokens)

    def replace(self, current, new):
        self.aspect = self.aspect.replace(current, new)
