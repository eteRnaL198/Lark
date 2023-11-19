from typing import List, Union

from lark import Lark

from customizer.aspect_container.abstract_aspect import AbstractAspect
from customizer.aspect_container.basic_aspect import BasicAspect
from customizer.aspect_container.concrete_aspect import ConcreteAspect
from customizer.lang_processor.inheritance_transformer import InheritanceTransformer
from util.file_util import generate_full_path


class AspectPreprocessor:
    """アスペクトファイルのプリプロセッサ"""

    def __init__(self, filenames: List[str]):
        self.filenames = filenames

    def __call__(self):
        return self.__preprocess()

    def __read(self):
        sources: List[str] = []
        for filename in self.filenames:
            sources.append(open(generate_full_path(filename)).read())
        return sources

    def __extract_aspect_containers(
        self, sources: List[str]
    ) -> List[Union[BasicAspect, ConcreteAspect, AbstractAspect]]:
        aspect_containers: List[Union[BasicAspect, ConcreteAspect, AbstractAspect]] = []
        grammar_path = generate_full_path(
            "src/customizer/lang_processor/inheritance.lark"
        )
        for src in sources:
            tmp: Union[
                List[Union[BasicAspect, ConcreteAspect, AbstractAspect]],
                Union[BasicAspect, ConcreteAspect, AbstractAspect],
            ] = Lark(
                grammar=open(grammar_path),
                parser="lalr",
                transformer=InheritanceTransformer(),
            ).parse(
                src
            )  # type: ignore
            aspect_containers += tmp if isinstance(tmp, list) else [tmp]
        return aspect_containers

    def __preprocess(self):
        print("Start preprocessing...")
        sources = self.__read()
        aspect_containers = self.__extract_aspect_containers(sources)
        concrete_aspects: List[ConcreteAspect] = [
            c for c in aspect_containers if isinstance(c, ConcreteAspect)
        ]
        abstract_aspects: List[AbstractAspect] = [
            c for c in aspect_containers if isinstance(c, AbstractAspect)
        ]
        abstract_aspect_table: dict[str, AbstractAspect] = dict(
            zip([a.name for a in abstract_aspects], abstract_aspects)
        )
        for concrete_aspect in concrete_aspects:
            try:
                concrete_aspect.inherit(
                    abstract_aspect_table[concrete_aspect.super_aspect_name]
                )
            except KeyError:
                raise Exception(
                    f"{concrete_aspect.name} was not able to inherit from {concrete_aspect.super_aspect_name} because {concrete_aspect.super_aspect_name} was not found"
                )
        print("Complete preprocessing!!")
        return sources
