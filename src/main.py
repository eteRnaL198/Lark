# from my_lang_transformer import MyLangTransformer
from acc_translator import AccTranslator
from util.file_util import generate_path

from lark import Lark

if __name__ == "__main__":
    grammar = generate_path("/acclang.lark")
    parser = Lark(
        grammar=open(grammar),
        parser="lalr",
        transformer=AccTranslator(),
    )

    src = open(generate_path("/acc/aspect.acc")).read()
    parser.parse(src)
