#include "../include/initialize.h"

MERCURY_API void MerCore_initialize() {
    BUILD_LIB_FUNC("pause", __builtin_pause);
    BUILD_LIB_FUNC("exit", __mer_builtin_exit);
    BUILD_LIB_FUNC("same", __builtin_same_string);
    BUILD_LIB_FUNC("size", __builtin_size);
    BUILD_LIB_FUNC("push", __builtin_push);
    BUILD_LIB_FUNC("pop", __builtin_pop);
    BUILD_LIB_FUNC("puts", __builtin_puts_val);
    BUILD_LIB_FUNC("sleep", __builtin_mer_sleep);
    BUILD_LIB_FUNC("type", __builtin_type);
    BUILD_LIB_FUNC("range", __builtin_range);
    BUILD_LIB_FUNC("randint", __builtin_randint);
    BUILD_LIB_FUNC("sub", __builtin_mer_sub);
    BUILD_LIB_FUNC("input", __builtin_mer_read_line);
    BUILD_LIB_FUNC("to_list", __builtin_mer_list);
    BUILD_LIB_FUNC("to_str", __builtin_to_string);
    BUILD_LIB_FUNC("to_int", __builtin_to_int);

    BUILD_GLOBAL_VARIABLE("inf", INFINITY);
}   

MERCURY_API void MerCore_Finalize(void) {
    _G.clear();
    _L.clear();
    GLOBAL_TABLE.clear();
    mer_core_libs.clear();
    STRING_ENTRY.clear();
}