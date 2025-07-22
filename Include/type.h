#ifndef MERCURY_TYPE_HEADER_FILE
#define MERCURY_TYPE_HEADER_FILE

#include "port.h"
#include "max.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>
using namespace std;

#define MER_INT_TYPE 0
#define MER_FLOAT_TYPE 1
#define MER_BOOL_TYPE 2
#define MER_CHAR_TYPE 3
#define MER_STRING_TYPE 4
#define MER_LIST_TYPE 5
#define MER_LONG_TYPE 6
#define MER_LONG_LONG_TYPE 7
#define MER_BYTE_TYPE 8
#define MER_SBYTE_TYPE 9
#define MER_VARIABLE_TYPE 10
#define MER_FUNCTION_TYPE 11
#define MER_PCODE_TYPE 12
#define MER_CODE_TYPE 13

#define GC_HEAD \
    int ref_count = 1; \

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

struct Mer_string_entry {
    vector<Mer_uint8_t> contents;
    hash_t hash_key;
};

struct _val {
    GC_HEAD;

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

    Mer_float f_value;
    int type;
};

struct _code
{
    GC_HEAD;
    Mer_uint8_t code;
    Mer_uint8_t byte;
    Mer_uint8_t address;
    Mer_uint8_t cvalue;

    const char *name;
    vector<Mer_uint8_t> buff;
    vector<Mer_uint8_t> raw;

    size_t belong_line;

    Mer_uint8_t cbuff[MAX_CODE_LEN];
    Mer_uint8_t raw_buff[MAX_CODE_LEN];
    _code *scr[MAX_CODE_LEN];
};

struct _dict {
    GC_HEAD;
    Mer_size_t size;

    vector<pair<void*, void*>> dict;
};

struct _char {
    GC_HEAD;
    char item;
    Mer_uint8_t citem;
};

struct _bool {
    GC_HEAD;
    Mer_bool value;
};

struct _string {
    GC_HEAD;
    Mer_size_t size;
    hash_t hash = 0x00;
    char contents[MAX_CODE_LEN];
    vector<Mer_uint8_t> buff;
    Mer_char *str;
};

struct _pcode
{
    GC_HEAD;
    _code prg_code;
    _code out_code;
    const char *scode;
    const char *cfile;
    ssize_t csize;
    vector<Mer_uint8_t> raw;

    size_t belong_line;

    Mer_uint8_t raw_in_buff[MAX_CODE_LEN];
    Mer_uint8_t raw_out_buff[MAX_CODE_LEN];
};

struct _func_object {
    GC_HEAD;
    Mer_uint8_t ui8_address;
    Mer_uint16_t ui16_address;
    Mer_uint32_t ui32_address;

    bool is_return;
    bool is_local;
    bool is_global;

    void *o;
    bool f_builtin;

    _func_object *sf;

    _code *f_bc;
    _code *fs_bc;
    vector<Mer_uint8_t> raw_body;
    
    Mer_size_t body_size;
    Mer_size_t args_size;

    float f_value;

    vector<void*> args;
};

struct block_obj  {
    GC_HEAD;
    Mer_uint8_t ui8_address;
    Mer_uint16_t ui16_address;
    Mer_uint32_t ui32_address;

    block_obj *sb;
    _code *b_bc;
    _code *bs_bc;
};

struct _list_object {
    GC_HEAD;
    Mer_uint8_t ui8_address;
    Mer_uint16_t ui16_address;
    Mer_uint32_t ui32_address;
    
    Mer_size_t size;
    vector<void*> args;
};

struct __iter {
    GC_HEAD;
    Mer_uint8_t ui8_address;
    Mer_uint16_t ui16_address;
    Mer_uint32_t ui32_address;
    
    union
    {
        _list_object *list;
        _string *str;
    } loop_obj;
    
    Mer_size_t index;
    Mer_size_t size;
};

struct _variable {
    GC_HEAD;
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

struct _type_obj {
    FLAG_HEAD;
    GC_HEAD;

    _func_object *func;
    _variable *variable;
    _string *str;
    _pcode *pcode;
    _code *code;
    _list_object *list;
    _bool *bool_obj;
    block_obj *block;
    _val *val;
    Mer_Reg *reg;
    Mer_string_entry *str_entry;
};

struct _class {
    GC_HEAD;
    Mer_uint8_t address;
    unordered_map<Mer_uint8_t, _type_obj *> members;
    
    _class *super_class;
    _class *inheritance;
};

struct _object
{
    GC_HEAD;

    _type_obj *obj_val;
    Mer_size_t obj_size;

    unordered_map<string, _object *> attributes;
};

static _object NULL_OBJECT_INSTANCE = _object();
static _pcode NULL_CODE_INSTANCE = _pcode();
static _code NULL_OPCODE_INSTANCE = _code();
static _type_obj NULL_TYPE_INSTANCE = _type_obj();

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
#define NULL_PTR nullptr
#define NULL_PTR_PTR &NULL_PTR
#define NULL_UINT_8_T 0x00
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

_val *MerCompiler_val_new(void);
_code MerCompiler_code_new(void);
_pcode *MerCompiler_pcode_new(void);
_string *MerCompiler_string_new(void);
_func_object *MerCompiler_func_object_new(void);
_list_object *MerCompiler_list_object_new(void);
_variable *MerCompiler_variable_new(void);
_object *MerCompiler_object_new(void);
_code *MerCompiler_code_new_as_ptr(void);

_type_obj *MerCompiler_type_obj_new(void);

int MerCompiler_free_object(_object *o);
int MerCompiler_free_pcode(_pcode *p);
int MerCompiler_free_code(_code *c);
int MerCompiler_free_string(_string *s);
int MerCompiler_free_func_object(_func_object *f);
int MerCompiler_free_list_object(_list_object *l);
int MerCompiler_free_variable(_variable *v);
int MerCompiler_free_val(_val *v);

#define get_v(o) ((o)->f_value)

#define get_f(o) ((o)->value_t.float_value)

#define get_i(o) ((o)->value_t.int_value)

#define get_b(o) ((o)->value_t.bool_value)

#define get_c(o) ((o)->value_t.char_value)

#define get_s(o) ((o)->value_t.string_value)

#define get_l(o) ((o)->value_t.long_value)

#define get_ll(o) ((o)->value_t.longlong_value)

#define get_by(o) ((o)->value_t.byte_value)

#define get_sb(o) ((o)->value_t.sbyte_value)

#define back_insrt(v, s) (v.insert(v.begin(), s))

#define front_insrt(v, s) (v.insert(v.end(), s))

#endif // MERCURY_TYPE_HEADER_FILE