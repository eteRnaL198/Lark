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
        aspects: List[Aspect] = []
        for filename in self.filenames:
            src = open(generate_full_path(filename)).read()
            aspect_containers: Union[list[PureAspect], PureAspect] = self.parser.parse(src)  # type: ignore
            if isinstance(aspect_containers, list):
                for aspect_container in aspect_containers:
                    aspects += aspect_container.get()
            else:
                aspects += aspect_containers.get()
        return aspects
