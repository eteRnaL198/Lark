from typing import List, Tuple


class Joinpoint:
    def __init__(self, before: int, after: List[int], around: Tuple[int, int]):
        """
        Args:
            before (int): 行目
            after (List[int]): 行目
            around (Tuple[int, int]): 行目
        """
        self.before_line = before
        self.after_lines = [*after]
        self.around_lines = {"start": around[0], "end": around[1]}

    def get_before(self):
        return self.before_line

    def get_after(self):
        return self.after_lines

    def get_around(self):
        return (self.around_lines["start"], self.around_lines["end"])
