#ifndef MERCURY_TYPE_HEADER_FILE
#define MERCURY_TYPE_HEADER_FILE

#include "port.h"
#include "max.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>
using namespace std;

#define FLAG_HEAD \
    bool f_str = false; \
    bool f_hash = false; \
    bool f_bool = false; \
    bool f_int = false; \
    bool f_float = false; \
    bool f_char = false; \
    bool f_long = false; \
    bool f_longlong = false; \
    bool f_byte = false; \
    bool f_sbyte = false; \
    bool f_variable = false; \
    bool f_func = false; \
    bool f_pcode = false; \
    bool f_code = false; \
    bool f_builtin = false;

struct Mer_Reg {
    Mer_uint8_t address;
    const char *name;
    void* func;
};

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

    Mer_uint8_t cbuff[MAX_CODE_LEN];
    Mer_uint8_t raw_buff[MAX_CODE_LEN];
    _code *scr[MAX_CODE_LEN];
};

struct _string {
    Mer_size_t size;
    hash_t hash = 0x00;
    char contents[MAX_CODE_LEN];
    vector<Mer_uint8_t> buff;
    Mer_char *str;
};

struct _pcode
{
    _code prg_code;
    _code out_code;
    char *scode;
    char *cfile;
    ssize_t csize;
    vector<Mer_uint8_t> raw;

    Mer_uint8_t raw_in_buff[MAX_CODE_LEN];
    Mer_uint8_t raw_out_buff[MAX_CODE_LEN];
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

    void *o;
    bool f_builtin;

    _func_object *sf;

    _code *f_bc;
    _code *fs_bc;
    Mer_size_t size;
    Mer_size_t args_size;
    vector<void*> args;
};

struct block_obj  {
    Mer_uint8_t ui8_address;
    Mer_uint16_t ui16_address;
    Mer_uint32_t ui32_address;
    block_obj *sb;
    _code *b_bc;
    _code *bs_bc;
};

struct _list_object {
    Mer_uint8_t ui8_address;
    Mer_uint16_t ui16_address;
    Mer_uint32_t ui32_address;
    
    Mer_size_t size;
    vector<void*> args;
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
    FLAG_HEAD;
    _func_object *func;
    _variable *variable;
    _string *str;
    _pcode *pcode;
    _code *code;
    void *o_ptr;
    bool is_builtin;
    Mer_real_string builtin_name;
    void* builtin_ptr;
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

static _object NULL_OBJECT_INSTANCE = _object();
static _type NULL_TYPE_INSTANCE = _type();
static _pcode NULL_CODE_INSTANCE = _pcode();
static _code NULL_OPCODE_INSTANCE = _code();

#define NULL_OBJECT NULL_OBJECT_INSTANCE
#define NULL_TYPE NULL_TYPE_INSTANCE
#define NULL_CODE NULL_CODE_INSTANCE
#define NULL_OPCODE NULL_OPCODE_INSTANCE
#define NULL_OBJECT_PTR &NULL_OBJECT_INSTANCE
#define NULL_OPCODE_PTR &NULL_OPCODE_INSTANCE
#define NULL_TYPE_PTR &NULL_TYPE_INSTANCE
#define NULL_CODE_PTR &NULL_CODE_INSTANCE
#define NULL_GLOBAL __global()
#define NULL_GLOBAL_PTR &NULL_GLOBAL
#define NULL_INT 0
#define NULL_FLOAT 0.0
#define NULL_DOUBLE 0.0
#define NULL_LONG 0
#define NULL_BOOL 0
#define NULL_STRING ""
#define NULL_CHAR '\0'
#define NULL_PTR NULL
#define NULL_PTR_PTR &NULL_PTR
#define NULL_UINT_8_T 0x0000
#define NULL_UINT_16_T 0x0000
#define NULL_UINT_32_T 0x0000
#define NULL_UINT_64_T 0x0000
#define NULL_MER_STRING ""
#define NULL_STRING_PTR &NULL_STRING
#define NULL_INT_PTR &NULL_INT
#define NULL_FLOAT_PTR &NULL_FLOAT
#define NULL_DOUBLE_PTR &NULL_DOUBLE
#define NULL_LONG_PTR &NULL_LONG
#define NULL_BOOL_PTR &NULL_BOOL

#endif // MERCURY_TYPE_HEADER_FILE