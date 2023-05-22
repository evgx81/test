#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject* CJsonError;

static PyObject* cjson_loads(PyObject* self, PyObject* args)
{
    const char* jsonstr;

    if (!PyArg_ParseTuple(args, "s", &jsonstr))
        return NULL;

    // Строка в словарь
    PyObject* dict = PyDict_New();
    if (!dict) {
        PyErr_SetString(CJsonError, "ERROR: Failed to create Dict Object");
        return NULL;
    }

    PyObject* key = Py_BuildValue("s", "value");
    if (!key) {
        PyErr_SetString(CJsonError, "ERROR: Failed to build string value");
        return NULL;
    }

    PyObject* value = Py_BuildValue("s", jsonstr);
    if (!value) {
        PyErr_SetString(CJsonError,  "ERROR: Failed to build string value");
        return NULL;
    }

    if (PyDict_SetItem(dict, key, value) < 0) {
        PyErr_SetString(CJsonError,  "ERROR: Failed to set item");
        return NULL;
    }

    return dict;
}

static PyObject* cjson_dumps(PyObject* self, PyObject* args)
{
    // Cловарь в строку
    PyErr_Format(PyExc_NotImplementedError, "Method not impemented yet");
    return NULL;
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