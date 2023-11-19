from typing import List

from customizer.aspect.stringified_aspect import StringifiedAspect
from customizer.aspect_container.constructor import Constructor
from customizer.method.method import Method
from customizer.pointcut.func_signature import FuncSignature


class AbstractAspect:
    def __init__(
        self,
        name,
        constructor: Constructor,
        abstract_methods: List[FuncSignature],
        methods: List[Method],
        aspects: List[StringifiedAspect],
    ):
        """
        Args:
            name (str): アスペクト名
            constructor (Constructor): コンストラクタ
            abstract_methods (list[AbstractMethod]): 抽象メソッドのリスト
        """
        self.name = name
        self.constructor = constructor
        self.abstract_methods: List[FuncSignature] = (
            abstract_methods
            if isinstance(abstract_methods, list)
            else [abstract_methods]
        )
        self.methods: List[Method] = methods if isinstance(methods, list) else [methods]
        self.aspects: List[StringifiedAspect] = (
            aspects if isinstance(aspects, list) else [aspects]
        )

    def bind_token_params(self, actual_args: List[str]):
        if len(self.constructor.args) != len(actual_args):
            raise Exception(
                "Number of arguments provided does not match the number of constructor arguments. given: {}, expected: {}".format(
                    len(actual_args), len(self.constructor.args)
                )
            )
        for i in range(len(actual_args)):
            for method in self.methods:
                method.replace("this." + self.constructor.args[i], actual_args[i])
            for aspect in self.aspects:
                aspect.replace("this." + self.constructor.args[i], actual_args[i])

    def bind_abstract_method(self):
        pass
