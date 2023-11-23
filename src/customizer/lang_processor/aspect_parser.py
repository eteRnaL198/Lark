from typing import List, Union

from lark import Lark

from src.customizer.aspect.aspect import Aspect
from src.customizer.aspect.basic_aspect import BasicAspect
from src.customizer.lang_processor.aspect_transformer import AspectTransformer
from src.util.file_util import generate_full_path


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
        print("Start parsing aspects...")
        aspect_containers: List[BasicAspect] = []
        for src in self.sources:
            aspect_containers += self.__extract_aspect_containers(src)
        aspects: List[Aspect] = []
        for container in aspect_containers:
            aspects += container.get_aspects()
        print("Complete parsing aspects!!")
        return aspects
