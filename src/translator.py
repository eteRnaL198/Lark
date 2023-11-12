import sys
from typing import List

from pycparser import c_ast

from base.lang_processor.c_parser import CParser
from customizer.lang_processor.aspect_parser import AspectParser
from customizer.src import Src
from src.customizer.aspect.pure_aspect import PureAspect
from util.file_util import backup_file, generate_full_path


class Translator:
    def __init__(self):
        if len(sys.argv) > 1:
            self.aspect_files = [sys.argv[1]]  # TODO 拡張子分岐
            self.base_files = [sys.argv[2]]
            # for arg in sys.argv[1:]:
            #     print(self.aspect_file.endswith(".acc"))
            #     print(self.base_file.endswith(".c"))
        else:
            self.aspect_files = ["acc/foo.acc", "acc/bar.acc"]
            self.base_files = ["acc/base.c", "acc/base2.c"]

    def parse_aspects(self):
        aspects: list[PureAspect] = []
        for file in self.aspect_files:
            aspects.extend((AspectParser(file)).parse())
        return aspects

    def parse_bases(self):
        c_asts: list[c_ast.FileAST] = []
        for file in self.base_files:
            c_asts.extend([CParser(file).parse()])
        return c_asts

    def translate(self, aspects: List[PureAspect], c_asts):
        for i in range(len(self.base_files)):
            backup_file(self.base_files[i])
            target_path = generate_full_path(self.base_files[i])
            with open(target_path, mode="r") as f:
                target_src = Src(f.readlines())
            for asp in aspects:
                asp.weave(target_src, c_asts[i])
            with open(target_path, mode="w") as f:
                f.writelines(target_src.get())


if __name__ == "__main__":
    translator = Translator()
    aspects = translator.parse_aspects()
    c_asts = translator.parse_bases()
    translator.translate(aspects, c_asts)
