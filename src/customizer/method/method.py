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
