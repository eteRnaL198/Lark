from typing import List


class Member:
    """メンバー"""

    def __init__(self, blocks: List[List[str]]):
        """
        Args:
            blocks (list[str]): ブロックの二次元リスト
                e.g.) [["method{", "}"], ["aspect{", "}"], ...]
        """
        flattened_str = "\n".join(
            ["\n".join(b) for b in blocks]
        )  # e.g.) "method() {\n ... }\n aspect{ ... }"
        self.data = flattened_str
