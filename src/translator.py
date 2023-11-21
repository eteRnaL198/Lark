import sys
from typing import List

from pycparser import c_ast

from base.lang_processor.c_parser import CParser
from customizer.aspect.aspect import Aspect
from customizer.lang_processor.aspect_parser import AspectParser
from customizer.lang_processor.preprocessor import AspectPreprocessor
from customizer.src import Src
from util.file_util import backup_file, generate_full_path


class Translator:
    def __init__(self):
        self.aspect_files: list[str] = []
        self.base_files: list[str] = []
        if len(sys.argv) == 1:  # TODO delete
            self.aspect_files = ["acc/basic/foo.acc", "acc/basic/bar.acc"]
            self.base_files = ["acc/basic/base.c", "acc/basic/base2.c"]
        else:
            for arg in sys.argv[1:]:
                if arg.endswith(".acc"):
                    self.aspect_files.append(arg)
                elif arg.endswith(".c"):
                    self.base_files.append(arg)
            if len(self.aspect_files) == 0 or len(self.base_files) == 0:
                raise Exception("No aspect file or base file specified.")

    def parse_aspects(self):
        preprocessed_sources = AspectPreprocessor(self.aspect_files)()
        aspects = (AspectParser(preprocessed_sources))()
        return aspects

    def parse_bases(self):
        c_asts: list[c_ast.FileAST] = []
        for file in self.base_files:
            c_asts += [CParser(file).parse()]
        return c_asts

    def translate(self, aspects: List[Aspect], c_asts):
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
