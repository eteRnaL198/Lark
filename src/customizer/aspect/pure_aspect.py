from typing import List, Union

from pycparser import c_ast

from customizer.aspect.aspect import Aspect
from customizer.src import Src


class PureAspect:
    def __init__(self, name, aspects: Union[List[Aspect], Aspect]):
        """
        Args:
            name (str): アスペクト名
            aspects list[(Aspect)]: アスペクトのリスト
        """
        self.name: str = name
        self.aspects: List[Aspect] = aspects if isinstance(aspects, list) else [aspects]

    def weave(self, src: Src, ast: c_ast.FileAST):
        for aspect in self.aspects:
            src = aspect.weave(src, ast)
        return src
