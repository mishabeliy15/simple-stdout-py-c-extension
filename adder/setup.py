# Собираем модули

from distutils.core import setup, Extension

adderExt = Extension(
    'addList',
    sources=['adder.c']
)

setup(
    name='addList',
    version='1.0',
    ext_modules=[adderExt],
)

# Run python3 setup.py install