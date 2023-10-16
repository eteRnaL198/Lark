from typing import List

from base.lang_processor.func_def_visitor import FuncDefVisitor
from customizer.func_signature import FuncSignature
from customizer.pointcut.pointcut import Pointcut


class Execution(Pointcut):
    """Executionポイントカット"""

    def __init__(self, signature):
        """
        Args:
            signature (FuncSignature): 関数のシグネチャ
        """
        self.visitor = FuncDefVisitor()
        self.func_signature: FuncSignature = signature

    def search(self, ast) -> List[int]:
        """ポイントカットにマッチするジョインポイントを探索
        Args:
            ast (c_ast.FileAST): 構文木
        Returns:
            joinpoints (list[int]): ジョインポイント(行目)のリスト
        """
        self.visitor.visit(ast)
        joinpoints: List[int] = []
        for func in self.visitor.functions:
            if func.name == self.func_signature.name:
                joinpoints.append(func.line)
        # TODO マッチしなかった場合の処理
        return joinpoints
