from typing import List, Union

from lark import Lark

from customizer.aspect.aspect import Aspect
from customizer.aspect_container.abstract_aspect import AbstractAspect
from customizer.aspect_container.basic_aspect import BasicAspect
from customizer.aspect_container.concrete_aspect import ConcreteAspect
from customizer.lang_processor.aspect_transformer import AspectTransformer
from util.file_util import generate_full_path


class AspectParser:
    """アスペクトファイルの構文解析器
    Args:
        filename (str): アスペクトファイルの相対パス
    """

    def __init__(self, filenames):
        self.filenames = filenames
        grammar_path = generate_full_path("src/customizer/lang_processor/acclang.lark")
        self.parser = Lark(
            grammar=open(grammar_path),
            parser="lalr",
            transformer=AspectTransformer(),
        )

    def parse(self) -> List[Aspect]:
        """構文解析を実行
        Returns:
            aspects (list[Aspect]): アスペクトのリスト
        """
        aspect_containers: List[Union[BasicAspect, ConcreteAspect, AbstractAspect]] = []
        for filename in self.filenames:
            src = open(generate_full_path(filename)).read()
            tmp: Union[
                List[Union[BasicAspect, ConcreteAspect, AbstractAspect]],
                Union[BasicAspect, ConcreteAspect, AbstractAspect],
            ] = self.parser.parse(
                src
            )  # type: ignore
            aspect_containers += tmp if isinstance(tmp, list) else [tmp]

        basic_aspecs: List[BasicAspect] = [
            c for c in aspect_containers if isinstance(c, BasicAspect)
        ]
        concrete_aspects: List[ConcreteAspect] = [
            c for c in aspect_containers if isinstance(c, ConcreteAspect)
        ]
        abstract_aspects: List[AbstractAspect] = [
            c for c in aspect_containers if isinstance(c, AbstractAspect)
        ]

        # resolve inheritance

        # resolve method

        aspects: List[Aspect] = []
        for container in aspect_containers:
            aspects += container.get()
        return aspects
