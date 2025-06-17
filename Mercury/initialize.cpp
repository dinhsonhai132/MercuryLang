#include "../include/initialize.h"

MERCURY_API void MerCore_initialize() {
    BUILD_LIB_FUNC("write", __builtin_io_write);
    BUILD_LIB_FUNC("print", __builtin_io_write);
    BUILD_LIB_FUNC("eval", __builtin_eval);
    BUILD_LIB_FUNC("pause", __builtin_pause);
    BUILD_LIB_FUNC("exit", __mer_builtin_exit);
    BUILD_LIB_FUNC("cls", __builtin_cls);
    BUILD_LIB_FUNC("help", __builtin_help);
    BUILD_LIB_FUNC("same", __builtin_same_string);
    BUILD_LIB_FUNC("size", __builtin_size);
    BUILD_LIB_FUNC("push", __builtin_push);
    BUILD_LIB_FUNC("pop", __builtin_pop);
    BUILD_LIB_FUNC("watch", __builtin_watch);
    BUILD_LIB_FUNC("puts", __builtin_puts_val);
    BUILD_LIB_FUNC("cos", __builtin_mer_cos);
    BUILD_LIB_FUNC("tan", __builtin_mer_tan);
    BUILD_LIB_FUNC("cot", __builtin_mer_cot);
    BUILD_LIB_FUNC("sqrt", __builtin_mer_sqrt);
    BUILD_LIB_FUNC("sleep", __builtin_mer_sleep);
    BUILD_LIB_FUNC("sin", __builtin_mer_sin);
    BUILD_LIB_FUNC("glb", __builtin_print_global_stack);
    BUILD_LIB_FUNC("ch", __builtin_change_item);
    BUILD_LIB_FUNC("type", __builtin_type);
    BUILD_LIB_FUNC("range", __builtin_range);
    BUILD_LIB_FUNC("randint", __builtin_randint);
    BUILD_LIB_FUNC("sub", __builtin_mer_sub);
    BUILD_LIB_FUNC("to_list", __builtin_mer_list);
    BUILD_LIB_FUNC("isdigit", __builtin_mer_is_digit);
    BUILD_LIB_FUNC("to_str", __builtin_to_string);
    BUILD_LIB_FUNC("to_int", __builtin_to_int);
    BUILD_LIB_FUNC("input", __builtin_mer_read_line);
    BUILD_LIB_FUNC("split", __builtin_mer_split);

    BUILD_GLOBAL_VARIABLE("pi", 3.1415926535897932384626433832795);
    BUILD_GLOBAL_VARIABLE("e", 2.7182818284590452353602874713527);
    BUILD_GLOBAL_VARIABLE("inf", INFINITY);
    BUILD_GLOBAL_VARIABLE("tau", 6.283185307179586476925286766559);
    BUILD_GLOBAL_VARIABLE("gr", 1.6180339887498948482045868343656);
}   

MERCURY_API void MerCore_Finalize(void) {
    _G.clear();
    _L.clear();
    GLOBAL_TABLE.clear();
    mer_core_libs.clear();
    STRING_ENTRY.clear();
}