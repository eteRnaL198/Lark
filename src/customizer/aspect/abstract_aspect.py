from typing import List, Union

from customizer.aspect.abstract_method import AbstractMethod
from customizer.aspect.aspect import Aspect
from customizer.aspect.constructor import Constructor
from customizer.aspect.method import Method


class AbstractAspect:
    def __init__(
        self,
        name,
        constructor: Constructor,
        abstract_methods: List[AbstractMethod],
        methods: List[Method],
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
        self.name: str = name
        self.constructor = constructor
        self.abstract_methods: List[AbstractMethod] = (
            abstract_methods
            if isinstance(abstract_methods, list)
            else [abstract_methods]
        )
        self.methods: List[Method] = methods if isinstance(methods, list) else [methods]
        self.aspects: List[Aspect] = aspects if isinstance(aspects, list) else [aspects]
