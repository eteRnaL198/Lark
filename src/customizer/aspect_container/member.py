from typing import List


class Member:
    """メンバー"""

    def __init__(self, blocks: List[List[str]]):
        """
        Args:
            blocks (list[str]): ブロック(アスペクト･メソッドを定義する文字列)の二次元リスト
                e.g.) [["void method() {", "...", "}"], ["after(): execution() {", "...", "}"], ...]
        """
        flattened_str = "\n".join(
            ["\n".join(b) for b in blocks]
        )  # e.g.) "method() {\n ... }\n aspect{ ... }"
        self.data = flattened_str

    def add(self, new):
        self.data += new + "\n"

    def replace(self, current, new):
        self.data = self.data.replace(current, new)
