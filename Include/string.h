#ifndef MERCURY_STRING_HEADER_FILE
#define MERCURY_STRING_HEADER_FILE

#include "Mercury.h"
#include "stack.h"

float __uint8_to_float(Mer_uint8_t c);

float __hash(mString_T *str);

__mer_core_api__ mString_T *__mer_core_api__ add_string(mString_T *a, mString_T *b);

__mer_core_api__ mString_T *__mer_core_api__ mul_string(mString_T *a, int times);

__mer_core_lib_api__ string __convert_to_string(mString_T *__string);

char* from_mstring_to_char(mString_T *str);

mString_T *creat_string_obj_with_code(vector<Mer_uint8_t> code);

mString_T *creat_char_obj(Mer_uint8_t c);

mString_T *creat_string_obj(string str);

table *creat_str(string str);
#endif