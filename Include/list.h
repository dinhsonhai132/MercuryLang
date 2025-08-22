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

table *creat_list(vector<void *> args);

mList_T *creat_list_obj(vector<void *> args);
mList_T *add_list(mList_T *a, mList_T *b);
mList_T *mul_list(mList_T *a, int times);

void insert_elem(table *list_table, void *elem);
void extend_list(table *list_table, vector<void *> args);
void clear_list(table *list_table);
void del_elem(table *list_table, int index);
void pop_elem(table *list_table);

#endif // MERCURY_LIST_HEADER_FILE