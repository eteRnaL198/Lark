from lark import Token, Transformer

from customizer.aspect.advice import Advice
from customizer.aspect.aspect import Aspect
from customizer.aspect_container.basic_aspect import BasicAspect
from customizer.method.method import Method
from customizer.pointcut.execution import Execution
from customizer.pointcut.func_signature import FuncSignature


class AspectTransformer(Transformer):
    def start(self, tree):
        return tree

    ######################## aspect ########################
    def basic_aspect(self, tree):
        """aspect Baz {
            Aspects
        }"""
        name = str(tree[0])
        methods = [t for t in tree[1:] if isinstance(t, Method)]
        aspects = [t for t in tree[1:] if isinstance(t, Aspect)]
        return BasicAspect(name, methods, aspects)

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

    ######################## method ########################
    def method(self, tree):
        """
        e.g.) tree[FuncSignature, str] → int foo(char) { ... }
        """
        type, names, args, body = tree[0].type, tree[0].name, tree[0].args, tree[1]
        return Method(type, names, args, body)

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
        """
        e.g.)
        foo();
        if() {
            bar();
        }
        → [foo();, if() {, bar();, }]
        """
        lines: list[str] = []
        for t in tree:
            if isinstance(t, Token):
                lines.append(t.value)
            else:
                lines += t
        return lines

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
