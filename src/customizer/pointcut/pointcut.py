from abc import ABCMeta, abstractmethod
from typing import List

from pycparser import c_ast

from customizer.joinpoint.joinpoint import Joinpoint


class Pointcut(metaclass=ABCMeta):
    @abstractmethod
    def search(self, ast: c_ast.FileAST) -> List[Joinpoint]:
        """ポイントカットにマッチするジョインポイントを探索"""
        raise NotImplementedError()
