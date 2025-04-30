#ifndef MERCURY_TYPE_HEADER_FILE
#define MERCURY_TYPE_HEADER_FILE

#include "port.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>
using namespace std;

struct _val {
    union
    {
        Mer_int int_value;
        Mer_float float_value;
        Mer_bool bool_value;
        Mer_char char_value;
        Mer_string string_value;
        Mer_long long_value;
        Mer_uint8_t byte_value;
        Mer_int8_t sbyte_value;
        Mer_longlong longlong_value;
    } value_t;
};

struct _code
{
    Mer_uint8_t code;
    Mer_uint8_t byte;
    Mer_uint8_t address;
    Mer_uint8_t cvalue;

    const char *name;
    vector<Mer_uint8_t> buff;
    vector<Mer_uint8_t> raw;
    vector<_code *> scr;
};

struct _pcode
{
    _code prg_code;
    _code out_code;
    char *scode;
    char *cfile;
    ssize_t csize;
    vector<Mer_uint8_t> raw;
};

struct _func_object {
    Mer_string name;
    Mer_real_string real_name;
    Mer_uint8_t ui8_address;
    Mer_uint16_t ui16_address;
    Mer_uint32_t ui32_address;

    bool _return;
    bool _is_local;
    bool _is_global;

    _func_object *sf;

    _code *f_bc;
    _code *fs_bc;
};

struct block_obj  {
    Mer_uint8_t ui8_address;
    Mer_uint16_t ui16_address;
    Mer_uint32_t ui32_address;
    block_obj *sb;
    _code *b_bc;
    _code *bs_bc;
};

struct _string {
    _code *str;
    Mer_uint64_t hash;
    void *user_data;
    char* sstr;
};

struct _variable {
    Mer_string name;
    Mer_string type;
    _val *val;
    Mer_uint8_t ui8_address;
    Mer_uint16_t ui16_address;
    Mer_uint32_t ui32_address;
    
    bool _is_constant;
    bool _is_local;
    bool _is_global;
};

struct _type
{
    _func_object *func;
    _variable *variable;
    _string *str;
    _pcode *pcode;
    _code *code;
    void *o_ptr;
    bool is_builtin;
    Mer_real_string builtin_name;
    void *builtin_ptr;
    const char *name;
    const char *type;
    const char *file_name;
};

struct _object
{
    _type *type;
    _type *data_type;
    _type *value;
    _type *file_name;
    _type *name;
    _pcode *code;

    unordered_map<string, _object *> attributes;
};

#endif // MERCURY_TYPE_HEADER_FILE