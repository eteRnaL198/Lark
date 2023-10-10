from aspect.func_signature import FuncSignature
from aspect.pointcut import Pointcut
from base.func_def_visitor import FuncDefVisitor


class Execution(Pointcut):
    """Executionポイントカット"""

    def __init__(self, signature):
        """
        Args:
            signature (FuncSignature): 関数のシグネチャ
        """
        self.visitor = FuncDefVisitor()
        self.func_signature: FuncSignature = signature

    def search(self, ast):
        """ポイントカットにマッチするジョインポイントを探索
        Args:
            ast (c_ast.FileAST): 構文木
        Returns:
            joinpoints (list[int]): ジョインポイント(行目)のリスト
        """
        self.visitor.visit(ast)
        joinpoints: list[int] = []
        for func in self.visitor.functions:
            if func.name == self.func_signature.name:
                joinpoints.append(func.line)
        return joinpoints
