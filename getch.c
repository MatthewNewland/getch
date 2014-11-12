#include <stdio.h>
#if defined(__linux__) || defined(__CYGWIN__)
#include <termios.h>

static struct termios old, new;

static void
initTermios(int echo)
{
    tcgetattr(0, &old);
    new = old;
    new.c_lflag &= ~ICANON;
    new.c_lflag &= echo ? ECHO : ~ECHO;	/* set echo mode */
    tcsetattr(0, TCSANOW, &new);	/* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
static void
resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
static char
getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
static char
getch(void)
{
    return getch_(0);
}

/* Read 1 character with echo */
static char
getche(void)
{
    return getch_(1);
}
#elif defined(MS_WINDOWS) || defined(_WIN32)
#include <conio.h>
#endif

#if 0
/* Let's test it out */
int
main(void)
{
    char c;
    printf("(getche example) please type a letter: ");
    c = getche();
    printf("\nYou typed: %c\n", c);
    printf("(getch example) please type a letter...");
    c = getch();
    printf("\nYou typed: %c\n", c);
    return 0;
}
#endif

#include <Python.h>

static PyObject *
PyGetch_getch(PyObject *self, PyObject *args) 
{
    char c = getch();
    return Py_BuildValue("c", c);
}

static PyObject *
PyGetch_getche(PyObject *self, PyObject *args) 
{
    char c = getche();
    return Py_BuildValue("c", c);
}

static PyMethodDef GetchMethods[] = {
    { "getch", PyGetch_getch, METH_NOARGS, "getch" },
    { "getche", PyGetch_getche, METH_NOARGS, "getche" },
    { NULL, NULL, 0, NULL }
};

static PyModuleDef getchmodule = {
    PyModuleDef_HEAD_INIT,
    "_getch",
    NULL,
    -1,
    GetchMethods
};

PyMODINIT_FUNC
PyInit__getch(void)
{
    return PyModule_Create(&getchmodule);
}
 
