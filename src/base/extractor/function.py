from typing import List, Union


class Function:
    """関数定義
    Args:
        name (str): 関数名
        start_line (int): 関数が定義されている行
        end_line (int): 関数の定義の末尾の行
        return_lines (List[int]): return文の行のリスト
    """

    def __init__(
        self,
        name,
        start_line: int,
        end_line: int,
        return_lines: Union[List[int], None] = None,
    ):
        self.name = name
        self.start_line = start_line
        self.end_line = end_line
        self.return_lines = return_lines

    def add_return_lines(self, return_line: int):
        self.return_lines = (
            [return_line]
            if self.return_lines == None
            else self.return_lines + [return_line]
        )

    def get_exec_start_line(self):
        """関数が実行開始する行を返す"""
        return self.start_line

    def get_exec_end_lines(self) -> List[int]:
        """関数が実行終了する直前の行のリストを返す
        e.g.)
            int foo(a) {
                if (a > 0) {
                                ←この行
                    return 0;
                } else {
                                ←この行
                    return 1;
                }
            }
            void bar() {
                baz(); ← この行
            }
        """
        if self.return_lines == None:
            return [self.end_line]
        else:
            lines = list(map(lambda l: l - 1, self.return_lines))  # return文の直前の行を取得
            return lines
