from customizer.pointcut.func_signature import FuncSignature


class Method:
    """メソッド"""

    def __init__(self, signature: FuncSignature, body):
        """
        Args:
            signature (FuncSignature): メソッドのシグネチャ
            body (list[str]): メソッドの中身
        """
        self.signature: FuncSignature = signature
        self.body: list[str] = body

    def replace(self, current, new):
        self.body = [line.replace(current, new) for line in self.body]
