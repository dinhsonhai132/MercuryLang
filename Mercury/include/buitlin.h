#ifndef MERCURY_BUILTIN_HEADER_FILE
#define MERCURY_BUILTIN_HEADER_FILE

#include "Mercury.h"
#include "C:\MercuryLang\Mercury\evallib.cpp"
#include "C:\MercuryLang\Mercury\ram.cpp"

#define __io_cout_int(x) \
    cout << x << endl;

#define __io_cout_stdout(x) \
    cout << x;
    
__mer_core_lib_api__ const char* to_char(Mer_uint8_t c);
__mer_core_lib_api__ void __builtin_print(mObject_T *str);
__mer_core_lib_api__ void __io_write(mString_T *__string);
__mer_core_lib_api__ void __io_puts(mString_T *__string);
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


MERCURY_API __mer_core_lib_api__ vector<Mer_Reg> mer_core_libs = {
    {IO_WRITE_ADDRESS, "write", (void*)__builtin_io_write},
    {EVAL_ADDRESS, "eval", (void*)__builtin_eval},
    {PAUSE_ADDRESS, "pause", (void*)__builtin_pause},
    {EXIT_ADDRESS, "exit", (void*)(void(*)(int))__builtin_exit},
    {CLS_ADDRESS, "cls", (void*)__builtin_cls},
    {HELP_ADDRESS, "help", (void*)__builtin_help},
    {SAME_STRING_ADDRESS, "same", (void*)__builtin_same_string},
    {SIZE_ADDRESS, "size", (void*)__builtin_size},
    {PUSH_ADDRESS, "push", (void*)__builtin_push},
    {POP_ADDRESS, "pop", (void*)__builtin_pop},
    {PRINT_LIST_ADDRESS, "watch", (void*)__builtin_watch},
    {PUTS_ADDRESS, "puts", (void*)__builtin_puts_val},
    {0x0001, "my_fav_number", (void*)__builtin_is_my_fav_number},
    {COS_ADDRESS, "cos", (void*)__builtin_mer_cos},
    {TAN_ADDRESS, "tan", (void*)__builtin_mer_tan},
    {COT_ADDRESS, "cot", (void*)__builtin_mer_cot},
    {SQRT_ADDRESS, "sqrt", (void*)__builtin_mer_sqrt},
    {0, "null", NULL_PTR},
}; 


#endif // MERCURY_BUILTIN_HEADER_FILE
