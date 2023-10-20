from abc import ABCMeta, abstractmethod
from typing import List

from pycparser import c_ast

from customizer.joinpoint.joinpoint import Joinpoint


class Pointcut(metaclass=ABCMeta):
    @abstractmethod
    def search(self, ast: c_ast.FileAST) -> List[Joinpoint]:
        # TODO 返り値の型指定できる？
        """ポイントカットにマッチするジョインポイントを探索"""
        raise NotImplementedError()
