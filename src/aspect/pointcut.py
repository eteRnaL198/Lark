from abc import ABCMeta, abstractmethod

from pycparser import c_ast


class Pointcut(metaclass=ABCMeta):
    @abstractmethod
    def search(self, ast: c_ast.FileAST):
        """ポイントカットにマッチするジョインポイントを探索"""
        raise NotImplementedError()
