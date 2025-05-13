#ifndef MERCURY_BUILTIN_HEADER_FILE
#define MERCURY_BUILTIN_HEADER_FILE

#include "Mercury.h"
#include "C:\MercuryLang\Mercury\evallib.cpp"
#include "stack.h"

#define IO_WRITE_ADDRESS 0xF3
#define EVAL_ADDRESS     0xF4
#define PAUSE_ADDRESS    0xF5
#define EXIT_ADDRESS     0xF6
#define CLS_ADDRESS      0xF7
#define HELP_ADDRESS     0xF8

__mer_core_lib_api__ const char* to_char(Mer_uint8_t c);
__mer_core_lib_api__ void __builtin_print(mObject_T *str);
__mer_core_lib_api__ void __io_write(mString_T *__string);
__mer_core_lib_api__  Mer_real_string hash_to_string(mString_T *str);

MERCURY_API __mer_core_lib_api__ void __builtin_io_write(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_eval(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_pause(stack *stk);
MERCURY_API __mer_core_lib_api__ void __mer_builtin_exit(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_cls(stack *stk);
MERCURY_API __mer_core_lib_api__ void __builtin_help(stack *stk);

#endif // MERCURY_BUILTIN_HEADER_FILE