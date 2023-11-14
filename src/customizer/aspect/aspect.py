from typing import List

from pycparser import c_ast

from customizer.aspect.advice import Advice
from customizer.joinpoint.joinpoint import Joinpoint
from customizer.pointcut.pointcut import Pointcut
from customizer.src import Src


class Aspect:
    def __init__(self, pointcut: List[Pointcut], advice: Advice):
        """
        Args:
            pointcut (List[Pointcut]): ポイントカット
            advice (Advice): アドバイス
        """
        self.pointcut = pointcut
        self.advice = advice

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
        joinpoints = self.__get_joinpoints(ast)
        if len(joinpoints) == 0:
            return
        for joinpoint in joinpoints:
            if self.advice.type == "before":
                line = joinpoint.get_before()
                src.insert(line, self.advice.body)
                continue
            if self.advice.type == "after":
                for line in joinpoint.get_after():
                    src.insert(line, self.advice.body)
                continue
            if self.advice.type == "around":
                start, end = joinpoint.get_around()
                src.replace(start, end, self.advice.body)
