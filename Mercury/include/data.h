#ifndef MERCURY_DATA_HEADER_FILE
#define MERCURY_DATA_HEADER_FILE

#include "C:\MercuryLang\Mercury\stack.cpp"

#define PRINT_ADDRESS               0xAA
#define IO_WRITE_ADDRESS            0xF3
#define EVAL_ADDRESS                0xF4
#define PAUSE_ADDRESS               0xF5
#define EXIT_ADDRESS                0xF6
#define CLS_ADDRESS                 0xF7
#define HELP_ADDRESS                0xF8
#define PI_ADDRESS                  0xF9
#define TAU_ADDRESS                 0xFA
#define GOLDEN_RATIO_ADDRESS        0xFB
#define EULER_ADDRESS               0xFC
#define INFINITY_ADDRESS            0xFD
#define THE_TRUE_ADDRESS            0xFE
#define THE_FALSE_ADDRESS           0xFF
#define SAME_STRING_ADDRESS         0xA1
#define SIZE_ADDRESS                0xA2
#define PUSH_ADDRESS                0xA3
#define POP_ADDRESS                 0xA4

MERCURY_API __mer_core_data__ vector<symtable *> _G = {
    MerCompiler_symboltable_setup("pi", PI, "float", PI_ADDRESS),
    MerCompiler_symboltable_setup("tau", TAU, "float", TAU_ADDRESS),
    MerCompiler_symboltable_setup("golden_ratio", GOLDEN_RATIO, "float", GOLDEN_RATIO_ADDRESS),
    MerCompiler_symboltable_setup("euler", EULER, "float", EULER_ADDRESS),
    MerCompiler_symboltable_setup("inf", INFINITY, "float", INFINITY_ADDRESS),
    MerCompiler_symboltable_setup("true", 1, "bool", THE_TRUE_ADDRESS),
    MerCompiler_symboltable_setup("false", 0, "bool", THE_FALSE_ADDRESS),
};

MERCURY_API __mer_core_data__ vector<symtable *> _L = {};
MERCURY_API __mer_core_data__ vector<symtable *> _T = {};

MERCURY_API __mer_core_data__ vector<mString_T *> STRING_ENTRY = {};

MERCURY_API __mer_core_data__ GlobalTable GLOBAL_TABLE = {
    CREAT_GLOBAL_TABLE(IO_WRITE_ADDRESS, "write", "write"),
    CREAT_GLOBAL_TABLE(EVAL_ADDRESS, "eval", "eval"),
    CREAT_GLOBAL_TABLE(PAUSE_ADDRESS, "pause", "pause"),
    CREAT_GLOBAL_TABLE(EXIT_ADDRESS, "exit", "exit"),
    CREAT_GLOBAL_TABLE(CLS_ADDRESS, "cls", "cls"),
    CREAT_GLOBAL_TABLE(HELP_ADDRESS, "help", "help"),
    CREAT_GLOBAL_TABLE(PI_ADDRESS, "pi", "pi"),
    CREAT_GLOBAL_TABLE(TAU_ADDRESS, "tau", "tau"),
    CREAT_GLOBAL_TABLE(GOLDEN_RATIO_ADDRESS, "golden_ratio", "golden_ratio"),
    CREAT_GLOBAL_TABLE(EULER_ADDRESS, "euler", "euler"),
    CREAT_GLOBAL_TABLE(INFINITY_ADDRESS, "inf", "inf"),
    CREAT_GLOBAL_TABLE(THE_TRUE_ADDRESS, "true", "true"),
    CREAT_GLOBAL_TABLE(THE_FALSE_ADDRESS, "false", "false"),
    CREAT_GLOBAL_TABLE(SAME_STRING_ADDRESS, "same", "same"),
    CREAT_GLOBAL_TABLE(SIZE_ADDRESS, "size", "size"),
    CREAT_GLOBAL_TABLE(PUSH_ADDRESS, "push", "push"),
    CREAT_GLOBAL_TABLE(POP_ADDRESS, "pop", "pop"),
};

MERCURY_API __mer_core_data__ stack *_S;

#endif // MERCURY_DATA_HEADER_FILE
