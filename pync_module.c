#include <Python.h>

#include "pync.h"

static PyObject *
pync_increment (PyObject *self, PyObject *args)
{
   increment ();
   Py_RETURN_NONE;
}

static PyObject *
pync_decrement (PyObject *self, PyObject *args)
{
   decrement ();
   Py_RETURN_NONE;
}

static PyObject *
pync_reset (PyObject *self, PyObject *args)
{
   reset ();
   Py_RETURN_NONE;
}

static PyObject *
pync_get_number (PyObject *self, PyObject *args)
{
   return Py_BuildValue ("i", get_number ());
}

static PyMethodDef PyncStuff[] = {
   { "increment", pync_increment, METH_VARARGS, "Increment the counter" },
   { "decrement", pync_decrement, METH_VARARGS, "Decrement the counter" },
   { "reset", pync_reset, METH_VARARGS, "Reset the counter value" },
   { "get_number", pync_get_number, METH_VARARGS, "Get the current counter value" },
   { NULL, NULL, 0, NULL },
};

static struct PyModuleDef pyncmod
    = { PyModuleDef_HEAD_INIT, "pync", NULL, -1, PyncStuff };

PyMODINIT_FUNC
PyInit_pync (void)
{
   return PyModule_Create (&pyncmod);
}
