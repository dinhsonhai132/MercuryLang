#ifndef MERCURY_BUILTIN_HEADER_FILE
#define MERCURY_BUILTIN_HEADER_FILE

#include "Mercury.h"

#define IO_WRITE_ADDRESS 0xF3

MERCURY_API __mer_core_lib_api__ const char* to_char(Mer_uint8_t c);
MERCURY_API __mer_core_lib_api__ void __builtin_print(mObject_T *str);
MERCURY_API __mer_core_lib_api__ void __io_write(mString_T *__string);



#endif // MERCURY_BUILTIN_HEADER_FILE