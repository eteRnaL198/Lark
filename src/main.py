import sys

from aspect.aspect_parser import AspectParser
from util.file_util import generate_full_path

if __name__ == "__main__":
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    else:
        aspect_parser = AspectParser("/acc/aspect.acc")
        aspect_parser.parse()
        base_filename = generate_full_path("/acc/base.c")
