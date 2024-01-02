class GrandParent:
    def __init__(self, p):
        self.param = p

    def method(self):
        print(self.param)


class Parent(GrandParent):
    def __init__(self, p):
        super().__init__(p)

    def method(self):
        print(self.param)


class Child(Parent):
    def __init__(self):
        super().__init__("I'm Child")


child = Child()
child.method()
