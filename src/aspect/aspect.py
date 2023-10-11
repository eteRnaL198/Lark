from pycparser import c_ast

from aspect.pointcut import Pointcut


class Aspect:
    def __init__(self, type, pointcut, body):
        """
        Args:
            type (str): アドバイスの種類
            pointcut (list[Pointcut]): ポイントカット
            body (str): アドバイスの内容
        """
        self.advice_type = type
        self.pointcut: list[Pointcut] = pointcut
        self.advice_body = body

    def weave(self, ast: c_ast.FileAST):
        """
        Args:
            ast (c_ast.FileAST): 構文木
        Returns:
            joinpoints (list[[int]]): ジョインポイント(行目)の二次元リスト
            # TODO ジョインポイントの形式整理する
            body (str): アドバイスの内容
        """
        joinpoints: list[int] = []
        for pt in self.pointcut:
            joinpoints.append(pt.search(ast))
        return {"lines": joinpoints, "body": self.advice_body}
