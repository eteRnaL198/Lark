import sys

import pycparser_fake_libc
from pycparser import c_ast, c_generator, c_parser, parse_file

from util.file_util import generate_path


class FuncDefVisitor(c_ast.NodeVisitor):
    def visit_FuncDef(self, node):
        print("FuncDef: %s at %s" % (node.decl.name, node.decl.coord))


if __name__ == "__main__":
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    else:
        filename = generate_path("/acc/base.c")
        # filename = generate_path("/toppers/kernel/alarm.c")

    ast = parse_file(
        filename,
        use_cpp=True,
        cpp_path="gcc",
        cpp_args=["-E", "-I" + pycparser_fake_libc.directory],  # type: ignore
        # cpp_args=["-E", r"-Isrc/toppers/include"],  # type: ignore
    )

    v = FuncDefVisitor()
    v.visit(ast)

    # ast.show()

    # c_ast.FuncCall()
    # print(ast.FuncDef)
