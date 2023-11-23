from typing import List

from src.base.visitor.variable_visitor import VarVisitor
from src.customizer.joinpoint.joinpoint import Joinpoint
from src.customizer.pointcut.pointcut import Pointcut


class Set(Pointcut):
    """Setポイントカット"""

    def __init__(self, name: str):
        """
        Args:
          name(str): 変数名
        """
        self.name = name

    def search(self, ast) -> List[Joinpoint]:
        """ポイントカットにマッチするジョインポイントを探索
        Args:
            ast (c_ast.FileAST): 構文木
        Returns:
            joinpoints (list[Joinopint]): ジョインポイントのリスト
        """
        Variables = (VarVisitor()).visit(ast)
        joinpoints: List[Joinpoint] = []
        for var in Variables:
            if var.name != self.name:
                continue
            for l in var.assigned_lines:
                before = l - 1
                after = l
                whole = (before, after)
                joinpoints.append(Joinpoint(before, [after], whole))
        return joinpoints
