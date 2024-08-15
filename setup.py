from distutils.core import setup, Extension

module1 = Extension("demo", sources=["demo.cpp"], extra_compile_args=["-O0"])

setup(
    name="PackageName",
    version="1.0",
    description="This is a demo package",
    ext_modules=[module1],
)
