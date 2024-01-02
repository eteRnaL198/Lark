from typing import List

from pycparser import c_ast

from src.base.visitor.file_visitor import FileVisitor
from src.customizer.joinpoint.joinpoint import Joinpoint
from src.customizer.pointcut.pointcut import Pointcut


class Infile(Pointcut):
    def __init__(self, filename) -> None:
        self.filename = filename.strip('"')

    def search(self, ast: c_ast.FileAST) -> List[Joinpoint]:
        filename, last_line = (FileVisitor()).visit(ast)
        joinpoints: List[Joinpoint] = []

        if filename == self.filename:
            joinpoints.append(Joinpoint(0, [last_line], (0, last_line)))
        return joinpoints
