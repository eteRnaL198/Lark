from typing import List, Union

from pycparser import c_ast

from customizer.aspect.aspect import Aspect


class PureAspect:
    def __init__(self, name, aspects: Union[List[Aspect], Aspect]):
        """
        Args:
            name (str): アスペクト名
            aspects list[(Aspect)]: アスペクトのリスト
        """
        self.name: str = name
        self.aspects: List[Aspect] = aspects if isinstance(aspects, list) else [aspects]

    def weave(self, src: List[str], ast: c_ast.FileAST):
        """アスペクトを織り込む
        Args:
            src (List[str]): アスペクトを織り込むソースコード
            ast (c_ast.FileAST): 構文木
        Returns:
            List[str]: アスペクトが織り込まれたソースコード
        """
        accumulated_line = 0
        for aspect in self.aspects:
            lines = aspect.get_joinpoints(ast)
            advice = (
                ["/* Start of aspect */\n"]
                + aspect.advice_body
                + ["/* End of aspect */\n"]
            )
            for l in lines:
                src[
                    l + accumulated_line : l + accumulated_line
                ] = advice  # aroundのときは挿入ではなく置換
                accumulated_line += len(advice)
        return src
