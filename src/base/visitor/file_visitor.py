from pycparser.c_ast import NodeVisitor


class FileVisitor(NodeVisitor):
    def __init__(self):
        self.filename: str = ""
        self.last_line: int = 0

    def visit(self, node):
        super().visit(node)
        return self.filename, self.last_line

    def visit_FuncDef(self, node):
        """ファイル名を取得
        Note:
            メソッドの命名規則: visit_XXX
        """
        if not self.filename:
            self.__setattr__(
                "filename", node.coord.file.split("/")[-1]
            )  # foo/.../filename.c -> filename.c

        last_line = node.body.block_items[-1].coord.line + 1  # } の行を取得
        if last_line > self.last_line:
            self.__setattr__("last_line", last_line)

        self.generic_visit(node)
