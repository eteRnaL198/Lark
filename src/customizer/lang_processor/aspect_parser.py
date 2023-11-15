from typing import List, Union

from lark import Lark

from customizer.aspect.aspect import Aspect
from customizer.aspect_container.abstract_aspect import AbstractAspect
from customizer.aspect_container.aspect_wrapper import AspectWrapper
from customizer.aspect_container.basic_aspect import BasicAspect
from customizer.aspect_container.concrete_aspect import ConcreteAspect
from customizer.lang_processor.aspect_transformer import AspectTransformer
from customizer.lang_processor.inheritance_transformer import InheritanceTransformer
from util.file_util import generate_full_path


class AspectParser:
    """アスペクトファイルの構文解析器
    Args:
        filename (str): アスペクトファイルの相対パス
    """

    def __init__(self, filenames):
        self.filenames = filenames

    def preprocess(self, sources):
        # return sources
        grammar_path = generate_full_path(
            "src/customizer/lang_processor/inheritance.lark"
        )
        for src in sources:
            aspect_containers: Union[
                List[Union[BasicAspect, ConcreteAspect, AbstractAspect]],
                Union[BasicAspect, ConcreteAspect, AbstractAspect],
            ] = Lark(
                grammar=open(grammar_path),
                parser="lalr",
                transformer=InheritanceTransformer(),
            ).parse(
                src
            )  # type: ignore
        return sources

    def extract_aspect_containers(self, src):
        grammar_path = generate_full_path("src/customizer/lang_processor/aspect.lark")
        aspect_containers: Union[
            List[Union[BasicAspect, ConcreteAspect, AbstractAspect]],
            Union[BasicAspect, ConcreteAspect, AbstractAspect],
        ] = Lark(
            grammar=open(grammar_path),
            parser="lalr",
            transformer=AspectTransformer(),
        ).parse(
            src
        )  # type: ignore
        # aspect_wrapepr = AspectWrapper()
        return (
            aspect_containers
            if isinstance(aspect_containers, list)
            else [aspect_containers]
        )

    def parse(self) -> List[Aspect]:
        """構文解析を実行
        Returns:
            aspects (list[Aspect]): アスペクトのリスト
        """
        sources: list[str] = []
        for filename in self.filenames:
            sources.append(open(generate_full_path(filename)).read())
        preprocessed_sources = self.preprocess(sources)
        aspect_containers: List[Union[BasicAspect, ConcreteAspect, AbstractAspect]] = []
        for src in preprocessed_sources:
            # aspect_containers += self.extract_aspect_containers(src)
            pass

        # pure_aspecs: List[BasicAspect] = [
        #     c for c in aspect_containers if isinstance(c, BasicAspect)
        # ]
        # concrete_aspects: List[ConcreteAspect] = [
        #     c for c in aspect_containers if isinstance(c, ConcreteAspect)
        # ]
        # abstract_aspects: List[AbstractAspect] = [
        #     c for c in aspect_containers if isinstance(c, AbstractAspect)
        # ]

        aspects: List[Aspect] = []
        for container in aspect_containers:
            aspects += container.get_aspects()
        return aspects
