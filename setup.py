from distutils.core import setup, Extension
_getch = Extension('_getch', sources=['getch.c'])

setup(name='getch', ext_modules=[_getch])
