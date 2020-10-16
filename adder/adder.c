// Python.h содержит все необходимые функции, для работы с объектами Python
#include <Python.h>

// Эту функцию мы вызываем из Python кода
static PyObject* addList_add(PyObject* self, PyObject* args){
  printf("Hello from printf\n");

  PyObject * listObj;

  // Входящие аргументы находятся в кортеже
  // В нашем случае есть только один аргумент - список, на который мы будем
  // ссылаться как listObj
  if (! PyArg_ParseTuple( args, "O", &listObj))
    return NULL;

  // Длина списка
  size_t length = PyList_Size(listObj);

  // Проходимся по всем элементам
  long sum = 0;
  for(size_t i = 0; i < length; ++i){
    // Получаем элемент из списка - он также Python-объект
    PyObject* temp = PyList_GetItem(listObj, i);
    // Мы знаем, что элемент это целое число - приводим его к типу C long
    long elem = PyLong_AsLong(temp);
    sum += elem;
  }

  // Возвращаемое в Python-код значение также Python-объект
  // Приводим C long к Python integer
  return Py_BuildValue("i", sum);
}

// Немного документации для `add`
static char addList_docs[] =
    "add( ): add all elements of the list\n";

/*
Эта таблица содержит необходимую информацию о функциях модуля
<имя функции в модуле Python>, <фактическая функция>,
<ожидаемые типы аргументов функции>, <документация функции>
*/
static PyMethodDef addList_funcs[] = {
    {"add", (PyCFunction)addList_add, METH_VARARGS, addList_docs},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef addList =
{
    PyModuleDef_HEAD_INIT,
    "addList", /* name of module */
    "usage: addList.add([1,2,3...])\n", /* module documentation, may be NULL */
    -1,   /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    addList_funcs
};

PyMODINIT_FUNC PyInit_addList(void)
{
    return PyModule_Create(&addList);
}