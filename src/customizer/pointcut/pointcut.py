from abc import ABCMeta, abstractmethod
from typing import List

from pycparser import c_ast


class Pointcut(metaclass=ABCMeta):
    @abstractmethod
    def search(self, ast: c_ast.FileAST) -> List[int]:
        # TODO 返り値の型指定できる？
        """ポイントカットにマッチするジョインポイントを探索"""
        raise NotImplementedError()
