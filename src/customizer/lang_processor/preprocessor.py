from re import U
from typing import Dict, List, Union

from lark import Lark

from src.customizer.lang_processor.inheritance_transformer import InheritanceTransformer
from src.customizer.primitive_aspect.abstract_aspect import AbstractAspect
from src.customizer.primitive_aspect.concrete_aspect import ConcreteAspect
from src.customizer.primitive_aspect.intermediate_aspect import IntermediateAspect
from src.customizer.primitive_aspect.primitive_aspect import PrimitiveAspect
from src.util.file_util import generate_full_path


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

    def __extract_aspect_containers(self, sources: List[str]) -> List[PrimitiveAspect]:
        aspect_containers: List[PrimitiveAspect] = []
        grammar_path = generate_full_path(
            "src/customizer/lang_processor/inheritance.lark"
        )
        for src in sources:
            tmp: Union[
                List[PrimitiveAspect],
                PrimitiveAspect,
            ] = Lark(
                grammar=open(grammar_path),
                parser="lalr",
                transformer=InheritanceTransformer(),
            ).parse(
                src
            )  # type: ignore
            aspect_containers += tmp if isinstance(tmp, list) else [tmp]
        return aspect_containers

    def __inherit(
        self,
        super_aspects: List[Union[AbstractAspect, IntermediateAspect]],
        sub_aspects: List[Union[ConcreteAspect, IntermediateAspect]],
        concrete_aspects: List[ConcreteAspect],
    ):
        """
        Args:
            super_aspects (List[Union[AbstractAspect, IntermediateAspect]]): 親アスペクト
            sub_aspects (List[Union[ConcreteAspect, IntermediateAspect]]): 子アスペクト
            concrete_aspects (List[ConcreteAspect]): 末端アスペクト
        """
        super_aspect_map: Dict[str, Union[AbstractAspect, IntermediateAspect]] = {
            aspect.name: aspect for aspect in super_aspects
        }
        inheritance_map: dict[
            str, Union[AbstractAspect, IntermediateAspect]
        ] = {}  # {sub_name: super_aspect}
        for aspect in sub_aspects:
            if aspect.super_aspect_name not in super_aspect_map:
                raise Exception(
                    f"{aspect.name} failed to inherit from {aspect.super_aspect_name} because {aspect.super_aspect_name} was not found"
                )
            inheritance_map[aspect.name] = super_aspect_map[aspect.super_aspect_name]

        inherited_super_aspects: List[Union[AbstractAspect, IntermediateAspect]] = []
        for concrete_aspect in concrete_aspects:
            current_aspect: Union[ConcreteAspect, IntermediateAspect] = concrete_aspect
            while True:
                try:
                    super_aspect = inheritance_map[current_aspect.name]
                except KeyError:
                    raise Exception(
                        f"{current_aspect.name} failed to inherit from {current_aspect.super_aspect_name} because {current_aspect.super_aspect_name} was not found"
                    )
                inherited_aspect: Union[
                    IntermediateAspect, AbstractAspect
                ] = current_aspect.inherit(super_aspect)
                inherited_super_aspects.append(inherited_aspect)
                if type(super_aspect) == AbstractAspect:
                    break
                current_aspect = inherited_aspect  # type: ignore
        return inherited_super_aspects

    def __preprocess(self):
        print("Start preprocessing...")
        sources = self.__read()
        aspect_containers = self.__extract_aspect_containers(sources)
        abstract_aspects: List[Union[AbstractAspect, IntermediateAspect]] = [
            c for c in aspect_containers if type(c) == AbstractAspect
        ]
        intermediate_aspects: List[IntermediateAspect] = [
            c for c in aspect_containers if type(c) == IntermediateAspect
        ]
        concrete_aspects: List[ConcreteAspect] = [
            c for c in aspect_containers if type(c) == ConcreteAspect
        ]
        inherited_super_aspects = self.__inherit(
            abstract_aspects + intermediate_aspects,
            concrete_aspects + intermediate_aspects,
            concrete_aspects,
        )
        primitive_aspects: List[PrimitiveAspect] = [
            c for c in aspect_containers if type(c) == PrimitiveAspect
        ]
        preprocessed_src: List[str] = [
            aspect.stringify()
            for aspect in inherited_super_aspects + concrete_aspects + primitive_aspects
        ]
        print("Complete preprocessing!!")
        return preprocessed_src
