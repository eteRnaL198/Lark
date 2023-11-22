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
    def parse_aspects(self):
        aspect_files: List[str] = ["acc/execution/aspect.acc"]
        preprocessed_sources = AspectPreprocessor(aspect_files)()
        aspects = (AspectParser(preprocessed_sources))()
        return aspects

    def parse_bases(self):
        c_asts: list[c_ast.FileAST] = []
        file = "acc/execution/void.c"
        c_asts += [CParser(file).parse()]


if __name__ == "__main__":
    translator = Translator()
    aspects = translator.parse_aspects()
    c_asts = translator.parse_bases()
