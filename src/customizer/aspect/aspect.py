from typing import List

from pycparser import c_ast

from customizer.pointcut.pointcut import Pointcut


class Aspect:
    def __init__(self, type, pointcut, body):
        """
        Args:
            type (str): アドバイスの種類
            pointcut (List[Pointcut]): ポイントカット
            body (str): アドバイスの内容
        """
        self.advice_type = type
        self.pointcut: List[Pointcut] = pointcut
        self.advice_body: List[str] = body

    def get_joinpoints(self, ast: c_ast.FileAST) -> List[int]:
        """
        Args:
            ast (c_ast.FileAST): 構文木
        Returns:
            joinpoints (List[int]): ジョインポイント(行目)のリスト
        """
        joinpoints: List[int] = []
        for pt in self.pointcut:
            joinpoints.append(*pt.search(ast))
        return joinpoints
