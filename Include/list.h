#ifndef MERCURY_LIST_HEADER_FILE
#define MERCURY_LIST_HEADER_FILE

#include "Mercury.h"
#include "stack.h"

float __list_value(mList_T *list);

#define MAKE_LIST_VALUE(list) __list_value(list)

#define list_v(a) (a->list_v)
#define list_size(a) (a->list_v->size)
#define list_args(a) (a->list_v->args)
#define list_is_empty(a) (a->list_v->size == 0)
#define set_size(a, lsize) (a->list_v->size = lsize)

#endif // MERCURY_LIST_HEADER_FILE