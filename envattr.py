# -*- coding: utf-8 -*-
# Simple python wrapper that runs on top of internally defined C extension
# `cenviron` module.
import os
from cenviron import getenv, putenv


class EnvWrapper(object):

    def __setattr__(self, name, value):
        os.environ[name] = value
        putenv(name, value)

    def __getattr__(self, name):
        value = getenv(name)
        os.environ[name] = value
        return value


Env = EnvWrapper()
