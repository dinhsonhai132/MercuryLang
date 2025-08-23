#include "../include/initialize.h"

MERCURY_API void MerCore_initialize() {
    BUILD_LIB_FUNC("print", __builtin_io_write);
    BUILD_LIB_FUNC("push", __builtin_push);
    BUILD_LIB_FUNC("pop", __builtin_pop);
    BUILD_LIB_FUNC("type", __builtin_type);
    BUILD_LIB_FUNC("puts", __builtin_puts_val);
    BUILD_LIB_FUNC("range", __builtin_range);
    BUILD_LIB_FUNC("same", __builtin_same_string);
    BUILD_LIB_FUNC("input", __builtin_mer_read_line);
    BUILD_LIB_FUNC("size", __builtin_size); 
    BUILD_LIB_FUNC("ord", __builtin_ord);
    BUILD_LIB_FUNC("chr", __builtin_chr);
    BUILD_LIB_FUNC("isdigit", __builtin_mer_is_digit);
    BUILD_LIB_FUNC("puts", __builtin_puts_val);
    BUILD_LIB_FUNC("dll_load", __builtin_dll_load_func);
    BUILD_LIB_FUNC("str", __builtin_to_string);
    BUILD_LIB_FUNC("int", __builtin_to_int);

    BUILD_GLOBAL_VARIABLE("inf", INFINITY);
}   

MERCURY_API void MerCore_Finalize(void) {
    _G.clear();
    _L.clear();
    GLOBAL_TABLE.clear();
    mer_core_libs.clear();
    STRING_ENTRY.clear();
}