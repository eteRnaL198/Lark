from customizer.pointcut.func_signature import FuncSignature


class Method:
    """メソッド"""

    def __init__(self, signature: FuncSignature, body: str):
        """
        Args:
            signature (FuncSignature): メソッドのシグネチャ
            body (str): メソッドの中身
        """
        self.signature: FuncSignature = signature
        self.body: str = body

    def __str__(self) -> str:
        return str(self.signature) + "{\n" + self.body + "\n}"

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Method):
            return False
        return self.signature == other.signature

    def replace(self, current, new):
        self.body.replace(current, new)

    def get_called_format(self):
        return "this." + self.signature.name + "();"
