import sys
from typing import List

from base.lang_processor.c_parser import CParser
from customizer.lang_processor.aspect_parser import AspectParser
from customizer.src import Src
from util.file_util import backup_file, generate_full_path

if __name__ == "__main__":
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    else:
        filename = "/acc/base.c"

    """Parse aspect file"""
    aspect_parser = AspectParser("/acc/aspect.acc")
    aspects = aspect_parser.parse()

    """Parse source file for customization"""
    c_parser = CParser("/acc/base.c")
    # c_parser = CParser("/toppers/kernel/alarm.c")
    c_ast = c_parser.parse()

    """Execute customizations"""
    backup_file(filename)
    target_path = generate_full_path(filename)
    with open(target_path, mode="r") as f:
        target_src = f.readlines()
    customized_src = Src(target_src)
    for asp in aspects:
        asp.weave(customized_src, c_ast)
    with open(target_path, mode="w") as f:
        f.writelines(customized_src.get())
