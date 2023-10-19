from typing import List


class Src:
    def __init__(self, data: List[str]):
        self.data = data
        self.line_table = list(
            range(len(data) + 1)
        )  # 元のコード行(raw line) → 変更後のコード行(line) 0は無効

    def get(self):
        return self.data

    def insert(self, raw_line: int, body: List[str]):
        line = self.line_table[raw_line]
        self.data[line:line] = body

        for i in range(raw_line, len(self.line_table)):
            self.line_table[i] += len(body)

    def replace(self, line: int, lines: List[str]):
        NotImplementedError("src replace")
