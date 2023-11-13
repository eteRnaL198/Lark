from typing import List, Union

from customizer.aspect.aspect import Aspect
from customizer.aspect_container.pure_aspect import PureAspect
from customizer.aspect_container.super import Super
from customizer.method.method import Method


class ConcreteAspect:
    def __init__(
        self,
        name,
        super_aspect_name,
        super: Super,
        methods: Union[List[Method], Method],
        aspects: Union[List[Aspect], Aspect],
    ):
        """
        Args:
            name (str): アスペクト名
            super_aspect_name (str): 継承アスペクト名
            super (Super): スーパーコンストラクタ
            methods (list[Method]): メソッドのリスト
            aspects list[(Aspect)]: アスペクトのリスト
        """
        self.name: str = name
        self.super_aspect_name: str = super_aspect_name
        self.super = super
        self.methods: List[Method] = methods if isinstance(methods, list) else [methods]
        self.aspects: List[Aspect] = aspects if isinstance(aspects, list) else [aspects]

    def inherit(self, super_aspect):
        return PureAspect(self.name, self.methods, self.aspects)

    def get(self):
        return self.aspects
