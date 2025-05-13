#ifndef MERCURY_DATA_HEADER_FILE
#define MERCURY_DATA_HEADER_FILE

#include "C:\MercuryLang\Mercury\stack.cpp"

MERCURY_API __mer_core_data__ vector<symtable *> _G = {};
MERCURY_API __mer_core_data__ vector<symtable *> _L = {};
MERCURY_API __mer_core_data__ vector<symtable *> _T = {};

MERCURY_API __mer_core_data__ GlobalTable GLOBAL_TABLE = {
    CREAT_GLOBAL_TABLE(IO_WRITE_ADDRESS, "write", "write"),
    CREAT_GLOBAL_TABLE(EVAL_ADDRESS, "eval", "eval"),
    CREAT_GLOBAL_TABLE(PAUSE_ADDRESS, "pause", "pause"),
    CREAT_GLOBAL_TABLE(EXIT_ADDRESS, "exit", "exit"),
    CREAT_GLOBAL_TABLE(CLS_ADDRESS, "cls", "cls"),
    CREAT_GLOBAL_TABLE(HELP_ADDRESS, "help", "help"),
};

MERCURY_API __mer_core_data__ stack *_S;

MERCURY_API __mer_core_lib_api__ vector<Mer_Reg> mer_core_libs = {
    {IO_WRITE_ADDRESS, "write", (void*)__builtin_io_write},
    {EVAL_ADDRESS, "eval", (void*)__builtin_eval},
    {PAUSE_ADDRESS, "pause", (void*)__builtin_pause},
    {EXIT_ADDRESS, "exit", (void*)(void(*)(int))__builtin_exit},
    {CLS_ADDRESS, "cls", (void*)__builtin_cls},
    {HELP_ADDRESS, "help", (void*)__builtin_help},
    {0, "null", NULL_PTR},
}; 

#endif // MERCURY_DATA_HEADER_FILE
