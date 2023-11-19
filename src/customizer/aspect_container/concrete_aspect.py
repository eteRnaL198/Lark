import copy
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

    def stringify(self) -> str:
        return "\n".join(
            [
                "aspect {} {{".format(self.name),
                "\n".join([str(m) for m in self.methods]),
                "\n".join([str(a) for a in self.aspects]),
                "}",
            ]
        )
