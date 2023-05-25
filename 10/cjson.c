#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "elem.h"

static PyObject* CJsonError;

static PyObject* cjson_loads(PyObject* self, PyObject* args)
{
    char* jsonstr;

    if (!PyArg_ParseTuple(args, "s", &jsonstr))
        return NULL;

    // Строка в словарь
    PyObject* dict = PyDict_New();
    if (!dict) {
        PyErr_SetString(CJsonError, "ERROR: Failed to create Dict Object");
        return NULL;
    }

    Elem *elem = elem_new();

    elem_parse(jsonstr, &elem);

    Elem_Iterator* iterator = elem_iterator(elem);

    while (iterator->elem->next)
    {
        char* key_parsed = elem_keys_iterate(elem, &iterator);

        char* val_parsed = NULL;

        elem_get(elem, key_parsed, &val_parsed);
        
        PyObject* key = Py_BuildValue("s", key_parsed);
        if (!key) {
            PyErr_SetString(CJsonError, "ERROR: Failed to build string value");
            return NULL;
        }

        PyObject* value = Py_BuildValue("s", val_parsed);
        if (!value) {
            PyErr_SetString(CJsonError,  "ERROR: Failed to build string value");
            return NULL;
        }

        if (PyDict_SetItem(dict, key, value) < 0) {
            PyErr_SetString(CJsonError,  "ERROR: Failed to set item");
            return NULL;
        }
    }

    elem_free(elem);

    return dict;
}

static const char* get_const_char(PyObject *obj) {
    PyObject* repr = PyObject_Repr(obj);
    PyObject* str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
    const char *bytes = PyBytes_AS_STRING(str);

    Py_XDECREF(repr);
    Py_XDECREF(str);

    return bytes;
}

static PyObject* cjson_dumps(PyObject* self, PyObject* args)
{   
    PyObject* dict;

    if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &dict))
    {
        PyErr_SetString(CJsonError, "ERROR: failed to parse dict");
        return NULL;
    }
}

static PyMethodDef CJsonMethods[] = {
    {"loads", cjson_loads, METH_VARARGS, "Loads JSON into dict"},
    {"dumps", cjson_dumps, METH_VARARGS, "Dumps JSON dict to a string"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef cjsonmodule = {
    PyModuleDef_HEAD_INIT,
    "cjson",
    "My json mdule on C",
    -1,
    CJsonMethods
};

PyMODINIT_FUNC PyInit_cjson(void)
{
    PyObject* m;
    m = PyModule_Create(&cjsonmodule);
    if (m == NULL)
        return NULL;

    CJsonError = PyErr_NewException("cjson.error", NULL, NULL);
    Py_XINCREF(CJsonError);
    if (PyModule_AddObject(m, "error", CJsonError) < 0) {
        Py_XDECREF(CJsonError);
        Py_CLEAR(CJsonError);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}