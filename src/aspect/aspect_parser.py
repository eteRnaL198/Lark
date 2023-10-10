# from my_lang_transformer import MyLangTransformer
from lark import Lark

from aspect.aspect_translator import AspectTranslator
from util.file_util import generate_full_path


class AspectParser:
    """アスペクトファイルを構文解析する
    Args:
        filename (str): アスペクトファイルの相対パス
    """

    def __init__(self, filename):
        self.filename = filename

    def parse(self):
        grammar = generate_full_path("/src/aspect/acclang.lark")
        parser = Lark(
            grammar=open(grammar),
            parser="lalr",
            transformer=AspectTranslator(),
        )

        src = open(generate_full_path(self.filename)).read()
        print(parser.parse(src))

        # return aspects
