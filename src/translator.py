import sys

from base.lang_processor.c_parser import CParser
from customizer.lang_processor.aspect_parser import AspectParser
from customizer.src import Src
from util.file_util import backup_file, generate_full_path


class Translator:
    def __init__(self):
        if len(sys.argv) > 1:
            self.aspect_file = sys.argv[1]
            self.base_file = sys.argv[2]
        else:
            self.aspect_file = "acc/aspect.acc"
            self.base_file = "acc/base.c"

    def parse_aspect(self):
        aspects = (AspectParser(self.aspect_file)).parse()
        return aspects

    def parse_base(self):
        c_ast = CParser(self.base_file).parse()
        return c_ast

    def translate(self, aspects, c_ast):
        backup_file(self.base_file)
        target_path = generate_full_path(self.base_file)
        with open(target_path, mode="r") as f:
            target_src = f.readlines()
        customized_src = Src(target_src)
        for asp in aspects:
            asp.weave(customized_src, c_ast)
        with open(target_path, mode="w") as f:
            f.writelines(customized_src.get())


if __name__ == "__main__":
    translator = Translator()
    aspects = translator.parse_aspect()
    c_ast = translator.parse_base()
    translator.translate(aspects, c_ast)
