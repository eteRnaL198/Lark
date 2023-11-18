from customizer.aspect_container.basic_aspect import BasicAspect
from customizer.aspect_container.member import Member
from customizer.aspect_container.super import Super


class ConcreteAspect(BasicAspect):
    def __init__(
        self,
        name: str,
        super_aspect_name: str,
        super_constructor: Super,
        member: Member,
    ):
        """
        Args:
            name (str): アスペクト名
            super_aspect_name (str): 継承アスペクト名
            super_constructor (Super): 継承アスペクトのコンストラクタ
            member (Member): メンバー
        """
        self.name = name
        self.super_aspect_name: str = super_aspect_name
        self.super = super_constructor
        self.member = member
