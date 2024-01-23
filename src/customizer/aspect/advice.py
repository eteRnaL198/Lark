class Advice:
    def __init__(self, type, body: str):
        """
        Args:
            type (str): アドバイスの種類(before, after, around)
            body (list[str]): アドバイスの中身
        """
        self.type = type
        self.body: str = "/* Start of advice */\n" + body + "\n/* End of advice */\n"

    def __str__(self):
        return self.body

    def get_formatted_body(self):
        """
        e.g.) "foo\nbar\nbaz" → ["foo\n", "bar\n", "baz\n"]
        """
        return [t + "\n" for t in self.body.split("\n")]

    def replace(self, current, new):
        self.body = self.body.replace(current, new)
