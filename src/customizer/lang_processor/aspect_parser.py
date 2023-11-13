from typing import List, Union

from lark import Lark

from customizer.aspect.aspect import Aspect
from customizer.aspect_container.pure_aspect import PureAspect
from customizer.lang_processor.aspect_transformer import AspectTransformer
from util.file_util import generate_full_path


class AspectParser:
    """アスペクトファイルの構文解析器
    Args:
        filename (str): アスペクトファイルの相対パス
    """

    def __init__(self, filename):
        self.filename = filename

    def parse(self) -> List[Aspect]:
        """構文解析を実行
        Returns:
            aspects (list[Aspect]): アスペクトのリスト
        """
        grammar_path = generate_full_path("src/customizer/lang_processor/acclang.lark")
        parser = Lark(
            grammar=open(grammar_path),
            parser="lalr",
            transformer=AspectTransformer(),
        )
        src = open(generate_full_path(self.filename)).read()
        aspect_containers: Union[list[PureAspect], PureAspect] = parser.parse(src)  # type: ignore
        if isinstance(aspect_containers, list):
            aspects: list[Aspect] = []
            for aspect_container in aspect_containers:
                aspects.extend(aspect_container.get())
            return aspects
        else:
            return aspect_containers.get()
