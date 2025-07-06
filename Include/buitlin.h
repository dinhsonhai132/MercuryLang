#ifndef MERCURY_BUILTIN_HEADER_FILE
#define MERCURY_BUILTIN_HEADER_FILE

#include "Mercury.h"
#include "..\Mercury\evallib.cpp"
#include "..\Mercury\ram.cpp"
#include "../Mercury/string.cpp"
#include "../Mercury/list.cpp"

typedef void __builtin_func_t;

#define __io_cout_int (x) \
    cout << x << endl;

#define __io_cout_stdout(x) \
    cout << x;

unordered_map<string, Mer_uint8_t> lib_hashmap = {
    {"write", IO_WRITE_ADDRESS}, 
    {"pause", PAUSE_ADDRESS}, 
    {"exit", EXIT_ADDRESS},
    {"cls", CLS_ADDRESS},
    {"help", HELP_ADDRESS},
    {"same", SAME_STRING_ADDRESS}, 
    {"size", SIZE_ADDRESS}, 
    {"push", PUSH_ADDRESS},
    {"pop", POP_ADDRESS},
    {"watch", PRINT_LIST_ADDRESS}, 
    {"puts", PUTS_ADDRESS}, 
    {"cos", COS_ADDRESS}, 
    {"tan", TAN_ADDRESS},
    {"cot", COT_ADDRESS}, 
    {"sqrt", SQRT_ADDRESS}, 
    {"sin", SIN_ADDRESS},
    {"glb", PRINT_GLOBAL_ADDRESS}, 
    {"ch", CHANGE_ITEM_ADDRESS},
    {"type", TYPE_ADDRESS}, 
    {"range", RANGE_ADDRESS},
    {"randint", RANDINT_ADDRESS},
    {"sub", SUB_STR}, 
    {"print", PRINT_ADDRESS}, 
    {"sleep", SLEEP_ADDRESS},
    {"to_list", LIST_ADDRESS},
    {"isdigit", ISDIGIT_ADDRESS},
    {"to_str", TO_STRING_ADDRESS},
    {"to_int", TO_INT_ADDRESS},
    {"input", INPUT_ADDRESS},
    {"split", SPLIT_ADDRESS},
    {"to_str", TO_STRING_ADDRESS},
    {"hash", HASH_ADDRESS},
    {"empty", EMPTY_ADDRESS},
    {"factorial", FACTORIAL_ADDRESS}
};


#define is_a_builtin(x) (lib_hashmap.find(x) != lib_hashmap.end())

unordered_map<string, Mer_uint8_t> global_hashmap = {
    {"pi", PI_ADDRESS}, 
    {"e", EULER_ADDRESS}, 
    {"inf", INFINITY_ADDRESS},
    {"tau", TAU_ADDRESS}, 
    {"gr", GOLDEN_RATIO_ADDRESS}
};

__mer_core_lib_api__ const char* to_char(Mer_uint8_t c);
__mer_core_lib_api__ void __io_write(mString_T *__string);
__mer_core_lib_api__ void __io_puts(mString_T *__string);
__mer_core_lib_api__ string __convert_to_string(mString_T *__string);
__mer_core_data__ float __randint(int a, int b);
__mer_core_lib_api__  Mer_real_string hash_to_string(mString_T *str);

__mer_core_lib_api__ __builtin_func_t __builtin_io_write(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_eval(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_pause(stack *stk);

__mer_core_lib_api__ __builtin_func_t __mer_builtin_exit(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_cls(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_help(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_same_string(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_size(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_push(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_pop(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_watch(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_date(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_puts_val(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_is_my_fav_number(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_mer_sqrt(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_mer_cos(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_mer_tan(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_mer_cot(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_mer_sin(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_print_global_stack(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_change_item(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_type(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_random(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_randint(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_range(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_mer_sub(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_mer_sleep(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_mer_list(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_mer_is_digit(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_to_string(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_to_int(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_mer_read_line(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_mer_split(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_mer_hash(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_mer_empty(stack *stk);

__mer_core_lib_api__ __builtin_func_t __builtin_mer_factorial(stack *stk);


mString_T *make_str_obj(string str);

__mer_core_lib_api__ vector<Mer_Reg> mer_core_libs = {};

#endif // MERCURY_BUILTIN_HEADER_FILE
