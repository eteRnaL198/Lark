from typing import List, Union

from lark import Lark

from customizer.aspect.pure_aspect import PureAspect
from customizer.lang_processor.aspect_transformer import AspectTransformer
from util.file_util import generate_full_path


class AspectParser:
    """アスペクトファイルの構文解析器
    Args:
        filename (str): アスペクトファイルの相対パス
    """

    def __init__(self, filename):
        self.filename = filename

    def parse(self) -> List[PureAspect]:
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
        aspects: Union[list[PureAspect], PureAspect] = parser.parse(src)  # type: ignore
        return aspects if isinstance(aspects, list) else [aspects]
