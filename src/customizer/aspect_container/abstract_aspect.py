from typing import List, Union

from customizer.aspect.aspect import Aspect
from customizer.aspect_container.basic_aspect import BasicAspect
from customizer.aspect_container.constructor import Constructor
from customizer.method.abstract_method import AbstractMethod
from customizer.method.method import Method


class AbstractAspect(BasicAspect):
    def __init__(
        self,
        name,
        constructor: Constructor,
        abstract_methods: List[AbstractMethod],
        methods: Union[List[Method], Method],
        aspects: Union[List[Aspect], Aspect],
    ):
        """
        Args:
            name (str): アスペクト名
            constructor (Constructor): コンストラクタ
            abstract_methods (list[AbstractMethod]): 抽象メソッドのリスト
            methods (list[Method]): メソッドのリスト
            aspects list[(Aspect)]: アスペクトのリスト
        """
        super().__init__(name, methods, aspects)
        self.constructor = constructor
        self.abstract_methods: List[AbstractMethod] = (
            abstract_methods
            if isinstance(abstract_methods, list)
            else [abstract_methods]
        )

    def get(self):
        return self.aspects
