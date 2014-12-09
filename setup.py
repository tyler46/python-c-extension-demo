from setuptools import setup, Extension

setup(name='cenviron',
      version='3.0',
      description='A simple get/set environment variable example',
      author="Tyler Durden",
      author_email="mail.doctor46@gmail.com",
      url="https://github.com/tyler46/python-c-extension-demo",
      py_modules=['envattr'],
      ext_modules=[Extension('cenviron', ['src/cenviron.c'])])
