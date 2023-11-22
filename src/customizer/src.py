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

    def replace(self, start_line: int, end_line: int, body: List[str]):
        """start_lineからend_lineまでの行をbodyで置き換える
        Args:
            start_line (int): 置き換え開始行
            end_line (int): 置き換え終了行
            body (List[str]): 置き換えるコード
        e.g.)
          int foo() { ← start_line
            printf("bar");
            return 0; ← end_line
          }
        """
        init_len = len(self.data)
        self.data[self.line_table[start_line] : self.line_table[end_line]] = body
        dif = len(self.data) - init_len
        for i in range(end_line + 1, len(self.line_table)):
            self.line_table[i] += dif
