from aspect.pointcut import Pointcut


class Aspect:
    def __init__(self, advice, pointcut, body):
        self.advice = advice
        self.pointcut = pointcut
        self.body = body

    # def weave(self):
    #     pass
