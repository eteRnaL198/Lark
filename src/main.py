# from my_lang_transformer import MyLangTransformer
import sys

from util.file_util import generate_path

if __name__ == "__main__":
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    else:
        c_filename = generate_path("/acc/base.c")
