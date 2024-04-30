#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *cvarint_encode(PyObject *self, PyObject *args) {
  unsigned long long n;
  char s[10], part;
  int i = 0;
  if (!PyArg_ParseTuple(args, "k", &n))
    return NULL;
  while (n > 0) {
    part = n & 0x7f;
    n >>= 7;
    if (n > 0) {
      part |= 0x80;
    }
    s[i++] = part;
  }
  return PyBytes_FromStringAndSize(s, i);
}

static PyObject *cvarint_decode(PyObject *self, PyObject *args) {

  const char *s;
  unsigned long n = 0;
  if (!PyArg_ParseTuple(args, "s#", &s))
    return NULL;
  size_t size = strlen(s);
  for (int i = size - 1; i >= 0; i--) {
    n <<= 7;
    n |= (s[i] & 0x7f);
  }
  return PyLong_FromUnsignedLongLong(n);
}

static PyMethodDef CVarintMethods[] = {
    {"encode", cvarint_encode, METH_VARARGS, "Encode an integer as varint."},
    {"decode", cvarint_decode, METH_VARARGS,
     "Decode varint bytes to an integer."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef cvarintmodule = {
    PyModuleDef_HEAD_INIT, "cvarint",
    "A C implementation of protobuf varint encoding", -1, CVarintMethods};

PyMODINIT_FUNC PyInit_cvarint(void) { return PyModule_Create(&cvarintmodule); }
