import sys

from aspect.aspect_parser import AspectParser
from base.c_parser import CParser
from util.file_util import backup_file

if __name__ == "__main__":
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    else:
        # aspect_parser = AspectParser("/acc/aspect.acc")
        # aspects = aspect_parser.parse()

        # base_filename = CParser("/acc/base.c")
        # base_filename = CParser("/toppers/kernel/alarm.c")
        # base_filename.parse()

        backup_file("/acc/foo.b")

        # base_src = open(base_src_path, "r")
        # line_cnt = 0
        # for line in base_src:
        #     print(line, end="")
        #     line_cnt += 1
        # base_src.close()

        # weaving_src_path = generate_full_path("/acc/base.c")
        # # TODO ↑ファイル名を定数にしたい
        # with open(weaving_src_path, "x") as f:
        #     print("hoge", file=f)
