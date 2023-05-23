#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "kson.h"

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

    Kson *kson = kson_new();

    kson_parse(jsonstr, &kson);

    Kson_Iterator* iterator = kson_iterator(kson);

    while (iterator->kson->next)
    {
        char* key_parsed = kson_keys_iterate(kson, &iterator);

        char* val_parsed = NULL;

        kson_get(kson, key_parsed, &val_parsed);
        
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

    kson_free(kson);

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

    PyArg_ParseTuple(args, "O!", &PyDict_Type, &dict);

    PyObject* key;
    PyObject* value;
    Py_ssize_t ppos = 0;

    Kson *kson = kson_new();

    while (PyDict_Next(&dict, &ppos, &key, &value)) 
    {
        const char* key_str = get_const_char(key);

        const char* value_str = get_const_char(value);

        kson_put(&kson, key_str, value_str);
    }

    char* jsonstr = NULL;

    kson_pack(&kson, &jsonstr);

    kson_free(kson);

    return jsonstr;
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