from typing import List

from customizer.primitive_aspect.stringified_aspect import StringifiedAspect
from customizer.method.method import Method


class PrimitiveAspect:
    def __init__(
        self,
        name: str,
        methods: List[Method],
        aspects: List[StringifiedAspect],
    ):
        """
        Args:
            name (str): アスペクト名
            methods (list[Method]): メソッドのリスト
            aspects (list[StringifiedAspect]): アスペクトのリスト
        """
        self.name = name
        self.methods: List[Method] = methods
        self.aspects: List[StringifiedAspect] = aspects

    def stringify(self) -> str:
        return "\n".join(
            [
                "aspect {} {{".format(self.name),
                "\n".join([str(m) for m in self.methods]),
                "\n".join([str(a) for a in self.aspects]),
                "}",
            ]
        )
