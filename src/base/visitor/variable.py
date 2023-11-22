from typing import List


class Variable:
    """変数"""

    def __init__(self, name: str, assigned_lines: List[int]):
        self.name = name
        self.assigned_lines = assigned_lines
