from typing import List, Union

from customizer.aspect.aspect import Aspect
from customizer.aspect_container.pure_aspect import PureAspect
from customizer.aspect_container.super import Super
from customizer.method.method import Method


class ConcreteAspect:
    def __init__(
        self,
        name,
        abstract_name,
        super: Super,
        methods: Union[List[Method], Method],
        aspects: Union[List[Aspect], Aspect],
    ):
        """
        Args:
            name (str): アスペクト名
            abstract_name (str): 抽象アスペクト名
            super (Super): スーパーアスペクト
            methods (list[Method]): メソッドのリスト
            aspects list[(Aspect)]: アスペクトのリスト
        """
        self.name: str = name
        self.abstract_aspect_name: str = abstract_name
        self.super = super
        self.methods: List[Method] = methods if isinstance(methods, list) else [methods]
        self.aspects: List[Aspect] = aspects if isinstance(aspects, list) else [aspects]

    def inherit(self):
        return PureAspect(self.name, self.methods, self.aspects)

    def get(self):
        return self.aspects
