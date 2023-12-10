from typing import List

from src.customizer.method.method import Method
from src.customizer.pointcut.func_signature import FuncSignature
from src.customizer.primitive_aspect.constructor import Constructor
from src.customizer.primitive_aspect.primitive_aspect import PrimitiveAspect
from src.customizer.primitive_aspect.stringified_aspect import StringifiedAspect
from src.customizer.primitive_aspect.super_constructor import SuperConstructor


class AbstractAspect(PrimitiveAspect):
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
            methods (list[Method]): メソッドのリスト
            aspects (list[StringifiedAspect]): アスペクトのリスト
        """
        super().__init__(name, methods, aspects)
        self.constructor = constructor
        self.abstract_methods: List[FuncSignature] = abstract_methods

    def bind_token_params(self, sub_constructor: SuperConstructor):
        if len(self.constructor.args) != len(sub_constructor.args):
            raise Exception(
                "Number of arguments provided does not match the number of constructor arguments. given: {}, expected: {}".format(
                    len(sub_constructor.args), len(self.constructor.args)
                )
            )
        for i in range(len(sub_constructor.args)):
            for method in self.methods:
                method.replace(
                    self.constructor.get_called_format(i), sub_constructor.args[i]
                )
            for aspect in self.aspects:
                aspect.replace(
                    self.constructor.get_called_format(i), sub_constructor.args[i]
                )

    def override_methods(self, sub_methods: List[Method]):
        for method in sub_methods:
            if method in self.methods:
                self.methods.remove(method)
                self.methods.append(method)
            if method.signature in self.abstract_methods:
                self.abstract_methods.remove(method.signature)
                self.methods.append(method)
        if len(self.abstract_methods) != 0:
            raise Exception(
                "{} aspect is missing implementations for the following abstract methods: {}".format(
                    self.name, self.abstract_methods
                ),
            )
