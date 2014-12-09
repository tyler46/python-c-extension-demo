#include "Python.h"

typedef struct {
    PyObject_HEAD
} cenviron_CenvironObject;

/* 1. Module functions */

static PyObject *
wrap_getenv(PyObject *self, PyObject *args)
{
    char *varName, *varValue;
    PyObject *returnObj = NULL;

    if (PyArg_ParseTuple(args, "s:wrap_getenv", &varName)) {
        varValue = getenv(varName);
        if (varValue != NULL)
            returnObj = Py_BuildValue("s", varValue);
        else
            PyErr_SetString(PyExc_SystemError, "Error calling getenv");
    }
    return returnObj;
}


static PyObject *
wrap_putenv(PyObject *self, PyObject *args)
{
    char *varName, *varValue, *varAssign;
    PyObject *returnObj = NULL;

    if (PyArg_Parse(args, "(ss)", &varName, &varValue))
    {
        varAssign = malloc(strlen(varName) + strlen(varValue) + 2);
        sprintf(varAssign, "%s=%s", varName, varValue);
        if (putenv(varAssign) == 0) {
            Py_INCREF(Py_None);
            returnObj = Py_None;
        }
        else
            PyErr_SetString(PyExc_SystemError, "Error calling putenv");
    }
    return returnObj;
}

/* registration table */
static PyMethodDef cenviron_methods[] = {
    {"getenv",          (PyCFunction)wrap_getenv,  METH_VARARGS,
        PyDoc_STR("getenv -> displays the value of an enviroment variable.")},
    {"putenv",          (PyCFunction)wrap_putenv,  METH_VARARGS,
        PyDoc_STR("putenv -> sets a value of an enviroment variable.")},
    {NULL, NULL, 0, NULL}           /* sentinel */
};

PyDoc_STRVAR(cenviron_doc,
"cenviron documentation.");


//  static PyTypeObject cenviron_CenvironType = {
//      PyVarObject_HEAD_INIT(NULL, 0)
//      "cenviron",                   /*tp_name*/
//      sizeof(cenviron_CenvironObject),               /*tp_basicsize*/
//      0,                                  /*tp_itemsize*/
//      /* methods */
//      0,                                  /*tp_dealloc*/
//      0,                                  /*tp_print*/
//      0,                                  /*tp_getattr*/
//      0,                                  /*tp_setattr*/
//      0,                                  /*tp_compare*/
//      0,                                  /*tp_repr*/
//      0,                                  /*tp_as_number*/
//      0,                                  /*tp_as_sequence*/
//      0,                                  /*tp_as_mapping*/
//      0,                                  /*tp_hash*/
//      0,                                  /*tp_call*/
//      0,                                  /*tp_str*/
//      PyObject_GenericGetAttr,            /*tp_getattro*/
//      0,                                  /*tp_setattro*/
//      0,                                  /*tp_as_buffer*/
//      Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,           /*tp_flags*/
//      cenviron_doc,                         /*tp_doc*/
//      0,                                  /*tp_traverse*/
//      0,                                  /*tp_clear*/
//      0,                                  /*tp_richcompare*/
//      0,                                  /*tp_weaklistoffset*/
//      0,                                  /*tp_iter*/
//      0,                                  /*tp_iternext*/
//      cenviron_methods,                     /*tp_methods*/
//      0,                                  /*tp_members*/
//      0,                                  /*tp_getset*/
//      0,                                  /*tp_base*/
//      0,                                  /*tp_dict*/
//      0,                                  /*tp_descr_get*/
//      0,                                  /*tp_descr_set*/
//      0,                                  /*tp_dictoffset*/
//      0,                                  /*tp_init*/
//      0,                                  /*tp_alloc*/
//      0,                         /*tp_new*/
//      _PyObject_Del,                      /*tp_free*/
//      0,                                  /*tp_is_gc*/
//  };


PyDoc_STRVAR(module_doc,
"Module implements a set/get enviroment variables program.");

PyMODINIT_FUNC
initcenviron(void)
{
    (void) Py_InitModule("cenviron", cenviron_methods);
}

//  PyMODINIT_FUNC
//  initcenviron(void)
//  {
//      PyObject *m;

//      if (PyType_Ready(&cenviron_CenvironType) < 0)
//          return;
//      m = Py_InitModule3("cenviron", NULL, module_doc);
//      if (m == NULL)
//          return;
//      Py_INCREF(&cenviron_CenvironType);
//      PyModule_AddObject(m, "Cenviron", (PyObject *)&cenviron_CenvironType);
//  }
