import pycparser_fake_libc
from pycparser import c_generator, c_parser, parse_file

from util.file_util import generate_path

# if len(sys.argv) > 1:
#     filename = sys.argv[1]
# else:
#     filename = generate_path("/acc/base.c")

filename = generate_path("/acc/base.c")
# filename = generate_path("/toppers/kernel/alarm.c")
# filename = "toppers/kernel/alarm.c"
ast = parse_file(
    filename,
    use_cpp=True,
    cpp_path="gcc",
    cpp_args=["-E", "-I" + pycparser_fake_libc.directory],  # type: ignore
    # cpp_args=["-E", r"-Isrc/toppers/include"],  # type: ignore
    # TODO ↑どこからでも実行できるようにしたい
)
ast.show()
# generator = c_generator.CGenerator()
# print(generator.visit(ast))
# c_ast.FuncCall()
# print(ast.FuncDef)
