class StringifiedAspect:
    def __init__(self, *tokens: str):
        self.aspect = "\n".join(tokens)

    def __str__(self):
        pass
