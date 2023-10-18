from typing import List

from pycparser import c_ast

from customizer.pointcut.pointcut import Pointcut


class Aspect:
    def __init__(self, type: str, pointcut, body: List[str]):
        """
        Args:
            type (str): アドバイスの種類(before, after, around)
            pointcut (List[Pointcut]): ポイントカット
            body (str): アドバイスの内容
        """
        self.advice_type = type
        self.pointcut: List[Pointcut] = pointcut
        self.advice_body: List[str] = list(
            map(lambda l: (l + "\n"), body)
        )  # 解析時に無視された改行コードを追加

    def get_joinpoints(self, ast: c_ast.FileAST) -> List[int]:
        """
        Args:
            ast (c_ast.FileAST): 構文木
        Returns:
            joinpoints (List[int]): ジョインポイント(行目)のリスト
        """
        joinpoints: List[int] = []
        for pt in self.pointcut:
            joinpoints += [*pt.search(ast)]
        return joinpoints
