import pycparser_fake_libc
from pycparser import c_ast, parse_file

from src.util.file_util import generate_full_path


class CParser:
    """Cファイルの構文解析器
    Args:
        filename (str): Cファイル名
    """

    def __init__(self, filename):
        self.filename = generate_full_path(filename)

    def parse(self) -> c_ast.FileAST:
        """構文解析を実行
        Returns:
            ast (c_ast.FileAST): 構文木
        """
        ast = parse_file(
            self.filename,
            use_cpp=True,
            cpp_path="gcc",
            cpp_args=["-E", "-I" + pycparser_fake_libc.directory],  # type: ignore
            # cpp_args=["-E", r"-Isrc/toppers/include"],  # type: ignore
            # TODO 本番のファイルでプリプロセス通るようにする
        )
        return ast
