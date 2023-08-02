# from my_lang_transformer import MyLangTransformer
from acc_transformer import AccTransformer
from util.file_util import generate_path

from lark import Lark

# grammar = generate_path("/mylang.lark")
# parser = Lark(open(grammar), parser="lalr", transformer=ToMyLang())

# parser.parse(r"変数 x に 10 を代入")
# parser.parse(r"変数 y に 10 を代入")
# parser.parse(r"変数 z に 10 を代入")
# parser.parse(r"x を表示")
# parser.parse(r"40 を表示")
# parser.parse(r"10 に 3 を足す")


grammar = generate_path("/acclang.lark")
parser = Lark(
    grammar=open(grammar),
    parser="lalr",
    transformer=AccTransformer(),
)

src = open(generate_path("/acc/aspect.acc")).read()
parser.parse(src)
