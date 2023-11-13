from typing import List

from pycparser import c_ast

from customizer.joinpoint.joinpoint import Joinpoint
from customizer.pointcut.pointcut import Pointcut
from customizer.src import Src


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

    def __get_joinpoints(self, ast: c_ast.FileAST) -> List[Joinpoint]:
        """
        Args:
            ast (c_ast.FileAST): 構文木
        Returns:
            joinpoints (List[Joinpoint]): ジョインポイントのリスト
        """
        joinpoints: List[Joinpoint] = []
        for pt in self.pointcut:
            joinpoints += [*pt.search(ast)]
        return joinpoints

    def weave(self, src: Src, ast: c_ast.FileAST):
        advice = (
            ["/* Start of aspect */\n"] + self.advice_body + ["/* End of aspect */\n"]
        )
        joinpoints = self.__get_joinpoints(ast)
        if len(joinpoints) == 0:
            return
        for joinpoint in joinpoints:
            if self.advice_type == "before":
                line = joinpoint.get_before()
                src.insert(line, advice)
                continue
            if self.advice_type == "after":
                for line in joinpoint.get_after():
                    src.insert(line, advice)
                continue
            if self.advice_type == "around":
                start, end = joinpoint.get_around()
                src.replace(start, end, advice)
