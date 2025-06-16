#ifndef MERCURY_LIST_HEADER_FILE
#define MERCURY_LIST_HEADER_FILE

#include "Mercury.h"
#include "stack.h"

float __list_value(mList_T *list);

#define MAKE_LIST_VALUE(list) __list_value(list)

#endif // MERCURY_LIST_HEADER_FILE