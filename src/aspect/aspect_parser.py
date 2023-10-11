# from my_lang_transformer import MyLangTransformer
from lark import Lark

from aspect.aspect import Aspect
from aspect.aspect_transformer import AspectTransformer
from util.file_util import generate_full_path


class AspectParser:
    """アスペクトファイルの構文解析器
    Args:
        filename (str): アスペクトファイルの相対パス
    """

    def __init__(self, filename):
        self.filename = filename

    def parse(self):
        """構文解析を実行
        Returns:
            aspects (list[Aspect]): アスペクトのリスト
        """
        grammar_path = generate_full_path("/src/aspect/acclang.lark")
        parser = Lark(
            grammar=open(grammar_path),
            parser="lalr",
            transformer=AspectTransformer(),
        )
        src = open(generate_full_path(self.filename)).read()
        aspects: list[Aspect] = parser.parse(src)  # type: ignore
        return aspects
