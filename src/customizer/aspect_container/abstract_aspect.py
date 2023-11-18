from typing import List

from customizer.aspect_container.constructor import Constructor
from customizer.aspect_container.member import Member
from src.customizer.pointcut.func_signature import FuncSignature


class AbstractAspect:
    def __init__(
        self,
        name,
        constructor: Constructor,
        abstract_methods: List[FuncSignature],
        member: Member,
    ):
        """
        Args:
            name (str): アスペクト名
            constructor (Constructor): コンストラクタ
            abstract_methods (list[AbstractMethod]): 抽象メソッドのリスト
            member (Member): メンバー
        """
        self.name = name
        self.constructor = constructor
        self.abstract_methods: List[FuncSignature] = (
            abstract_methods
            if isinstance(abstract_methods, list)
            else [abstract_methods]
        )
        self.member: Member = member
