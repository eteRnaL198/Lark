from pycparser import c_generator, c_parser, parse_file

from util.file_util import generate_path

# if len(sys.argv) > 1:
#     filename = sys.argv[1]
# else:
#     filename = generate_path("/acc/base.c")

filename = generate_path("/acc/base.c")
# filename = generate_path("/toppers/kernel/alarm.c")
ast = parse_file(
    filename,
    # use_cpp=True,
    # cpp_path="gcc",
    # cpp_args=["-E", "-Isrc/util/fake_libc_include"],  # type: ignore
    # TODO ↑どこからでも実行できるようにしたい
)
ast.show()
# generator = c_generator.CGenerator()
# print(generator.visit(ast))
# c_ast.FuncCall()
# print(ast.FuncDef)
