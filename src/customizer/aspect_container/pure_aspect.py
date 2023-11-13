from typing import List, Union

from customizer.aspect.aspect import Aspect
from customizer.method.method import Method


class PureAspect:
    def __init__(
        self,
        name,
        methods: Union[List[Method], Method],
        aspects: Union[List[Aspect], Aspect],
    ):
        """
        Args:
            name (str): アスペクト名
            aspects list[(Aspect)]: アスペクトのリスト
        """
        self.name: str = name
        self.methods: List[Method] = methods if isinstance(methods, list) else [methods]
        self.aspects: List[Aspect] = aspects if isinstance(aspects, list) else [aspects]

    def get(self):
        return self.aspects
