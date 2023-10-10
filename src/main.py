import sys

from aspect.aspect_parser import AspectParser
from base.c_parser import CParser
from util.file_util import backup_file, generate_full_path

if __name__ == "__main__":
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    else:
        filename = "/acc/base.c"

    aspect_parser = AspectParser("/acc/aspect.acc")
    aspects = aspect_parser.parse()

    c_parser = CParser("/acc/base.c")
    # c_parser = CParser("/toppers/kernel/alarm.c")
    c_ast = c_parser.parse()

    for asp in aspects:
        print(asp.weave(c_ast))

    """file input/output"""
    # backup_file(filename)

    # target_path = generate_full_path(filename)
    # with open(target_path, mode="r") as f:
    #     src = f.readlines()

    # # weave(line, aspect.body)
    # src.insert(5, 'printf("hoge");\n')
    # src.insert(14 + 1, 'printf("piyo");\n')

    # with open(target_path, mode="w") as f:
    #     f.writelines(src)
