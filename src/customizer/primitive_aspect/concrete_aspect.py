import copy
from typing import List

from customizer.method.method import Method
from customizer.primitive_aspect.abstract_aspect import AbstractAspect
from customizer.primitive_aspect.constructor import Constructor
from customizer.primitive_aspect.primitive_aspect import PrimitiveAspect
from customizer.primitive_aspect.stringified_aspect import StringifiedAspect


class ConcreteAspect(PrimitiveAspect):
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
        super().__init__(name, methods, aspects)
        self.super_aspect_name: str = super_aspect_name
        self.super = super_constructor

    def inherit(self, aspect: AbstractAspect):
        """
        Args:
            aspect (AbstractAspect): 継承アスペクト
        Returns:
            super_aspect (AbstractAspect): 継承完了後のアスペクト
        """
        super_aspect = copy.deepcopy(aspect)
        super_aspect.bind_token_params(self.super)
        super_aspect.override_methods(self.methods)
        return super_aspect
