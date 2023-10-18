from typing import List

from base.extractor.func_extractor import FuncExtractor
from customizer.func_signature import FuncSignature
from customizer.pointcut.pointcut import Pointcut


class Execution(Pointcut):
    """Executionポイントカット"""

    def __init__(self, signature):
        """
        Args:
            signature (FuncSignature): 関数のシグネチャ
        """
        self.func_signature: FuncSignature = signature

    def search(self, ast) -> List[int]:
        """ポイントカットにマッチするジョインポイントを探索
        Args:
            ast (c_ast.FileAST): 構文木
        Returns:
            joinpoints (list[int]): ジョインポイント(行目)のリスト
        """
        extractor = FuncExtractor()
        extractor.visit(ast)
        joinpoints: List[int] = []
        for func in extractor.functions:
            if func.name == self.func_signature.name:
                # beforeのとき
                # joinpoints.append(func.get_exec_start_line())
                # afterのとき
                joinpoints += [*func.get_exec_end_lines()]
        # TODO マッチしなかった場合の処理
        return joinpoints
