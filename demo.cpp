#include <Python.h>
#include <iostream>

struct foometa {
    PyTypeObject head;
};

int foometa_init(foometa *cls, PyObject *args, PyObject *kwargs) {
    if (PyType_Type.tp_init((PyObject*)cls, args, kwargs) < 0) {
      return -1;
    }
    std::cerr << "I'm called on class construction time!\n";
    return 0;
}

static PyObject* foometa_getitem(PyObject* self, Py_ssize_t ix) {
    printf("foometa_getitem %zd\n", ix);
    PyObject_Print(self, stdout, 0);
    printf("\n");
    return Py_None;
}

static PySequenceMethods foometa_seqmeth = {
    NULL, NULL, NULL, foometa_getitem,
    NULL, NULL, NULL, NULL,
    NULL, NULL
};


#define DEFERRED_ADDRESS(ADDR) nullptr

static PyTypeObject foometa_type = {
    PyVarObject_HEAD_INIT(DEFERRED_ADDRESS(&PyType_Type), 0)
    "demo.foometa",
    0,
    0,
    0,                                          /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    0,                                          /* tp_repr */
    0,                                          /* tp_as_number */
    &foometa_seqmeth,                            /* tp_as_sequence */
    0,                                          /* tp_as_mapping */
    0,                                          /* tp_hash */
    0,                                          /* tp_call */
    0,                                          /* tp_str */
    0,                                          /* tp_getattro */
    0,                                          /* tp_setattro */
    0,                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    0,                                          /* tp_doc */
    0,                                          /* tp_traverse */
    0,                                          /* tp_clear */
    0,                                          /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    0,                           /* tp_methods */
    0,                                          /* tp_members */
    0,                           /* tp_getset */
    DEFERRED_ADDRESS(&PyType_Type),             /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    (initproc)foometa_init,                    /* tp_init */
    0,                                          /* tp_alloc */
    0                                           /* tp_new */
};

struct hocclass {
    PyTypeObject head;
};

static int hocclass_init(hocclass *cls, PyObject *args, PyObject *kwds) {
    if (PyType_Type.tp_init((PyObject*)cls, args, kwds) < 0) {
        return -1;
    }
    printf("hocclass_init\n");
    return 0;
}

static PyObject* hocclass_getitem(PyObject* self, Py_ssize_t ix) {
    printf("hocclass_getitem %zd\n", ix);
    PyObject_Print(self, stdout, 0);
    printf("\n");
    return Py_None;
}

// Note use of slots was informed by nanobind (search for nb_meta)

static PyType_Slot hocclass_slots[] = {
    {Py_tp_base, nullptr}, // &PyType_Type : not obvious why it must be set at runtime
    {Py_tp_init, (void *)hocclass_init},
    {Py_sq_item, (void *)hocclass_getitem},
    {0, NULL}
};

static PyType_Spec hocclass_spec = {
    .name = "demo.hocclass",
    .basicsize = 0,
    .itemsize = 0,
    .flags = Py_TPFLAGS_DEFAULT, //  | Py_TPFLAGS_HEAPTYPE,
    .slots = hocclass_slots
};

PyObject *hocobject_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    PyObject* obj = type->tp_alloc(type, 0);
    return obj;
}   

static PyObject* hocobject_getitem(PyObject* self, Py_ssize_t ix) {
    printf("hocobject_getitem %zd\n", ix);
    PyObject_Print(self, stdout, 0);   
    printf("\n");
    return Py_None;
}

static PyType_Slot hocobject_slots[] = {
    {Py_tp_new, (void *)hocobject_new},
    {Py_sq_item, (void *)hocobject_getitem},
    {0, NULL}
};   
    
static PyType_Spec hocobject_spec = {
    .name = "demo.hocobject",
    .basicsize = 0,
    .itemsize = 0,
    .flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .slots = hocobject_slots
};


PyObject *fooparent_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    PyObject* obj = type->tp_alloc(type, 0);
    return obj;
}

static PyObject* fooparent_getitem(PyObject* self, Py_ssize_t ix) {
    printf("fooparent_getitem %zd\n", ix);
    PyObject_Print(self, stdout, 0);
    printf("\n");
    return Py_None;
}

static PySequenceMethods fooparent_seqmeth = {
    NULL, NULL, NULL, fooparent_getitem,
    NULL, NULL, NULL, NULL,
    NULL, NULL
};

static PyTypeObject fooparent_type = {
    PyVarObject_HEAD_INIT(&foometa_type, 0)
    "demo.fooparent",
    sizeof(PyObject),
    0,
    0,                                          /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    0,                                          /* tp_repr */
    0,                                          /* tp_as_number */
    &fooparent_seqmeth,                         /* tp_as_sequence */
    0,                                          /* tp_as_mapping */
    0,                                          /* tp_hash */
    0,                                          /* tp_call */
    0,                                          /* tp_str */
    0,                                          /* tp_getattro */
    0,                                          /* tp_setattro */
    0,                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    0,                                          /* tp_doc */
    0,                                          /* tp_traverse */
    0,                                          /* tp_clear */
    0,                                          /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    0,                           /* tp_methods */
    0,                                          /* tp_members */
    0,                           /* tp_getset */
    0,             /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    0,                    /* tp_init */
    0,                                          /* tp_alloc */
    fooparent_new                                           /* tp_new */
};

#if PY_VERSION_HEX < 0x030C0000
#define TYPE_FROM_METACLASS_IMPL 1
#else
#define TYPE_FROM_METACLASS_IMPL 0
#endif

static PyObject *type_from_metaclass(PyTypeObject *meta, PyObject *mod,
                                        PyType_Spec *spec) {
#if TYPE_FROM_METACLASS_IMPL == 0
    return PyType_FromMetaclass(meta, mod, spec, nullptr);
#else
    // add the nanobind implementation from nb_type.cpp
    return nullptr;
#endif
}

int
demo_init(PyObject *m) {
    foometa_type.tp_base = &PyType_Type;
    if (PyType_Ready(&foometa_type) < 0) {
        return -1;
    }

    hocclass_slots[0].pfunc = (PyObject *) &PyType_Type;
    PyObject *custom_hocclass = PyType_FromSpec(&hocclass_spec);
    if (custom_hocclass == NULL) {
        return -1;
    }

    PyObject* custom_hocobject = type_from_metaclass((PyTypeObject*)custom_hocclass,
                                  m, &hocobject_spec);
    if (custom_hocobject == NULL) {
        return -1;
    }

    if (PyType_Ready(&fooparent_type) < 0) {
        return -1;
    }

    Py_INCREF(&foometa_type);
    if (PyModule_AddObject(m, "foometa", (PyObject *) &foometa_type) < 0) {
        return -1;
    }

    if (PyModule_AddObject(m, "hocclass", custom_hocclass) < 0) {
        return -1;
    }

    if (PyModule_AddObject(m, "hocobject", custom_hocobject) < 0) {
        return -1;
    }

    Py_INCREF(&fooparent_type);
    if (PyModule_AddObject(m, "fooparent", (PyObject *) &fooparent_type) < 0) {
         return -1;
    }
    return 0;
}

static PyModuleDef demomodule = {
    PyModuleDef_HEAD_INIT,
    "demo",
    "Example module",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC
PyInit_demo() {
    PyObject* m = PyModule_Create(&demomodule);
    if (m == nullptr) return nullptr;
    if (demo_init(m) < 0) return nullptr;
    return m;
}
