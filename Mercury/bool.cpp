#include "../include/bool.h"

mBool_T *make_bool(bool value) {
    mBool_T *boolen = MerCompiler_bool_new();
    if (value) {
        boolen->value = true;
    } else {
        boolen->value = false;
    }

    return boolen;
}

table *make_true_value() {
    table *bool_obj = MerCompiler_Table_new();
    bool_obj->bool_v = MerCompiler_bool_new();
    bool_obj->bool_v->value = true;
    bool_obj->is_bool = true;
    bool_obj->cval = 1;
    return bool_obj;
}

table *make_false_value() {
    table *bool_obj = MerCompiler_Table_new();
    bool_obj->bool_v = MerCompiler_bool_new();
    bool_obj->bool_v->value = false;
    bool_obj->is_bool = true;
    bool_obj->cval = 0;
    return bool_obj;
}