from typing import List

from customizer.aspect.stringified_aspect import StringifiedAspect
from customizer.aspect_container.abstract_aspect import AbstractAspect
from customizer.aspect_container.basic_aspect import BasicAspect
from customizer.aspect_container.constructor import Constructor
from customizer.method.method import Method


class ConcreteAspect(BasicAspect):
    def __init__(
        self,
        name: str,
        super_aspect_name: str,
        super_constructor: Constructor,
        methods: List[Method],
        aspects: List[StringifiedAspect],
    ):
        """
        Args:
            name (str): アスペクト名
            super_aspect_name (str): 継承アスペクト名
            super_constructor (Constructor): 継承アスペクトのコンストラクタ
            methods (list[Method]): メソッドのリスト
            aspects (list[StringifiedAspect]): アスペクトのリスト
        """
        self.name = name
        self.super_aspect_name: str = super_aspect_name
        self.super = super_constructor
        self.methods: List[Method] = methods
        self.aspects: List[StringifiedAspect] = aspects

    def inherit(self, super_aspect: AbstractAspect):
        super_aspect.bind_token_params(self.super)
        super_aspect.override_methods(self.methods)
        return super_aspect
