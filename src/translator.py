import sys
from typing import List

from pycparser import c_ast

from src.base.lang_processor.c_parser import CParser
from src.customizer.aspect.aspect import Aspect
from src.customizer.lang_processor.aspect_parser import AspectParser
from src.customizer.lang_processor.preprocessor import AspectPreprocessor
from src.customizer.src import Src
from src.util.file_util import backup_file


class Translator:
    def __init__(self):
        self.aspect_files: list[str] = []
        self.base_files: list[str] = []
        for arg in sys.argv[1:]:
            if arg.endswith(".aspect"):
                self.aspect_files.append(arg)
            elif arg.endswith(".c"):
                self.base_files.append(arg)
        if len(self.aspect_files) == 0 or len(self.base_files) == 0:
            raise Exception("No aspect file or base file specified.")

    def parse_aspects(self):
        preprocessed_sources = AspectPreprocessor(self.aspect_files)()
        # for l in preprocessed_sources:  # TODO delete: print preprocessed source
        #     print(l)
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
            target_path = self.base_files[i]
            with open(target_path, mode="r") as f:
                target_src = Src(f.readlines())
            for asp in aspects:
                asp.weave(target_src, c_asts[i])
            # for l in target_src.get():  # TODO delete: print translated source
            #     print(l, end="")
            with open(target_path, mode="w") as f:
                f.writelines(target_src.get())


def main():
    translator = Translator()
    aspects = translator.parse_aspects()
    c_asts = translator.parse_bases()
    translator.translate(aspects, c_asts)


if __name__ == "__main__":
    main()
