#ifndef MERCURY_TYPE_HEADER_FILE
#define MERCURY_TYPE_HEADER_FILE

#include "C:\MercuryLang\v2.0.1\mercury\include\port.h"
#include "C:\MercuryLang\v2.0.1\mercury\include\marco.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>
using namespace std;

struct _code
{
    Mer_uint8_t code;
    Mer_uint8_t byte;
    Mer_uint8_t address;
    Mer_uint8_t cvalue;

    const char *name;
    vector<Mer_uint8_t> buff;
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

struct _type
{
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
        vector<_type *> *list;
    } value_t;

    typedef struct _func
    {
        _type *func_name;
        _type *func_address;
        _type *func_type;
        _type *func_val;
        _type *func_args;
        _type *func_son;
        _pcode *func_code;
    } func_t;

    typedef struct _variable
    {
        _type *var_name;
        _type *var_address;
        _type *var_type;
        _type *var_val;
    } var_t;

    _pcode *pcode;
    _code *code;

    const char *name;
    const char *type;
    const char *file_name;
};

struct _object
{
    _type *type;
    _type *file_name;
    _type *name;
    _pcode *code;

    bool is_constant;
    bool is_global;
    bool is_local;

    unordered_map<string, _object *> attributes;
};

#endif // MERCURY_TYPE_HEADER_FILE