#include "../include/list.h"

float __list_value(mList_T *list) {
    size_t seed = list->args.size();

    for (size_t i = 0; i < list->args.size(); i++) {
        float val = ((table *)list->args[i])->cval;

        uint32_t int_val;
        memcpy(&int_val, &val, sizeof(float));

        seed ^= int_val * i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    float result;
    memcpy(&result, &seed, sizeof(float));
    return result;
}

mList_T *creat_list_obj(vector<void *> args) {
    mList_T *list = MerCompiler_list_object_new();
    list->size = args.size();
    list->args = args;
    return list;
}

mList_T *add_list(mList_T *a, mList_T *b) {
    mList_T *list = MerCompiler_list_object_new();
    list->size = a->size + b->size;
    list->args.insert(list->args.end(), a->args.begin(), a->args.end());
    list->args.insert(list->args.end(), b->args.begin(), b->args.end());
    return list;
}

mList_T *mul_list(mList_T *a, int times) {
    mList_T *list = MerCompiler_list_object_new();
    list->size = a->size * times;
    for (int i = 0; i < times; i++) {
        list->args.insert(list->args.end(), a->args.begin(), a->args.end());
    }
    return list;
}

table *creat_list(vector<void *> args) {
    table *list_table = MerCompiler_Table_new();
    list_table->is_list = true;
    list_table->list_v = creat_list_obj(args);
    list_table->list_v->size = list_table->list_v->args.size();
    list_table->cval = __list_value(list_table->list_v);
    return list_table;
}

void insert_elem(table *list_table, void *elem) {
    list_table->list_v->args.push_back(elem);
    list_table->list_v->size = list_table->list_v->args.size();
    list_table->cval = __list_value(list_table->list_v);
}

void extend_list(table *list_table, vector<void *> args) {
    list_table->list_v->args.insert(list_table->list_v->args.end(), args.begin(), args.end());
    list_table->list_v->size = list_table->list_v->args.size();
    list_table->cval = __list_value(list_table->list_v);
}

void clear_list(table *list_table) {
    list_table->list_v->args.clear();
    list_table->list_v->size = list_table->list_v->args.size();
    list_table->cval = __list_value(list_table->list_v);
}

void del_elem(table *list_table, int index) {
    list_table->list_v->args.erase(list_table->list_v->args.begin() + index);
    list_table->list_v->size = list_table->list_v->args.size();
    list_table->cval = __list_value(list_table->list_v);
}

void pop_elem(table *list_table) {
    list_table->list_v->args.pop_back();
    list_table->list_v->size = list_table->list_v->args.size();
    list_table->cval = __list_value(list_table->list_v);
}