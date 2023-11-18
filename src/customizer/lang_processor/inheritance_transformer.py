from lark import Token, Transformer

from customizer.aspect_container.abstract_aspect import AbstractAspect
from customizer.aspect_container.basic_aspect import BasicAspect
from customizer.aspect_container.concrete_aspect import ConcreteAspect
from customizer.aspect_container.constructor import Constructor
from customizer.aspect_container.member import Member
from customizer.aspect_container.super import Super
from customizer.pointcut.func_signature import FuncSignature


class InheritanceTransformer(Transformer):
    def start(self, tree):
        return tree

    ######################## aspect ########################
    def aspect_container(self, tree):
        return tree[0]

    def abstract_aspect(self, tree):
        """
        abstract aspect Foo {
            Aspects
        }
        """
        name = str(tree[0])
        constructor: Constructor = tree[1]
        abstract_methods = [t for t in tree[2:] if isinstance(t, FuncSignature)]
        member = Member([t for t in tree[2:] if isinstance(t, list)])
        return AbstractAspect(name, constructor, abstract_methods, member)

    def concrete_aspect(self, tree):
        """
        aspect Bar extends Foo {
            Aspects
        }
        """
        name = str(tree[0])
        super_asp_name = str(tree[1])
        super: Super = tree[2]
        member = Member([t for t in tree[2:] if isinstance(t, list)])
        return ConcreteAspect(name, super_asp_name, super, member)

    def basic_aspect(self, tree):
        """
        aspect Baz {
            Aspects
        }
        """
        name = str(tree[0])
        member = Member([t for t in tree[1:] if isinstance(t, list)])
        # TODO そのままの形にしたい
        # return BasicAspect(name, member)

    def aspect_name(self, tree):
        return str(tree[0])

    ######################## constructor ########################
    def constructor(self, tree):
        return Constructor(tree[1])

    def constructor_args(self, tree):
        """
        return:
            e.g.) ['foo', 'bar']
        """
        return [str(t) for t in tree]

    def super(self, tree):
        return Super(tree[1])

    def super_args(self, tree):
        """
        return:
            e.g.) foo.c, "bar2" →[foo.c, "bar2"]
        """
        return tree

    def super_arg(self, tree):
        return "".join([t.value for t in tree])

    ######################## method ########################
    def abstract_method(self, tree) -> FuncSignature:
        return tree[1]

    def func_signature(self, tree):
        """
        e.g.) tree[int, foo, char] -> int foo(char)
        """
        type, name, args = str(tree[0]), tree[1], tree[2]
        return FuncSignature(type, name, args)

    def func_name(self, tree):
        """
        e.g.) set_foo
        """
        return str(tree[0])

    def func_args(self, tree):
        """
        return:
            e.g.) ['int', 'float', 'char']
        """
        return [str(t) for t in tree]

    ######################## block ########################

    def block(self, tree):
        """
        e.g.)
        if() {
            if() {
                foo();
            }
         }
        →[if(), {, if(), foo();, }, }]
        """
        lines: list[str] = []
        for t in tree:
            if isinstance(t, Token):
                lines.append(t.value)
            else:
                lines += t
        return lines
