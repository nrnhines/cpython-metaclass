# See https://stackoverflow.com/questions/67077317/how-to-define-a-python-metaclass-from-c-extension
# https://github.com/ezyang/cpython-metaclass
# Build in place with: pip install -e .


def p(s):
    print(s, eval(s))


import demo

fp = demo.fooparent()
p("fp")
p("type(fp)")
p("type(type(fp))")
p("type(type(type(fp)))")

p("fp[3]")
p("type(fp)[5]")
