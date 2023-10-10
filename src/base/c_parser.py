import sys

import pycparser_fake_libc
from pycparser import c_ast, c_generator, c_parser, parse_file

from base.func_def_visitor import FuncDefVisitor
from util.file_util import generate_full_path


class CParser:
    """Cファイルを構文解析する
    Args:
        filename (str): Cファイル名
    """

    def __init__(self, filename):
        self.filename = generate_full_path(filename)

    def parse(self):
        ast = parse_file(
            self.filename,
            use_cpp=True,
            cpp_path="gcc",
            cpp_args=["-E", "-I" + pycparser_fake_libc.directory],  # type: ignore
            # cpp_args=["-E", r"-Isrc/toppers/include"],  # type: ignore
        )

        v = FuncDefVisitor()
        print(v.visit(ast))

        # ast.show()

        # c_ast.FuncCall()
        # print(ast.FuncDef)
