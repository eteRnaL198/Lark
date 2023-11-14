from lark import Transformer

from customizer.aspect.advice import Advice
from customizer.aspect.aspect import Aspect
from customizer.aspect_container.abstract_aspect import AbstractAspect
from customizer.aspect_container.concrete_aspect import ConcreteAspect
from customizer.aspect_container.constructor import Constructor
from customizer.aspect_container.pure_aspect import PureAspect
from customizer.aspect_container.super import Super
from customizer.method.abstract_method import AbstractMethod
from customizer.method.method import Method
from customizer.pointcut.execution import Execution
from customizer.pointcut.func_signature import FuncSignature


class AspectTransformer(Transformer):
    def start(self, tree):
        return tree

    ######################## aspect ########################
    def aspect_declarator(self, tree):
        return tree[0]

    def abstract_aspect(self, tree):
        """
        abstract aspect Foo {
            Aspects
        }
        """
        name = str(tree[0])
        constructor: Constructor = tree[1]
        abstract_methods = [t for t in tree[2:] if isinstance(t, AbstractMethod)]
        methods = [t for t in tree[2:] if isinstance(t, Method)]
        aspects = [t for t in tree[2:] if isinstance(t, Aspect)]
        return AbstractAspect(name, constructor, abstract_methods, methods, aspects)

    def concrete_aspect(self, tree):
        """
        aspect Bar extends Foo {
            Aspects
        }
        """
        name = str(tree[0])
        super_asp_name = str(tree[1])
        super: Super = tree[2]
        methods = [t for t in tree[3:] if isinstance(t, Method)]
        aspects = [t for t in tree[3:] if isinstance(t, Aspect)]
        return ConcreteAspect(name, super_asp_name, super, methods, aspects)

    def pure_aspect(self, tree):
        """aspect Baz {
            Aspects
        }"""
        name = str(tree[0])
        methods = [t for t in tree[1:] if isinstance(t, Method)]
        aspects = [t for t in tree[1:] if isinstance(t, Aspect)]
        return PureAspect(name, methods, aspects)

    def aspect_name(self, tree):
        return str(tree[0])

    def aspect(self, tree):
        advice_type, pointcut, advice_body = tree[0], tree[1], tree[2]
        return Aspect(pointcut, Advice(advice_type, advice_body))

    ######################## advice ########################
    def advice_type(self, tree):
        return tree[0]

    ######################## pointcut ########################
    def pointcut(self, tree):
        """
        Return:
            e.g.) [Call, Execution, etc...]
        """
        primitive_pointcuts = [*tree]
        return primitive_pointcuts

    def primitive_pointcut(self, tree):
        """
        Return:
            e.g.) Call or Execution or etc...
        """
        return tree[0]

    def call(self, tree):
        return {"name": "call", "arg": tree[0]}

    def execution(self, tree):
        return Execution(tree[0])

    def infunc(self, tree):
        return {"name": "infunc", "arg": tree[0]}

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
    def method(self, tree):
        """
        e.g.) tree[FuncSignature, str] → int foo(char) { ... }
        """
        type, names, args, body = tree[0].type, tree[0].name, tree[0].args, tree[1]
        return Method(type, names, args, body)

    def abstract_method(self, tree):
        """
        e.g.) tree[abstract, FuncSignature] → int foo(char)
        """
        return AbstractMethod(tree[1].type, tree[1].name, tree[1].args)

    ######################## func ########################

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

    def body(self, tree):
        return [t.value for t in tree]
