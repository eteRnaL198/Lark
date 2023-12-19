import copy
from typing import List

from src.customizer.method.method import Method
from src.customizer.primitive_aspect.primitive_aspect import PrimitiveAspect
from src.customizer.primitive_aspect.stringified_aspect import StringifiedAspect
from src.customizer.primitive_aspect.super_constructor import SuperConstructor


class ConcreteAspect(PrimitiveAspect):
    def __init__(
        self,
        name: str,
        super_aspect_name: str,
        super_constructor: SuperConstructor,
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

    def inherit(self, aspect):  # 型を指定すると循環importになる
        """
        Args:
            aspect (Union[AbstractAspect, IntermediateAspect]): 継承元アスペクト
        Returns:
            super_aspect (AbstractAspect): 継承完了後のアスペクト
        """
        super_aspect = copy.deepcopy(aspect)
        super_aspect.bind_token_params(self.super)
        super_aspect.override_methods(self.methods)
        for a in self.aspects:
            super_aspect.add_aspect(a)
        super_aspect.set_name(self.name)
        return super_aspect
