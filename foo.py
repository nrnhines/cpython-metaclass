import demo

class foometa(metaclass=demo.foometa):
    pass

class A(demo.fooparent):
    pass

class B(demo.fooparent):
    pass

class foohocclass(metaclass=demo.hocclass):
    pass

