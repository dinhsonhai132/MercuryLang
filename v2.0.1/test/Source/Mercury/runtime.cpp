#include "runtime.h"

RunTimeVal valuelize(string type, float value) {
    RunTimeVal val;
    val.type = type;
    val.value = value;
    return val;
}

RunTimeVal *valuelize_as_ptr(string type, float value) {
    RunTimeVal *val;
    val->type = type;
    val->string_iden = value;
    return val;
}