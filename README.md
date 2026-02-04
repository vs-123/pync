# PYNC

Pync is a simple Python module written in C, for demonstrative purposes.

## BUILD INSTRUCTIONS

Clone this reposintory:
```
   %  git clone https://github.com/vs-123/pync
   %  cd pync/
```

Build the module using GNU Make:
```
   %  make b
   %  ls pync.so
   pync.so*
```

Edit `pync.py`:   (optional)
```
   % vi pync.py   # or any editor you prefer
```

Run `pync.py`:
```
   %  python3 pync.py 
   [PYNC.PY] INCREMENT LOOP: 256
   [PYNC.PY] INCREMENT TWICE: 258
   [PYNC.PY] DECREMENT: 257
   [PYNC.PY] RESET: 0
```

Clean: (optional)
```
   %  make c
   rm pync.so
```

## IMPLEMENTATION DETAILS

We implement the core library in `pync.h` and `pync.c`.

```c
/* ----- pync.h ----- */
#ifndef PYNC_H
#define PYNC_H

void increment(void);
void decrement(void);
void reset(void);
int get_number(void);

#endif /* PYNC_H */

/* ----- pync.c ----- */
#include "pync.h"

static int counter = 0;

void increment (void)
{
   counter++;
}

void decrement (void)
{
   counter--;
}

void reset (void)
{
   counter = 0;
}

int get_number (void)
{
   return counter;
}
```

Simple enough, right?

Now the *real* magic happens in `pync_module.c`

`pync_module.c` does the talking with Python. It essentially utilises Python's CPython API to wrap our library to make it callable from Python.


We first include the CPython API along with our library.

```c
#include <Python.h>

#include "pync.h"
```

We wrap our library's functions in functions that deal with `PyObject`s.

```c
static PyObject *pync_increment (PyObject *self, PyObject *args)
{
   increment ();
   Py_RETURN_NONE;
}

static PyObject *pync_decrement (PyObject *self, PyObject *args)
{
   decrement ();
   Py_RETURN_NONE;
}

static PyObject *pync_reset (PyObject *self, PyObject *args)
{
   reset ();
   Py_RETURN_NONE;
}

static PyObject *pync_get_number (PyObject *self, PyObject *args)
{
   return Py_BuildValue ("i", get_number ());
}
```

Next, we map these wrapped functions into a Python "module":

```c
static PyMethodDef PyncStuff[] = {
   { "increment", pync_increment, METH_VARARGS, "Increment the counter" },
   { "decrement", pync_decrement, METH_VARARGS, "Decrement the counter" },
   { "reset", pync_reset, METH_VARARGS, "Reset the counter value" },
   { "get_number", pync_get_number, METH_VARARGS, "Get the current counter value" },
   { NULL, NULL, 0, NULL },
};

static struct PyModuleDef pyncmod = { PyModuleDef_HEAD_INIT, "pync", NULL, -1, PyncStuff };
```

Finally, we initialise the module so Python can actually use it:

```c
PyMODINIT_FUNC PyInit_pync (void)
{
   return PyModule_Create (&pyncmod);
}
```

## LICENSE

This project is released under the GNU Affero General Public License version 3.0 or later.

For more information, see `LICENSE` or visit **https://www.gnu.org/licenses/agpl-3.0.en.html**.
