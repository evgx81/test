from distutils.core import setup, Extension

module_name = "cjson"
c_files = ["cjson.c"]

extension = Extension(
    module_name,
    c_files
)

setup(
    name=module_name,
    version="0.1",
    description="My CJson module",
    author="evgx81",
    author_email="my_email@mail.ru",
    url="https://github.com/evgx81",
    ext_modules=[extension]
)
