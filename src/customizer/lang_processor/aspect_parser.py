from typing import List, Union

from lark import Lark

from customizer.aspect.aspect import Aspect
from customizer.aspect_container.basic_aspect import BasicAspect
from customizer.lang_processor.aspect_transformer import AspectTransformer
from util.file_util import generate_full_path


class AspectParser:
    """アスペクトファイルの構文解析器
    Args:
        filename (str): アスペクトファイルの相対パス
    """

    def __init__(self, sources: List[str]):
        self.sources = sources

    def __call__(self):
        return self.__parse()

    def __extract_aspect_containers(self, src):
        print("Start extracting aspects...")
        grammar_path = generate_full_path("src/customizer/lang_processor/aspect.lark")
        aspect_containers: Union[
            List[BasicAspect],
            BasicAspect,
        ] = Lark(
            grammar=open(grammar_path),
            parser="lalr",
            transformer=AspectTransformer(),
        ).parse(
            src
        )  # type: ignore
        print("Complete extracting aspects!!")
        return (
            aspect_containers
            if isinstance(aspect_containers, list)
            else [aspect_containers]
        )

    def __parse(self) -> List[Aspect]:
        """構文解析を実行
        Returns:
            aspects (list[Aspect]): アスペクトのリスト
        """
        aspect_containers: List[BasicAspect] = []
        for src in self.sources:
            aspect_containers += self.__extract_aspect_containers(src)
        aspects: List[Aspect] = []
        for container in aspect_containers:
            aspects += container.get_aspects()
        return aspects
