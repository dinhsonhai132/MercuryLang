#include "../include/initialize.h"

MERCURY_API void MerCore_initialize() {
    __register_global(lib_hashmap["help"], "help");
    __register_lib(lib_hashmap["help"], (void*) __builtin_help, "help");
    __register_lib_to_global(lib_hashmap["help"], (mFunc_T) __builtin_help);

    __register_global(lib_hashmap["exit"], "exit");
    __register_lib(lib_hashmap["exit"], (void*) __mer_builtin_exit, "exit");
    __register_lib_to_global(lib_hashmap["exit"], (mFunc_T) __mer_builtin_exit);

    __register_global(lib_hashmap["pause"], "pause");
    __register_lib(lib_hashmap["pause"], (void*) __builtin_pause, "pause");
    __register_lib_to_global(lib_hashmap["pause"], (mFunc_T) __builtin_pause);        

    __register_global(lib_hashmap["cls"], "cls");
    __register_lib(lib_hashmap["cls"], (void*) __builtin_cls, "cls");
    __register_lib_to_global(lib_hashmap["cls"], (mFunc_T) __builtin_cls);

    __register_global(lib_hashmap["write"], "write");
    __register_lib(lib_hashmap["write"], (void*)  __builtin_io_write, "write");
    __register_lib_to_global(lib_hashmap["write"], (mFunc_T) __builtin_io_write);

    __register_global(lib_hashmap["push"], "push");
    __register_lib(lib_hashmap["push"], (void*) __builtin_push, "push");
    __register_lib_to_global(lib_hashmap["push"], (mFunc_T) __builtin_push);

    __register_global(lib_hashmap["pop"], "pop");
    __register_lib(lib_hashmap["pop"], (void*) __builtin_pop, "pop");
    __register_lib_to_global(lib_hashmap["pop"], (mFunc_T) __builtin_pop);

    __register_global(lib_hashmap["type"], "type");
    __register_lib(lib_hashmap["type"], (void*) __builtin_type, "type");
    __register_lib_to_global(lib_hashmap["type"], (mFunc_T) __builtin_type);

    __register_global(lib_hashmap["ch"], "ch");
    __register_lib(lib_hashmap["ch"], (void*) __builtin_change_item, "ch");
    __register_lib_to_global(lib_hashmap["ch"], (mFunc_T) __builtin_change_item);

    __register_global(lib_hashmap["size"], "size");
    __register_lib(lib_hashmap["size"], (void*) __builtin_size, "size");
    __register_lib_to_global(lib_hashmap["size"], (mFunc_T) __builtin_size);

    __register_global(lib_hashmap["watch"], "watch");
    __register_lib(lib_hashmap["watch"], (void*) __builtin_watch, "watch");
    __register_lib_to_global(lib_hashmap["watch"], (mFunc_T) __builtin_watch);

    __register_global(lib_hashmap["puts"], "puts");
    __register_lib(lib_hashmap["puts"], (void*) __builtin_puts_val, "puts");
    __register_lib_to_global(lib_hashmap["puts"], (mFunc_T) __builtin_puts_val);

    __register_global(lib_hashmap["cos"], "cos");
    __register_lib(lib_hashmap["cos"], (void*) __builtin_mer_cos, "cos");
    __register_lib_to_global(lib_hashmap["cos"], (mFunc_T) __builtin_mer_cos);

    __register_global(lib_hashmap["tan"], "tan");
    __register_lib(lib_hashmap["tan"], (void*) __builtin_mer_tan, "tan");
    __register_lib_to_global(lib_hashmap["tan"], (mFunc_T) __builtin_mer_tan);

    __register_global(lib_hashmap["cot"], "cot");
    __register_lib(lib_hashmap["cot"], (void*) __builtin_mer_cot, "cot");
    __register_lib_to_global(lib_hashmap["cot"], (mFunc_T) __builtin_mer_cot);

    __register_global(lib_hashmap["sqrt"], "sqrt");
    __register_lib(lib_hashmap["sqrt"], (void*) __builtin_mer_sqrt, "sqrt");
    __register_lib_to_global(lib_hashmap["sqrt"], (mFunc_T) __builtin_mer_sqrt);

    __register_global(lib_hashmap["sin"], "sin");
    __register_lib(lib_hashmap["sin"], (void*) __builtin_mer_sin, "sin");
    __register_lib_to_global(lib_hashmap["sin"], (mFunc_T) __builtin_mer_sin);

    __register_global(lib_hashmap["glb"], "glb");
    __register_lib(lib_hashmap["glb"], (void*) __builtin_print_global_stack, "glb");
    __register_lib_to_global(lib_hashmap["glb"], (mFunc_T) __builtin_print_global_stack);

    __register_global(lib_hashmap["eval"], "eval");
    __register_lib(lib_hashmap["eval"], (void*) __builtin_eval, "eval");
    __register_lib_to_global(lib_hashmap["eval"], (mFunc_T) __builtin_eval);

    __register_global(lib_hashmap["cls"], "cls");
    __register_lib(lib_hashmap["cls"], (void*) __builtin_cls, "cls");
    __register_lib_to_global(lib_hashmap["cls"], (mFunc_T) __builtin_cls);

    __register_global_variable(global_hashmap["pi"], PI);
    __register_global_variable(global_hashmap["e"], EULER);
    __register_global_variable(global_hashmap["true"], 1);
    __register_global_variable(global_hashmap["false"], 0);
    __register_global_variable(global_hashmap["inf"], INFINITY);
    __register_global_variable(global_hashmap["tau"], TAU);
    __register_global_variable(global_hashmap["gr"], GOLDEN_RATIO);

    __register_global(global_hashmap["pi"], "pi");
    __register_global(global_hashmap["e"], "e");
    __register_global(global_hashmap["true"], "true");
    __register_global(global_hashmap["false"], "false");
    __register_global(global_hashmap["inf"], "inf");
    __register_global(global_hashmap["tau"], "tau");
    __register_global(global_hashmap["gr"], "gr");
}   

MERCURY_API void MerCore_Finalize(void) {
    _G.clear();
    _L.clear();
    GLOBAL_TABLE.clear();
    mer_core_libs.clear();
    STRING_ENTRY.clear();
}