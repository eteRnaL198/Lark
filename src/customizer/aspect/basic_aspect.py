from typing import List, Union

from src.customizer.aspect.aspect import Aspect
from src.customizer.method.method import Method


class BasicAspect:
    def __init__(
        self,
        name,
        methods: Union[List[Method], Method],
        aspects: Union[List[Aspect], Aspect],
    ):
        """
        Args:
            name (str): アスペクト名
            methods (list[Method]): メソッドのリスト
            aspects (list[(Aspect)]): アスペクトのリスト
        """
        self.name: str = name
        self.methods: List[Method] = methods if isinstance(methods, list) else [methods]
        self.aspects: List[Aspect] = aspects if isinstance(aspects, list) else [aspects]

    def __bind_methods(self):
        for method in self.methods:
            body = "{\n" + method.body + "\n}" if method.body else ""
            called_format = method.get_called_format()
            for aspect in self.aspects:
                aspect.advice.replace(called_format, body)
            for method in self.methods:
                method.replace(called_format, body)
        for aspect in self.aspects:
            if "this." in aspect.advice.body:
                raise Exception(
                    "The following methods were not binded: {}".format(aspect.advice)
                )

    def get_aspects(self):
        self.__bind_methods()
        return self.aspects
