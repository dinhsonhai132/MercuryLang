#ifndef MERCURY_BUILTIN_HEADER_FILE
#define MERCURY_BUILTIN_HEADER_FILE

#include "Mercury.h"
#include "..\Mercury\evallib.cpp"
#include "..\Mercury\ram.cpp"

#define __io_cout_int(x) \
    cout << x << endl;

#define __io_cout_stdout(x) \
    cout << x;



unordered_map<string, Mer_uint8_t> lib_hashmap = {
    {"write", IO_WRITE_ADDRESS}, {"eval", EVAL_ADDRESS}, {"pause", PAUSE_ADDRESS}, {"exit", EXIT_ADDRESS},
    {"cls", CLS_ADDRESS}, {"help", HELP_ADDRESS}, {"same", SAME_STRING_ADDRESS}, {"size", SIZE_ADDRESS}, {"push", PUSH_ADDRESS},
    {"pop", POP_ADDRESS}, {"watch", PRINT_LIST_ADDRESS}, {"puts", PUTS_ADDRESS}, {"cos", COS_ADDRESS}, {"tan", TAN_ADDRESS},
    {"cot", COT_ADDRESS}, {"sqrt", SQRT_ADDRESS}, {"sin", SIN_ADDRESS}, {"glb", PRINT_GLOBAL_ADDRESS}, {"ch", CHANGE_ITEM_ADDRESS},
    {"type", TYPE_ADDRESS}, {"range", RANGE_ADDRESS}, {"random", RANDOM_ADDRESS}, {"randint", RANDINT_ADDRESS}, {"sub", SUB_STR}
};

unordered_map<string, Mer_uint8_t> global_hashmap = {
    {"pi", PI_ADDRESS}, {"e", EULER_ADDRESS}, {"true", TRUE_ADDRESS}, {"false", FALSE_ADDRESS}, {"inf", INFINITY_ADDRESS},
    {"tau", TAU_ADDRESS}, {"gr", GOLDEN_RATIO_ADDRESS}
};

__mer_core_lib_api__ const char* to_char(Mer_uint8_t c);
__mer_core_lib_api__ void __builtin_print(mObject_T *str);
__mer_core_lib_api__ void __io_write(mString_T *__string);
__mer_core_lib_api__ void __io_puts(mString_T *__string);
__mer_core_data__ float __randint(int a, int b);
__mer_core_lib_api__  Mer_real_string hash_to_string(mString_T *str);

MERCURY_API __mer_core_lib_api__ void __builtin_io_write(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_eval(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_pause(stack *stk);
MERCURY_API __mer_core_lib_api__ void __mer_builtin_exit(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_cls(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_help(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_same_string(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_size(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_push(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_pop(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_watch(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_date(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_puts_val(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_is_my_fav_number(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_mer_sqrt(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_mer_cos(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_mer_tan(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_mer_cot(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_mer_sin(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_print_global_stack(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_change_item(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_type(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_random(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_randint(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_range(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_mer_sub_str(stack *stk);

MERCURY_API __mer_core_lib_api__ vector<Mer_Reg> mer_core_libs = {};

#endif // MERCURY_BUILTIN_HEADER_FILE
