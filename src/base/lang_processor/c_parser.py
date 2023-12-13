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
            # use_cpp=False,
            cpp_path="gcc",
            cpp_args=["-E", "-I" + pycparser_fake_libc.directory],  # type: ignore
            # cpp_args=[
            #     "-E",
            #     "-I" + pycparser_fake_libc.directory,
            #     "-P",
            #     # '-D"_CPU_INSN_H_"',
            #     "-I../config/sh2aFPU-renesas",
            #     "-I../config/sh2aFPU-renesas/SDK7205",
            #     "-I../Distribute",
            #     "-I../include",
            #     "-I../kernel",
            #     "-I../kernel/ecc2",
            #     "-I../multi",
            #     "-I../sample",
            #     "-I../send",
            #     "-I../syslib",
            #     "-I../syslib/sh2aFPU-renesas/SDK7205",
            #     "-I../can",
            #     "-I../OrenoATK_cpu0/SG",
            #     "-I../HardwareSetupCPU0",
            #     "-I./",
            # ],  # type: ignore
            # cpp_args=["-E", r"-Isrc/toppers/include"],  # type: ignore
            # TODO 本番のファイルでプリプロセス通るようにする
        )
        return ast
