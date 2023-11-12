import sys
from typing import List
from uu import Error

from pycparser import c_ast

from base.lang_processor.c_parser import CParser
from customizer.lang_processor.aspect_parser import AspectParser
from customizer.src import Src
from src.customizer.aspect.pure_aspect import PureAspect
from util.file_util import backup_file, generate_full_path


class Translator:
    def __init__(self) -> None:
        self.aspect_files = [
            "acc/inheritance/concrete.acc",
            "acc/inheritance/abstract.acc",
            "acc/inheritance/pure.acc",
        ]

    def parse_aspects(self):
        aspects: list[PureAspect] = []
        for file in self.aspect_files:
            aspects.extend((AspectParser(file)).parse())
        return aspects


if __name__ == "__main__":
    (Translator()).parse_aspects()
