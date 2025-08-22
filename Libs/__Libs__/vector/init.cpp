#include <Mercury.h>
#include "expr.hpp"

START_DLL

DLL_EXPORT table* extend(table* args[]) {
    table *item1 = args[0];
    table *item2 = args[1];

    if (item1->is_list && item2->is_list) {
        item1->list_v->args.insert(item1->list_v->args.end(), item2->list_v->args.begin(), item2->list_v->args.end());
        item1->list_v->size += item2->list_v->size;
        return item1;
    } else if (item1->is_str && item2->is_str) {
        item1->f_str_v->buff.insert(item1->f_str_v->buff.end(), item2->f_str_v->buff.begin(), item2->f_str_v->buff.end());
        item1->f_str_v->size += item2->f_str_v->size;
        return item1;
    } else {
        item1->cval += item2->cval;
        item1->value += item2->value;
        return item1;
    }
}

DLL_EXPORT table* insert(table* args[]) {
    table *list = args[0];
    table *index = args[1];
    table *item = args[2];

    if (list->is_list) {
        if (item->is_list) {
            list->list_v->args.insert(list->list_v->args.begin() + index->cval, item->list_v->args.begin(), item->list_v->args.end());
            list->list_v->size += item->list_v->size;
        } else {
            list->list_v->args.insert(list->list_v->args.begin() + index->cval, item);
            list->list_v->size++;
        }
    } else if (list->is_str) {
        if (item->is_str) {
            list->f_str_v->buff.insert(list->f_str_v->buff.begin() + index->cval, item->f_str_v->buff.begin(), item->f_str_v->buff.end());
            list->f_str_v->size += item->f_str_v->size;
        } else {
            return list;
        }
    } else {
        return list;
    }

    return list;
}

DLL_EXPORT table* insert_item(table* args[]) {
    table *list = args[0];
    table *index = args[1];
    table *item = args[2];

    list->list_v->args.insert(list->list_v->args.begin() + index->cval, item);

    return list;
}

float __eval(string expr) {
    return Expr::eval(expr);
}

DLL_EXPORT table* eval(table* args[]) {
    table *expr = args[0];
    if (!expr->is_str) {
        return expr;
    }

    string str = __convert_to_string(expr->f_str_v);
    return MER_VALUE(__eval(str));
}

DLL_EXPORT table* to_list(table* args[]) {
    table *list = args[0];

    if (list->is_str) {
        table *val = MerCompiler_Table_new();
        
        val->is_list = true;
        val->list_v = MerCompiler_list_object_new();

        for (auto &charr : list->f_str_v->buff) {
            mString_T *str = MerCompiler_string_new();
            str->buff.push_back(charr);
            str->size = 1;

            table *str_tab = MerCompiler_Table_new();
            str_tab->is_str = true;
            str_tab->f_str_v = str;
            str_tab->cval = __hash(str);
            str_tab->value = str_tab->cval;

            val->list_v->args.push_back(str_tab);
            val->list_v->size++;
        }
    } else {
        return list;
    }

    return list;
}

END_DLL