from typing import List, Union

from customizer.aspect.aspect import Aspect
from customizer.aspect_container.pure_aspect import PureAspect
from customizer.aspect_container.super import Super
from customizer.method.method import Method


class ConcreteAspect(PureAspect):
    def __init__(
        self,
        name,
        super_aspect_name,
        super_constructor: Super,
        methods: Union[List[Method], Method],
        aspects: Union[List[Aspect], Aspect],
    ):
        """
        Args:
            name (str): アスペクト名
            super_aspect_name (str): 継承アスペクト名
            super_constructor (Super): 継承アスペクトのコンストラクタ
            methods (list[Method]): メソッドのリスト
            aspects (list[(Aspect)]): アスペクトのリスト
        """
        super().__init__(name, methods, aspects)
        self.super_aspect_name: str = super_aspect_name
        self.super = super_constructor

    def inherit(self, super_aspect):
        return PureAspect(self.name, self.methods, self.aspects)

    def get(self):
        return self.aspects
