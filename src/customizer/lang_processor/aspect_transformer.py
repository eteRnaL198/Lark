from customizer.aspect.advice import Advice
from customizer.aspect.aspect import Aspect
from customizer.aspect.basic_aspect import BasicAspect
from customizer.method.method import Method
from customizer.pointcut.execution import Execution
from customizer.lang_processor.base_transformer import BaseTransformer


class AspectTransformer(BaseTransformer):
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
