from typing import List


class Advice:
    def __init__(self, type, body: List[str]):
        """
        Args:
            type (str): アドバイスの種類(before, after, around)
            body (str): アドバイスの内容
        """
        self.type = type
        body_eol = list(map(lambda l: (l + "\n"), body))  # 解析時に無視された改行コードを追加
        self.body: List[str] = (
            ["{ /* Start of advice*/\n"] + body_eol + ["} /* End of advice */\n"]
        )
