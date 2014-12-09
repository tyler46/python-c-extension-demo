from distutils.core import setup, Extension

setup(name='cenviron',
      version='2.0',
      description='A simple get/set environment variable example',
      py_modules=['envattr'],
      ext_modules=[Extension('cenviron', ['src/cenviron.c'])])
