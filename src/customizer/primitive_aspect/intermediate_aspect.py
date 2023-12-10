from typing import List

from src.customizer.method.method import Method
from src.customizer.pointcut.func_signature import FuncSignature
from src.customizer.primitive_aspect.abstract_aspect import AbstractAspect
from src.customizer.primitive_aspect.concrete_aspect import ConcreteAspect
from src.customizer.primitive_aspect.constructor import Constructor
from src.customizer.primitive_aspect.primitive_aspect import PrimitiveAspect
from src.customizer.primitive_aspect.super_constructor import SuperConstructor


class IntermediateAspect(PrimitiveAspect):
    def __init__(
        self,
        name: str,
        super_aspect_name: str,
        super_constructor: SuperConstructor,
        constructor: Constructor,
        abstract_methods: List[FuncSignature],
        methods: List[Method],
        aspects,
    ):
        """
        Args:
            name (str): アスペクト名
            super_aspect_name (str): 継承アスペクト名
            super_constructor (Constructor): 継承アスペクトのコンストラクタ
            constructor (Constructor): コンストラクタ
            abstract_methods (list[AbstractMethod]): 抽象メソッドのリスト
            methods (list[Method]): メソッドのリスト
            aspects (list[StringifiedAspect]): アスペクトのリスト
        """
        self.super_aspect_name = super_aspect_name
        self.constructor = constructor
        self.super_constructor = super_constructor
        self.abstract_methods: List[FuncSignature] = abstract_methods

        super().__init__(name, methods, aspects)
        self.abstract_aspect = AbstractAspect(
            self.name,
            self.constructor,
            self.abstract_methods,
            self.methods,
            self.aspects,
        )
        self.concrete_aspect = ConcreteAspect(
            self.name,
            self.super_aspect_name,
            self.super_constructor,
            self.methods,
            self.aspects,
        )

    def bind_token_params(self, sub_constructor: SuperConstructor):
        self.abstract_aspect.bind_token_params(sub_constructor)

    def override_methods(self, other_methods: List[Method]):
        self.abstract_aspect.override_methods(other_methods)

    def inherit(self, aspect):  # 型を指定すると循環importになる
        """
        Args:
            aspect (Union[AbstractAspect, IntermediateAspect]): 継承元アスペクト
        Returns:
            super_aspect (AbstractAspect): 継承完了後のアスペクト
        """

        return self.concrete_aspect.inherit(aspect)
