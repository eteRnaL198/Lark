import sys

from aspect.aspect_parser import AspectParser
from base.c_parser import CParser
from util.file_util import generate_full_path

if __name__ == "__main__":
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    else:
        aspect_parser = AspectParser("/acc/aspect.acc")
        # aspects = aspect_parser.parse()

        base_filename = CParser("/acc/base.c")
        # base_filename = CParser("/toppers/kernel/alarm.c")
        base_filename.parse()
