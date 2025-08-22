#ifndef MERCURY_2_2_1_HPP
#define MERCURY_2_2_1_HPP

#define     START_DLL                   extern "C" {

#define     END_DLL                     }   

#define     DLL_EXPORT                  __declspec(dllexport)

#define     DLL_IMPORT                  __declspec(dllimport)

#define     ARGS                        table* args[]
#define     GET_ARGS        (x)         args[x - 1]

#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <unordered_set>
#include <thread>
#include <cstring>
#include <stdio.h>
#include <unordered_map>
#include <filesystem>
#include <random>
#include <functional>

namespace fs = std::filesystem;

#define GC_THRESHOLD 100

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h> 
#define mkdir _mkdir
#else
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

#ifdef str
#undef str
#endif

using namespace std;

bool IS_CONTINUE = false;
const char* CUSTOM_VERSION = "2.2.1";
const char* AUTHOR = "dinhsonhai132";  
const char* LANGUAGE = "MercuryLang";

static inline vector<string> para_temp = {};
static inline vector<string> lib_iden = {"print", "empty", "input", "to_list", "range", "type", "write", "sin", "cos", "tan", "cot", "sqrt", "split", "size", "pop", "watch", "puts", "push", "ch", "glb", "sub", "help", "exit", "pause", "eval", "cls", "same", "random", "randint", "sleep", "isdigit", "to_str", "to_int", "hash", "factorial"};

const char* LET_S = "LET";
const char* LOCAL_S = "LOCAL";
const char* TRUE_S = "TRUE";
const char* FALSE_S = "FALSE";
const char* INCLUDE_S = "INCLUDE";
const char* LOOP_S = "LOOP";
const char* IMPORT_S = "IMPORT";
const char* FUNCTION_S = "FUNC";
const char* FUNCTION2_S = "FUNCTION";
const char* RETURN_S = "RETURN";
const char* ELIF_S = "ELIF";
const char* DO_S = "DO";
const char* END_S = "END";
const char* DEFINED_S = "DEFINE";
const char* IF_S = "IF";
const char* AND_S = "AND";
const char* OR_S = "OR";
const char* NOT_S = "NOT";
const char* ELSE_S = "ELSE";
const char* FOR_S = "FOR";
const char* IS_S = "IS";
const char* IN_S = "IN";
const char* WHILE_S = "WHILE";
const char* BREAK_S = "BREAK";
const char* CONTINUE_S = "CONTINUE";
const char* CONST_S = "CONST";
const char* STATIC_S = "STATIC";
const char* GLOBAL_S = "GLOBAL";
const char* ASSERT_S = "ASSERT";
const char* STRING_S = "STRING";
const char* STR_S = "STRING";
const char* CLASS_S = "CLASS";
const char* INTERFACE_S = "INTERFACE";
const char* STRUCT_S = "STRUCT";
const char* NEW_S = "NEW";
const char* LIST_S = "LIST";
const char* DELETE_S = "DELETE";
const char* CAST_S = "CAST";
const char* FLOAT_S = "FLOAT";
const char* DOUBLE_S = "DOUBLE";
const char* CHAR_S = "CHAR";
const char* SHORT_S = "SHORT";
const char* LONG_S = "LONG";
const char* AUTO_S = "AUTO";
const char* VOID_S = "VOID";
const char* THEN_S = "THEN";
const char* BOOL_S = "BOOL";

#define __iter__ "__iter__version_2_5_0_global_variable"
#define __i__ "__i__version_2_5_0_global_variable"

#ifndef MER3_CC
#define MER_BREAK_POINT while(1);
#endif

#define __SUCCESS__ 0
#define __FAILURE__ 1

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0601
    #endif

    #include <windows.h>
    #include <timezoneapi.h> 
    #include <winbase.h>   
#endif

#ifdef _WIN32
    #ifndef __API
        #define MERCURY_API             __declspec(dllexport)
    #endif
    #ifndef __mer_core_data__
        #define __mer_core_data__       __declspec(dllexport)
    #endif
    #ifndef __mer_core_api__
        #define __mer_core_api__        __declspec(dllexport)
    #endif
    #ifndef __mer_core_lib_api__
        #define __mer_core_lib_api__    __declspec(dllexport)
    #endif
#else
    #define MERCURY_API                 #define __mer_core_data__           #define __mer_core_api__            #define __mer_core_lib_api__    #endif

#ifdef SYSTEM_TEST
#define SYSTEM_TEST 1
#endif

#define MERCURY_FUNCTION_VALUE           0
#define MERCURY_LIST_VALUE               1
#define MERCURY_STRING_VALUE             2
#define MERCURY_OPCODE_VALUE             3
#define MERCURY_OBJECT_VALUE             4
#define MERCURY_ITERATOR_VALUE           5

#endif

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

#define THIS_ADDRESS 0x00 

#define SYNTAX_ERROR "SyntaxError"
#define RUNTIME_ERROR "RuntimeError"
#define RUNTIME_WARNING "RuntimeWarning"
#define SYSTEM_WARNING "SystemWarning"
#define SYSTEM_ERROR "RunTimeError"
#define COMPILER_WARNING "CompilerWarning"
#define COMPILER_ERROR "CompilerError"

#define PARSER_ERROR_INCOMPLETE "ParserErrorIncomplete"
#define PARSER_ERROR_UNEXPECTED "ParserErrorUnexpected"
#define PARSER_ERROR_UNEXPECTED_TOKEN "ParserErrorUnexpectedToken"

#define cval_of(a) ((a)->cval)
#define value_of(a) ((a)->value)

#define CPUSH_FLOAT                             0x01
#define CPUSH_NORMAL_MODE                       0x02
#define CSTORE_GLOBAL                           0x03
#define CLOAD_GLOBAL                            0x04
#define CLOAD_ARGS                              0x05

#define CBINARY_ADD                             0x10
#define CBINARY_SUB                             0x11
#define CBINARY_MUL                             0x12
#define CBINARY_DIV                             0x13
#define CBINARY_MOD                             0x14
#define CBINARY_POW                             0xF1
#define CBINARY_SUBSCRIBE                       0x15

#define TRUE_ADDRESS                            0x20
#define FALSE_ADDRESS                           0x21
#define CEQUAL                                  0x22
#define CNOT_EQUAL                              0x23
#define CLESS                                   0x24
#define CLESS_EQUAL                             0x25
#define CGREATER                                0x26
#define CGREATER_EQUAL                          0x27
#define CNOT                                    0x28
#define CLEN                                    0x29

#define CFUNCTION_CALL_WITH_ARGS                0x30
#define CMAKE_FUNCTION_WITH_ARGS                0x31
#define CMAKE_FUNCTION                          0x32
#define CFUNCTION_CALL                          0x33
#define CRETURN                                 0x34

#define CJUMP_IF_FALSE                          0x40
#define CJUMP_IF_TRUE                           0x41
#define CPOP_JUMP_IF_FALSE                      0x42
#define CPOP_JUMP_IF_TRUE                       0x43
#define CJUMP_TO                                0x44

#define CBUILD_LIST                             0x50
#define CGET_ITEM                               0x51
#define CSTORE_INDEX                            0x52

#define CPROGRAM_START                          0x60
#define CPROGRAM_END                            0x8D
#define CADDRESS                                0xFE

#define CLOAD_TRUE                              0x4F
#define CLOAD_FALSE                             0xF2

#define CINC                                    0x9A
#define CDEC                                    0x9B

#define CAND                                    0x9C
#define COR                                     0x62

#define CCLASS_BEGIN                            0x9E 
#define CCLASS_END                              0x9F

#define CSTORE_ATTR                             0xA0
#define CLOAD_ATTR                              0xA1

#define CLOAD_METHOD                            0xA2
#define CCALL_METHOD                            0xA4

#define CDELETE                                 0xA2
#define CPOP_TOP                                0xA5

#define CIS                                     0xA3

#define CEND_FUNCTION                           0xFF

#define NUMBER_0 {0x00, 0x00, 0x00, 0x00}
#define NUMBER_1 {0x00, 0x00, 0x80, 0x3F}
#define NUMBER_2 {0x00, 0x00, 0x00, 0x40}
#define NUMBER_3 {0x00, 0x00, 0x40, 0x40}

#define MER_PAUSE system("pause");
#define MER_CLEAR system("cls");
#define MER_EXIT exit(0)

#define GLOBAL_TABLE(address, name) create_global_table(address, name)
#define GLOBAL_TABLE_PTR(address, name) create_global_table_ptr(address, name)
#define PUSH(code, opcode) _MerCode_push_opcode(code, opcode)
#define INSERT(code, opcode, size) _MerCode_insert_opcode(code, opcode, size)
#define INSERT_VEC(code, ins) _MerCode_insert_vec_code(code, ins)
#define INSERT_VEC_TO_OUTCODE_AND_PROG_CODE(code, ins) _MerCode_super_insert_vec_code(code, ins)
#define PUSH_TO_OUTCODE(code, opcode) _MerCode_push_opcode_to_outcode(code, opcode)
#define INSERT_TO_OUTCODE(code, opcode, size) _MerCode_insert_opcode_to_outcode(code, opcode, size)
#define INSERT_VEC_TO_OUTCODE(code, ins) _MerCode_insert_vec_code_to_outcode(code, ins)
#define INSERT_OUT_BY_PRG(code, ins) _MerCode_insert_vec_code_to_outcode_by_prog_code(code, ins)
#define INSERT_PRG_BY_OUT(code, ins) _MerCode_insert_vec_code_to_prg_code_by_out_code(code, ins)

#define __do_not_change const

#define __Mer_return_Void void
#define __Mer_return_Object mObject_T
#define __Mer_return_Code mCode_T
#define __Mer_return_Type mType_T
#define __Mer_return_Void_ptr void *
#define __Mer_return_Object_ptr mObject_T *
#define __Mer_return_Code_ptr mCode_T *
#define __Mer_return_Type_ptr mType_T *
#define __Mer_return_Void_ptr_ptr void **
#define __Mer_return_Object_ptr_ptr mObject_T **
#define __Mer_return_Code_ptr_ptr mCode_T **
#define __Mer_return_Type_ptr_ptr mType_T **
#define __Mer_return_Mer_uint8_t Mer_uint8_t
#define __Mer_return_Mer_uint8_t_ptr Mer_uint8_t *
#define __Mer_return_Mer_int8_t Mer_int8_t
#define __Mer_return_Mer_int8_t_ptr Mer_int8_t *
#define __Mer_return_Mer_uint16_t Mer_uint16_t
#define __Mer_return_Mer_uint16_t_ptr Mer_uint16_t *
#define __Mer_return_Mer_int16_t Mer_int16_t
#define __Mer_return_Mer_int16_t_ptr Mer_int16_t *
#define __Mer_return_Mer_uint32_t Mer_uint32_t
#define __Mer_return_Mer_uint32_t_ptr Mer_uint32_t *
#define __Mer_return_Mer_int32_t Mer_int32_t
#define __Mer_return_Mer_int32_t_ptr Mer_int32_t *
#define __Mer_return_Mer_uint64_t Mer_uint64_t
#define __Mer_return_Mer_uint64_t_ptr Mer_uint64_t *
#define __Mer_return_Mer_int64_t Mer_int64_t
#define __Mer_return_Mer_int64_t_ptr Mer_int64_t *
#define __Mer_return_Mer_float_t Mer_float_t
#define __Mer_return_Mer_float_t_ptr Mer_float_t *
#define __Mer_return_Mer_double_t Mer_double_t
#define __Mer_return_Mer_double_t_ptr Mer_double_t *
#define __Mer_return_Mer_long_t Mer_long_t
#define __Mer_return_Mer_long_t_ptr Mer_long_t *
#define __Mer_return_Mer_bool_t Mer_bool_t
#define __Mer_return_Mer_bool_t_ptr Mer_bool_t *
#define __Mer_return_Mer_string Mer_string
#define __Mer_return_Mer_string_ptr Mer_string *
#define __Mer_return_Mer_char_t Mer_char_t
#define __Mer_return_Mer_char_t_ptr Mer_char_t *

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
#define NULL_UINT_8_T 0
#define NULL_UINT_16_T 0
#define NULL_UINT_32_T 0
#define NULL_UINT_64_T 0
#define NULL_MER_STRING ""
#define NULL_STRING_PTR &NULL_STRING
#define NULL_INT_PTR &NULL_INT
#define NULL_FLOAT_PTR &NULL_FLOAT
#define NULL_DOUBLE_PTR &NULL_DOUBLE
#define NULL_LONG_PTR &NULL_LONG
#define NULL_BOOL_PTR &NULL_BOOL

#define MAX_STACK_SIZE 1024
#define MAX_GLOBAL_SIZE 1024
#define MAX_LOCAL_SIZE 1024
#define MAX_CODE_LEN 1024

typedef float Mer_number_t;
typedef float *Mer_number_t_ptr;
typedef size_t Mer_index_t;
typedef size_t *Mer_index_t_ptr;
typedef bool Mer_flag_t;

typedef const char* Error_t;

typedef unsigned int hash_t;

#ifndef MER_LONG_LONG
typedef long long Mer_longlong;
#endif

#ifndef MER_LONG
typedef long Mer_long;
#endif

#ifndef MER_INT
typedef int Mer_int;
#endif

#ifndef MER_SHORT
typedef short Mer_short;
#endif

#ifndef MER_CHAR
typedef char Mer_char;
#endif

#ifndef MER_BYTE
typedef unsigned char Mer_byte;
#endif

#ifndef MER_FLOAT
typedef float Mer_float;
#endif

#ifndef MER_DOUBLE
typedef double Mer_double;
#endif

#ifndef MER_UINT8_T
#ifndef MER_UINT8_LIB
#define MER_UINT8_LIB 1
#endif
#ifdef MER_UINT8_LIB
#include <stdint.h>
typedef uint8_t Mer_uint8_t;
typedef int8_t Mer_int8_t;
#else
typedef unsigned char Mer_uint8_t;
typedef char Mer_int8_t;
#endif
#endif

#ifndef MER_UINT16_T
#ifndef MER_UINT16_LIB
#define MER_UINT16_LIB 1
#endif
#ifdef MER_UINT16_LIB
#include <stdint.h>
typedef uint16_t Mer_uint16_t;
#else
typedef unsigned short Mer_uint16_t;
#endif
#endif

#ifndef MER_UINT32_T
#ifndef MER_UINT32_LIB
#define MER_UINT32_LIB 1
#endif
#ifdef MER_UINT32_LIB
#include <stdint.h>
typedef uint32_t Mer_uint32_t;
#else
typedef unsigned int Mer_uint32_t;
#endif
#endif

#ifndef MER_UINT64_T
#ifndef MER_UINT64_LIB
#define MER_UINT64_LIB 1
#endif
#ifdef MER_UINT64_LIB
#include <stdint.h>
typedef uint64_t Mer_uint64_t;
#else
typedef unsigned long long Mer_uint64_t;
#endif
#endif

#ifndef MER_BOOL
typedef bool Mer_bool;
#endif

#ifndef MER_VOID
typedef void Mer_void;
#endif

#ifndef MER_SSIZE_T
#ifdef _WIN32
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif
typedef ssize_t Mer_ssize_t;
#endif

#ifndef MER_SIZE_T
#ifdef _WIN32
#include <BaseTsd.h>
typedef SIZE_T size_t;
#endif
typedef unsigned long long Mer_size_t;
#endif

#ifndef MER_NULL
#define MER_NULL nullptr
#endif

#ifndef MER_UNUSED
#define MER_UNUSED(x) (void)(x)
#endif

#ifndef MER_CONST_CHAR
typedef const char *Mer_string;
#define REAL_STRING 1
#ifdef REAL_STRING
#include <string>
typedef string Mer_real_string;
#else
typedef const char *Mer_real_string;
#endif
#endif

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

#define DEBUG(x) cout << x << endl;

#define BREAK_POINT while(1);

#define MAX_TOKEN_SIZE 1024

#define EOF_T "EOF"
#define EOL_T "EOL"
#define ASSIGN "ASSIGN"
#define MOD "MOD"
#define IS "IS"
#define INT_ "INT_"
#define PLUS "PLUS"
#define MINUS "MINUS"
#define STR "STR"
#define LIST "LIST"
#define EXTRACT "EXTRACT"
#define DEFINE_VAL "DEFINE_VAL"
#define DEFINE_STA "DEFINE_STA"
#define DIV "DIV"
#define TIME "TIME"
#define VARIABLE "VARIABLE"
#define STRING "STRING"
#define LET "LET"
#define IS "IS"
#define DOT "DOT"
#define COMMA "COMMA"
#define ASSIGN "ASSIGN"
#define IF "IF"
#define ELSE "ELSE"
#define FOR "FOR"
#define WHILE "WHILE"
#define RETURN "RETURN"
#define FUNCTION "FUNCTION"
#define LEFT_PAREN "LEFT_PAREN"
#define RIGHT_PAREN "RIGHT_PAREN"
#define LEFT_BRACKET "LEFT_BRACKET"
#define RIGHT_BRACKET "RIGHT_BRACKET"
#define ASSERT "ASSERT"
#define LEFT_BRACE "LEFT_BRACE"
#define END_T "END_T"
#define RIGHT_BRACE "RIGHT_BRACE"
#define EQUAL "EQUAL"
#define NOT_EQUAL "NOT_EQUAL"
#define LESS "LESS"
#define LESS_EQUAL "LESS_EQUAL"
#define GREATER "GREATER"
#define GREATER_EQUAL "GREATER_EQUAL"
#define AND "AND"
#define OR "OR"
#define NOT "NOT"
#define DO_T "DO_T"
#define END_LINE "END_LINE"
#define BREAK "BREAK"
#define ELIF "ELIF"
#define CONTINUE "CONTINUE"
#define CLASS "CLASS"
#define INTERFACE_ "INTERFACE_"
#define STRUCT "STRUCT"
#define NEW "NEW"
#define DELETE_ "DELETE_"
#define CAST "CAST"
#define FLOAT_ "FLOAT"
#define DOUBLE_ "DOUBLE"
#define CHAR_ "CHAR"
#define SHORT_ "SHORT"
#define LONG_ "LONG"
#define AUTO_ "AUTO"
#define VOID_ "VOID"
#define IMPORT "IMPORT"
#define BOOL_ "BOOL"
#define SEMICOLON "SEMICOLON"
#define COLON "COLON"
#define ARROW "ARROW"
#define LOOP "LOOP"
#define COMMENT "COMMENT"
#define INCLUDE "INCLUDE"
#define EXTERN_T "EXTERN_T"
#define USING "USING"
#define VOID_T "VOID_T"
#define TRUE_T "TRUE_T"
#define FALSE_T "FALSE_T"
#define BREAK_T "BREAK_T"
#define POW "POW"
#define CONST_ "CONST"
#define ARG "ARG"
#define KWARG "KWARG"
#define FUNCTION_CALL "FUNCTION_CALL"
#define PLUS_PLUS "PLUS_PLUS"
#define MINUS_MINUS "MINUS_MINUS"
#define THEN "THEN"
#define IN_T "IN"
#define PLUS_EQUAL "PLUS_EQUAL"
#define MINUS_EQUAL "MINUS_EQUAL"
#define TIMES_EQUAL "TIMES_EQUAL"
#define DIV_EQUAL "DIV_EQUAL"
#define MOD_EQUAL "MOD_EQUAL"

#define INT_T "INT_T"
#define FLOAT_T "FLOAT_T"
#define DOUBLE_T "DOUBLE_T"
#define STRING_T "STRING_T"
#define AUTO_T "AUTO_T"
#define NULL_T "NULL_T"
#define VOID_T "VOID_T"
#define BOOL_T "BOOL_T"
#define CHAR_T "CHAR_T"
#define SHORT_T "SHORT_T"
#define LONG_T "LONG_T"
#define LITERAL_T "LITERAL_T"
#define FUNCTION_T "FUNCTION_T"
#define ARRAY_T "ARRAY_T"
#define STRUCT_T "STRUCT_T"
#define POINTER_T "POINTER_T"
#define CLASS_T "CLASS_T"
#define INTERFACE__T "INTERFACE__T"

#define LITERAL {INT_, FLOAT_, DOUBLE_}
#define IDENTIFIER {DIV, MOD, PLUS, TIME, MINUS, VARIABLE}
#define EXPR {PLUS, MINUS, DIV, TIME, MOD, INT_, FLOAT_, DOUBLE_}
#define TYPE {INT_T, FLOAT_T, DOUBLE_T, CHAR_T, SHORT_T, LONG_T, AUTO_T, VOID_T, BOOL_T, STRING_T, STRUCT_T, CLASS_T}

#define is_tok_literal(tok) (\
    tok == INT_ \
    || tok == FLOAT_ \
    || tok == DOUBLE_ \
)

#define is_tok_identifier(tok) (\
    tok == EOF_T \
    || tok == VARIABLE \
)

#define is_tok_expr(tok) (\
    is_tok_literal(tok) \
    || is_tok_identifier(tok) \
)

#define is_tok_type(tok) (\
    tok == INT_T \
    || tok == FLOAT_T \
    || tok == DOUBLE_T \
    || tok == CHAR_T \
    || tok == SHORT_T \
    || tok == LONG_T \
    || tok == AUTO_T \
    || tok == VOID_T \
    || tok == BOOL_T \
    || tok == STRING_T \
)

#define isskippable(c) (\
    c == ' ' \
    || c == '\n' \
    || c == '\t' \
    || c == '\r' \
    || c == '\0')

#define is_potential_identifier_char(c) (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_')

#define is_potential_literal_char(c) (c >= '0' && c <= '9' || c == '.')

#define is_digit(c) (c >= '0' && c <= '9')

#define is_alpha(c) (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')

#define is_alpha_num(c) (is_alpha(c) || is_digit(c))

#define is_keywords(c) (c == '+' || c == '-' || c == '*' || c == '/' || c == ',' \
    || c == ':' || c == '=' || c == '!' || c == '%' \
    || c == '<' || c == '>' || c == '&' || c == '\\' \
    || c == '^' || c == ';' || c == '!' \
    || c == '[' || c == ']' || c == '.' \
    || c == '|')

#define WEIRD_CHAR(c) ( \
    !(is_alpha(c) || is_digit(c) || c == '_' || \
    c == '+' || c == '-' || c == '*' || c == '/' || \
    c == '=' || c == '<' || c == '>' || c == '!' || \
     c == '&' || c == '|' || c == '^' || c == '%' || \
    c == '(' || c == ')' || c == '{' || c == '}' || c == '$' || \
    c == '[' || c == ']' || c == ';' || c == ':' || c == '@' || \
    c == ',' || c == '.' || c == '"' || c == '\'' || \
    c == '#' || c == '\n' || c == '\r' || c == '\t' || c == '\0') \
)

#define IS_C_SPACE(c) (c == ' ' || c == '\t' || c == '\r')

#define GET_NEXT_TOK(lexer) (lexer->cur = lexer->buf[lexer->id++])
#define PEEK(lexer) (lexer->buf[lexer->id])
#define LOOK_AHEAD(lexer, n) (lexer->buf[lexer->id + n])
#define IS_EOF(lexer) (lexer->buf[lexer->id] == '\0')
#define IS_EOL(lexer) (lexer->buf[lexer->id] == '\n')
#define IS_SPACE(lexer) (lexer->buf[lexer->id] == ' ' || lexer->buf[lexer->id] == '\t' || lexer->buf[lexer->id] == '\r')
#define LEX_ADVANCE(lexer) (lexer->col++, lexer->cur = lexer->buf[++lexer->id])
#define LEX_PRE_ADVANCE(lexer) (lexer->col++, lexer->cur = lexer->buf[lexer->id++])
#define LEX_DECR_ADVANCE(lexer) (lexer->col++, lexer->cur = lexer->buf[--lexer->id])
#define LEX_DECR_PRE_ADVANCE(lexer) (lexer->col++, lexer->cur = lexer->buf[lexer->id--])
#define LEX_RESET(lexer) (lexer->id = 0, lexer->col = 0)
#define LEX_NEWLINE(lexer) (lexer->col = 0, lexer->row++)
#define LEX_INCR(lexer) (lexer->id++, lexer->col++)
#define LEX_DECR(lexer) (lexer->id--, lexer->col--)
#define LEX_PEEK(lexer) (lexer->buf[lexer->id + 1])
#define LEX_STAY(lexer) (lexer->buf[lexer->id])
#define LEX_CUR(lexer) (lexer->cur);

#define IS_HEX_CHAR(c) ( \
    ((c) >= '0' && (c) <= '9') || \
    ((c) >= 'a' && (c) <= 'f') || \
    ((c) >= 'A' && (c) <= 'F') \
)

#define TRUE_LINE(parser) (parser->lexer->row)

#define Program "Program"
#define LetStatement "LetStatement"
#define ExpressionStatement "ExpressionStatement"
#define ImportStatement "ImportStatement"
#define IfStatement "IfStatement"
#define AssignStatement "AssignStatement"
#define DefineStatement "DefineStatement"
#define WhileStatement "WhileStatement"
#define ForStatement "ForStatement"
#define ImportStatement "ImportStatement"
#define IncludeStatement "IncludeStatement"
#define BlockStatement "BlockStatement"
#define ReturnStatement "ReturnStatement"
#define MemberAccess "MemberAccess"
#define StoreAttributeStatement "StoreAttributeStatement"
#define AttributeExpression "AttributeExpression"
#define StoreIndexStatement "StoreIndexStatement"
#define ExtractExpression "ExtractExpression"
#define StringExpression "StringExpression"
#define ExtractExpression "ExtractExpression"
#define ArrayExpression "ArrayExpression"
#define StringIdentifier "StringIdentifier"
#define Expression "Expression"
#define FunctionStatement "FunctionStatement"
#define FunctionCallExpression "FunctionCallExpression"
#define Identifier_ "Identifier"
#define ComparisonExpression "ComparisonExpression"
#define StringVariableStatement "StringVariableStatement"
#define Literal "Literal"
#define DictionaryExpression "DictionaryExpression"
#define TrueExpression "TrueExpression"
#define FalseExpression "FalseExpression"
#define IntegerLiteral "IntegerLiteral"
#define LoopStatement "LoopStatement"
#define BreakStatement "BreakStatement"
#define ContinueStatement "ContinueStatement"
#define BinaryExpression "BinaryExpression"
#define StringExpression "StringExpression"
#define ListStatement "ListStatement"
#define ListExpression "ListExpression"
#define ArrayStoreElementExpression "ArrayStoreElementExpression"
#define ForInStatement "ForInStatement"
#define DefineExpression "DefineExpression" 
#define AndExpression "AndExpression"
#define OrExpression "OrExpression"
#define NotExpression "NotExpression"
#define IncrementExpression "IncrementExpression"
#define AttrExpression "AttrExpression"
#define DecrementExpression "DecrementExpression"
#define FunctionWithArgsStatement "FunctionWithArgsStatement"
#define FunctionCallWithArgsExpression "FunctionCallWithArgsStatement"
#define ClassStatement "ClassStatement"
#define InitalizeStatement "InitializeStatement"
#define DeleteStatement "DeleteStatement"
#define AssertStatement "AssertStatement"

#define is_ast_attribute(type) ((type) == ExtractExpression || (type) == FunctionCallExpression || (type) == Identifier_)

#define is_ast_expression(type) \
    ((type) == BinaryExpression                 || \
     (type) == Literal                          || \
     (type) == DictionaryExpression             || \
     (type) == Identifier_                      || \
     (type) == ComparisonExpression             || \
     (type) == ArrayExpression                  || \
     (type) == FunctionCallExpression           || \
     (type) == AttributeExpression              || \
     (type) == FunctionCallWithArgsExpression   || \
     (type) == IncrementExpression              || \
     (type) == AndExpression                    || \
     (type) == DefineExpression                 || \
     (type) == OrExpression                     || \
     (type) == NotExpression                    || \
     (type) == ExtractExpression                || \
     (type) == TrueExpression                   || \
     (type) == FalseExpression                  || \
     (type) == StringIdentifier)

#define PRINT_ADDRESS                      0x71
#define IO_WRITE_ADDRESS                   0x72
#define EVAL_ADDRESS                       0x73
#define PAUSE_ADDRESS                      0x74
#define EXIT_ADDRESS                       0x75
#define CLS_ADDRESS                        0x76
#define HELP_ADDRESS                       0x77
#define PI_ADDRESS                         0x78
#define LIST_ADDRESS                       0x79
#define TAU_ADDRESS                        0x7A
#define GOLDEN_RATIO_ADDRESS               0x7B
#define EULER_ADDRESS                      0x7C
#define SLEEP_ADDRESS                      0x7D
#define INFINITY_ADDRESS                   0x7E
#define THE_TRUE_ADDRESS                   0x7F
#define TO_STRING_ADDRESS                  0x80
#define INPUT_ADDRESS                      0x81
#define TO_INT_ADDRESS                     0x82
#define THE_FALSE_ADDRESS                  0x83
#define SAME_STRING_ADDRESS                0x84
#define SIZE_ADDRESS                       0x85
#define PUSH_ADDRESS                       0x86
#define POP_ADDRESS                        0x87
#define PRINT_LIST_ADDRESS                 0x88
#define PUTS_ADDRESS                       0x89
#define ISDIGIT_ADDRESS                    0x8A
#define COS_ADDRESS                        0x8B
#define SIN_ADDRESS                        0x8C
#define TAN_ADDRESS                        0x8D
#define FFI_CHARR_ADDRESS                  0x8E
#define FFI_FLOAT_ADDRESS                  0x8F
#define FFI_ADDRESS                        0x90
#define CHANGE_ITEM_ADDRESS                0x91
#define TYPE_ADDRESS                       0x92
#define RANGE_ADDRESS                      0x93
#define DLL_LOAD_FUNC                      0xF9
#define SUB_STR                            0x95
#define SPLIT_ADDRESS                      0x96
#define HASH_ADDRESS                       0x97
#define EMPTY_ADDRESS                      0x98
#define FREE_ADDRESS                       0x99
#define TIME_ADDRESS                       0xFA

// system variable
#define __file__G                          0xE0
#define __Global_G                         0xE1
#define __Module__G                        0xE2
#define __Libs__G                          0xE3
#define __Ver__G                           0xE4
#define __name__G                          0xE5
#define __path__G                          0xE8
#define __cached__G                        0xE9

#define TO_STRING(x) std::to_string(x).c_str()

#define MAX_FLOAT 3.4028235e+38
#define MERCURY_BINARY_SUB(c1, c2) ((c1) - (c2))
#define MERCURY_BINARY_ADD(c1, c2) ((c1) + (c2))
#define MERCURY_BINARY_DIV(c1, c2) ((c2) != 0 ? ((c1) / (c2)) : MAX_FLOAT)
#define MERCURY_BINARY_POW(c1, c2) (powf((c1), (c2)))
#define MERCURY_BINARY_MUL(c1, c2) ((c1) * (c2))
#define MERCURY_BINARY_MOD(c1, c2) ((c1) % (c2))
#define MERCURY_BINARY_AND(c1, c2) ((c1) & (c2))
#define MERCURY_BINARY_OR(c1, c2) ((c1) | (c2))
#define MERCURY_BINARY_XOR(c1, c2) ((c1) ^ (c2))
#define MERCURY_BINARY_SHL(c1, c2) ((c1) << (c2))
#define MERCURY_BINARY_SHR(c1, c2) ((c1) >> (c2))
#define MERCURY_BINARY_NOT(c1) (~(c1))
#define MERCURY_BINARY_GREATER(c1, c2) ((c1) > (c2))
#define MERCURY_BINARY_LESS(c1, c2) ((c1) < (c2))
#define MERCURY_BINARY_GREATER_EQUAL(c1, c2) ((c1) >= (c2))
#define MERCURY_BINARY_LESS_EQUAL(c1, c2) ((c1) <= (c2))
#define MERCURY_BINARY_EQUAL(c1, c2) ((c1) == (c2))
#define MERCURY_BINARY_NOT_EQUAL(c1, c2) ((c1) != (c2))
#define MERCURY_INSERT(code, ins, size) code.insert(code.end(), ins, ins + size);
#define MERCURY_PUSH(code, ins) code.push_back(ins);
#define MERCURY_POP(code) code.pop_back();
#define INCREMENT(var) var++;
#define DECREMENT(var) var--;
#define INCREMENT_BY(var, value) var += value;
#define DECREMENT_BY(var, value) var -= value;
#define INCR_BYTE_uint8_t(var) var += 0x0001;
#define DECR_BYTE_uint8_t(var) var -= 0x0001;
#define INCR_BYTE_uint16_t(var) var += 0x0001;
#define DECR_BYTE_uint16_t(var) var -= 0x0001;
#define INCR_BYTE_uint32_t(var) var += 0x0001;
#define DECR_BYTE_uint32_t(var) var -= 0x0001;

#define stack_push(val) push_stack(stk, val)

#define stack_pop() (stk->s_table->table.pop_back())

#define MER_VALUE(val) MerCompiler_table_setup(val, NULL_UINT_8_T)
#define NULL_VALUE value(0)

#define CHECK 1
#define CONST_M(x) const x
#define IS_TRUE(x) ((x) == 1)
#define IS_FALSE(x) ((x) == 0)
#define TRUE_MARCO 1
#define NULL_MARCO 0
#define INLINE(x) inline x
#define CONSTEXPR(x) constexpr x
#define EXTERN(x) extern x

#define both(a, b) (a && b)
#define tstr(a) ((a)->is_str)
#define tlist(a) ((a)->is_list)
#define trbool(a) (a->is_bool)
#define tfunc(a) (a->is_func)
#define both_list(a, b) (both(tlist(a), tlist(b)))
#define both_str(a, b) (both(tstr(a), tstr(b)))
#define both_func(a, b) (both(tfunc(a), tfunc(b)))
#define both_bool(a, b) (both(trbool(a), trbool(b)))

#define push_true_to_stack()                        \
    table *true_value = MerCompiler_Table_new();      \
    true_value->bool_v = MerCompiler_bool_new();      \
    true_value->bool_v->value = true;                 \
    true_value->is_bool = true;                       \
    true_value->cval = 1;                             \
    stack_push(true_value);                           \

#define push_false_to_stack()                       \
    table *false_value = MerCompiler_Table_new();      \
    false_value->bool_v = MerCompiler_bool_new();      \
    false_value->bool_v->value = false;                \
    false_value->is_bool = true;                       \
    false_value->cval = 0;                             \
    stack_push(false_value);                           
    

#define TRUE_VALUE                                  \
    table *bool_obj = MerCompiler_Table_new();      \
    bool_obj->bool_v = MerCompiler_bool_new();      \
    bool_obj->bool_v->value = true;                 \
    bool_obj->is_bool = true;                       \
    bool_obj->cval = 1;                             \

#define FALSE_VALUE                                 \
    table *bool_obj = MerCompiler_Table_new();      \
    bool_obj->bool_v = MerCompiler_bool_new();      \
    bool_obj->bool_v->value = false;                \
    bool_obj->is_bool = true;                       \
    bool_obj->cval = 0;                             \

#define MERCURY_ADD_VALUE(stk, value) (stk->s_table->table.push_back(MerCompiler_table_setup(value)))
#define MERCURY_ADD_VALUE_ADDRESS(stk, value, address) (stk->s_table->table.push_back(MerCompiler_table_setup(value, address)))
#define POP_STACK(stk) pop_stack(stk)    
#define EAT_STACK(stk) eat_stack(stk)
#define POP() pop_stack(stk)
#define PUSH_STACK(stk, value) push_stack(stk, value)

#define LIST_VALUE(size_of_list, first_element_value, last_element_value) (size_of_list * (first_element_value + last_element_value) / 2)

#define PRINT_VECTOR(vec) for (int i = 0; i < vec.size(); i++) { cout << vec[i] << endl; }

typedef void __builtin_func_t;

#define __io_cout_int(x) cout << (x) << endl;

#define __io_cout_stdout(x) \
    cout << x;

#define CREAT_GLOBAL_TABLE(address, name, real_name) create_global_table_ptr(address, name, real_name)
#define CREAT_LOCAL_TABLE(address, name, real_name) create_global_table_ptr(address, name, real_name)

#define INC_U(u) (u.byte++, u.cid++)

#define create_label(glb) ++glb.address
#define create_para(glb) ++glb.para_address

__mer_core_data__ unordered_map<string, Mer_uint8_t> lib_hashmap = {
    {"pause", PAUSE_ADDRESS}, 
    {"exit", EXIT_ADDRESS},
    {"same", SAME_STRING_ADDRESS}, 
    {"size", SIZE_ADDRESS}, 
    {"push", PUSH_ADDRESS},
    {"pop", POP_ADDRESS},
    {"puts", PUTS_ADDRESS}, 
    {"free", FREE_ADDRESS},
    {"type", TYPE_ADDRESS}, 
    {"dll_loadf", DLL_LOAD_FUNC},
    {"print", PRINT_ADDRESS},
    {"range", RANGE_ADDRESS},
    {"sub", SUB_STR}, 
    {"ffi", FFI_ADDRESS},
    {"ffi_float", FFI_FLOAT_ADDRESS},
    {"ffi_char", FFI_CHARR_ADDRESS},
    {"isdigit", ISDIGIT_ADDRESS},
    {"sleep", SLEEP_ADDRESS},
    {"to_list", LIST_ADDRESS},
    {"to_str", TO_STRING_ADDRESS},
    {"to_int", TO_INT_ADDRESS},
    {"input", INPUT_ADDRESS},
    {"to_str", TO_STRING_ADDRESS},
};

__mer_core_data__ unordered_map<string, Mer_uint8_t> global_hashmap = {
    {"inf", INFINITY_ADDRESS},
    {"__file__", __file__G},
    {"__Global__", __Global_G},
    {"__Module__", __Module__G},
    {"__Libs__", __Libs__G},
    {"__Ver__", __Ver__G},
    {"__name__", __name__G},
    {"__path__", __path__G},
    {"__cached__", __cached__G}
};

#define STACK_PUSH(stk, value) \
    stk->s_table->table.push_back(value);

#define STACK_POP(stk) \
    stk->s_table->table.pop_back();

#define STACK_VAL(a) \
    MerCompiler_table_setup(a, NULL_UINT_8_T);

#define MAKE_LIST_VALUE(list) __list_value(list)

#define list_v(a) (a->list_v)
#define list_size(a) (a->list_v->size)
#define list_args(a) (a->list_v->args)
#define list_is_empty(a) (a->list_v->size == 0)
#define set_size(a, lsize) (a->list_v->size = lsize)

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

#define BUILD_LIB_FUNC(name, func) \
    __register_lib_to_global(lib_hashmap[name], name); \
    __register_lib(lib_hashmap[name], (void*) func, name); \
    __register_lib_to_global_stack(lib_hashmap[name], (mFunc_T) func); \

#define BUILD_GLOBAL_VARIABLE(name, val) \
    __register_global_variable(global_hashmap[name], val); \
    __register_global(global_hashmap[name], name); \

#define BUILD_GLOBAL_VARIABLE_WITH_OBJECT(name, obj) \
    __register_global_variable_with_object(name, obj); \
    __register_global(global_hashmap[name], name); \

#define is_a_builtin(x) (lib_hashmap.find(x) != lib_hashmap.end())

#define push_to_gc(o) { \
    if ((o)) { \
        if ((o)->ref_count < 1) { \
            GARBAGE_POOL.push_back((o)); \
        } \
    } \
}

// ---------------------------------------------------------------

struct mAST_T
{
    string file; // for ast program

    string type;
    string tok;
    float value = 0.0;
    string string_iden;
    mAST_T *poutput;

    // class
    string class_name;
    vector<mAST_T *> members;

    int true_line;

    bool is_at_start;
    bool is_if;
    bool is_while;
    bool is_for;
    bool is_import;
    bool is_block;
    bool is_arg = false;

    // For if statement
    mAST_T *comp;
    
    vector<mAST_T *> then_body;
    vector<mAST_T *> else_body;
    vector<mAST_T *> elif_body;

    bool has_else = false;
    bool has_elif = false;

    // incr expr
    bool is_inc;
    bool is_dec;
    mAST_T *inc_dec_value;

    // define
    mAST_T * define_val;

    // dict
    vector<pair<mAST_T*, mAST_T*>> dict;

    // assginment
    string assign_iden;
    mAST_T *assign_value;
    bool is_assign_operator;
    bool is_plus_assign;
    bool is_minus_assign;
    bool is_mul_assign;
    bool is_div_assign;
    bool is_mod_assign;

    // initalize
    string init_iden;
    vector<mAST_T *> init_body;
    vector<mAST_T *> init_args;

    // not expr
    mAST_T *not_expr;
    
    // for break and continue
    bool is_break;
    bool is_continue;

    // for built-in function
    string built_in_func_name;
    bool is_built_in_func;

    // for while loop
    mAST_T *while_cond;
    bool is_inf;
    vector<mAST_T *> while_body;

    // for string
    bool is_string;
    string str_v;
    vector<mAST_T *> str_children;

    // for string statement
    string str_iden;
    mAST_T *str_value;

    //for print
    string str_print_v;
    bool is_print;
    mAST_T *print_v;

    // For literal
    bool is_var;
    bool is_constant;
    bool is_global;
    bool is_local;
    bool is_mom;
    bool is_list;
    bool is_extract_expression = false;
    bool is_None;

    // for attr System.out.println("hello");
    mAST_T *attr;
    string attr_iden;
    vector<mAST_T *> attrs;
    bool is_dad;

    // for delete
    bool is_del_element_from_list;
    string del_iden;
    mAST_T *del_index;

    // for comparison expression
    string comp_op;
    mAST_T *comp_left;
    mAST_T *comp_right;

    // for do while loop
    vector<mAST_T *> do_body;

    // for in statement
    string in_iden;
    mAST_T *in_value;
    vector<mAST_T *> in_body;   
    bool for_is_having_else;
    vector<mAST_T *> in_else_body; 

    // For variable
    string var_name;
    string data_type;
    mAST_T *var_value;

    // For function
    string func_name;
    vector<mAST_T *> body;
    vector<string> args_idens;
    string func_type;

    // for dictionary
    mAST_T *dict_key;
    mAST_T *dict_value;
    vector<mAST_T *> dict_list;

    // for return
    mAST_T *return_v;
    bool is_return;
    bool is_void;

    // For function call
    string func_call;
    bool is_having_args;
    vector<mAST_T *> args;

    // For binary expression
    string op;
    mAST_T *left;
    mAST_T *right;
    bool cond;

    // For list
    string list_name;
    string list_type;
    vector<mAST_T *> list;
    bool is_alone_val;
    size_t list_size;

    // for extract expression and statement
    string extract_name;
    vector<mAST_T *> mul_extract;
    mAST_T *extract_value;
    mAST_T *extract_assign;
    vector<mAST_T *> extract_list;
    bool is_mul_extract;
    bool is_value_extract;
    bool is_extract;
    bool is_string_extract;
    bool is_extract_statement;
    bool is_extract_list;

    // for string variable
    string str_var_name;
    string str_var_type;
    mAST_T *str_var_value;

    // for array store
    mAST_T *array_store;
    mAST_T *array_store_value;
    
    // for attr store
    mAST_T *attr_store;
    mAST_T *attr_store_value;

    int args_size = 0;
    vector<mAST_T *> children;
};

struct mLexer_T
{
    const char *buf;  // line of buffer for the source code
    const char *inp;  // input buffer for the source code
    const char *file; // file name
    const char *scr;        // source code this is what compiler need to read
    const char *iden;       // identifier buffer for the source code
    char *str;        // string buffer for the source code
    char *com;        // comment buffer for the source code
    char *sytx;       // syntax buffer for the source code
    char *num;        // number buffer for the source code
    char *mmode;      // mode like :p, :string, :o

    char cstart; // start of the buffer for the source code
    char cend;   // end of the buffer for the source code
    char cur;    // current character in the buffer
    char ncur;   // next character in the buffer

    int col;   // current column in the buffer
    int row;   // current row in the buffer
    int line;  // current line in the buffer
#ifdef DEBUG
    char c_cur;  // current character in the buffer (for debug)
    char *c_line;// current line in the buffer (for debug)
    int c_col;   // current line in the buffer (for debug)
    int c_row;   // current row in the buffer (for debug)
    int c_id;    // current index in the buffer (for debug)
    int c_start; // start of the buffer in the buffer (for debug)
    int c_end;   // end of the buffer in the buffer (for debug)
#endif

    int l_idx; // look ahead index
    char l_cur; // look ahead character

    int blk;   // check is block 1 is true 0 is false
    int size;  // size of the buffer
    int id;    // current index in the buffer
    int nid;   // next index in the buffer
    int level; // level of parent () [] {} in the buffer
    int end;   // is end of the buffer 1 is true 0 is false
    int start; // is start of the buffer 1 is true 0 is false

    size_t buf_size; // size of the buffer
};

struct mToken_T {
    string tok;
    string type;
    string name;
    string symbol;
    string string_iden;

    float value;
    size_t index;
};

struct mParser_T {
    mLexer_T *lexer;
    mToken_T *token;
    mToken_T *next;
    bool is_eof = false;
};

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
    vector<Mer_uint8_t> buff;
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
    vector<void*> methods;
    
    _class *super_class;
    _class *inheritance;
    _class *this_obj;
};

struct _object
{
    GC_HEAD;

    _type_obj *obj_val;
    Mer_size_t obj_size;

    unordered_map<string, _object *> attributes;
}; 

struct __global {
    Mer_uint8_t __Address;
    Mer_string __Name;
    Mer_real_string __name;

    Mer_uint8_t args_size = 0x00;
    Mer_size_t true_args_size = 0;
    bool is_let = true;
};

typedef struct _pcode           mCode_T;
typedef struct _code            mOpCode_T;
typedef struct _val             mValue_T;
typedef struct _string          mString_T;
typedef struct _variable        mVariable_T;
typedef struct _func_object     mFunc_object_T;
typedef struct _list_object     mList_T;
typedef struct _object          mObject_T;
typedef struct _class           mClass_T;   
typedef struct __iter           mIter_T;
typedef struct _bool            mBool_T;
typedef vector<__global *>      GlobalTable;
typedef void* (*mFunc_T)();
typedef void* (*Point_to)();

struct loop_stack {
    Mer_uint8_t continue_label;
    Mer_uint8_t break_label;
};

struct code_stack {
    Mer_uint8_t address;
    string name;
    mCode_T &code;
};

struct __compiler_u {
    const char* file;
    Mer_uint8_t address;
    Mer_uint8_t para_address;
    Mer_uint8_t cid;
    Mer_string name;
    bool is_in_func = false;
    bool is_in_class = false;
    Mer_string type;
    vector<loop_stack> loop;
};

#define OTHER_STACK \
    bool is_in_glb; \
    bool is_in_lc; \
    Mer_uint8_t address_of; \


#define HEAD_OBJ \
    mObject_T *f_address; \
    mObject_T *f_type; \
    mObject_T *f_name; \
    mObject_T *f_value; \
    mObject_T *f_size; \
    mObject_T *f_local; \
    mObject_T *f_global; \
    mObject_T *f_string; \
    mObject_T *f_hash; \
    mObject_T *f_error;

#define FLAG \
    bool is_str = false; \
    bool is_var = false; \
    bool is_instance = false; \
    bool is_func = false; \
    bool is_class = false; \
    bool is_code = false; \
    bool is_type = false; \
    bool is_iter = false; \
    bool is_bool = false; \
    bool is_list = false; \
    bool is_obj = false; \
    bool is_opcode = false;

#define HEAD_VALUE \
    mString_T *f_str_v; \
    mVariable_T *var_v; \
    mFunc_T func_v; \
    mBool_T *bool_v; \
    mCode_T *code_v; \
    mIter_T *iter_v; \
    mClass_T *class_ref; \
    mClass_T *class_v; \
    mList_T *list_v; \
    mObject_T *obj_v; \
    mOpCode_T *opcode_v; \
    mFunc_object_T *func_obj_v; \

#define HEAD_STACK \
    Mer_number_t cbuf = 0; \
    Mer_number_t value = 0; \
    Mer_number_t cval = 0; \
    Mer_index_t size = 0; \
    Mer_index_t cidx = 0; \
    Mer_uint8_t address = 0; \
    Mer_real_string name; \
    Mer_real_string type; \
    Mer_real_string str_v; \
    Mer_real_string err; \
    Mer_flag_t is_builtin = false; \
    Mer_flag_t is_same = false; \
    Mer_flag_t is_local = false; \
    vector<Mer_uint8_t> tbody;

typedef struct __table
{
    int ref_count = 0;
    bool gc_freed = false;
    HEAD_STACK HEAD_OBJ HEAD_VALUE FLAG OTHER_STACK
    vector<__table *> table;
    __table* class_p;

} table;

typedef struct __symboltable
{
    int ref_count = 0;
    bool gc_freed = false;
    HEAD_STACK HEAD_OBJ HEAD_VALUE FLAG OTHER_STACK
    table *tab;
} symtable;

typedef struct __stack
{
    table *s_table;
    symtable *s_symtable;
    symtable *s_global;
    symtable *s_local;

    size_t code_idx; // Debug
    string code_name; // Debug
    Mer_uint8_t raw_debug; // Debug
} stack;

typedef struct __call_context {
    mCode_T &code;
    
    Mer_uint8_t address;
    __call_context *caller;

    table* return_val;

    mFunc_object_T* func_obj;

    vector<symtable *> local;
} CallContext;

struct __program_bytecode {
    mCode_T &code;
    Mer_size_t lid;             
    hash_t hash;
    Mer_size_t glb_id;
    Mer_size_t lc_id;
    Mer_size_t iid;             
    Mer_size_t oid;             
    Mer_uint8_t icode;          
    Mer_uint8_t ocode;          
    unordered_map<Mer_uint8_t, Mer_size_t> label_map;
    Mer_size_t loop_size;
    bool is_in_func;
    const char *file;
    bool is_label = false;
};

#define incr_stk_idx(stk) \
    stk->code_idx++; \

vector<string> import = {};
vector<code_stack> code_s = {};

__mer_core_data__ vector<Mer_Reg> mer_core_libs = {};

__mer_core_data__ vector<table*> GARBAGE_POOL = {};

__mer_core_data__ vector<symtable *> _G = {};
__mer_core_data__ vector<symtable *> _L = {};
__mer_core_data__ vector<symtable *> _T = {};

__mer_core_data__ GlobalTable GLOBAL_TABLE = {};
__mer_core_data__ GlobalTable LOCAL_TABLE = {};
__mer_core_data__ GlobalTable ATTRIBUTE_TABLE = {};

__mer_core_data__ vector<void*> _EXIST = {};

__mer_core_data__ vector<table *> GC_TABLE = {};

__mer_core_data__ vector<Mer_string_entry*> STRING_ENTRY = {};

mLexer_T *_MerLexer_init(const char *buf);
mLexer_T *_MerLexer_get_next_char(mLexer_T *lexer);
mLexer_T *_MerLexer_peek_char(mLexer_T *lexer);
mLexer_T *_MerLexer_new(void);
int _MerLexer_free(mLexer_T *lexer);

mToken_T *_MerLexer_look_ahead(mLexer_T *lexer);
mToken_T *_MerLexer_get_next_tok(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_number(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_keyword(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_string(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_syntax(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_function_call(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_define(mLexer_T *lexer);

void _MerLexer_jump_to(mLexer_T *lexer, int n);
void _MerLexer_skip_whitespace(mLexer_T *lexer);
void _MerLexer_skip_comment(mLexer_T *lexer);

static _object NULL_OBJECT_INSTANCE = _object();
static _pcode NULL_CODE_INSTANCE = _pcode();
static _code NULL_OPCODE_INSTANCE = _code();
static _type_obj NULL_TYPE_INSTANCE = _type_obj();

stack *MerCompiler_Stack_new(void);
table *MerCompiler_Table_new(void);
symtable *MerCompiler_SymbolTable_new(void);

int MerCompiler_free_stack(stack *s);
int MerCompiler_free_table(table *t);
int MerCompiler_free_symboltable(symtable *s);

stack *MerCompiler_stack_setup(stack *s, table *t, symtable *sy);
table *MerCompiler_table_setup(float cval, uint8_t address = 0x00);
symtable *MerCompiler_symboltable_setup(string name, float value, string type, uint8_t address);
table *pop_stack(stack *stk);
table *eat_stack(stack *stk);
table *table_clone_shallow(table *dst, table *src);
void reset_table(table *t);
table *push_stack(stack *stk, table *t);

__program_bytecode init_program_bytecode(mCode_T &code);

MERCURY_API unordered_map<Mer_uint8_t, Mer_size_t> __get_label_map(__program_bytecode &u, string mode);   

MERCURY_API Mer_uint8_t next_c(__program_bytecode &u);           
MERCURY_API Mer_uint8_t next_o(__program_bytecode &u);          

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_program(mCode_T &code);
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_statement(__program_bytecode &u, stack *stk);
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_call_context(CallContext *ctx, __program_bytecode &u, stack *stk);

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_PUSH_FLOAT(__program_bytecode &u, stack *stk);                           
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_PUSH_NORMAL_MODE(__program_bytecode &u, stack *stk);         
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_LOAD_GLOBAL(__program_bytecode &u, stack *stk);                
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_COMPARE(__program_bytecode &u, stack *stk, Mer_uint8_t op);          
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_BINARY_OPER(__program_bytecode &u, stack *stk, Mer_uint8_t op);           
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_STORE_GLOBAL(__program_bytecode &u, stack *stk);          
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_MAKE_FUNCTION(__program_bytecode &u, stack *stk);         
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_FUNCTION_CALL(__program_bytecode &u, stack *stk);         
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_JUMP_IF_FALSE(__program_bytecode &u, stack *stk);           
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_BUILD_LIST(__program_bytecode &u, stack *stk);                                   
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_GET_ITEM(__program_bytecode &u, stack *stk);                 
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_STORE_INDEX(__program_bytecode &u, stack *stk);                     
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_CLEN(__program_bytecode &u, stack *stk);                
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_JUMP_TO(__program_bytecode &u, stack *stk);               
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_POP_JUMP_IF_FALSE(__program_bytecode &u, stack *stk);             
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_LOAD_TRUE(__program_bytecode &u, stack *stk);                 
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_LOAD_FALSE(__program_bytecode &u, stack *stk);                              
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_AND(__program_bytecode &u, stack *stk);               
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_OR(__program_bytecode &u, stack *stk);                                
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_NOT(__program_bytecode &u, stack *stk);          
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_INC(__program_bytecode &u, stack *stk);                
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_DEC(__program_bytecode &u, stack *stk);
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_DELETE(__program_bytecode &u, stack *stk);
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_IS(__program_bytecode &u, stack *stk);
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_NOT(__program_bytecode &u, stack *stk);
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_LOAD_ARGS(__program_bytecode &u, stack *stk);
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_CLASS_BEGIN(__program_bytecode &u, stack *stk);
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_LOAD_ATTR(__program_bytecode &u, stack *stk);
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_STORE_ATTR(__program_bytecode &u, stack *stk);
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_CALL_METHOD(__program_bytecode &u, stack *stk);
MERCURY_API __mer_core_data__ stack *MerVM_evaluate_LOAD_METHOD(__program_bytecode &u, stack *stk);

MERCURY_API mCode_T MerCompiler_compile_ast_program(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_id(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_literal(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_binary_expression(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_function_call(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_string_identifier(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_if(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_let(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_return(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_identifier(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_id_expression_statment(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_function(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_print(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_comparison_expression(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_while(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_list(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_assign(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_string_var(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_array(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_extract(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_store_index_statement(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_for_in_statement(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_loop(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_break(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_continue(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_true(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_false(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_function_with_args(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_function_call_with_args(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_and_expression(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_not_expression(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_or_expression(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_import(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_include(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_define(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_define_expression(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_class_statement(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_attribute_expression(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_store_attribute_statement(mAST_T *ast, __compiler_u &glb);

MERCURY_API mCode_T MerCompiler_compile_ast_initialize_statement(mAST_T *ast, __compiler_u &glb);

mParser_T *_MerParser_new(void);
mParser_T *_MerParser_init(mLexer_T *lexer);
int _MerParser_free(mParser_T *parser);

mAST_T *MerParser_parse_binary_expression(mAST_T *left, string op, mAST_T *right);

mAST_T *MerParser_parse_operator_expression(mAST_T *left, string op, mAST_T *right, string type);

mAST_T *MerParser_parse_program(mParser_T *parser);

mAST_T *MerParser_parse(mParser_T *parser);

mAST_T *MerParser_parse_primary_expression(mParser_T *parser);

mAST_T *MerParser_parse_additive_expression(mParser_T *parser);

mAST_T *MerParser_parse_multiplicative_expression(mParser_T *parser);

mAST_T *MerParser_parse_expression_statement(mParser_T *parser);

mAST_T *MerParser_parse_let_statement(mParser_T *parser);

mAST_T *MerParser_parse_function_statement(mParser_T *parser);

mAST_T *MerParser_parse_function_call_expression(mParser_T *parser);

mAST_T *MerParser_parse_return_statement(mParser_T *parser);

mAST_T *MerParser_parse_comparison_expression(mParser_T *parser);

mAST_T *MerParser_parse_compair(mAST_T *left, string op, mAST_T *right);

mAST_T *MerParser_parse_if_statement(mParser_T *parser);

mAST_T *MerParser_parse_while_statement(mParser_T *parser);

mAST_T *MerParser_parse_assignment_statement(mParser_T *parser);

mAST_T *MerParser_parse_string_expression(mParser_T *parser);

mAST_T *MerParser_parse_list_statement(mParser_T *parser);

mAST_T *MerParser_parse_variable_statement(mParser_T *parser);

mAST_T *MerParser_parse_extract_expression(mParser_T *parser);

mAST_T *MerParser_parse_string_statement(mParser_T *parser);

mAST_T *MerParser_parse_array_expression(mParser_T *parser);

mAST_T *MerParser_parse_for_statement(mParser_T *parser);

mAST_T *MerParser_parse_loop_statement(mParser_T *parser);

mAST_T *MerParser_parse_and_expression(mParser_T *parser);

mAST_T *MerParser_parse_or_expression(mParser_T *parser);

mAST_T *MerParser_parse_not_expression(mParser_T *parser);

mAST_T *MerParser_parse_logical_expression(mParser_T *parser);

mAST_T *MerParser_parse_import_statement(mParser_T *parser);

mAST_T *MerParser_parse_define_statement(mParser_T *parser);

mAST_T *MerParser_parse_parent_expression(mParser_T *parser);

mAST_T *MerParser_parse_dictionary_expression(mParser_T *parser);

mAST_T *MerParser_parse_include_statement(mParser_T *parser);

mAST_T *MerParser_parse_class_statement(mParser_T *parser);

mAST_T *MerParser_parse_store_index_statement(mParser_T *parser, mAST_T *left);

mAST_T *MerParser_parse_attribute_expression(mParser_T *parser);

inline mAST_T *MerAST_new(void)
{
    mAST_T *node = new mAST_T();

    node->is_alone_val = false;
    node->is_if = false;
    node->is_while = false;
    node->is_for = false;
    node->is_import = false;
    node->is_block = false;
    node->has_else = false;
    node->is_built_in_func = false;
    node->is_inf = false;
    node->is_string = false;
    node->is_print = false;
    node->is_var = false;
    node->is_constant = false;
    node->is_global = false;
    node->is_local = false;
    node->is_mom = false;
    node->is_list = false;
    node->is_None = false;
    node->is_return = false;
    node->is_void = false;
    node->is_having_args = false;
    node->cond = false;
    node->is_extract = false;
    node->is_string_extract = false;
    node->for_is_having_else = false;
    node->is_plus_assign = false;
    node->is_minus_assign = false;
    node->is_mul_assign = false;
    node->is_div_assign = false;
    node->is_mod_assign = false;
    node->is_assign_operator = false;
    node->is_break = false;
    node->is_continue = false;
    node->is_dad = false;
    node->is_inc = false;
    node->is_extract_list = false;
    node->is_dec = false;

    node->inc_dec_value = nullptr;
    node->attr = nullptr;
    node->poutput = nullptr;
    node->comp = nullptr;
    node->assign_value = nullptr;
    node->while_cond = nullptr;
    node->print_v = nullptr;
    node->comp_left = nullptr;
    node->comp_right = nullptr;
    node->var_value = nullptr;
    node->return_v = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    node->extract_value = nullptr;
    node->str_var_value = nullptr;
    node->extract_assign = nullptr;

    node->true_line = 0;

    return node;
}

inline mAST_T *MerAST_make_parent(string type)
{
    mAST_T *node = MerAST_new();
    node->type = type;
    return node;
}

inline mAST_T *MerAST_make(string type, string tok, float value, string dt, string iden, int row)
{
    mAST_T *node = MerAST_new();
    node->tok = tok;
    node->value = value;
    node->data_type = dt;
    node->type = type;
    node->string_iden = iden;
    return node;
}

inline int MerAST_free(mAST_T* node) {
    if (!node) return 0;

    MerAST_free(node->poutput);
    MerAST_free(node->comp);
    MerAST_free(node->inc_dec_value);
    MerAST_free(node->define_val);
    MerAST_free(node->assign_value);
    MerAST_free(node->not_expr);
    MerAST_free(node->while_cond);
    MerAST_free(node->str_value);
    MerAST_free(node->print_v);
    MerAST_free(node->attr);
    MerAST_free(node->del_index);
    MerAST_free(node->comp_left);
    MerAST_free(node->comp_right);
    MerAST_free(node->in_value);
    MerAST_free(node->var_value);
    MerAST_free(node->dict_key);
    MerAST_free(node->dict_value);
    MerAST_free(node->return_v);
    MerAST_free(node->left);
    MerAST_free(node->right);
    MerAST_free(node->extract_value);
    MerAST_free(node->extract_assign);
    MerAST_free(node->str_var_value);
    MerAST_free(node->array_store);
    MerAST_free(node->array_store_value);
    MerAST_free(node->attr_store);
    MerAST_free(node->attr_store_value);

    for (auto child : node->members) MerAST_free(child);
    for (auto child : node->then_body) MerAST_free(child);
    for (auto child : node->else_body) MerAST_free(child);
    for (auto child : node->elif_body) MerAST_free(child);
    for (auto& kv : node->dict) { 
        MerAST_free(kv.first);
        MerAST_free(kv.second);
    }
    for (auto child : node->init_body) MerAST_free(child);
    for (auto child : node->init_args) MerAST_free(child);
    for (auto child : node->while_body) MerAST_free(child);
    for (auto child : node->str_children) MerAST_free(child);
    for (auto child : node->body) MerAST_free(child);
    for (auto child : node->dict_list) MerAST_free(child);
    for (auto child : node->args) MerAST_free(child);
    for (auto child : node->list) MerAST_free(child);
    for (auto child : node->mul_extract) MerAST_free(child);
    for (auto child : node->extract_list) MerAST_free(child);
    for (auto child : node->children) MerAST_free(child);
    for (auto child : node->do_body) MerAST_free(child);
    for (auto child : node->in_body) MerAST_free(child);
    for (auto child : node->in_else_body) MerAST_free(child);
    for (auto child : node->attrs) MerAST_free(child);

    delete node;
    return 0;
}

inline void MerAST_print_ast(mAST_T *ast, int indent = 0) {
    if (!ast) return;

    auto print_indent = [&](int lv) {
        for (int i = 0; i < lv; i++) cout << "  ";
    };

    print_indent(indent);
    cout << "- Node Type: " << ast->type;

    if (!ast->var_name.empty()) cout << ", var: " << ast->var_name;
    if (!ast->assign_iden.empty()) cout << ", assign: " << ast->assign_iden;
    if (!ast->func_name.empty()) cout << ", func: " << ast->func_name;
    if (!ast->func_call.empty()) cout << ", call: " << ast->func_call;
    if (!ast->string_iden.empty()) cout << ", str_iden: " << ast->string_iden;
    if (!ast->extract_name.empty()) cout << ", extract: " << ast->extract_name;
    if (!ast->op.empty()) cout << ", op: " << ast->op;
    if (!ast->comp_op.empty()) cout << ", cmp: " << ast->comp_op;
    if (!ast->str_v.empty()) cout << ", str: \"" << ast->str_v << "\"";
    if (!ast->tok.empty()) cout << ", tok: " << ast->tok;
    if (ast->value != 0.0) cout << ", val: " << ast->value;
    if (ast->is_string) cout << ", is_string";
    if (ast->is_list) cout << ", is_list";

    cout << " (line " << ast->true_line << ")" << endl;

    if (ast->assign_value) {
        print_indent(indent + 1);
        cout << "assign_value:" << endl;
        MerAST_print_ast(ast->assign_value, indent + 2);
    }

    if (ast->return_v) {
        print_indent(indent + 1);
        cout << "return:" << endl;
        MerAST_print_ast(ast->return_v, indent + 2);
    }

    if (ast->left) {
        print_indent(indent + 1);
        cout << "left:" << endl;
        MerAST_print_ast(ast->left, indent + 2);
    }

    if (ast->right) {
        print_indent(indent + 1);
        cout << "right:" << endl;
        MerAST_print_ast(ast->right, indent + 2);
    }

    if (ast->comp_left) {
        print_indent(indent + 1);
        cout << "comp_left:" << endl;
        MerAST_print_ast(ast->comp_left, indent + 2);
    }

    if (ast->comp_right) {
        print_indent(indent + 1);
        cout << "comp_right:" << endl;
        MerAST_print_ast(ast->comp_right, indent + 2);
    }

    if (ast->array_store) {
        print_indent(indent + 1);
        cout << "array_index:" << endl;
        MerAST_print_ast(ast->array_store, indent + 2);
    }

    if (ast->array_store_value) {
        print_indent(indent + 1);
        cout << "array_value:" << endl;
        MerAST_print_ast(ast->array_store_value, indent + 2);
    }

    if (!ast->args.empty()) {
        print_indent(indent + 1);
        cout << "args:" << endl;
        for (auto &arg : ast->args) {
            MerAST_print_ast(arg, indent + 2);
        }
    }

    if (!ast->body.empty()) {
        print_indent(indent + 1);
        cout << "body:" << endl;
        for (auto &stmt : ast->body) {
            MerAST_print_ast(stmt, indent + 2);
        }
    }

    if (!ast->children.empty()) {
        print_indent(indent + 1);
        cout << "children:" << endl;
        for (auto &child : ast->children) {
            MerAST_print_ast(child, indent + 2);
        }
    }

    if (!ast->then_body.empty()) {
        print_indent(indent + 1);
        cout << "then:" << endl;
        for (auto &stmt : ast->then_body) {
            MerAST_print_ast(stmt, indent + 2);
        }
    }

    if (!ast->else_body.empty()) {
        print_indent(indent + 1);
        cout << "else:" << endl;
        for (auto &stmt : ast->else_body) {
            MerAST_print_ast(stmt, indent + 2);
        }
    }

    if (!ast->list.empty()) {
        print_indent(indent + 1);
        cout << "list:" << endl;
        for (auto &item : ast->list) {
            MerAST_print_ast(item, indent + 2);
        }
    }

    if (ast->comp) {
        print_indent(indent + 1);
        cout << "condition:" << endl;
        MerAST_print_ast(ast->comp, indent + 2);
    }

    if (!ast->do_body.empty()) {
        print_indent(indent + 1);
        cout << "do_body:" << endl;
        for (auto &stmt : ast->do_body) {
            MerAST_print_ast(stmt, indent + 2);
        }
    }

    if (!ast->in_body.empty()) {
        print_indent(indent + 1);
        cout << "for_in_body:" << endl;
        for (auto &stmt : ast->in_body) {
            MerAST_print_ast(stmt, indent + 2);
        }
    }

    if (!ast->in_else_body.empty()) {
        print_indent(indent + 1);
        cout << "for_else_body:" << endl;
        for (auto &stmt : ast->in_else_body) {
            MerAST_print_ast(stmt, indent + 2);
        }
    }
}

void MerDebug_print_message(const char *msg, const char *file, int line) {
    cerr << "MercuryLang system message: " << msg << endl;
    cerr << "At file '" << file << "', line " << line << endl;
}

void MerDebug_print_error(const char *type, const char *msg, const char *file, int line) {
    cerr << type << ": " << msg << endl;
    cerr << "At file '" << file << "', line " << line << endl;
    BREAK_POINT
}

void MerDebug_system_error(const char *type, const char *msg, const char* file)
{
    cerr << type << ": " << msg << endl;
    cerr << "At file '" << file << "'" << endl;
    BREAK_POINT
}

void MerDebug_system_warning(const char* msg, const char* file) {
    cerr << "Warning: " << msg << endl;
    cerr << "At file '" << file << "'" << endl;
    BREAK_POINT
}

void MerDebug_print_warning(const char *msg, const char *file, int line, const char *c_line) {
    cerr << "Warning: " << msg << endl;
    cerr << "At file '" << file << "', line " << line << endl;
    cerr << c_line << endl;
    BREAK_POINT
}

inline bool is_identifier(const std::string& c) {
    return (c == LET_S)
    || (c == IF_S)
    || (c == LOCAL_S)
    || (c == DO_S)
    || (c == END_S)
    || (c == ELIF_S)
    || (c == BREAK_S)
    || (c == IMPORT_S)
    || (c == CONTINUE_S)
    || (c == AUTO_S)
    || (c == FLOAT_S)
    || (c == DOUBLE_S)
    || (c == CHAR_S)
    || (c == LIST_S)
    || (c == ASSERT_S)
    || (c == NOT_S)
    || (c == AND_S)
    || (c == OR_S)
    || (c == SHORT_S)
    || (c == IS_S)
    || (c == LONG_S)
    || (c == VOID_S)
    || (c == BOOL_S)
    || (c == STR_S)
    || (c == TRUE_S)
    || (c == FALSE_S)
    || (c == LOOP_S)
    || (c == STRING_S)
    || (c == DEFINED_S)
    || (c == INCLUDE_S)
    || (c == ELSE_S)
    || (c == FOR_S)
    || (c == WHILE_S)
    || (c == RETURN_S)
    || (c == FUNCTION_S)
    || (c == IN_S)
    || (c == CLASS_S)
    || (c == STRUCT_S)
    || (c == INTERFACE_S)
    || (c == NEW_S)
    || (c == DELETE_S)
    || (c == CAST_S)
    || (c == CONST_S)
    || (c == THEN_S)
    || (c == "let")
    || (c == "if")
    || (c == "do")
    || (c == "end")
    || (c == "function")
    || (c == "break")
    || (c == "continue")
    || (c == "elif")
    || (c == "auto")
    || (c == "is")
    || (c == "float")
    || (c == "double")
    || (c == "char")
    || (c == "list")
    || (c == "short")
    || (c == "true")
    || (c == "false")
    || (c == "long")
    || (c == "void")    
    || (c == "bool")
    || (c == "str")
    || (c == "string")
    || (c == "loop")
    || (c == "define")
    || (c == "not")
    || (c == "include")
    || (c == "else")
    || (c == "for")
    || (c == "import")
    || (c == "while")
    || (c == "local")
    || (c == "assert")
    || (c == "in")
    || (c == "return")
    || (c == "func")
    || (c == "class")
    || (c == "struct")
    || (c == "interface")
    || (c == "new")
    || (c == "delete")
    || (c == "cast")
    || (c == "const")
    || (c == "and")
    || (c == "or")
    || (c == "not")
    || (c == "then");
}

inline string GET_SYNTAX(const std::string& c) {
    if (c == LET_S || c == LOCAL_S) return LET;
    else if (c == IF_S) return IF;
    else if (c == ELSE_S) return ELSE;
    else if (c == FOR_S) return FOR;
    else if (c == WHILE_S) return WHILE;
    else if (c == IN_S) return IN_T;
    else if (c == NOT_S) return NOT;
    else if (c == LOOP_S) return LOOP;
    else if (c == TRUE_S) return TRUE_T;
    else if (c == FALSE_S) return FALSE_T;
    else if (c == ELIF_S) return ELIF;
    else if (c == IMPORT_S) return IMPORT;
    else if (c == RETURN_S) return RETURN;
    else if (c == FUNCTION_S) return FUNCTION;
    else if (c == IS_S) return IS;
    else if (c == DO_S) return DO_T;
    else if (c == END_S) return END_T;
    else if (c == INCLUDE_S) return INCLUDE;
    else if (c == AND_S) return AND;
    else if (c == DEFINED_S) return DEFINE_STA;
    else if (c == OR_S) return OR;
    else if (c == BREAK_S) return BREAK;
    else if (c == CONTINUE_S) return CONTINUE;
    else if (c == CLASS_S) return CLASS;
    else if (c == INTERFACE_S) return INTERFACE_;
    else if (c == STRUCT_S) return STRUCT;
    else if (c == NEW_S) return NEW;
    else if (c == LIST_S) return LIST;
    else if (c == DELETE_S) return DELETE_;
    else if (c == CAST_S) return CAST;
    else if (c == FLOAT_S) return FLOAT_;
    else if (c == DOUBLE_S) return DOUBLE_;
    else if (c == CHAR_S) return CHAR_;
    else if (c == SHORT_S) return SHORT_;
    else if (c == LONG_S) return LONG_;
    else if (c == AUTO_S) return AUTO_;
    else if (c == VOID_S) return VOID_T;
    else if (c == THEN_S) return THEN;
    else if (c == BOOL_S) return BOOL_;
    else if (c == STRING_S) return STR;
    else if (c == "let" || c == "local") return LET;
    else if (c == "if") return IF;
    else if (c == "else") return ELSE;
    else if (c == "for") return FOR;
    else if (c == "while") return WHILE;
    else if (c == "in") return IN_T;
    else if (c == "not") return NOT;
    else if (c == "return") return RETURN;
    else if (c == "import") return IMPORT;
    else if (c == "assert") return ASSERT;
    else if (c == "func" || c == "function") return FUNCTION;
    else if (c == "include") return INCLUDE;
    else if (c == "elif") return ELIF;
    else if (c == "and") return AND;
    else if (c == "true") return TRUE_T;
    else if (c == "false") return FALSE_T;
    else if (c == "or") return OR;
    else if (c == "do") return DO_T;
    else if (c == "is") return IS;
    else if (c == "end") return END_T;
    else if (c == "break") return BREAK;
    else if (c == "loop") return LOOP;
    else if (c == "continue") return CONTINUE;
    else if (c == "class") return CLASS;
    else if (c == "interface") return INTERFACE_;
    else if (c == "define") return DEFINE_STA;
    else if (c == "struct") return STRUCT;
    else if (c == "new") return NEW;
    else if (c == "list") return LIST;
    else if (c == "delete") return DELETE_;
    else if (c == "cast") return CAST;
    else if (c == "void") return VOID_T;
    else if (c == "double") return DOUBLE_;
    else if (c == "char") return CHAR_;
    else if (c == "short") return SHORT_;
    else if (c == "long") return LONG_;
    else if (c == "auto") return AUTO_;
    else if (c == "then") return THEN;
    else if (c == "else") return ELSE;
    else if (c == "bool") return BOOL_;
    else if (c == "string") return STR;
    return NULL_T;
}

inline string GET_1_CHAR(char c) {
    switch (c) {
        case '=': return ASSIGN;
        case '<': return LESS;
        case '>': return GREATER;
        case '^': return POW;
        case '+': return PLUS;
        case '.': return DOT;
        case '-': return MINUS;
        case '/': return DIV;
        case ';': return SEMICOLON;
        case ':': return COLON;
        case '!': return NOT;
        case ',': return COMMA;
        case '%': return MOD;
        case '*': return TIME;
        case '(': return LEFT_PAREN;
        case ')': return RIGHT_PAREN;
        case '{': return LEFT_BRACE;
        case '}': return RIGHT_BRACE;
        case '[': return LEFT_BRACKET;
        case ']': return RIGHT_BRACKET;
    }
    return NULL_T;
}

inline string GET_2_CHAR(char c1, char c2) {
    switch (c1) {
        case '=':
            if (c2 == '=') return EQUAL;
            break;
        case '<':
            if (c2 == '=') return LESS_EQUAL;
            break;
        case '>':
            if (c2 == '=') return GREATER_EQUAL;
            break;
        case '+':
            if (c2 == '+') return PLUS_PLUS;
            if (c2 == '=') return PLUS_EQUAL;
            break;
        case '-':
            if (c2 == '-') return MINUS_MINUS;
            if (c2 == '=') return MINUS_EQUAL;
            break;
        case '&':
            if (c2 == '&') return AND;
            break;
        case '|':
            if (c2 == '|') return OR;
            break;
        case '*':
            if (c2 == '*') return POW;
            if (c2 == '=') return TIMES_EQUAL;
            break;
        case '!':
            if (c2 == '=') return NOT_EQUAL;
            break;
        case '/':
            if (c2 == '/') return COMMENT;
            if (c2 == '=') return DIV_EQUAL;
            break;
        case '%':
            if (c2 == '=') return MOD_EQUAL;
            break;
    }

    return NULL_T;
}

inline mToken_T *_MerToken_new(void) {
    mToken_T *token = new mToken_T;
    token->tok = "";
    token->type = "";
    token->value = 0.0;
    token->name = "";
    token->index = 0;
    token->symbol = "";
    token->string_iden = "";
    return token;
}

inline int _MerToken_free(mToken_T *token) {
    delete token;    
    return 0;
}

inline mToken_T *_MerInit_token(string tok, string type, float value, string name, string symbol, string string_iden) {
    mToken_T *token = _MerToken_new();
    token->tok = tok;
    token->type = type;
    token->value = value;
    token->name = name;
    token->symbol = symbol;
    token->string_iden = string_iden;
    return token;
}

inline bool MerBuffer_create_folder(const string &folderName)
{
    mkdir(folderName.c_str());
    return true;
}

inline char* MerBuffer_read_file_source(const std::string &file_name) {
    if (!std::filesystem::exists(file_name)) {
        throw std::runtime_error("File does not exist: " + file_name);
    }

    std::ifstream file(file_name, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + file_name);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string str = buffer.str();
    char* result = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), result);
    result[str.size()] = '\0';
    return result;
}

inline char *MerBuffer_read_file(const string &file_name)
{
    char *buffer = NULL;
    FILE *f = fopen(file_name.c_str(), "rb");
    if (f == NULL) return NULL;
    fseek(f, 0, SEEK_END);
    size_t length = ftell(f);
    rewind(f);
    buffer = new char[length + 1];
    fread(buffer, 1, length, f);
    buffer[length] = '\0';
    fclose(f);
    return buffer;
}

inline void MerBuffer_make_and_write_file(const string &filename, const char *content)
{
    ofstream outFile(filename);

    if (!outFile)
    {
        cerr << "Error: Could not create file " << filename << endl;
        return;
    }

    outFile << content << endl;

    outFile.close();
}

inline void MerBuffer_make_and_write_file_bytecode(const string &filename, const vector<uint8_t> &data)
{
    ofstream file(filename, ios::binary);
    file.write(reinterpret_cast<const char *>(data.data()), data.size());
    file.close();
}

inline vector<uint8_t> MerBuffer_read_file_bytecode(const string &file_name)
{
    vector<uint8_t> data;
    ifstream file(file_name, ios::binary);
    if (!file)
    {
        cerr << "Error: Could not open file " << file_name << endl;
        return data;
    }
    file.seekg(0, ios::end);
    size_t size = file.tellg();
    file.seekg(0, ios::beg);
    data.resize(size);
    file.read(reinterpret_cast<char *>(data.data()), size);
    file.close();
    return data;
}

inline vector<string> list_files_in_folder(const string& folder_path) {
    vector<string> file_names;

    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.is_regular_file()) {
            file_names.push_back(entry.path().filename().string());
        }
    }

    return file_names;
}

inline vector<string> list_folder(const string& folder_path) {
    vector<string> folder_names;

    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.is_directory()) {
            folder_names.push_back(entry.path().filename().string());
        }
    }

    return folder_names;
}


inline mLexer_T *_MerLexer_init(const char *buf)
{
    mLexer_T *lexer = _MerLexer_new();
    lexer->buf = buf;
    lexer->inp = buf;
    lexer->buf_size = strlen(buf);
    lexer->iden = NULL;
    lexer->cstart = buf[0];
    lexer->cend = buf[lexer->buf_size - 1];
    lexer->str = NULL;
    lexer->com = NULL;
    lexer->sytx = NULL;
    
    lexer->file = "stdin";

    lexer->cur = '\0';
    lexer->ncur = '\0';
    lexer->col = 0;
    lexer->row = 1;
    lexer->line = 0;
    lexer->blk = 0;
    lexer->size = 0;
    lexer->id = 0;
    lexer->level = 0;
#ifdef DEBUG
    lexer->c_id = 0;
    lexer->c_row = 0;
    lexer->c_line = NULL;
    lexer->c_cur = '\0';
    lexer->c_col = 0;
#endif
    return lexer;
}

inline mLexer_T* _MerLexer_new(void) {
    mLexer_T* lexer = (mLexer_T*)calloc(1, sizeof(mLexer_T));
    if (!lexer) return NULL;

    lexer->col  = 1;
    lexer->row  = 1;
    lexer->line = 1;

    return lexer;
}

int _MerLexer_free(mLexer_T *lexer)
{
    if (!lexer) return 0;

    if (lexer->str)   free(lexer->str);
    if (lexer->com)   free(lexer->com);
    if (lexer->sytx)  free(lexer->sytx);
    if (lexer->num)   free(lexer->num);
    if (lexer->mmode) free(lexer->mmode);

#ifdef DEBUG
    if (lexer->c_line) free(lexer->c_line);
#endif

    free(lexer);
    return 0;
}

inline mLexer_T *_MerLexer_get_next_char(mLexer_T *lexer)
{
    if (lexer->id >= lexer->buf_size)
    {
        lexer->cur = '\0';
        return lexer;
    }
    lexer->cur = lexer->buf[lexer->id++];
    if (lexer->cur == '\n')
    {
        lexer->row++;
        lexer->col = 0;
    }
    else
    {
        lexer->col++;
    }
    return lexer;
}

inline mLexer_T *_MerLexer_peek_char_c(mLexer_T *lexer)
{
    if (lexer->id >= lexer->buf_size)
    {
        lexer->cur = '\0';
        return lexer;
    }
    lexer->ncur = lexer->buf[lexer->id];
    return lexer;
}

inline mToken_T *_MerLexer_get_next_tok(mLexer_T *lexer)
{
    for (;;)
    {
        _MerLexer_skip_whitespace(lexer);
        _MerLexer_skip_comment(lexer);

        char c = _MerLexer_get_next_char(lexer)->cur;

        if (WEIRD_CHAR(c)) {
            MerDebug_print_error(SYNTAX_ERROR, "Invalid character", lexer->file, lexer->row + 1);
        }
        
        if (is_potential_identifier_char(c))
        {
            mToken_T *token = _MerLexer_tokenize_syntax(lexer);
            token->index++;
            return token;
        }

        if (c == '$')
        {
            mToken_T *token = _MerLexer_tokenize_define(lexer);
            token->index++;
            return token;
        }

        if (c == '"')
        {
            mToken_T *token = _MerLexer_tokenize_string(lexer);
            token->index++;
            return token;
        }

        if (is_digit(c))
        {
            mToken_T *token = _MerLexer_tokenize_number(lexer);
            token->index++;
            return token;
        }

        if (is_keywords(c))
        {
            mToken_T *token = _MerLexer_tokenize_keyword(lexer);
            token->index++;
            return token;
        }

        if (is_keywords(c) && lexer->col == 1)
        {
            MerDebug_print_error(SYNTAX_ERROR, "Invalid character at start", lexer->file, lexer->row);
        }

        if (c == '(')
        {
            mToken_T *token = _MerInit_token(LEFT_PAREN, NULL_T, 0.0, "(", "(", "(");
            token->index++;
            return token;
        }

        else if (c == ')')
        {
            mToken_T *token = _MerInit_token(RIGHT_PAREN, NULL_T, 0.0, ")", ")", ")");
            token->index++;
            return token;
        }

        else if (c == '\0')
        {
            break;
        }
    }

    return _MerInit_token(EOF_T, NULL_T, 0.0, (const char *)"", (const char *)"\n", (const char *)"");
}

inline mToken_T *_MerLexer_look_ahead(mLexer_T *lexer) {
    mLexer_T temp = *lexer;
    return _MerLexer_get_next_tok(&temp);
}

inline mToken_T *_MerLexer_tokenize_define(mLexer_T *lexer)
{
    lexer->cur = lexer->buf[lexer->id++];
    string extract_name = "";
    while (is_potential_identifier_char(lexer->cur))
    {
        extract_name += lexer->cur;
        LEX_PRE_ADVANCE(lexer);
    }

    LEX_DECR(lexer);

    const char *extract_name_c = strdup(extract_name.c_str());
    return _MerInit_token(DEFINE_VAL, "AUTO_T", 0.0, extract_name_c, extract_name_c, extract_name_c);
}

inline mToken_T *_MerLexer_tokenize_number(mLexer_T *lexer)
{
    string num = "";
    int dot_count = 0;
    num += lexer->cur;
    
    while (is_potential_literal_char(lexer->cur))
    {
        
        if (lexer->cur == '.')
        {
            dot_count++;
            if (dot_count > 1)
            {
                MerDebug_print_error(SYNTAX_ERROR, "Invalid character", lexer->file, lexer->row);
            }
        }
        LEX_PRE_ADVANCE(lexer);

        if (is_potential_literal_char(lexer->cur))
        {
            num += lexer->cur;
        }
        else
        {
            break;
        }
    }

    LEX_DECR(lexer);
    float num_value = atof(num.c_str());
    return _MerInit_token(FLOAT_, FLOAT_T, num_value, (const char*)"", (const char*)"", (const char*)"");
}

inline mToken_T *_MerLexer_tokenize_syntax(mLexer_T *lexer)
{
    string keyword = "";

    LEX_DECR_ADVANCE(lexer);
    while (is_potential_identifier_char(lexer->cur) || is_digit(lexer->cur))
    {
        if (IS_SPACE(lexer))
        {
            break;
        }

        if (is_potential_identifier_char(lexer->cur) || is_digit(lexer->cur))
        {
            keyword += lexer->cur;
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Invalid character", lexer->file, lexer->row);
        }
        
        LEX_ADVANCE(lexer);
        
    }

    const char *key = strdup(keyword.c_str());
    if (is_identifier(key))
    {
        return _MerInit_token(GET_SYNTAX(key), NULL_T, 0.0, key, key, key);
    }
    else
    {
        return _MerInit_token(VARIABLE, NULL_T, 0.0, key, key, key);
    }
}

inline mToken_T *_MerLexer_tokenize_keyword(mLexer_T *lexer)
{
    string keyword = "";
    char c = lexer->cur;
    int idx = 0;
    if (is_keywords(c))
    {
        keyword += c;
        char c2 = LEX_STAY(lexer);
        if (is_keywords(c2) && GET_2_CHAR(c, c2) != NULL_T)
        {
            keyword += c2;
            const char *temp = strdup(keyword.c_str());
            LEX_INCR(lexer);
            return _MerInit_token(GET_2_CHAR(c, c2), NULL_T, 0.0, temp, temp, temp);
        }
    }

    const char *temp = strdup(keyword.c_str());
    return _MerInit_token(GET_1_CHAR(c), NULL_T, 0.0, temp, temp, temp);
}

inline mToken_T *_MerLexer_tokenize_string(mLexer_T *lexer)
{
    string str;
    lexer->cur = lexer->buf[lexer->id];
    int idx = 0;
    char string_start = lexer->buf[lexer->id - 1];

    if (lexer->cur == '\n') {
        MerDebug_print_error(SYNTAX_ERROR, "Expected empty string", lexer->file, lexer->row);
    }

    while (lexer->cur != '"') {
        str += lexer->cur;
        ++idx;

        if (lexer->cur == '\n') {
            MerDebug_print_error(SYNTAX_ERROR, "Missing the end of string", lexer->file, lexer->row);
        }

        if (idx > 4300) {
            MerDebug_print_error(SYSTEM_WARNING, "The number of keyword in string is too large, this can cause a crash", lexer->file, lexer->row);
        }

        if (lexer->cur == '\\') {
            str.pop_back();
            LEX_ADVANCE(lexer);

            switch(lexer->cur) {
                case '\\':
                    str += '\\';
                    break;
                case '"':
                    str += '"';
                    break;
                case 'n':
                    str += '\n';
                    break;
                case 't':
                    str += '\t';
                    break;
                case 'r':
                    str += '\r';
                    break;
                case 'f':
                    str += '\f';
                    break;
                case 'b':
                    str += '\b';
                    break;
                case 'x':
                    {
                        string hex = "";
                        LEX_ADVANCE(lexer);

                        if (IS_HEX_CHAR(lexer->cur)) {
                            hex += lexer->cur;
                            LEX_ADVANCE(lexer);
                            if (IS_HEX_CHAR(lexer->cur)) {
                                hex += lexer->cur;
                            } else {
                                MerDebug_print_error(SYNTAX_ERROR, "Invalid hex character", lexer->file, lexer->row);
                            }
                        } else {
                            MerDebug_print_error(SYNTAX_ERROR, "Invalid hex character", lexer->file, lexer->row);
                        }

                        str += (char)strtol(hex.c_str(), NULL, 16);
                        break;
                    }
                default:
                    str += lexer->cur;
            }
        }

        LEX_ADVANCE(lexer);
    }

    LEX_ADVANCE(lexer);
    const char *str_c = strdup(str.c_str());
    return _MerInit_token(STRING, STRING_T, 0.0, str_c, str_c, str_c);
}

inline void _MerLexer_jump_to(mLexer_T *lexer, int n)
{
    while (lexer->id < n)
    {
        LEX_ADVANCE(lexer);
        if (lexer->cur == '\n')
        {
            LEX_NEWLINE(lexer);
        }
    }

    lexer->cur = lexer->buf[lexer->id];
}

inline void _MerLexer_skip_whitespace(mLexer_T *lexer)
{
    lexer->cur = lexer->buf[lexer->id];
    while (IS_SPACE(lexer) || lexer->cur == ';')
    {
        LEX_ADVANCE(lexer);
    }
}

inline void _MerLexer_skip_comment(mLexer_T *lexer)
{
    char c = lexer->buf[lexer->id];
    if (c == '#' || c == '@') {
        while (c != '\n')
        {
            LEX_ADVANCE(lexer);
            c = lexer->buf[lexer->id];
        }
    } else if (c == '/') {
        c = lexer->buf[lexer->id + 1];
        if (c == '*')  {
            while (c != '*' || lexer->buf[lexer->id + 1] != '/')
            {
                LEX_ADVANCE(lexer);
                c = lexer->buf[lexer->id];
            }
            LEX_ADVANCE(lexer);
        }
    }
}


inline mParser_T *_MerParser_new(void)
{
    mParser_T *parser = new mParser_T;

    parser->lexer = _MerLexer_new();
    parser->token = _MerToken_new();
    parser->next = _MerToken_new();

    return parser;
}

inline mParser_T *_MerParser_init(mLexer_T *lexer)
{
    mParser_T *parser = _MerParser_new();
    parser->lexer = lexer;

    return parser;
}

inline int _MerParser_free(mParser_T *parser)
{
    _MerLexer_free(parser->lexer);
    _MerToken_free(parser->token);
    free(parser);
    return 0;
}

inline mAST_T *MerParser_parse_binary_expression(mAST_T *left, string op, mAST_T *right)
{
    mAST_T *node = MerAST_make_parent(BinaryExpression);
    node->left = left;
    node->op = op;
    node->right = right;
    return node;
}

inline mAST_T *MerParser_parse_program(mParser_T *parser)
{
    mAST_T *node = MerAST_make_parent(Program);
    string file = parser->lexer->file;
    node->file = file;
    node->children.push_back(MerParser_parse_expression_statement(parser));
    return node;
}

inline mAST_T *MerParser_parse_expression_statement(mParser_T *parser)
{
    mAST_T *node = MerAST_make_parent(ExpressionStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    while (parser->token->tok != EOF_T)
        node->children.push_back(MerParser_parse(parser));

    return node;
}

inline mAST_T *MerParser_parse(mParser_T *parser)
{
    if (parser->token->tok == LET)
        return MerParser_parse_let_statement(parser);
    if (parser->token->tok == FUNCTION)
        return MerParser_parse_function_statement(parser);
    if (parser->token->tok == RETURN)
        return MerParser_parse_return_statement(parser);
    if (parser->token->tok == IF)
        return MerParser_parse_if_statement(parser);
    if (parser->token->tok == WHILE)
        return MerParser_parse_while_statement(parser);
    if (parser->token->tok == VARIABLE) {
        parser->next = _MerLexer_look_ahead(parser->lexer);
        if (parser->next->tok == ASSIGN 
            || parser->next->tok == PLUS_EQUAL 
            || parser->next->tok == MINUS_EQUAL 
            || parser->next->tok == TIMES_EQUAL 
            || parser->next->tok == DIV_EQUAL 
            || parser->next->tok == MOD_EQUAL) {
            return MerParser_parse_assignment_statement(parser);
        } else {
            return MerParser_parse_logical_expression(parser);
        }
    }

    if (parser->token->tok == LOOP) {
        return MerParser_parse_loop_statement(parser);
    }
    if (parser->token->tok == LIST)
        return MerParser_parse_list_statement(parser);
    if (parser->token->tok == STR)
        return MerParser_parse_variable_statement(parser);
    if (parser->token->tok == FOR)
        return MerParser_parse_for_statement(parser);
    if (parser->token->tok == CONTINUE) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *node = MerAST_make_parent(ContinueStatement);
        node->true_line = TRUE_LINE(parser);
        return node;
    } if (parser->token->tok == BREAK) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *node = MerAST_make_parent(BreakStatement);
        node->true_line = TRUE_LINE(parser);
        return node;
    } if (parser->token->tok == IMPORT) {
        return MerParser_parse_import_statement(parser);
    } if (parser->token->tok == DEFINE_STA) {
        return MerParser_parse_define_statement(parser);
    } if (parser->token->tok == INCLUDE) {
        return MerParser_parse_include_statement(parser);
    } if (parser->token->tok == CLASS) {
        return MerParser_parse_class_statement(parser);
    }

    return MerParser_parse_logical_expression(parser);
}

inline mAST_T *MerParser_parse_class_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(ClassStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);

    if (parser->token->tok == VARIABLE) {
        node->class_name = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected class name", parser->lexer->file, TRUE_LINE(parser));
    }

    if (parser->token->tok == DO_T) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);

        while (parser->token->tok != END_T) {
            mAST_T *member = MerParser_parse(parser);
            node->members.push_back(member);
        }

        parser->token = _MerLexer_get_next_tok(parser->lexer);
        node->true_line = TRUE_LINE(parser);
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected 'do' keyword in class statement", parser->lexer->file, TRUE_LINE(parser));
    }

    return node;
}

inline mAST_T *MerParser_parse_include_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(IncludeStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    node->true_line = TRUE_LINE(parser);
    
    if (parser->token->tok == STRING) {
        node->string_iden = parser->token->string_iden;
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Invalide syntax in import, import \"<file>\" ", parser->lexer->file, TRUE_LINE(parser));
    }

    return node;
}

inline mAST_T *MerParser_parse_define_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(DefineStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);

    if (parser->token->tok == VARIABLE) {
        node->string_iden = parser->token->string_iden;
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Missing name in define, 'define <name> {<code>}' ", parser->lexer->file, TRUE_LINE(parser));
    }

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    node->define_val = MerParser_parse(parser);
    if (!node) {
        MerDebug_print_error(SYNTAX_ERROR, "Invalide syntax in define", parser->lexer->file, TRUE_LINE(parser));
    }

    if (!is_ast_expression(node->define_val->type)) {
        MerDebug_print_error(SYNTAX_ERROR, "Invalide syntax in define", parser->lexer->file, TRUE_LINE(parser));
    }

    
    return node;
}

inline mAST_T *MerParser_parse_import_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(ImportStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    node->true_line = TRUE_LINE(parser);
    
    if (parser->token->tok == STRING) {
        node->string_iden = parser->token->string_iden;
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Invalide syntax in import, import \"<file>\" ", parser->lexer->file, TRUE_LINE(parser));
    }

    return node;
}

inline mAST_T *MerParser_parse_loop_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(LoopStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);

    while (parser->token->tok != END_T) {
        node->do_body.push_back(MerParser_parse(parser));
    }
    
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    return node;
}

inline mAST_T *MerParser_parse_array_expression(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(ArrayExpression);

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    while (parser->token->tok != RIGHT_BRACKET) {

        if (parser->token->tok == EOF_T) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression, reached <EOF> in the end of list", parser->lexer->file, TRUE_LINE(parser));
        }

        mAST_T *item = MerParser_parse(parser);

        if (!is_ast_expression(item->type)) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression in list", parser->lexer->file, TRUE_LINE(parser));
        }

        if (!item) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression in list", parser->lexer->file, TRUE_LINE(parser));
        }

        node->list.push_back(item);

        if (parser->token->tok == COMMA)
        {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            continue;
        }
    }

    node->is_list = true;
    node->is_alone_val = true;

    parser->next = _MerLexer_look_ahead(parser->lexer);
    mAST_T *new_node = MerAST_make_parent(ExtractExpression);
    new_node->extract_value = node;
    new_node->is_value_extract = true;

    left_bracket:
    if (parser->next->tok == LEFT_BRACKET) {
        parser->token = _MerLexer_get_next_tok(parser->lexer); // eat '['

        parser->token = _MerLexer_get_next_tok(parser->lexer);

        mAST_T *item = MerParser_parse(parser);

        if (!item || !is_ast_expression(item->type)) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression in list", parser->lexer->file, TRUE_LINE(parser));
        }

        if (item->type == ArrayExpression) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression in list", parser->lexer->file, TRUE_LINE(parser));
        }

        new_node->mul_extract.push_back(item);

        if (parser->token->tok == RIGHT_BRACKET) {
            parser->next = _MerLexer_look_ahead(parser->lexer);

            if (parser->next->tok == LEFT_BRACKET) {
                new_node->is_mul_extract = true;
                goto left_bracket;
            } else {
                return new_node;
            }
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Missing ']'", parser->lexer->file, TRUE_LINE(parser));
        }
    }

    return node;
}

inline mAST_T *MerParser_parse_for_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(ForInStatement);

    parser->token = _MerLexer_get_next_tok(parser->lexer);

    if (parser->token->tok == VARIABLE) {
        node->in_iden = parser->token->string_iden;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable", parser->lexer->file, TRUE_LINE(parser));
    }

    if (parser->token->tok == IN_T) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        node->in_value = MerParser_parse(parser);

        if (node->in_value->type == Literal || node->in_value->type == BinaryExpression || node->in_value->type == ComparisonExpression) {
            MerDebug_print_error(SYNTAX_ERROR, "'int' object is not iterable", parser->lexer->file, TRUE_LINE(parser));
        }

        if (!node->in_value) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
        }

        if (!is_ast_expression(node->in_value->type)) {
            MerDebug_print_error(SYNTAX_ERROR, "'null' object is not iterable", parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected 'IN' keyword in for in statement", parser->lexer->file, TRUE_LINE(parser));
    }

    if (parser->token->tok == DO_T) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        while (parser->token->tok != END_T) {
            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing 'END' keyword in the for loop", parser->lexer->file, TRUE_LINE(parser));
                return NULL;
            }

            mAST_T *body = MerParser_parse(parser);
            if (body) {
                node->in_body.push_back(body);
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Unexpected statement", parser->lexer->file, TRUE_LINE(parser));
            }
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected 'DO' keyword in for in statement", parser->lexer->file, TRUE_LINE(parser));
    }

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    node->true_line = TRUE_LINE(parser);
    return node;
}

mAST_T *parser_string_identifier_primary(mToken_T *token) {
    mAST_T *node = MerAST_make_parent(StringIdentifier);

    node->str_v = token->string_iden;
    node->is_string = true;
    return node;
}

inline mAST_T *MerParser_parse_string_expression(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(StringIdentifier);

    node->str_v = parser->token->name;
    node->is_string = true;
    node->true_line = TRUE_LINE(parser);
    return node;
}

inline mAST_T *MerParser_parse_return_statement(mParser_T *parser)
{
    mAST_T *node = MerAST_make_parent(ReturnStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);

    node->return_v = MerParser_parse(parser);
    if (!is_ast_expression(node->return_v->type)) {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
    }

    node->true_line = TRUE_LINE(parser);
    return node;
}

inline mAST_T *MerParser_parse_string_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(StringVariableStatement);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == VARIABLE) {
        node->str_var_name = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == ASSIGN) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            node->str_var_value = MerParser_parse_string_expression(parser);
            return node;
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected assignment", parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable name", parser->lexer->file, TRUE_LINE(parser));
    }

    return node;
}

inline mAST_T *MerParser_parse_if_statement(mParser_T *parser)
{
    mAST_T *node = MerAST_make_parent(IfStatement);

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    mAST_T *comp = MerParser_parse(parser);
    if (!is_ast_expression(comp->type)) {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
    }
    
    if (!comp)
    {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'IF'", parser->lexer->file, TRUE_LINE(parser));
        return NULL;
    }
    node->comp = comp;

    if (parser->token->tok == THEN)
    {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        while (parser->token->tok != END_T)
        {
            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing 'END'", parser->lexer->file, TRUE_LINE(parser));
            }

            mAST_T *body = MerParser_parse(parser);
            if (body)
            {
                node->then_body.push_back(body);
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Unexpected statement", parser->lexer->file, TRUE_LINE(parser));
            }
        }
    }    else
    {
        MerDebug_print_error(SYNTAX_ERROR, "Missing 'THEN'", parser->lexer->file, TRUE_LINE(parser));
        return NULL;
    }

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    elif:
    if (parser->token->tok == ELIF) {
        mAST_T *elif_node = MerAST_make_parent(IfStatement);
        node->has_elif = true;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        elif_node->comp = MerParser_parse(parser);

        if (!is_ast_expression(elif_node->comp->type) || !elif_node->comp) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
        }

        if (parser->token->tok == THEN) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            while (parser->token->tok != END_T)
            {
                if (parser->token->tok == EOF_T) {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing 'end'", parser->lexer->file, TRUE_LINE(parser));
                }

                mAST_T *body = MerParser_parse(parser);
                if (body)
                {
                    elif_node->then_body.push_back(body);
                } else {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected statement", parser->lexer->file, TRUE_LINE(parser));
                }
            }

            node->elif_body.push_back(elif_node);
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            goto elif;
        }    
        else
        {
            MerDebug_print_error(SYNTAX_ERROR, "Missing 'then'", parser->lexer->file, TRUE_LINE(parser));
        }
    }
    
    
    if (parser->token->tok == ELSE) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        while (parser->token->tok != END_T)
        {
            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing END", parser->lexer->file, TRUE_LINE(parser));
            }

            mAST_T *body = MerParser_parse(parser);
            if (body)
            {
                node->else_body.push_back(body);
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Expected statement", parser->lexer->file, TRUE_LINE(parser));
            }

        }

        node->has_else = true;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        return node;
    }

    node->true_line = TRUE_LINE(parser);
    return node;
}

inline mAST_T *MerParser_parse_let_statement(mParser_T *parser)
{
    mAST_T *node = MerAST_make_parent(LetStatement);
    node->true_line = TRUE_LINE(parser);
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    string var_name;
    if (parser->token->tok == VARIABLE)
    {
        node->var_name = parser->token->name;
        var_name = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == ASSIGN)
        {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'LET'", parser->lexer->file, TRUE_LINE(parser));
            }

            node->var_value = MerParser_parse(parser);

            if (!node->var_value) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'LET'", parser->lexer->file, TRUE_LINE(parser));
            }   

            if (!is_ast_expression(node->var_value->type)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'LET'", parser->lexer->file, TRUE_LINE(parser));
            }

            return node;
        } else if (parser->token->tok == LEFT_PAREN) {
            node = MerAST_make_parent(FunctionStatement);
            node->true_line = TRUE_LINE(parser);
            node->func_name = var_name;

            parser->token = _MerLexer_get_next_tok(parser->lexer);

            while (parser->token->tok != RIGHT_PAREN) {
                if (parser->token->tok == EOF_T) {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'LET'", parser->lexer->file, TRUE_LINE(parser));
                }
                if (parser->token->tok == COMMA) {
                    parser->token = _MerLexer_get_next_tok(parser->lexer);
                    continue;
                }

                if (parser->token->tok == VARIABLE) {
                    node->args_idens.push_back(parser->token->string_iden);
                    node->args_size++;
                    node->is_having_args = true;
                    para_temp.push_back(parser->token->string_iden);

                    parser->token = _MerLexer_get_next_tok(parser->lexer);
                } else {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected variable name in function arguments", parser->lexer->file, TRUE_LINE(parser));
                }
            }

            parser->token = _MerLexer_get_next_tok(parser->lexer);
            parser->next = _MerLexer_look_ahead(parser->lexer);

            if (parser->token->tok == ASSIGN) {
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                if (parser->token->tok == EOF_T) {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected <EOF> after lambda function", parser->lexer->file, TRUE_LINE(parser));
                }

                mAST_T *return_v = MerAST_make_parent(ReturnStatement);
                return_v->true_line = TRUE_LINE(parser);
                return_v->return_v = MerParser_parse(parser);
                if (!return_v->return_v || !is_ast_expression(return_v->return_v->type)) {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected expression in lambda function", parser->lexer->file, TRUE_LINE(parser));
                }

                node->body.push_back(return_v);
                para_temp.clear();
                return node;
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Missing '=' in lambda function", parser->lexer->file, TRUE_LINE(parser));
            }
        }
        
        else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected assignment, missing '='", parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable name, the token after 'LET' is not a variable", parser->lexer->file, TRUE_LINE(parser));
    }

    return NULL;
}

inline mAST_T *MerParser_parse_while_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(WhileStatement);
    node->true_line = TRUE_LINE(parser);

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    mAST_T *comp = MerParser_parse(parser);

    if (!is_ast_expression(comp->type)) {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'WHILE'", parser->lexer->file, TRUE_LINE(parser));
        return NULL;
    }

    if (!comp) {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'WHILE'", parser->lexer->file, TRUE_LINE(parser));
        return NULL;
    }
    node->while_cond = comp;

    if (parser->token->tok == DO_T) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        while (parser->token->tok != END_T)
        {
            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing 'END' keyword in the while loop", parser->lexer->file, TRUE_LINE(parser));
            }

            mAST_T *body = MerParser_parse(parser);
            if (body)
            {
                node->while_body.push_back(body);
            } else if (body->type == BreakStatement) {
                node->while_body.push_back(body);
                node->is_break = true;
            } else if (body->type == ContinueStatement) {
                node->while_body.push_back(body);
                node->is_continue = true;
            }
        }
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        return node;
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected 'DO', while loop body must start with keyword 'DO'", parser->lexer->file, TRUE_LINE(parser));
        return NULL;
    }
}

inline mAST_T *MerParser_parse_variable_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(StringVariableStatement);
    node->true_line = TRUE_LINE(parser);

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == VARIABLE) {
        node->str_var_name = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == ASSIGN) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            node->str_var_value = MerParser_parse_string_expression(parser);
            return node;
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected assignment", parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable name", parser->lexer->file, TRUE_LINE(parser));
    }

    return NULL;
}

inline mAST_T *MerParser_parse_list_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(ListStatement);
    node->true_line = TRUE_LINE(parser);

    parser->token = _MerLexer_get_next_tok(parser->lexer);

    if (parser->token->tok == VARIABLE) {
        node->list_name = parser->token->string_iden;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == ASSIGN) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            if (parser->token->tok == LEFT_BRACKET) {
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                node->is_list = true;
                node->list_type = "list";
                while (parser->token->tok != RIGHT_BRACKET)
                {
                    if (parser->token->tok == COMMA)
                    {
                        parser->token = _MerLexer_get_next_tok(parser->lexer);
                        continue;
                    }

                    if (parser->token->tok == EOF_T) {
                        MerDebug_print_error(SYNTAX_ERROR, "Expected expression, reached <EOF>", parser->lexer->file, TRUE_LINE(parser));
                    }

                    mAST_T *item = MerParser_parse(parser);

                    if (!is_ast_expression(item->type)) {
                        MerDebug_print_error(SYNTAX_ERROR, "Expected expression in list", parser->lexer->file, TRUE_LINE(parser));
                    }

                    if (item)
                    {
                        node->list.push_back(item);
                        node->list_size++;
                    } else {
                        MerDebug_print_error(SYNTAX_ERROR, "Expected expression in list", parser->lexer->file, TRUE_LINE(parser));
                    }
                }
                
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                return node;
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Expected '[' in list", parser->lexer->file, TRUE_LINE(parser));
            }
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected '=' in list", parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable name, in list", parser->lexer->file, TRUE_LINE(parser));
    }

    return NULL;
}

inline mAST_T *MerParser_parse_assignment_statement(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(AssignStatement);
    node->true_line = TRUE_LINE(parser);

    if (parser->token->tok == VARIABLE) {
        node->assign_iden = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);

        if (parser->token->tok == ASSIGN) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);

            node->assign_value = MerParser_parse(parser);

            if (!is_ast_expression(node->assign_value->type)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression in assignment", parser->lexer->file, TRUE_LINE(parser));
            }

            return node;
        } 

        else if (parser->token->tok == PLUS_EQUAL || parser->token->tok == MINUS_EQUAL || parser->token->tok == TIMES_EQUAL || parser->token->tok == DIV_EQUAL || parser->token->tok == MOD_EQUAL) {

            if (parser->token->tok == PLUS_EQUAL) {
                node->is_plus_assign = true;
            } else if (parser->token->tok == MINUS_EQUAL) {
                node->is_minus_assign = true;
            } else if (parser->token->tok == TIMES_EQUAL) {
                node->is_mul_assign = true;
            } else if (parser->token->tok == DIV_EQUAL) {
                node->is_div_assign = true;
            } else if (parser->token->tok == MOD_EQUAL) {
                node->is_mod_assign = true;
            }

            node->is_assign_operator = true;

            parser->token = _MerLexer_get_next_tok(parser->lexer);

            node->assign_value = MerParser_parse(parser);

            if (!is_ast_expression(node->assign_value->type)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression in assignment", parser->lexer->file, TRUE_LINE(parser));
            }

            return node;
        }
        
        else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected '=' in assignment", parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected variable name in assignment", parser->lexer->file, TRUE_LINE(parser));
    }

    return NULL;
}

inline mAST_T *MerParser_parse_function_statement(mParser_T *parser)
{
    mAST_T *node = MerAST_make_parent(FunctionStatement);
    node->true_line = TRUE_LINE(parser);

    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == VARIABLE)
    {
        if (parser->token->name == "")
        {
            MerDebug_print_error(SYNTAX_ERROR, "Expected function name", parser->lexer->file, TRUE_LINE(parser));
            return NULL;
        }
        node->func_name = parser->token->name;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        if (parser->token->tok == LEFT_PAREN)
        {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            while (parser->token->tok != RIGHT_PAREN)
            {
                if (parser->token->tok == VARIABLE)
                {
                    node->args_idens.push_back(parser->token->name);
                    para_temp.push_back(parser->token->name);
                    node->is_having_args = true;
                    node->args_size++;
                } else {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected argument in function definition", parser->lexer->file, TRUE_LINE(parser));
                }

                if (parser->token->tok == EOF_T) {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing 'end' of the function definition", parser->lexer->file, TRUE_LINE(parser));
                }    

                parser->token = _MerLexer_get_next_tok(parser->lexer);
                if (parser->token->tok == COMMA)
                {
                    parser->token = _MerLexer_get_next_tok(parser->lexer);
                }
            }
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            int idex_amount = 0;
            if (parser->token->tok == DO_T)
            {
                parser->token = _MerLexer_get_next_tok(parser->lexer);

                while (parser->token->tok != END_T)
                {
                    if (parser->token->tok == EOF_T) {
                        MerDebug_print_error(SYNTAX_ERROR, "Expected statement, missing 'END'", parser->lexer->file, TRUE_LINE(parser));
                    }
        
                    node->body.push_back(MerParser_parse(parser));
                }
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                para_temp.clear();
                return node;
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "missing 'DO' in function definition", parser->lexer->file, TRUE_LINE(parser));
            }
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Expected '(' in function definition", parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected function name", parser->lexer->file, TRUE_LINE(parser));
    }

    return NULL;
}

inline mAST_T *MerParser_parse_function_call_expression(mParser_T *parser)
{
    mAST_T *node = MerAST_make_parent(FunctionCallExpression);
    node->true_line = TRUE_LINE(parser);

    node->func_call = parser->token->name;
    
    parser->token = _MerLexer_get_next_tok(parser->lexer);
    if (parser->token->tok == LEFT_PAREN)
    {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        while (parser->token->tok != RIGHT_PAREN)
        {
            if (parser->token->tok == COMMA)
            {
                parser->token = _MerLexer_get_next_tok(parser->lexer);
                continue;
            }

            if (parser->token->tok == EOF_T) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression, reached <EOF>", parser->lexer->file, TRUE_LINE(parser));
            }

            if (parser->token->tok != RIGHT_PAREN) {
                node->is_having_args = true;
            }

            mAST_T *arg = MerParser_parse(parser);

            if (!is_ast_expression(arg->type)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression in function call, not an expression", parser->lexer->file, TRUE_LINE(parser));
            }

            if (arg)
            {
                node->args.push_back(arg);
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression in function call", parser->lexer->file, TRUE_LINE(parser));
            }
        }
    }
    else
    {
        MerDebug_print_error(SYNTAX_ERROR, "Expected '('", parser->lexer->file, TRUE_LINE(parser));
        return NULL;
    }

    mAST_T *new_node = MerAST_make_parent(ExtractExpression);
    new_node->extract_value = node;
    new_node->is_value_extract = true;

    if (parser->token->tok == RIGHT_PAREN) {
        parser->next = _MerLexer_look_ahead(parser->lexer);
        left_bracket:
        if (parser->next->tok == LEFT_BRACKET) {
            parser->token = _MerLexer_get_next_tok(parser->lexer); // eat '[' 
            
            parser->token = _MerLexer_get_next_tok(parser->lexer);
            mAST_T *value = MerParser_parse(parser);
            
            if (!value || !is_ast_expression(value->type)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected extract expression", parser->lexer->file, TRUE_LINE(parser));
            }
            
            new_node->mul_extract.push_back(value);
            
            if (parser->token->tok == RIGHT_BRACKET) {
                parser->next = _MerLexer_look_ahead(parser->lexer);
                if (parser->next->tok == LEFT_BRACKET) {
                    goto left_bracket;
                }

                return new_node;
            } else {
                MerDebug_print_error(SYNTAX_ERROR, "Expected ']' in extract expression", parser->lexer->file, TRUE_LINE(parser));
            }

        } else {
            return node;
        }
    } else {
        MerDebug_print_error(SYNTAX_ERROR, "Expected ')'", parser->lexer->file, TRUE_LINE(parser));
    }

    return node;
}

inline mAST_T *MerParser_parse_comparison_expression(mParser_T *parser)
{
    mAST_T *left = MerParser_parse_additive_expression(parser);

    while (parser->token->tok == EQUAL || parser->token->tok == NOT_EQUAL ||
           parser->token->tok == LESS || parser->token->tok == LESS_EQUAL ||
           parser->token->tok == GREATER || parser->token->tok == GREATER_EQUAL || parser->token->tok == IS)
    {
        string op = parser->token->tok;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *right = MerParser_parse_additive_expression(parser);

        if (!right)
        {
            MerDebug_print_error(SYNTAX_ERROR, "Expected comparison expression", parser->lexer->file, TRUE_LINE(parser));
        }
        left = MerParser_parse_compair(left, op, right);
    }

    left->true_line = TRUE_LINE(parser);
    return left;
}

inline mAST_T *MerParser_parse_multiplicative_expression(mParser_T *parser)
{
    mAST_T *left = MerParser_parse_attribute_expression(parser);
    parser->token = _MerLexer_get_next_tok(parser->lexer);

    while (parser->token->tok == TIME || parser->token->tok == DIV || parser->token->tok == MOD)
    {
        string op = parser->token->tok;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *right = MerParser_parse_attribute_expression(parser);
        if (!right) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
        }
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        left = MerParser_parse_binary_expression(left, op, right);
    }
    left->true_line = TRUE_LINE(parser);
    return left;
}

inline mAST_T *MerParser_parse_additive_expression(mParser_T *parser)
{
    mAST_T *left = MerParser_parse_multiplicative_expression(parser);
    while (parser->token->tok == PLUS || parser->token->tok == MINUS)
    {
        string op = parser->token->tok;
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *right = MerParser_parse_multiplicative_expression(parser);
        if (!right) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
        }
        left = MerParser_parse_binary_expression(left, op, right);
        left->true_line = TRUE_LINE(parser);
    }

    left->true_line = TRUE_LINE(parser);
    return left;
}

inline mAST_T *MerParser_parse_extract_expression(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(ExtractExpression);
    node->extract_name = parser->token->string_iden;
    parser->token = _MerLexer_get_next_tok(parser->lexer);

    if (parser->token->tok == LEFT_BRACKET) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        node->is_extract = true;
        node->extract_value = MerParser_parse(parser);
        if (!node->extract_value || !is_ast_expression(node->extract_value->type)) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected extract expressuin", parser->lexer->file, TRUE_LINE(parser));
        }

        if (node->extract_value->type == ArrayExpression) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected extract expression, can not be list", parser->lexer->file, TRUE_LINE(parser));
        }

        if (parser->token->tok == RIGHT_BRACKET) {
            parser->next = _MerLexer_look_ahead(parser->lexer);

            left_bracket:
            if (parser->next->tok == LEFT_BRACKET) {
                node->is_mul_extract = true;

                parser->token = _MerLexer_get_next_tok(parser->lexer); // eat '['

                parser->token = _MerLexer_get_next_tok(parser->lexer);
                mAST_T *value = MerParser_parse(parser);

                if (!value || !is_ast_expression(value->type)) {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected extract expression", parser->lexer->file, TRUE_LINE(parser));
                }

                if (value->type == ArrayExpression) {
                    MerDebug_print_error(SYNTAX_ERROR, "Expected extract expression, can not be list", parser->lexer->file, TRUE_LINE(parser));
                }

                node->mul_extract.push_back(value);

                if (parser->token->tok == RIGHT_BRACKET) {
                    parser->next = _MerLexer_look_ahead(parser->lexer);
                    goto left_bracket;
                } else {
                    string msg = "Expected ']' in expression, name: " + node->extract_name;
                    MerDebug_print_error(SYNTAX_ERROR, msg.c_str(), parser->lexer->file, TRUE_LINE(parser));
                }
            }

            return node;
        } else {
            string msg = "Expected ']' in expression, name: " + node->extract_name;
            MerDebug_print_error(SYNTAX_ERROR, msg.c_str(), parser->lexer->file, TRUE_LINE(parser));
        }
    } else {
        string msg = "Expected '[' in expression, name: " + node->extract_name;
        MerDebug_print_error(SYNTAX_ERROR, msg.c_str(), parser->lexer->file, TRUE_LINE(parser));
    }

    return NULL;
}

inline mAST_T *MerParser_parse_compair(mAST_T *left, string op, mAST_T *right)
{
    mAST_T *node = MerAST_make_parent(ComparisonExpression);
    node->comp_left = left;
    node->comp_op = op;
    node->comp_right = right;
    return node;
}

inline mAST_T *MerParser_parse_or_expression(mParser_T *parser) {
    mAST_T *left = MerParser_parse_and_expression(parser);
    while (parser->token->tok == OR) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *right = MerParser_parse_and_expression(parser);
        left = MerParser_parse_operator_expression(left, OR, right, OrExpression);
    }

    return left;
}

inline mAST_T *MerParser_parse_and_expression(mParser_T *parser) {
    mAST_T *left = MerParser_parse_not_expression(parser);
    while (parser->token->tok == AND) {
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        mAST_T *right = MerParser_parse_not_expression(parser);
        left = MerParser_parse_operator_expression(left, AND, right, AndExpression);
    }
    
    return left;
}

inline mAST_T *MerParser_parse_not_expression(mParser_T *parser) {
    if (parser->token->tok == NOT) {
        mAST_T *node = MerAST_make_parent(NotExpression);
        parser->token = _MerLexer_get_next_tok(parser->lexer);
        node->not_expr = MerParser_parse_not_expression(parser);
        if (!node->not_expr) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression after 'not'", parser->lexer->file, TRUE_LINE(parser));
        }
        return node;
    } else if (parser->token->tok == IN_T) {
        // Handle 'in' operator
    }
    
    return MerParser_parse_comparison_expression(parser);
}

inline mAST_T *MerParser_parse_dictionary_expression(mParser_T *parser) {
    mAST_T *node = MerAST_make_parent(DictionaryExpression);

    while (parser->token->tok != RIGHT_BRACE) {
        mAST_T *dict_key = MerAST_make_parent(DictionaryExpression);
        parser->token = _MerLexer_get_next_tok(parser->lexer);

        mAST_T *key = MerParser_parse(parser);

        if (!key || !is_ast_expression(key->type)) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression in dictionary", parser->lexer->file, TRUE_LINE(parser));
        }

        dict_key->dict_key = key;

        if (parser->token->tok == COLON) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);

            mAST_T *value = MerParser_parse(parser);

            if (!value || !is_ast_expression(value->type)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression in dictionary", parser->lexer->file, TRUE_LINE(parser));
            }

            dict_key->dict_value = value;
            node->dict_list.push_back(dict_key);
        } else {
            MerDebug_print_error(SYNTAX_ERROR, "Missing ':' in dictionary", parser->lexer->file, TRUE_LINE(parser));
        }

        if (parser->token->tok == COMMA) {
            parser->token = _MerLexer_get_next_tok(parser->lexer);
        } else if (parser->token->tok != RIGHT_BRACE) {
            MerDebug_print_error(SYNTAX_ERROR, "Missing ',' in dictionary", parser->lexer->file, TRUE_LINE(parser));
        }

    }

    return node;
}

inline mAST_T *MerParser_parse_parent_expression(mParser_T *parser) {
    parser->token = _MerLexer_get_next_tok(parser->lexer);

    mAST_T *left = MerParser_parse_logical_expression(parser);
    if (!left) {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
    }

    if (parser->token->tok != RIGHT_PAREN) {
        MerDebug_print_error(SYNTAX_ERROR, "Missing ')' at the end of expression", parser->lexer->file, TRUE_LINE(parser));
    }

    return left;
}

inline mAST_T *MerParser_parse_store_index_statement(mParser_T *parser, mAST_T *left) {
    if (parser->token->tok == ASSIGN) {
        mAST_T *node = MerAST_make_parent(StoreIndexStatement);
        parser->token = _MerLexer_get_next_tok(parser->lexer);

        mAST_T *right = MerParser_parse(parser);

        if (!right || !is_ast_expression(right->type)) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
        }

        node->array_store = left;
        node->array_store_value = right;
        node->true_line = TRUE_LINE(parser);
        
        return node;
    }

    return left;
}

inline mAST_T *MerParser_parse_store_attribute_statement(mParser_T *parser, mAST_T *left) {
    if (parser->token->tok == ASSIGN) {
        mAST_T *node = MerAST_make_parent(StoreAttributeStatement);
        parser->token = _MerLexer_get_next_tok(parser->lexer);

        mAST_T *right = MerParser_parse(parser);

        if (!right || !is_ast_expression(right->type)) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
        }

        node->attr_store = left;
        node->attr_store_value = right;
        node->true_line = TRUE_LINE(parser);

        return node;
    }

    return left;    
}

inline mAST_T *MerParser_parse_logical_expression(mParser_T *parser) {
    mAST_T *value = MerParser_parse_or_expression(parser);
    if (!value) {
        MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
    }

    if (value->type == ExtractExpression) {
        return MerParser_parse_store_index_statement(parser, value);
    } else if (value->type == AttributeExpression) {
        return MerParser_parse_store_attribute_statement(parser, value);
    }
 
    value->true_line = TRUE_LINE(parser);
    return value;
}

inline mAST_T *MerParser_parse_attribute_expression(mParser_T *parser) {
    mAST_T *node = MerParser_parse_primary_expression(parser);
    parser->next = _MerLexer_look_ahead(parser->lexer);
    
    if (parser->next->tok == DOT) {
        mAST_T *attr = MerAST_make_parent(AttributeExpression);

        parser->token = _MerLexer_get_next_tok(parser->lexer); // token is now '.'

        attr->attr = node;

        if (!is_ast_attribute(node->type)) {
            MerDebug_print_error(SYNTAX_ERROR, "Expected attribute expression", parser->lexer->file, TRUE_LINE(parser));
        }

        while (true) {
            parser->token = _MerLexer_get_next_tok(parser->lexer); // token is now a primary expression

            mAST_T *value = MerParser_parse_primary_expression(parser);

            if (!value) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected expression", parser->lexer->file, TRUE_LINE(parser));
            }

            if (!is_ast_attribute(value->type)) {
                MerDebug_print_error(SYNTAX_ERROR, "Expected attribute expression", parser->lexer->file, TRUE_LINE(parser));
            }

            attr->attrs.push_back(value);

            parser->next = _MerLexer_look_ahead(parser->lexer); // check if '.'

            if (parser->next->tok == DOT) {
                parser->token = _MerLexer_get_next_tok(parser->lexer); // token is now '.'
                continue;
            } else {
                break;
            }
        }

        attr->true_line = TRUE_LINE(parser);
        return attr;
    }

    node->true_line = TRUE_LINE(parser);
    return node;
}

inline mAST_T *MerParser_parse_primary_expression(mParser_T *parser)
{
    parser->next = _MerLexer_look_ahead(parser->lexer);

    if (is_tok_literal(parser->token->tok))                     return MerAST_make(Literal, parser->token->tok, parser->token->value, "AUTO_T", "", TRUE_LINE(parser));
    if (parser->token->tok == TRUE_T)                           return MerAST_make(TrueExpression, TRUE_T, 1, "AUTO_T", "", TRUE_LINE(parser));
    if (parser->token->tok == FALSE_T)                          return MerAST_make(FalseExpression, FALSE_T, 0, "AUTO_T", "", TRUE_LINE(parser));
    if (parser->token->tok == DEFINE_VAL)                       return MerAST_make(DefineExpression, parser->token->tok, 0, "AUTO_T", parser->token->string_iden, TRUE_LINE(parser));
    if (parser->token->tok == STRING)                           return MerParser_parse_string_expression(parser);
    if (parser->token->tok == LEFT_BRACKET)                     return MerParser_parse_array_expression(parser);
    if (parser->token->tok == LEFT_BRACE)                       return MerParser_parse_dictionary_expression(parser);
    if (parser->token->tok == LEFT_PAREN)                       return MerParser_parse_parent_expression(parser);
    if (parser->token->tok == VARIABLE) {
        if (parser->next->tok == LEFT_BRACKET) return MerParser_parse_extract_expression(parser);
        if (parser->next->tok == LEFT_PAREN) return MerParser_parse_function_call_expression(parser);
        return MerAST_make(Identifier_, parser->token->tok, 0, "AUTO_T", parser->token->string_iden, TRUE_LINE(parser));
    }
    if (parser->token->tok == EOF_T 
        || parser->token->tok == DO_T
        || parser->token->tok == DOT
        || parser->token->tok == COLON) return NULL;
    
    string sym = parser->token->string_iden;
    string msg = "Unexpected primary expression near '" + sym + "'";
    MerDebug_print_error(SYNTAX_ERROR, msg.c_str(), parser->lexer->file, TRUE_LINE(parser));
    return NULL;
}

inline mAST_T *MerParser_parse_operator_expression(mAST_T *left, string op, mAST_T *right, string type) {
    mAST_T *node = MerAST_make_parent(type);
    node->left = left;
    node->op = op;
    node->right = right;
    return node;
}

_val *MerCompiler_val_new(void) {
    _val *v = new _val;
    v->value_t.int_value = 0;
    v->value_t.float_value = 0.0;
    v->value_t.bool_value = false;
    v->value_t.char_value = NULL_CHAR;
    v->value_t.string_value = "";
    v->value_t.long_value = 0;
    v->value_t.byte_value = NULL_UINT_8_T;
    v->value_t.sbyte_value = NULL_UINT_8_T;
    v->value_t.longlong_value = NULL_UINT_8_T;
    return v;
}

_bool *MerCompiler_bool_new(void) {
    _bool *b = new _bool;
    b->value = false;
    return b;
}

_code MerCompiler_code_new(void) {
    _code c = {};
    c.code = NULL_UINT_8_T;
    c.byte = NULL_UINT_8_T;
    c.address = NULL_UINT_8_T;
    c.cvalue = NULL_UINT_8_T;
    c.name = "";
    c.buff.clear();
    c.raw.clear();
    return c;
}

__iter *MerCompiler_iter_new(void) {
    __iter *it = new __iter();

    it->index = 0;
    it->size = 0;
    it->ui8_address = NULL_UINT_8_T;
    it->ui16_address = NULL_UINT_16_T;
    it->ui32_address = NULL_UINT_32_T;

    it->loop_obj.list = NULL_PTR;
    it->loop_obj.list = NULL_PTR;

    return it;
}

_class *MerCompiler_class_new(void) {
    _class *c = new _class;
    c->address = NULL_UINT_8_T;
    c->super_class = NULL_PTR;
    c->inheritance = NULL_PTR;
    c->members.clear();
    c->methods.clear();
    return c;
}

_code *MerCompiler_code_new_as_ptr(void) {
    _code *c = new _code;
    c->buff.clear();
    c->raw.clear();
    return c;
}


_string *MerCompiler_string_new(void) {
    _string *s = new _string;
    s->size = 0;
    s->buff.clear();
    return s;
}

_pcode *MerCompiler_pcode_new(void) {
    _pcode *p = new _pcode;
    p->prg_code = MerCompiler_code_new();
    p->cfile = "stdin";
    return p;
}

_func_object *MerCompiler_func_object_new(void) {
    _func_object *f = new _func_object;
    f->f_bc = MerCompiler_code_new_as_ptr();
    f->body_size = 0;
    f->args_size = 0;
    f->f_value = 0.0;
    return f;
}

_list_object *MerCompiler_list_object_new(void) {
    _list_object *l = new _list_object;
    l->size = 0;
    l->args.clear();
    return l;
}

_variable *MerCompiler_variable_new(void) {
    _variable *v = new _variable;
    v->name = "";
    v->type = "";
    v->val = MerCompiler_val_new();
    v->ui8_address = NULL_UINT_8_T;
    v->ui32_address = NULL_UINT_8_T;
    v->ui16_address = NULL_UINT_8_T;
    v->_is_constant = false;
    v->_is_local = false;
    v->_is_global = false;
    return v;
}

_object *MerCompiler_object_new(void) {
    _object *o = new _object;
    o->attributes.clear();
    o->obj_size = 0;
    o->obj_val;

    return o;
}

_type_obj *MerCompiler_type_obj_new(void) {
    _type_obj *obj = new _type_obj();

    obj->func = NULL_PTR;
    obj->variable = NULL_PTR;
    obj->str = NULL_PTR;
    obj->pcode = NULL_PTR;
    obj->code = NULL_PTR;
    obj->list = NULL_PTR;
    obj->bool_obj = NULL_PTR;
    obj->block = NULL_PTR;
    obj->val = NULL_PTR;
    obj->reg = NULL_PTR;
    obj->str_entry = NULL_PTR;

    return obj;
}
int MerCompiler_free_object(_object *o) {
    if (!o) return 0;

    o->attributes.clear();
    o->attributes.rehash(0);

    delete o;
    return 1;
}

int MerCompiler_free_code(_code *c) {
    if (!c) return 0;

    std::vector<Mer_uint8_t>().swap(c->buff);
    std::vector<Mer_uint8_t>().swap(c->raw);

    delete c;
    return 1;
}

int MerCompiler_free_string(_string *s) {
    if (!s) return 0;

    // std::vector<Mer_uint8_t>().swap(s->buff);
    
    delete s;
    return 1;
}

int MerCompiler_free_list_object(_list_object *l) {
    if (!l) return 0;

    std::vector<void*>().swap(l->args);
    delete l;
    return 1;
}

int MerCompiler_free_bool(_bool *b) {
    if (!b) return 0;
    delete b;
    return 1;
}

int MerCompiler_free_func_object(_func_object *f) {
    if (!f) return 0;

    MerCompiler_free_code(f->f_bc);
    std::vector<void*>().swap(f->args);

    delete f;
    return 1;
}

int MerCompiler_free_val(_val *v) {
    if (!v) return 0;
    delete v;
    return 1;
}

int MerCompiler_free_variable(_variable *v) {
    if (!v) return 0;

    MerCompiler_free_val(v->val);
    delete v;
    return 1;
}

int MerCompiler_free_pcode(_pcode *p) {
    if (!p) return 0;

    MerCompiler_free_code(&p->prg_code);
    MerCompiler_free_code(&p->out_code);
    std::vector<Mer_uint8_t>().swap(p->raw);

    delete p;
    return 1;
}

stack *MerCompiler_Stack_new(void) {
    stack *s = new stack;
    s->s_table = MerCompiler_Table_new();
    s->s_symtable = MerCompiler_SymbolTable_new();
    s->code_idx = 0; // Debug
    s->code_name = ""; // Debug
    s->raw_debug = NULL_UINT_8_T; // Debug
    return s;
}

table *MerCompiler_Table_new(void) {
    table *t = new table;
    t->ref_count = 0;
    t->cval = 0;
    t->cidx = 0;
    t->cbuf = 0;
    t->is_list = false;
    t->is_bool = false;
    t->is_str = false;
    t->is_code = false;
    t->is_builtin = false;
    t->is_same = false;
    t->is_local = false;
    t->is_obj = false;
    t->is_func = false;
    t->is_type = false;
    t->is_opcode = false;
    t->is_same = false;
    t->is_var = false;
    t->is_class = false;
    t->is_instance = false;
    t->value = 0;
    t->address = 0x01;
    t->size = 0;
    t->is_in_glb = false;
    t->f_value = 0;
    return t;
}

symtable *MerCompiler_SymbolTable_new(void) {
    symtable *s = new symtable;
    s->ref_count = 0;
    s->value = 0;
    s->is_str = false;
    s->is_code = false;
    s->is_list = false;
    s->is_bool = false;
    s->is_obj = false;
    s->is_func = false;
    s->is_type = false;
    s->is_opcode = false;
    s->is_same = false;
    s->is_var = false;
    s->is_builtin = false;
    s->is_local = false;
    s->is_in_glb = false;
    s->tbody = vector<uint8_t>();
    s->cidx = 0;
    s->address = 0x01;
    s->tab = MerCompiler_Table_new();
    return s;
}

table *push_stack(stack *stk, table *t) {
    if (!stk || !t) return nullptr;

    t->ref_count++;

    stk->s_table->table.push_back(t);
    return t;
}

int MerCompiler_free_stack(stack *s) {
    if (!s) return __FAILURE__;

    MerCompiler_free_table(s->s_table);
    MerCompiler_free_symboltable(s->s_symtable);
    MerCompiler_free_symboltable(s->s_global);
    MerCompiler_free_symboltable(s->s_local);

    delete s;
    return __SUCCESS__;
}

int MerCompiler_free_table(table *t) {
#ifdef GC_DEBUG
    cout << "[stack.cpp] [MerCompiler_free_table] [start] " << endl;
#endif
    if (!t) {
        cout << "Error: GC: NULL table passed to MerCompiler_free_table" << endl;
        MER_BREAK_POINT;
    }

    if (t->gc_freed) {
        return __SUCCESS__;
    }

    if (t->is_list) {
#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free list] " << endl;
#endif

        if (t->list_v->args.empty()) {
            delete t->list_v;
            delete t;
            return __SUCCESS__;
        }

        // for (auto it = t->list_v->args.begin(); it != t->list_v->args.end();) {
        //     table *item = (table *) *it;
        //     if (item && --item->ref_count < 1) {
        //         if (MerCompiler_free_table(item)) {
        //             cout << "failed to free table Error: GC1" << endl;
        //             MER_BREAK_POINT;
        //         }

        //         it = t->list_v->args.erase(it);
        //     } else {
        //         ++it;
        //     }
        // }

        delete t->list_v;
        delete t;

#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free list done] " << endl;
#endif
    }

    else if (t->is_str) {
#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free str] " << endl;
#endif
        delete t->f_str_v;
        delete t;
#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free str done] " << endl;
#endif
    }

    else if (t->is_bool) {
#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free bool] " << endl;
#endif
        MerCompiler_free_bool(t->bool_v);

        delete t;

#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free bool done] " << endl;
#endif
    } 
    
    else {
#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free table] " << endl;
#endif
        delete t;

#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free table done] " << endl;
#endif
    }

#ifdef GC_DEBUG
    cout << "[stack.cpp] [MerCompiler_free_table] [pass] " << endl;
#endif

    t->gc_freed = true;
    return __SUCCESS__;
}


int MerCompiler_free_symboltable(symtable *s) {
    if (!s) return __FAILURE__;

    if (s->list_v) delete s->list_v;
    if (s->f_str_v) delete s->f_str_v;
    if (s->code_v) delete s->code_v;
    if (s->func_obj_v) delete s->func_obj_v;
    if (s->obj_v) delete s->obj_v;
    if (s->opcode_v) delete s->opcode_v;
    if (s->tab) MerCompiler_free_table(s->tab);

    delete s;
    return __SUCCESS__;
}

stack *MerCompiler_stack_setup(stack *s, table *t, symtable *sy) {
    if (!s || !t || !sy) return NULL;
    s = MerCompiler_Stack_new();
    s->s_table = t;
    s->s_symtable = sy;
    return s;
}

table *MerCompiler_table_setup(float cval, uint8_t address) {
    table *t = MerCompiler_Table_new();
    t->cval = cval;
    t->address = address;
    return t;
}

symtable *MerCompiler_symboltable_setup(string name, float value, string type, uint8_t address) {
    symtable *s = MerCompiler_SymbolTable_new();
    s->name = name;
    s->value = value;
    s->type = type;
    s->address = address;
    return s;
}

void release_table_obj(table *obj) {
    if (obj == nullptr) return;

    obj->ref_count--;
    if (obj->ref_count == 0) {
        MerCompiler_free_table(obj);
    }
}

table *pop_stack(stack *stk) { 
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [pop_stack] [start]" << endl;
    #endif

    if (stk->s_table->table.empty()) {
        cerr << "Error: Stack is empty, can not pop while using pop_stack" << endl;
        MER_BREAK_POINT;
    }
    
    table *top = stk->s_table->table.back();

    if (!top) {
        cerr << "Error: Top of stack is NULL, cannot pop" << endl;
        MER_BREAK_POINT;
    }
    
    stk->s_table->table.pop_back();
    --top->ref_count;

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [pop_stack] [pass]" << endl;
    #endif

    return top;
}

table *pop_stack_no_ref(stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [pop_stack_no_ref] [start]" << endl;
    #endif

    if (stk->s_table->table.empty()) {
        cerr << "Error: Stack is empty, can not pop while using pop_stack_no_ref" << endl;
    }   
    table *top = stk->s_table->table.back();
    top->ref_count--;

    if (top->is_list && top->ref_count < 1) {
        for (auto it = top->list_v->args.begin(); it != top->list_v->args.end(); ++it) {
            table *item = (table *) *it;
            item->ref_count--;
        }
    }

    stk->s_table->table.pop_back();

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [pop_stack_no_ref] [pass]" << endl;
    #endif

    return top;
}

table *eat_stack(stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eat_stack] [start]" << endl;
    #endif
    
    if (stk->s_table->table.empty()) {
        cerr << "Error: Stack underflow in eat_stack" << endl;
    }
    table *top = stk->s_table->table.back();

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eat_stack] [pass]" << endl;
    #endif

    return top;
}

void reset_table(table *t) {
    if (!t) {
        cerr << "Error: NULL table passed to reset_table" << endl;
        MER_BREAK_POINT;
    }

    t->cval = 0;
    t->cidx = 0;
    t->cbuf = 0;
    t->is_list = false;
    t->is_bool = false;
    t->is_str = false;
    t->is_code = false;
    t->is_builtin = false;
    t->is_same = false;
    t->is_local = false;
    t->is_obj = false;
    t->is_func = false;
    t->is_type = false;
    t->is_opcode = false;
    t->is_same = false;
    t->is_var = false;
    t->is_class = false;
    t->is_instance = false;
    t->value = 0;
    t->address = 0x01;
    t->size = 0;
    t->is_in_glb = false;
    t->f_value = 0;
    t->f_str_v = nullptr;
    t->list_v = nullptr;
    t->func_obj_v = nullptr;
    t->bool_v = nullptr;
    t->obj_v = nullptr;
    t->opcode_v = nullptr;
}

table *table_clone_shallow(table *dst, table *src) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [table_clone_shallow] [start]" << endl;
    #endif

    if (!src || !dst) {
        cerr << "Error: NULL pointer passed into table_clone_shallow" << endl;
        MER_BREAK_POINT;
    }

    dst->value = src->value;
    dst->cval = src->cval;
    dst->address = src->address;
    dst->ref_count = src->ref_count;

    dst->is_str = src->is_str;
    dst->is_list = src->is_list;
    dst->is_func = src->is_func;
    dst->is_class = src->is_class;
    dst->is_instance = src->is_instance;

    if (src->is_str && src->f_str_v) {
        mString_T *copy = MerCompiler_string_new();
        copy->hash = src->f_str_v->hash;
        copy->size = src->f_str_v->size;
        for (auto &ch : src->f_str_v->buff) {
            copy->buff.push_back(ch);
        }
        dst->f_str_v = copy;
    }

    else if (src->is_list && src->list_v) {
        dst->list_v = MerCompiler_list_object_new();

        dst->list_v->size = src->list_v->size;
        for (auto &item : src->list_v->args) {
            table *new_item = table_clone_shallow(MerCompiler_Table_new(), (table *) item);
            dst->list_v->args.push_back(new_item);
        }
    }

    else if (src->is_func) {
        dst->func_obj_v = MerCompiler_func_object_new();

        dst->func_obj_v->is_return = src->func_obj_v->is_return;
        dst->func_obj_v->is_global = src->func_obj_v->is_global;
        dst->func_obj_v->is_local = src->func_obj_v->is_local;
        dst->func_obj_v->o = src->func_obj_v->o;
        dst->func_obj_v->f_builtin = src->func_obj_v->f_builtin;
        dst->func_obj_v->sf = src->func_obj_v->sf;
        dst->func_obj_v->body_size = src->func_obj_v->body_size;
        dst->func_obj_v->args_size = src->func_obj_v->args_size;

        for (Mer_uint8_t opcode : src->func_obj_v->f_bc->buff) {
            dst->func_obj_v->f_bc->buff.push_back(opcode);
        }

        for (Mer_uint8_t opcode : src->func_obj_v->f_bc->raw) {
            dst->func_obj_v->f_bc->raw.push_back(opcode);
        }

        dst->func_obj_v->ref_count = src->func_obj_v->ref_count;
    }

    else if (src->is_class) {
        dst->class_v = MerCompiler_class_new();

        dst->class_v = src->class_v;
    }

    else if (src->is_instance) {
        dst->class_v = MerCompiler_class_new();

        dst->class_v = src->class_v;
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [table_clone_shallow] [pass]" << endl;
    #endif

    return dst;
}

int _MerCode_push_opcode(mCode_T &code, Mer_uint8_t op) {
    code.prg_code.buff.push_back(op);
    return 0;
}
int _MerCode_insert_opcode(mCode_T &code, Mer_uint8_t *op, Mer_size_t size) {
    code.prg_code.buff.insert(code.prg_code.buff.end() , op, op + size);
    return 0;
}
int _MerCode_insert_vec_code(mCode_T &code, mCode_T &ins) {
    code.prg_code.buff.insert(code.prg_code.buff.end(), ins.prg_code.buff.begin(), ins.prg_code.buff.end());
    return 0;
}

int _MerCode_super_insert_vec_code(mCode_T &code, mCode_T &ins) {
    code.prg_code.buff.insert(code.prg_code.buff.end(), ins.prg_code.buff.begin(), ins.prg_code.buff.end());
    code.out_code.buff.insert(code.out_code.buff.end(), ins.out_code.buff.begin(), ins.out_code.buff.end());
    return 0;
}

int _MerCode_push_opcode_to_outcode(mCode_T &code, Mer_uint8_t op) {
    code.out_code.buff.push_back(op);
    return 0;
}
int _MerCode_insert_opcode_to_outcode(mCode_T &code, Mer_uint8_t *op, Mer_size_t size) {
    code.out_code.buff.insert(code.out_code.buff.end() , op, op + size);
    return 0;
}
int _MerCode_insert_vec_code_to_outcode(mCode_T &code, mCode_T &ins) {
    code.out_code.buff.insert(code.out_code.buff.end(), ins.out_code.buff.begin(), ins.out_code.buff.end());
    return 0;
}

int _MerCode_insert_vec_code_to_outcode_by_prog_code(mCode_T &code, mCode_T &ins) {
    code.out_code.buff.insert(code.out_code.buff.end(), ins.prg_code.buff.begin(), ins.prg_code.buff.end());
    return 0;
}

int _MerCode_insert_vec_code_to_prg_code_by_out_code(mCode_T &code, mCode_T &ins) {
    code.prg_code.buff.insert(code.prg_code.buff.end(), ins.out_code.buff.begin(), ins.out_code.buff.end());
    return 0;
}

mBool_T *make_bool(bool value) {
    mBool_T *boolen = MerCompiler_bool_new();
    if (value) {
        boolen->value = true;
    } else {
        boolen->value = false;
    }

    return boolen;
}

table *make_true_value() {
    table *bool_obj = MerCompiler_Table_new();
    bool_obj->bool_v = MerCompiler_bool_new();
    bool_obj->bool_v->value = true;
    bool_obj->is_bool = true;
    bool_obj->cval = 1;
    return bool_obj;
}

table *make_false_value() {
    table *bool_obj = MerCompiler_Table_new();
    bool_obj->bool_v = MerCompiler_bool_new();
    bool_obj->bool_v->value = false;
    bool_obj->is_bool = true;
    bool_obj->cval = 0;
    return bool_obj;
}


float __uint8_to_float(Mer_uint8_t c) {
    return static_cast<float>(c);
}

float __hash(mString_T *str) {
    float result = 0.0f;
    float power = 1.0f;
    
    for (int i = (int)str->buff.size() - 1; i >= 0; --i) {
        result += (float)str->buff[i] * power;
        power *= 31.0f;
    }
    
    return result;
}

__mer_core_api__ mString_T *__mer_core_api__ add_string(mString_T *a, mString_T *b) {
    mString_T *result = MerCompiler_string_new();
    result->buff.insert(result->buff.end(), a->buff.begin(), a->buff.end());
    result->buff.insert(result->buff.end(), b->buff.begin(), b->buff.end());
    result->size = a->size + b->size;
    result->hash = __hash(result);
    return result;
}

__mer_core_api__ mString_T *__mer_core_api__ mul_string(mString_T *a, int times) {
    mString_T *result = MerCompiler_string_new();

    for (int i = 0; i < times; i++) {
        result->buff.insert(result->buff.end(), a->buff.begin(), a->buff.end());
    }

    result->size = a->size * times;
    result->hash = __hash(result);
    return result;
}

__mer_core_lib_api__ string __convert_to_string(mString_T *__string) {
    string value = "";
    vector<Mer_uint8_t> cont = __string->buff;

    for (auto &item : cont) {
        value += static_cast<char>(item);
    }

    return value;
}

char* from_mstring_to_char(mString_T *str) {
    char* result = new char[str->size];
    vector<Mer_uint8_t> code = str->buff;
    for (Mer_size_t i = 0; i < str->size; i++) {
        result[i] = code[i];
    }
    return result;
}

mString_T *creat_string_obj_with_code(vector<Mer_uint8_t> code) {
    mString_T *str_obj = MerCompiler_string_new();
    str_obj->buff.insert(str_obj->buff.end(), code.begin(), code.end());
    str_obj->size = code.size();
    str_obj->hash = __hash(str_obj);
    return str_obj;
}

mString_T *creat_char_obj(Mer_uint8_t c) {
    mString_T *str_obj = MerCompiler_string_new();
    str_obj->buff.push_back(c);
    str_obj->size = size(str_obj->buff);
    str_obj->hash = __hash(str_obj);
    return str_obj;
}

mString_T *creat_string_obj(string str) {
    mString_T *str_obj = MerCompiler_string_new();
    str_obj->buff.insert(str_obj->buff.end(), str.begin(), str.end());
    str_obj->size = str.size();
    str_obj->hash = __hash(str_obj);
    return str_obj;
}

table *creat_str(string str) {
    mString_T *str_obj = creat_string_obj(str);
    table *str_tab = MerCompiler_Table_new();
    str_tab->is_str = true;
    str_tab->f_str_v = str_obj;
    str_tab->cval = static_cast<float>(str_obj->hash);
    return str_tab;
}


float __list_value(mList_T *list) {
    size_t seed = list->args.size();

    for (size_t i = 0; i < list->args.size(); i++) {
        float val = ((table *)list->args[i])->cval;

        uint32_t int_val;
        memcpy(&int_val, &val, sizeof(float));

        seed ^= int_val * i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    float result;
    memcpy(&result, &seed, sizeof(float));
    return result;
}

mList_T *creat_list_obj(vector<void *> args) {
    mList_T *list = MerCompiler_list_object_new();
    list->size = args.size();
    list->args = args;
    return list;
}

mList_T *add_list(mList_T *a, mList_T *b) {
    mList_T *list = MerCompiler_list_object_new();
    list->size = a->size + b->size;
    list->args.insert(list->args.end(), a->args.begin(), a->args.end());
    list->args.insert(list->args.end(), b->args.begin(), b->args.end());
    return list;
}

mList_T *mul_list(mList_T *a, int times) {
    mList_T *list = MerCompiler_list_object_new();
    list->size = a->size * times;
    for (int i = 0; i < times; i++) {
        list->args.insert(list->args.end(), a->args.begin(), a->args.end());
    }
    return list;
}

table *creat_list(vector<void *> args) {
    table *list_table = MerCompiler_Table_new();
    list_table->is_list = true;
    list_table->list_v = creat_list_obj(args);
    list_table->list_v->size = list_table->list_v->args.size();
    list_table->cval = __list_value(list_table->list_v);
    return list_table;
}

void insert_elem(table *list_table, void *elem) {
    list_table->list_v->args.push_back(elem);
    list_table->list_v->size = list_table->list_v->args.size();
    list_table->cval = __list_value(list_table->list_v);
}

void extend_list(table *list_table, vector<void *> args) {
    list_table->list_v->args.insert(list_table->list_v->args.end(), args.begin(), args.end());
    list_table->list_v->size = list_table->list_v->args.size();
    list_table->cval = __list_value(list_table->list_v);
}

void clear_list(table *list_table) {
    list_table->list_v->args.clear();
    list_table->list_v->size = list_table->list_v->args.size();
    list_table->cval = __list_value(list_table->list_v);
}

void del_elem(table *list_table, int index) {
    list_table->list_v->args.erase(list_table->list_v->args.begin() + index);
    list_table->list_v->size = list_table->list_v->args.size();
    list_table->cval = __list_value(list_table->list_v);
}

void pop_elem(table *list_table) {
    list_table->list_v->args.pop_back();
    list_table->list_v->size = list_table->list_v->args.size();
    list_table->cval = __list_value(list_table->list_v);
}

__global *create_global_table_ptr(Mer_uint8_t __Address, const Mer_string &__Name, Mer_real_string __name) {
    __global *__glb = new __global();
    __glb->__Address = __Address;
    __glb->__Name = __Name;
    __glb->__name = __name;
    return __glb;
}

__global create_global_table(Mer_uint8_t __Address, const Mer_string &__Name, Mer_real_string __name){
    __global __glb = NULL_GLOBAL;
    __glb.__Address = __Address;
    __glb.__Name = __Name;
    __glb.__name = __name;
    return __glb;
}

MERCURY_API __mer_core_api__ void __register_lib(Mer_uint8_t address, void *func, Mer_string name) {
    mer_core_libs.push_back({address, name, func});
}

MERCURY_API __mer_core_api__ void __register_global(Mer_uint8_t address, Mer_string name) {
    GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(address, name, name));
    LOCAL_TABLE.push_back(CREAT_LOCAL_TABLE(address, name, name));
}

MERCURY_API __mer_core_api__ void __register_lib_to_global(Mer_uint8_t address, Mer_string name) {
    __global *item = CREAT_GLOBAL_TABLE(address, name, name);
    item->is_let = false;
    GLOBAL_TABLE.push_back(item);
    LOCAL_TABLE.push_back(item);
}

MERCURY_API __mer_core_api__ void __register_global_data(symtable *item) {
    if (!item) return;
    _G.push_back(item);
}

MERCURY_API __mer_core_api__ void __register_lib_to_global_stack(Mer_uint8_t address, mFunc_T func) {
    symtable *item = MerCompiler_SymbolTable_new();
    item->address = address;
    item->is_builtin = true;
    item->func_v = func;
    _G.push_back(item);
}

MERCURY_API __mer_core_api__ void __register_global_variable(Mer_uint8_t address, float value) {
    _G.push_back(MerCompiler_symboltable_setup("", value, "AUTO_T", address));
}

MERCURY_API __mer_core_api__ void __register_global_variable_with_object(string name, table *obj) {
    Mer_uint8_t address = global_hashmap[name];
    symtable *item = MerCompiler_symboltable_setup("", obj->cval, "AUTO_T", address);
    item->tab = obj;
    _G.push_back(item);
}


__mer_core_data__ float __randint(int a, int b) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis;

    dis.param(std::uniform_int_distribution<int>::param_type(a, b));
    return static_cast<float>(dis(gen));
}

__mer_core_data__ float __random() {
    static std::random_device rd;
    static std::mt19937 gen(rd()); 
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    return dis(gen);
}


 __mer_core_lib_api__ const char* to_char(Mer_uint8_t c) {
    static char s[1];
    s[0] = c;
    return s;
}

const float to_float(string c) {
    int idx = 0;
    float value = 0.0f;
    bool is_negative = false;
    if (c[idx] == '-') {
        is_negative = true;
        idx++;
    }
    for (; idx < c.length(); idx++) {
        value = value * 10 + (c[idx] - '0');
    }
    if (is_negative) {
        value = -value;
    }

    return value;
}

const int to_int(string c) {
    return int(to_float(c));
}

float get_current_time() {
    auto now = std::chrono::high_resolution_clock::now();
    auto sec = std::chrono::duration<float>(now.time_since_epoch());
    return sec.count();
}

__mer_core_lib_api__ __builtin_func_t __builtin_mer_whats_time_is_it(stack *stk) {
    float __value = get_current_time();
    stack_push(MerCompiler_table_setup(__value, NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_read_line(stack *stk) {
    string input_line;
    getline(cin, input_line);

    mString_T* str = MerCompiler_string_new();
    for (char ch : input_line) {
        str->buff.push_back(ch);
    }
    str->size = str->buff.size();
    str->hash = __hash(str);

    table* tab = MerCompiler_Table_new();
    tab->is_str = true;
    tab->f_str_v = str;
    tab->cval = static_cast<float>(str->hash);

    stack_push(tab);
}

int ISDIGIT(string str) {
    for (auto &ch : str) {
        if (!isdigit(ch)) {
            return 0;
        }
    }
    return 1;
}

__mer_core_lib_api__ __builtin_func_t __builtin_mer_is_digit(stack *stk) {
    table *top = POP();
    
    if (top->is_str) {
        string str = __convert_to_string(top->f_str_v);
        if (ISDIGIT(str)) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    } else {
        push_false_to_stack();
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __io_write(mString_T *__string) {
    vector<Mer_uint8_t> cont = __string->buff;

    for (auto &item : cont) {
        fwrite(to_char(item), 1, 1, stdout);
    }

    fwrite("\n", 1, 1, stdout);

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__io_write] [pass]" << endl;
    #endif
}

__mer_core_lib_api__ __builtin_func_t __io_puts(mString_T *__string) {
    vector<Mer_uint8_t> cont = __string->buff;

    for (auto &item : cont) {
        fwrite(to_char(item), 1, 1, stdout);
    }

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__io_write] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_to_string(stack *stk) {
    table *top = POP();
    
    if (top->is_str) {
        stack_push(top);
    } else {
        string str = to_string(top->cval);
        mString_T *str_obj = creat_string_obj(str);
        table *str_tab = MerCompiler_Table_new();
        str_tab->is_str = true;
        str_tab->f_str_v = str_obj;
        str_tab->cval = static_cast<float>(str_obj->hash);
        stack_push(str_tab);
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_to_int(stack *stk) {
    table *top = POP();
    
    if (top->is_str) {
        string str = __convert_to_string(top->f_str_v);
        if (ISDIGIT(str)) {
            stack_push(MerCompiler_table_setup(to_int(str), NULL_UINT_8_T));
        } else {
            push_false_to_stack();
        }
    } else if (top->is_list) {
        push_false_to_stack();
    } else {
        stack_push(MerCompiler_table_setup(int(top->cval), NULL_UINT_8_T));
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_print_global_stack(stack *stk) {
    for (auto &item : _G) {
        cout << int(item->address) << endl;
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_list(stack *stk) {
    table *list = POP();
    table *val = MerCompiler_Table_new();

    if (list->is_str) {
        val->is_list = true;
        val->list_v = MerCompiler_list_object_new();

        for (auto &charr : list->f_str_v->buff) {
            mString_T *str = MerCompiler_string_new();
            str->buff.push_back(charr);
            str->size = 1;

            table *str_tab = MerCompiler_Table_new();
            str_tab->is_str = true;
            str_tab->f_str_v = str;
            str_tab->cval = __hash(str);
            str_tab->value = str_tab->cval;

            val->list_v->args.push_back(str_tab);
            val->list_v->size++;
        }

        stack_push(val);
    }
    
    stack_push(val);
}

int __ContainsOnlySpaces(const vector<Mer_uint8_t>& cont) {
    for (const auto &item : cont) {
        if (item != 0x20) {
            return 0;
        }
    }
    return 1;
}


MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_empty(stack *stk) {
    table *list = POP();
    if (list->is_list) {
        if (list->list_v->size == 0) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    } else if (list->is_str) {
        if (__ContainsOnlySpaces(list->f_str_v->buff)) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    } else {
        push_true_to_stack();
    }
}

vector<string> __split(string a, char b) {
    vector<string> result;
    string temp = "";

    for (char ch : a) {
        if (ch == b) {
            result.push_back(temp);
            temp.clear();
        } else {
            temp += ch;
        }
    }

    result.push_back(temp);
    return result;
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_sub(stack *stk) {
    table *lstr = POP();
    table *rstr = POP();

    if (!lstr || !rstr) {push_false_to_stack();}

    if (lstr->is_str && lstr->is_str) {
        rstr->f_str_v->buff.insert(rstr->f_str_v->buff.end(),
        lstr->f_str_v->buff.begin(),
        lstr->f_str_v->buff.end());
        
        rstr->f_str_v->size += lstr->f_str_v->size;
        stack_push(rstr);
        return;
    } else if (lstr->is_list && lstr->is_list) {
        rstr->list_v->args.insert(rstr->list_v->args.end(),
        lstr->list_v->args.begin(), 
        lstr->list_v->args.end());

        rstr->list_v->size += lstr->list_v->size;
        stack_push(rstr);
        return;
    } else {
        rstr->cval += lstr->cval;
        rstr->value += lstr->value;
        stack_push(rstr);
        return;
    }
}

__builtin_func_t sleep_ms(int num) {
    num *= 1000;
    this_thread::sleep_for(chrono::milliseconds((num)));
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_sleep(stack *stk) {
    table *num = POP();
    sleep_ms(num->cval);
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_random(stack *stk) {
    stack_push(MerCompiler_table_setup(__random(), NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_range(stack *stk) {
    table *start = POP();
    table *end = POP();

    Mer_size_t start_int = start->cval;
    Mer_size_t end_int = end->cval;

    mList_T *list = MerCompiler_list_object_new();

    if (start_int > end_int) {
        for (Mer_size_t i = start_int; i > end_int; i--) {
            table *val = MerCompiler_table_setup(i, NULL_UINT_8_T);
            val->ref_count++;
            back_insrt(list->args, val);
        }
    } else {
        for (Mer_size_t i = start_int; i < end_int; i++) {
            table *val = MerCompiler_table_setup(i, NULL_UINT_8_T);
            val->ref_count++;
            back_insrt(list->args, val);
        }
    }

    table *list_table = MerCompiler_Table_new();
    list_table->is_list = true;

    list_table->list_v = list;
    list_table->list_v->size = list->args.size();
    stack_push(list_table);

    push_to_gc(start);
    push_to_gc(end);
}

__mer_core_api__ int __same(vector<Mer_uint8_t> a, vector<Mer_uint8_t> b) {
    if (a.size() != b.size()) {
        return 0;
    }

    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_same_string(stack *stk) {
    table *item1 = POP();
    table *item2 = POP();

    if (item1->is_str && item2->is_str) {
        if (__same(item1->f_str_v->buff, item2->f_str_v->buff)) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    } else if (item1->is_list && item2->is_list) {
        if (item1->list_v->size == item2->list_v->size) {
            for (int i = 0; i < item1->list_v->size; i++) {
                if (item1->list_v->args[i] != item2->list_v->args[i]) {
                    push_false_to_stack();
                    return;
                }
            }

            push_true_to_stack();

        } else {
            push_false_to_stack();
        }
    } else if (item1->is_bool && item2->is_bool) {
        if (item1->bool_v->value == item2->bool_v->value) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    } else if (item1->cval == item2->cval) {
        push_true_to_stack();
    } else {
        push_false_to_stack();
    }
}

__mer_core_lib_api__  Mer_real_string hash_to_string(mString_T *str) {
    Mer_real_string result = "";
    Mer_size_t size = str->size;
    vector<Mer_uint8_t> buff = str->buff;

    for (Mer_size_t i = 0; i < buff.size(); ++i) {
        result += buff[i];
    }

    return result;
}

bool is_float(float value) {
    return (value - static_cast<int>(value)) != 0;
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_size(stack *stk) {
    table *top = POP();

    if (top->is_list) {
        stack_push(MerCompiler_table_setup(top->list_v->size, NULL_UINT_8_T));
    } else if (top->is_str) {
        stack_push(MerCompiler_table_setup(top->f_str_v->size, NULL_UINT_8_T));
    } else {
        stack_push(MerCompiler_table_setup(4, NULL_UINT_8_T));
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_io_write(stack *stk) {
    table *top = POP();

    push_to_gc(top);

    if (top->is_str) {
        mString_T *str_v = top->f_str_v;
        __io_write(str_v);
    } else if (top->is_list) {
        __io_cout_stdout("[")

        if (top->list_v->size == 1) {
            table *value = (table *) top->list_v->args[0];
            if (value->is_str) {
                mString_T *str_v = value->f_str_v;
                __io_cout_stdout("\"");
                __io_puts(str_v);
                __io_cout_stdout("\"");
            } else {
                __io_cout_stdout(value->cval);
            }
        } else {
            for (Mer_size_t i = 0; i < top->list_v->size; i++) {
                table *value = (table *) top->list_v->args[i];
                if (value->is_str) {
                    mString_T *str_v = value->f_str_v;
                    __io_cout_stdout("\"");
                    __io_puts(str_v);
                    __io_cout_stdout("\"");
                } else {
                    __io_cout_stdout(value->cval);
                }
                if (i != top->list_v->size - 1) {
                    __io_cout_stdout(", ");
                }
            }
        }
        
        __io_cout_stdout("]");
        __io_cout_stdout("\n");
    } else if (top->is_bool) {
        if (top->bool_v->value) {
            __io_cout_stdout("true");
        } else {
            __io_cout_stdout("false");
        }
        __io_cout_stdout("\n");
    } else if (top->is_class || top->is_instance) {
        cout << "<Address of object: " << "0x" << hex << setfill('0') << setw(2) << (int)top->class_v->address << ">" << endl;
    } else {
        __io_cout_stdout(top->cval);
        __io_cout_stdout("\n");
    }

    table* value = MER_VALUE(0);
    stack_push(value);
    
    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_io_write] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_puts_val(stack *stk) {
    table *top = POP();

    push_to_gc(top);

    if (top->is_str) {
        mString_T *str_v = top->f_str_v;
        __io_puts(str_v);
    } else {
        __io_cout_stdout(top->cval);
    }
    
    stack_push(MER_VALUE(0));
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_push(stack *stk) {
    table *value = POP();
    table *list = POP();

    if (list->is_list) {
        list->list_v->args.push_back(value);
        list->list_v->size++;
        STACK_PUSH(stk, list);
    } else {
        STACK_PUSH(stk, list);
    }

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_push] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_type(stack *stk) {
    table *top = POP();
    if (top->is_list) {
        STACK_PUSH(stk, MerCompiler_table_setup(MER_LIST_TYPE, NULL_UINT_8_T));
    } else if (top->is_str) {
        STACK_PUSH(stk, MerCompiler_table_setup(MER_STRING_TYPE, NULL_UINT_8_T));
    } else if (top->is_func) {
        STACK_PUSH(stk, MerCompiler_table_setup(MER_FUNCTION_TYPE, NULL_UINT_8_T));
    } else if (top->is_code) {
        STACK_PUSH(stk, MerCompiler_table_setup(MER_CODE_TYPE, NULL_UINT_8_T));
    } else if (top->is_bool) {
        STACK_PUSH(stk, MerCompiler_table_setup(MER_BOOL_TYPE, NULL_UINT_8_T));
    } else {
        STACK_PUSH(stk, MerCompiler_table_setup(MER_FLOAT_TYPE, NULL_UINT_8_T));
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_pop(stack *stk) {
    table *list = POP();

    if (list->is_list) {
        list->list_v->size--;
        table *val = nullptr;

        if (list_size(list) <= 0) {
            set_size(list, 0);
        } else {
            val = (table *) list->list_v->args.back();
            list->list_v->args.pop_back();
        }

        STACK_PUSH(stk, val);
        return;
    }
    
    STACK_PUSH(stk, MerCompiler_table_setup(0, NULL_UINT_8_T));

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_pop] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_pause(stack *stk) {
    MER_PAUSE;
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __mer_builtin_exit(stack *stk) {
    MER_EXIT;
}

typedef table*(*Function_ffi)(table*[]);

table* dll_load_func(string dll_path, string func, vector<table*> args) {
#ifdef _WIN32
    HMODULE hModule = LoadLibraryA(dll_path.c_str());

    if (!hModule) {
        cerr << "Failed to load DLL: " << dll_path << endl;
        FreeLibrary(hModule);
        return nullptr;
    }

    FARPROC pFunc = GetProcAddress(hModule, func.c_str());

    if (!pFunc) {
        cerr << "Failed to find function: " << func << endl;
        FreeLibrary(hModule);
        return nullptr;
    }

    Function_ffi sumFunc = (Function_ffi)pFunc;

    table* result = sumFunc(args.data());

    return result;

#else   
    cerr << "FFI is not supported on this platform." << endl;
#endif
}

MERCURY_API __mer_core_api__ __builtin_func_t __builtin_dll_load_func(stack *stk) {
    table *args = POP();
    table *func_to_call = POP();
    table *path_to_dll = POP();

    vector<table*> args_list;

    if (args->is_list) {
        for (auto &item : args->list_v->args) {
            table *val = (table *) item;
            args_list.push_back(val);
        }
    }

    if (!func_to_call->is_str || !path_to_dll->is_str) {
        return;
    }
    
    string dll_path = __convert_to_string(path_to_dll->f_str_v);
    string func = __convert_to_string(func_to_call->f_str_v);
    
    table* result = dll_load_func(dll_path, func, args_list);

    if (result) {
        stack_push(result);
    } else {
        stack_push(MerCompiler_table_setup(0, NULL_UINT_8_T));
    }

    push_to_gc(args);
    push_to_gc(func_to_call);
    push_to_gc(path_to_dll);
}

MERCURY_API void MerCore_initialize() {
    BUILD_LIB_FUNC("print", __builtin_io_write);
    BUILD_LIB_FUNC("push", __builtin_push);
    BUILD_LIB_FUNC("pop", __builtin_pop);
    BUILD_LIB_FUNC("type", __builtin_type);
    BUILD_LIB_FUNC("puts", __builtin_puts_val);
    BUILD_LIB_FUNC("range", __builtin_range);
    BUILD_LIB_FUNC("same", __builtin_same_string);
    BUILD_LIB_FUNC("input", __builtin_mer_read_line);
    BUILD_LIB_FUNC("size", __builtin_size); 
    BUILD_LIB_FUNC("isdigit", __builtin_mer_is_digit);
    BUILD_LIB_FUNC("puts", __builtin_puts_val);
    BUILD_LIB_FUNC("dll_load", __builtin_dll_load_func);
    BUILD_LIB_FUNC("to_str", __builtin_to_string);
    BUILD_LIB_FUNC("to_int", __builtin_to_int);

    BUILD_GLOBAL_VARIABLE("inf", INFINITY);
}   

MERCURY_API void MerCore_Finalize(void) {
    _G.clear();
    _L.clear();
    GLOBAL_TABLE.clear();
    mer_core_libs.clear();
    STRING_ENTRY.clear();
}


int ref_counting_on_stack(stack *stk) {
    int total_ref = 0;
    for (auto it = stk->s_table->table.begin(); it != stk->s_table->table.end(); it++) {
        table *t = *it;
        if (t->ref_count <= 1) {
            total_ref++;
        }
    }

    return total_ref;
}

void collect(stack *stk, const char* file) {
    int total_ref = ref_counting_on_stack(stk);
    int DANGEROUS_REF = 1000;
    
    if (total_ref >= DANGEROUS_REF && !IS_CONTINUE) {
        cout << "Warning: This program has more than " << total_ref << " references on stack, which is too high. This may cause memory leak." << endl;
        std::string input;
        std::cout << "Do you want to continue? (y/n): ";
        std::getline(std::cin, input);
        if (input == "y" || input == "Y") {
            IS_CONTINUE = true;
        } else {
            cout << "Exiting program to prevent memory leak." << endl;
            exit(0);
        }
    }
}

void __unique(std::vector<table*> &tables) {
    std::unordered_set<table*> seen;
    std::vector<table*> result;
    result.reserve(tables.size());

    for (auto ptr : tables) {
        if (seen.insert(ptr).second) {  
            result.push_back(ptr);
        }
    }

    tables.swap(result);
}

void GC_collect(vector<table*> &tables, stack *stk, const char* file) {
#ifdef GC_DEBUG
    cout << "[gc.cpp] [GC_collect] [start] with size of " << tables.size() << " " << endl;
#endif
    
    int sym_ref_0 = 0;
    __unique(tables);

    for (auto it = tables.begin(); it != tables.end(); ) {
        table *t = *it;
        if (!t) {
            cout << "Error: GC: NULL table passed to GC_collect" << endl;
            MER_BREAK_POINT;
        }

        if (t->ref_count <= 0) {
#ifdef GC_DEBUG
            cout << "[gc.cpp] [GC_collect] [starting...] collecting 0x" << int(t->address) << " found at index " << sym_ref_0++ << " " << endl;
#endif
            if (MerCompiler_free_table(t)) {
                cout << "failed to free table Error: GC0" << endl;
                MER_BREAK_POINT;
            }

            it = tables.erase(it);

#ifdef GC_DEBUG
            cout << "[gc.cpp] [GC_collect] [collecting done] done collecting" << " found at index " << sym_ref_0 - 1 << " " << endl;
#endif  
        } else {
            it++;
        }
    }

#ifdef GC_DEBUG
    cout << "[gc.cpp] [GC_collect] [pass]" << endl;
#endif
}

bool skip = false;

__compiler_u compiler_init(void) {
  __compiler_u glb;
  glb.address = 0x50;
  glb.cid = 0x0000;
  glb.name = nullptr;
  glb.type = nullptr;
  glb.is_in_func = false;
  glb.para_address = 0x0000;
  glb.file = "stdin";
  return glb;
}

MERCURY_API mCode_T MerCompiler_compile_ast_id(mAST_T *ast, __compiler_u &glb) {
  if (!ast) return NULL_CODE;

  if (ast->type == Identifier_)             return MerCompiler_compile_ast_identifier(ast, glb);
  if (ast->type == Literal)                 return MerCompiler_compile_ast_literal(ast, glb);
  if (ast->type == FunctionStatement)       return MerCompiler_compile_ast_function(ast, glb); 
  if (ast->type == BinaryExpression)        return MerCompiler_compile_ast_binary_expression(ast, glb);
  if (ast->type == FunctionCallExpression)  return MerCompiler_compile_ast_function_call(ast, glb);
  if (ast->type == IfStatement)             return MerCompiler_compile_ast_if(ast, glb);
  if (ast->type == LetStatement)            return MerCompiler_compile_ast_let(ast, glb);
  if (ast->type == ReturnStatement)         return MerCompiler_compile_ast_return(ast, glb);
  if (ast->type == ExpressionStatement)     return MerCompiler_compile_ast_id_expression_statment(ast, glb);
  if (ast->type == ComparisonExpression)    return MerCompiler_compile_ast_comparison_expression(ast, glb);
  if (ast->type == AssignStatement)         return MerCompiler_compile_ast_assign(ast, glb);
  if (ast->type == WhileStatement)          return MerCompiler_compile_ast_while(ast, glb);
  if (ast->type == StringIdentifier)        return MerCompiler_compile_ast_string_identifier(ast, glb);
  if (ast->type == ListStatement)           return MerCompiler_compile_ast_list(ast, glb);
  if (ast->type == ArrayExpression)         return MerCompiler_compile_ast_array(ast, glb);
  if (ast->type == ExtractExpression)       return MerCompiler_compile_ast_extract(ast, glb);
  if (ast->type == StoreIndexStatement)     return MerCompiler_compile_ast_store_index_statement(ast, glb);
  if (ast->type == ForInStatement)          return MerCompiler_compile_ast_for_in_statement(ast, glb);
  if (ast->type == LoopStatement)           return MerCompiler_compile_ast_loop(ast, glb);
  if (ast->type == BreakStatement)          return MerCompiler_compile_ast_break(ast, glb);
  if (ast->type == ContinueStatement)       return MerCompiler_compile_ast_continue(ast, glb);
  if (ast->type == TrueExpression)          return MerCompiler_compile_ast_true(ast, glb);
  if (ast->type == FalseExpression)         return MerCompiler_compile_ast_false(ast, glb);
  if (ast->type == AndExpression)           return MerCompiler_compile_ast_and_expression(ast, glb);
  if (ast->type == NotExpression)           return MerCompiler_compile_ast_not_expression(ast, glb);
  if (ast->type == OrExpression)            return MerCompiler_compile_ast_or_expression(ast, glb);
  if (ast->type == ImportStatement)         return MerCompiler_compile_ast_import(ast, glb);
  if (ast->type == DefineStatement)         return MerCompiler_compile_ast_define(ast, glb);
  if (ast->type == DefineExpression)        return MerCompiler_compile_ast_define_expression(ast, glb);
  if (ast->type == IncludeStatement)        return MerCompiler_compile_ast_include(ast, glb);
  if (ast->type == ClassStatement)          return MerCompiler_compile_ast_class_statement(ast, glb);
  if (ast->type == AttributeExpression)     return MerCompiler_compile_ast_attribute_expression(ast, glb);
  if (ast->type == StoreAttributeStatement) return MerCompiler_compile_ast_store_attribute_statement(ast, glb);

  return NULL_CODE;
}

MERCURY_API mCode_T MerCompiler_make_store_attribute(mAST_T *ast, __compiler_u &glb) {
  Mer_real_string attr_name = ast->string_iden;
  Mer_uint8_t address = NULL_UINT_8_T;
  bool found = false;

  for (auto &item : LOCAL_TABLE) {
    if (item->__Name == attr_name) {
      address = item->__Address;
      found = true;
      break;
    }
  }

  if (!found) {
    for (auto &item : GLOBAL_TABLE) {
      if (item->__Name == attr_name) {
        address = item->__Address;
        found = true;
        break;
      }
    }
  }

  if (!found) {
    MerDebug_print_error(COMPILER_ERROR, "Error cannot found attribute while compiling", glb.file, ast->true_line);
  }

  mCode_T result = NULL_CODE;
  PUSH(result, CSTORE_ATTR);
  PUSH(result, address);

  return result;
}

MERCURY_API mCode_T MerCompiler_make_store_attribute_extract(mAST_T *ast, __compiler_u &glb) {
  Mer_real_string attr_name = ast->extract_name;
  Mer_uint8_t address = NULL_UINT_8_T;
  bool found = false;

  for (auto &item : LOCAL_TABLE) {
    if (item->__Name == attr_name) {
      address = item->__Address;
      found = true;
      break;
    }
  }

  if (!found) {
    for (auto &item : GLOBAL_TABLE) {
      if (item->__Name == attr_name) {
        address = item->__Address;
        found = true;
        break;
      }
    }
  }

  if (!found) {
    MerDebug_print_error(COMPILER_ERROR, "Error cannot found attribute while compiling", glb.file, ast->true_line);
  }

  if (ast->is_value_extract) {
    MerDebug_print_error(COMPILER_ERROR, "Error attribute cannot be value", glb.file, ast->true_line);
  }

  mCode_T index = MerCompiler_compile_ast_id(ast->extract_value, glb);

  if (ast->is_mul_extract) {

  }

  return NULL_CODE;
}

MERCURY_API mCode_T MerCompiler_compile_ast_attribute_expression_load_attribute(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;

  Mer_real_string identifer = ast->string_iden;
  Mer_uint8_t address = NULL_UINT_8_T;
  bool found = false;

  for (auto &item : LOCAL_TABLE) {
    if (item->__Name == identifer) {
      address = item->__Address;
      found = true;
      break;
    }
  }

  if (!found) {
    for (auto &item : GLOBAL_TABLE) {
      if (item->__Name == identifer) {
        address = item->__Address;
        found = true;
        break;
      }
    }
  }

  if (!found) {
    MerDebug_print_error(COMPILER_ERROR, "Error cannot found attribute while compiling", glb.file, ast->true_line);
  }

  PUSH(result, CLOAD_ATTR);
  PUSH(result, address);

  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_attribute_expression_call_method(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;

  Mer_uint8_t address;
  Mer_bool found = false;
  Mer_string name = strdup(ast->func_call.c_str());
  __global *func;
  for (auto &item : LOCAL_TABLE) {
    if (item->__name == name && !item->is_let) {
      address = item->__Address;
      found = true;
      func = item;
      break;
    }
  }

  if (!found) {
    for (auto &item : GLOBAL_TABLE) {
      if (item->__name == name && !item->is_let) {
        address = item->__Address;
        found = true;
        func = item;
        break;
      }
    }
  }

  if (!found) {
    Mer_real_string str = ast->func_call.c_str();
    Mer_real_string msg = "Attribute not found '" + str + "'";
    MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
    return NULL_CODE;
  }

  Mer_size_t args_size = 0;
  if (ast->is_having_args) {
    for (auto child : ast->args) {
      mCode_T _code = MerCompiler_compile_ast_id(child, glb);
      INSERT_VEC(result, _code);
      _code.prg_code.buff.clear();
      ++args_size;
    }
  }

  if (args_size > func->true_args_size) {
    Mer_real_string str = ast->func_call.c_str();
    Mer_real_string msg = "Too many arguments for function '" + str + "'";
    MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
  } else if (args_size < func->true_args_size) {
    Mer_real_string str = ast->func_call.c_str();
    Mer_real_string msg = "Not enough arguments for function '" + str + "'";
    MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
  }

  PUSH(result, CLOAD_ATTR);
  PUSH(result, address);
  PUSH(result, CCALL_METHOD);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_function_call] [pass]" << endl;
  #endif

  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_attribute_expression_get_item(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T index = MerCompiler_compile_ast_id(ast->extract_value, glb);

  if (ast->is_value_extract) {
    MerDebug_print_error(COMPILER_ERROR, "Error attribute cannot be value", glb.file, ast->true_line);
  }

  Mer_real_string identifer = ast->extract_name;
  Mer_uint8_t address = NULL_UINT_8_T;
  bool found = false;
  
  for (auto &item : LOCAL_TABLE) {
    if (item->__Name == identifer) {
      address = item->__Address;
      found = true;
      break;
    }
  }

  if (!found) {
    for (auto &item : GLOBAL_TABLE) {
      if (item->__Name == identifer) {
        address = item->__Address;
        found = true;
        break;
      }
    }
  }

  if (!found) {
    MerDebug_print_error(COMPILER_ERROR, "Error cannot found attribute while compiling", glb.file, ast->true_line);
  }

  PUSH(result, CLOAD_ATTR);
  PUSH(result, address);

  INSERT_VEC(result, index);
  PUSH(result, CGET_ITEM);

  if (ast->is_mul_extract) {
    for (auto &item : ast->mul_extract) {
      mCode_T _code = MerCompiler_compile_ast_id(item, glb);
      INSERT_VEC(result, _code);
      PUSH(result, CGET_ITEM);
    }
  }

  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_attribute_expression(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = MerCompiler_compile_ast_id(ast->attr, glb);

  for (auto it = ast->attrs.begin(); it != ast->attrs.end(); it++) {
    mAST_T *attr = *it;

    if (attr->type == Identifier_) {
      mCode_T code = MerCompiler_compile_ast_attribute_expression_load_attribute(attr, glb);
      INSERT_VEC(result, code);
    } else if (attr->type == FunctionCallExpression) {
      mCode_T code = MerCompiler_compile_ast_attribute_expression_call_method(attr, glb);
      INSERT_VEC(result, code);
    } else if (attr->type == ExtractExpression) {
      mCode_T code = MerCompiler_compile_ast_attribute_expression_get_item(attr, glb);
      INSERT_VEC(result, code);
    } else {
      MerDebug_print_error(COMPILER_ERROR, "Invalid attribute expression", glb.file, attr->true_line);
    }
  }

  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_store_attribute_statement(mAST_T *ast, __compiler_u &glb) {
  mAST_T *attr = ast->attr_store;
  mAST_T *assign = ast->attr_store_value;

  mCode_T store_value = MerCompiler_compile_ast_id(assign, glb);
  mCode_T result = MerCompiler_compile_ast_id(attr->attr, glb);

  for (auto it = attr->attrs.begin(); it != attr->attrs.end() - 1; it++) {
    mAST_T *attr = *it;

    if (attr->type == Identifier_) {
      mCode_T code = MerCompiler_compile_ast_attribute_expression_load_attribute(attr, glb);
      INSERT_VEC(result, code);
    } else if (attr->type == FunctionCallExpression) {
      mCode_T code = MerCompiler_compile_ast_attribute_expression_call_method(attr, glb);
      INSERT_VEC(result, code);
    } else if (attr->type == ExtractExpression) {
      mCode_T code = MerCompiler_compile_ast_attribute_expression_get_item(attr, glb);
      INSERT_VEC(result, code);
    } else {
      MerDebug_print_error(COMPILER_ERROR, "Invalid attribute expression", glb.file, attr->true_line);
    }
  }

  mAST_T *value = *(attr->attrs.end() - 1);

  INSERT_VEC(result, store_value);

  if (value->type == Identifier_) {
    mCode_T code = MerCompiler_make_store_attribute(value, glb);
    INSERT_VEC(result, code);
  }

  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_class_statement(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;

  Mer_uint8_t class_address = create_label(glb);     
  
  __global* class_glb = CREAT_GLOBAL_TABLE(class_address, ast->class_name.c_str(), ast->class_name);
  class_glb->is_let = false;

  GLOBAL_TABLE.push_back(class_glb);

  glb.is_in_func = true;
  glb.is_in_class = true;

  PUSH(result, CCLASS_BEGIN);
  PUSH(result, class_address);

  for (auto &item : ast->members) {
    mCode_T code = MerCompiler_compile_ast_id(item, glb);

    if (is_ast_expression(item->type)) {
      PUSH(code, CPOP_TOP);
    }

    INSERT_VEC(result, code);
  }
  
  PUSH(result, CCLASS_END);

  glb.is_in_func = false;

  return result;

}

MERCURY_API mCode_T MerCompiler_compile_ast_define_expression(mAST_T *ast, __compiler_u &glb) {
  bool found = false;
  mCode_T code = NULL_CODE;
  for (auto &item : code_s) {
    if (item.name == ast->string_iden) {
      found = true;
      code = item.code;
      break;
    }
  }

  if (!found) {
    string msg = ast->string_iden + " not defined";
    MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
  }

  return code;
}

MERCURY_API mCode_T MerCompiler_compile_ast_define(mAST_T *ast, __compiler_u &glb) {
  mCode_T code = MerCompiler_compile_ast_id(ast->define_val, glb);
  code_s.push_back(code_stack {create_label(glb), ast->string_iden, code});
  return NULL_CODE;
}

MERCURY_API mCode_T MerCompiler_compile_ast_id_expression_statment(mAST_T *ast, __compiler_u &glb) {
  
  mCode_T code = NULL_CODE;
  const char* file = ast->file.c_str();
  code.cfile = file;

  mAST_T *root;
  if (ast->children[0]->type == ExpressionStatement) {
    root = ast->children[0];
  }

  PUSH(code, CPROGRAM_START);
  
  for (auto child : root->children) {
    mCode_T _code = MerCompiler_compile_ast_id(child, glb);
    INSERT_VEC(code, _code);
  }

  PUSH(code, CPROGRAM_END);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_id_expression_statment] [pass]" << endl;
  #endif
  return code;
}

MERCURY_API mCode_T MerCompiler_compile_ast_import(mAST_T *ast, __compiler_u &glb) {
  string path = ast->string_iden;

  if (glb.is_in_func) {
    MerDebug_print_error(COMPILER_ERROR, "Can not import in function", glb.file, ast->true_line);
  }

  for (auto &item : import) {
    if (item == path) {
      MerDebug_print_error(COMPILER_ERROR, "File already imported", glb.file, ast->true_line);
    }
  }

  import.push_back(path);

  vector<string> paths = list_files_in_folder("C:\\MercuryLang\\Libs");
  char *buff;
  bool found = false;
  for (auto &item : paths) {
    if (item == path) {
      path = "C:\\MercuryLang\\Libs\\" + item;
      buff = MerBuffer_read_file(path);
      found = true;
      break; 
    }
  }

  if (!found) {
    paths = list_folder("C:\\MercuryLang\\Libs\\__Libs__");
    for (auto &item : paths) {
      if (item == path) {
        path = "C:\\MercuryLang\\Libs\\__Libs__\\" + item + "\\main.mer";
        buff = MerBuffer_read_file(path);
        import.push_back(path);
        found = true;
        break; 
      }
    }

    if (!found) {
      MerDebug_print_error(COMPILER_ERROR, "File not found, make sure it exists in ..\\MercuryLang\\Libs or ..\\MercuryLang\\Libs\\__Libs__", glb.file, ast->true_line);
    }
  }

  mLexer_T *lexer = _MerLexer_init(buff);
  mParser_T *parser = _MerParser_init(lexer);
  mAST_T *new_ast = MerParser_parse_program(parser);
  mCode_T code = NULL_CODE;

  mAST_T *root;
  if (new_ast->children[0]->type == ExpressionStatement) {
    root = new_ast->children[0];
  }

  for (auto child : root->children) {
    mCode_T _code = MerCompiler_compile_ast_id(child, glb);
    INSERT_VEC_TO_OUTCODE_AND_PROG_CODE(code, _code);
    _code.prg_code.buff.clear();
  }
  
  return code;
}

MERCURY_API mCode_T MerCompiler_compile_ast_include(mAST_T *ast, __compiler_u &glb) {
  string path = ast->string_iden;
  if (glb.is_in_func) {
    MerDebug_print_error(COMPILER_ERROR, "Can not include in function", glb.file, ast->true_line);
  }

  for (auto &item : import) {
    if (item == path) {
      MerDebug_print_error(COMPILER_ERROR, "File already imported", glb.file, ast->true_line);
    }
  }

  // check if file is .mer
  if (path.find(".mer") == string::npos) {
    MerDebug_print_error(COMPILER_ERROR, "Include file must be .mer", glb.file, ast->true_line);
  }

  import.push_back(path);
  char* buff = MerBuffer_read_file(path);

  mLexer_T *lexer = _MerLexer_init(buff);
  mParser_T *parser = _MerParser_init(lexer);
  mAST_T *new_ast = MerParser_parse_program(parser);
  mCode_T code = NULL_CODE;

  mAST_T *root;
  if (new_ast->children[0]->type == ExpressionStatement) {
    root = new_ast->children[0];
  }

  for (auto child : root->children) {
    mCode_T _code = MerCompiler_compile_ast_id(child, glb);
    INSERT_VEC_TO_OUTCODE_AND_PROG_CODE(code, _code);
    _code.prg_code.buff.clear();
  }
  
  return code;
}


MERCURY_API mCode_T MerCompiler_compile_ast_or_expression(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T left = MerCompiler_compile_ast_id(ast->left, glb);
  mCode_T right = MerCompiler_compile_ast_id(ast->right, glb);
  INSERT_VEC(result, left);
  INSERT_VEC(result, right);
  PUSH(result, COR);
  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_function_call_with_args(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T args = NULL_CODE;
  
  Mer_uint8_t address = NULL_UINT_8_T;
  Mer_uint8_t args_size = NULL_UINT_8_T;
  bool found = false;
  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__Name == ast->func_call) {
      address = item->__Address;
      args_size = item->args_size;
      found = true;
      break;
    }
  }

  if (!found) {
    MerDebug_print_error(COMPILER_ERROR, "Error cannot found global function while compiling", glb.file, ast->true_line);
  }


  for (auto &item : ast->args) {
    mCode_T _code = MerCompiler_compile_ast_id(item, glb);
    INSERT_VEC(args, _code);
    _code.prg_code.buff.clear();
  }

  INSERT_VEC(result, args);
  PUSH(result, CFUNCTION_CALL_WITH_ARGS);
  PUSH(result, address);
  PUSH(result, args_size);

  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_not_expression(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = MerCompiler_compile_ast_id(ast->not_expr, glb);
  PUSH(result, CNOT);
  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_and_expression(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T left = MerCompiler_compile_ast_id(ast->left, glb);
  mCode_T right = MerCompiler_compile_ast_id(ast->right, glb);
  
  INSERT_VEC(result, left);
  INSERT_VEC(result, right); 

  PUSH(result, CAND);
  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_function_with_args(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T body = NULL_CODE;
  Mer_uint8_t size = ast->args_idens.size();
  Mer_uint8_t func_address = create_label(glb);
  
  for (auto &node : ast->args_idens) {
    Mer_uint8_t address = create_label(glb);
    GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(address, node.c_str(), node));
  }

  __global *func_glb = CREAT_GLOBAL_TABLE(func_address, ast->func_name.c_str(), ast->func_name);
  func_glb->args_size = size;
  GLOBAL_TABLE.push_back(func_glb);

  for (auto &node : ast->body) {
    mCode_T _code = MerCompiler_compile_ast_id(node, glb);
    INSERT_VEC(body, _code);
    _code.prg_code.buff.clear();
  }

  PUSH(result, CMAKE_FUNCTION_WITH_ARGS);
  PUSH(result, func_address);
  PUSH(result, size);

  INSERT_VEC(result, body);

  PUSH(result, CRETURN);
  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_true(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  PUSH(result, CLOAD_TRUE);
  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_false(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  PUSH(result, CLOAD_FALSE);
  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_break(mAST_T *ast, __compiler_u &glb) {
    mCode_T result = NULL_CODE;
    if (glb.loop.empty()) {
        MerDebug_print_error(COMPILER_ERROR, "break outside of loop", glb.file, ast->true_line);
        return result;
    }

    PUSH(result, CJUMP_TO);
    PUSH(result, glb.loop.back().break_label);
    return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_continue(mAST_T *ast, __compiler_u &glb) {
    mCode_T result = NULL_CODE;
    if (glb.loop.empty()) {
        MerDebug_print_error(COMPILER_ERROR, "continue outside of loop", glb.file, ast->true_line);
        return result;
    }

    PUSH(result, CJUMP_TO);
    PUSH(result, glb.loop.back().continue_label);
    return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_loop(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T body = NULL_CODE;
  mCode_T _code = NULL_CODE;

  Mer_uint8_t label_start = create_label(glb);
  Mer_uint8_t label_end = create_label(glb);
  glb.loop.push_back(loop_stack { label_start, label_end });

  for (auto &node : ast->do_body) {
    _code = MerCompiler_compile_ast_id(node, glb);

    if (is_ast_expression(node->type)) {
      PUSH(_code, CPOP_TOP);
    }

    INSERT_VEC(body, _code);
    _code.prg_code.buff.clear();
  }

  PUSH(result, CADDRESS);
  PUSH(result, label_start);
  
  INSERT_VEC(result, body);
  PUSH(result, CJUMP_TO);
  PUSH(result, label_start); 

  PUSH(result, CADDRESS);
  PUSH(result, label_end);

  glb.loop.pop_back();

  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_store_index_statement(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T mul_extract = NULL_CODE;
  mCode_T value = MerCompiler_compile_ast_id(ast->array_store_value, glb);
  mCode_T index = MerCompiler_compile_ast_id(ast->array_store->extract_value, glb);

  Mer_uint8_t list_address = NULL_UINT_8_T;  
  Mer_real_string list_name = ast->array_store->extract_name.c_str();

  bool found = false;
  for (auto &global : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (global->__name == ast->array_store->extract_name) {
      list_address = global->__Address;
      found = true;
      break;
    }
  }

  if (!found) {
    MerDebug_print_error(COMPILER_ERROR, "List not found, can not store value in list", glb.file, ast->true_line);
  }

  if (ast->array_store->is_mul_extract) {
      PUSH(result, CLOAD_GLOBAL);
      PUSH(result, list_address);

      INSERT_VEC(result, index);
      PUSH(result, CGET_ITEM);

      size_t size = ast->array_store->mul_extract.size();
      size_t id = 0;

      for (auto &node : ast->array_store->mul_extract) {
          mul_extract = MerCompiler_compile_ast_id(node, glb);

          if (id < size - 1) {
              INSERT_VEC(result, mul_extract);
              PUSH(result, CGET_ITEM);
          } else {
              INSERT_VEC(result, mul_extract);
          }

          id++;
      }

      INSERT_VEC(result, value);
      PUSH(result, CSTORE_INDEX);

      return result;
  }

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, list_address);

  INSERT_VEC(result, index);

  INSERT_VEC(result, value);
  PUSH(result, CSTORE_INDEX);

  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_extract(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;

  bool found = false;
  Mer_uint8_t list_address = NULL_UINT_8_T;

  if (ast->is_value_extract) {
    mCode_T value = MerCompiler_compile_ast_id(ast->extract_value, glb);
    mCode_T result = NULL_CODE;
    mCode_T index = NULL_CODE;

    INSERT_VEC(result, value);

    for (auto &item : ast->mul_extract) {
      mCode_T _code = MerCompiler_compile_ast_id(item, glb);
      INSERT_VEC(result, _code);
      PUSH(result, CGET_ITEM);
    }

    return result;
  }

  for (auto &global : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (global->__name == ast->extract_name) {
      found = true;
      list_address = global->__Address;
      break;
    }
  }

  if (!found) {
    MerDebug_print_error(COMPILER_ERROR, "List not found, can not extract value from list", glb.file, ast->true_line);
  }

  mCode_T _code = MerCompiler_compile_ast_id(ast->extract_value, glb);
  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, list_address);

  INSERT_VEC(result, _code);
  PUSH(result, CGET_ITEM);

  if (ast->is_mul_extract) {
    for (auto &item : ast->mul_extract) {
      mCode_T _code = MerCompiler_compile_ast_id(item, glb);
      INSERT_VEC(result, _code);
      PUSH(result, CGET_ITEM);
    }
  }

  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_array(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T array = NULL_CODE;

  if (ast->type != ArrayExpression) {
    MerDebug_print_error(COMPILER_ERROR, "Invalid creating array", glb.file, ast->true_line);
  }
  
  if (!ast->is_alone_val) {
    MerDebug_print_error(COMPILER_ERROR, "Invalid creating array", glb.file, ast->true_line);
  }

  Mer_uint8_t size = ast->list.size();

  for (auto &item : ast->list) {
    mCode_T _code = MerCompiler_compile_ast_id(item, glb);
    INSERT_VEC(array, _code);
  }

  INSERT_VEC(result, array);
  PUSH(result, CBUILD_LIST);
  PUSH(result, size);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_array] [pass]" << endl;
  #endif
  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_list(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T list = NULL_CODE;

  if (ast->type != ListStatement) {
    MerDebug_print_error(COMPILER_ERROR, "Invalid creating list", glb.file, ast->true_line);
  }

  Mer_uint8_t size = ast->list.size();
  Mer_uint8_t address = create_label(glb);

  for (auto &item : ast->list) {
    mCode_T _code = MerCompiler_compile_ast_id(item, glb);
    INSERT_VEC(list, _code);
  }

  INSERT_VEC(result, list);
  PUSH(result, CBUILD_LIST);
  PUSH(result, size);
  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, address);

  GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(address, ast->list_name.c_str(), ast->list_name));

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_list] [pass]" << endl;
  #endif
  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_string_identifier(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T str = NULL_CODE;
  
  if (ast->type != StringIdentifier) {
    MerDebug_print_error(COMPILER_ERROR, "Invalid creating string identifier", glb.file, ast->true_line);
  }

  Mer_uint8_t size = ast->str_v.size();
  
  vector<Mer_uint8_t> str_v;
  for (auto &item : ast->str_v) {
    str_v.push_back(item);
  }

  str.prg_code.buff.insert(str.prg_code.buff.end(), str_v.begin(), str_v.end());

  PUSH(result, CPUSH_NORMAL_MODE);
  PUSH(result, size);
  INSERT_VEC(result, str);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_string_identifier] [pass]" << endl;
  #endif
  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_assign(mAST_T *ast, __compiler_u &glb) {
  mCode_T _ass = NULL_CODE;
  if (!ast->assign_value) {
    MerDebug_print_error(COMPILER_ERROR, "Invalid assign statement", glb.file, ast->true_line);
  }

  mCode_T result = NULL_CODE;
  Mer_uint8_t address;
  bool found = false;

  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__name == ast->assign_iden) {
      address = item->__Address;
      found = true;
      break;
    }
  }

  if (!found) {
    address = create_label(glb);
    glb.is_in_func ? LOCAL_TABLE.push_back(CREAT_LOCAL_TABLE(address, ast->assign_iden.c_str(), ast->assign_iden)) : GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(address, ast->assign_iden.c_str(), ast->assign_iden));
  }

  if (ast->is_assign_operator) {
    if (!found) {
      MerDebug_print_error(COMPILER_ERROR, "Variable not found, can not assign to it", glb.file, ast->true_line);
    }

    Mer_uint8_t opcode = NULL_UINT_8_T;
    if (ast->is_plus_assign) {
      opcode = CBINARY_ADD;
    } else if (ast->is_minus_assign) {
      opcode = CBINARY_SUB;
    } else if (ast->is_mul_assign) {
      opcode = CBINARY_MUL;
    } else if (ast->is_div_assign) {
      opcode = CBINARY_DIV;
    } else if (ast->is_mod_assign) {
      opcode = CBINARY_MOD;
    } else {
      MerDebug_system_error(COMPILER_ERROR, "Invalid assign operator", glb.file);
    }

    PUSH(_ass, CLOAD_GLOBAL);
    PUSH(_ass, address);

    mCode_T _code = MerCompiler_compile_ast_id(ast->assign_value, glb);
    INSERT_VEC(_ass, _code);

    PUSH(_ass, opcode);

    INSERT_VEC(result, _ass);
    PUSH(result, CSTORE_GLOBAL);
    PUSH(result, address);
  } else {
    _ass = MerCompiler_compile_ast_id(ast->assign_value, glb);
    INSERT_VEC(result, _ass);
    PUSH(result, CSTORE_GLOBAL);
    PUSH(result, address);
  }

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_assign] [pass]" << endl;
  #endif
  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_while(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T while_cond = MerCompiler_compile_ast_id(ast->while_cond, glb);
  mCode_T while_body = NULL_CODE;
  mCode_T _code = NULL_CODE;

  Mer_uint8_t while_begin = create_label(glb);
  Mer_uint8_t while_end = create_label(glb);

  glb.loop.push_back(loop_stack { while_begin, while_end });

  for (auto child : ast->while_body) {
    _code = MerCompiler_compile_ast_id(child, glb);

    if (is_ast_expression(child->type)) {
      PUSH(_code, CPOP_TOP);
    }

    INSERT_VEC(while_body, _code);
    _code.prg_code.buff.clear();
  }

  PUSH(result, CADDRESS);
  PUSH(result, while_begin);

  INSERT_VEC(result, while_cond);

  PUSH(result, CPOP_JUMP_IF_FALSE);
  PUSH(result, while_end);

  INSERT_VEC(result, while_body);

  PUSH(result, CJUMP_TO);
  PUSH(result, while_begin);

  PUSH(result, CADDRESS);
  PUSH(result, while_end);

  glb.loop.pop_back();

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_while] [pass]" << endl;
  #endif
  
  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_for_in_statement(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T for_body = NULL_CODE;
  mCode_T for_loop_iter = NULL_CODE;

  bool found = false;

  Mer_uint8_t __iter = create_label(glb);
  Mer_uint8_t __i = create_label(glb);
  Mer_uint8_t __value = create_label(glb);

  Mer_uint8_t loop_start = create_label(glb);
  Mer_uint8_t loop_end = create_label(glb);

  glb.loop.push_back(loop_stack { loop_start, loop_end });

  GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(__iter, __iter__, __iter__));
  GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(__i, __i__, __i__));

  LOCAL_TABLE.push_back(CREAT_LOCAL_TABLE(__iter, __iter__, __iter__));
  LOCAL_TABLE.push_back(CREAT_LOCAL_TABLE(__i, __i__, __i__));


  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__name == ast->in_iden) {
      __value = item->__Address;
      found = true;
      break;
    }
  }

  if (!found) {
    GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(__value, ast->in_iden.c_str(), ast->in_iden));
    LOCAL_TABLE.push_back(CREAT_LOCAL_TABLE(__value, ast->in_iden.c_str(), ast->in_iden));
  }

  for (auto child : ast->in_body) {
    mCode_T _code = MerCompiler_compile_ast_id(child, glb);

    if (is_ast_expression(child->type)) {
      PUSH(_code, CPOP_TOP);
    }

    INSERT_VEC(for_body, _code);
    _code.prg_code.buff.clear();
  }

  for_loop_iter = MerCompiler_compile_ast_id(ast->in_value, glb);

  INSERT_VEC(result, for_loop_iter);
  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, __iter);

  PUSH(result, CPUSH_FLOAT);
  PUSH(result, 0x00);
  PUSH(result, 0x00);
  PUSH(result, 0x00);
  PUSH(result, 0x00);

  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, __i);

  PUSH(result, CADDRESS);
  PUSH(result, loop_start);

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, __i);

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, __iter);

  PUSH(result, CLEN);
  
  PUSH(result, CLESS);

  PUSH(result, CPOP_JUMP_IF_FALSE);
  PUSH(result, loop_end);

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, __iter);

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, __i);

  PUSH(result, CGET_ITEM);

  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, __value);

  INSERT_VEC(result, for_body);

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, __i);

  PUSH(result, CPUSH_FLOAT);
  PUSH(result, 0x00);
  PUSH(result, 0x00);
  PUSH(result, 0x80);
  PUSH(result, 0x3F);

  PUSH(result, CBINARY_ADD);

  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, __i);

  PUSH(result, CJUMP_TO);
  PUSH(result, loop_start);

  PUSH(result, CADDRESS);
  PUSH(result, loop_end);

  glb.loop.pop_back();  

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_for_in_statement] [pass]" << endl;
  #endif
  
  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_literal(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  Mer_uint8_t cval[sizeof(float)];

  memcpy(cval, &ast->value, sizeof(float));
  result.prg_code.buff.push_back(CPUSH_FLOAT);
  result.prg_code.buff.insert(result.prg_code.buff.end(), cval, cval + sizeof(float));

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_literal] [pass]" << endl;
  #endif
  return result;  
}

MERCURY_API mCode_T MerCompiler_compile_ast_binary_expression(mAST_T *ast, __compiler_u &glb) {
  mCode_T _left = MerCompiler_compile_ast_id(ast->left, glb);
  mCode_T _right = MerCompiler_compile_ast_id(ast->right, glb);

  Mer_uint8_t _oper;
  if (ast->op == PLUS)           _oper = CBINARY_ADD;
  else if (ast->op == MINUS)     _oper = CBINARY_SUB;
  else if (ast->op == DIV)       _oper = CBINARY_DIV;
  else if (ast->op == MOD)       _oper = CBINARY_MOD;
  else if (ast->op == TIME)      _oper = CBINARY_MUL;
  else if (ast->op == POW)       _oper = CBINARY_POW;

  mCode_T result = NULL_CODE;
  
  INSERT_VEC(result, _left);
  INSERT_VEC(result, _right);
  PUSH(result, _oper);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_binary_expression] [pass]" << endl;
  #endif

  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_function_call(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;

  Mer_uint8_t address;
  Mer_bool found = false;
  Mer_string name = strdup(ast->func_call.c_str());
  __global *func;
  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__name == name && !item->is_let) {
      address = item->__Address;
      found = true;
      func = item;
      break;
    }
  }

  if (!found) {
    for (auto &item : GLOBAL_TABLE) {
      if (item->__name == name && !item->is_let) {
        address = item->__Address;
        found = true;
        func = item;
        break;
      }
    }
  }

  if (!found) {
    Mer_real_string str = ast->func_call.c_str();
    if (str == "print") {
      Mer_real_string msg = "Function not found '" + str + "', you forgot to import \"IO\"?";
      MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
    }
    Mer_real_string msg = "Function not found '" + str + "'";
    MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
    return NULL_CODE;
  }

  Mer_size_t args_size = 0;
  if (ast->is_having_args) {
    for (auto child : ast->args) {
      mCode_T _code = MerCompiler_compile_ast_id(child, glb);
      INSERT_VEC(result, _code);
      _code.prg_code.buff.clear();
      ++args_size;
    }
  }

  if (is_a_builtin(ast->func_call)) {
    // do nothing
  } else if (args_size > func->true_args_size) {
    Mer_real_string str = ast->func_call.c_str();
    Mer_real_string msg = "Too many arguments for function '" + str + "'";
    MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
  } else if (args_size < func->true_args_size) {
    Mer_real_string str = ast->func_call.c_str();
    Mer_real_string msg = "Not enough arguments for function '" + str + "'";
    MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
  }

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, address);
  PUSH(result, CFUNCTION_CALL);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_function_call] [pass]" << endl;
  #endif

  return result;    
}

MERCURY_API mCode_T MerCompiler_compile_ast_if(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T comp = NULL_CODE;
  mCode_T if_body = NULL_CODE;
  mCode_T else_body = NULL_CODE;
  
  comp = MerCompiler_compile_ast_id(ast->comp, glb);
  
  if (!ast->comp) {
    MerDebug_print_error(COMPILER_ERROR, "Invalid if statement", glb.file, ast->true_line);
  }

  Mer_uint8_t end_if = create_label(glb);
  Mer_uint8_t label_else = create_label(glb);

  for (auto child : ast->then_body) {
    mCode_T _code = MerCompiler_compile_ast_id(child, glb);
    INSERT_VEC(if_body, _code);
    _code.prg_code.buff.clear();
  }

  INSERT_VEC(result, comp);
  
  PUSH(result, CPOP_JUMP_IF_FALSE);
  PUSH(result, label_else);

  INSERT_VEC(result, if_body);
  
  PUSH(result, CJUMP_TO);
  PUSH(result, end_if);

  PUSH(result, CADDRESS);
  PUSH(result, label_else);

  if (ast->has_elif) {
    for (auto &child : ast->elif_body) {
      mCode_T elifcomp = MerCompiler_compile_ast_id(child->comp, glb);
      mCode_T elifbody = NULL_CODE;

      for (auto child : child->then_body) {
        mCode_T _code = MerCompiler_compile_ast_id(child, glb);
        INSERT_VEC(elifbody, _code);
        _code.prg_code.buff.clear();
      }

      label_else = create_label(glb);

      INSERT_VEC(result, elifcomp);
      
      PUSH(result, CPOP_JUMP_IF_FALSE);
      PUSH(result, label_else);
      
      INSERT_VEC(result, elifbody);
      
      PUSH(result, CJUMP_TO);
      PUSH(result, end_if);
    }
  }

  PUSH(result, CADDRESS);
  PUSH(result, label_else);
  
  if (ast->has_else) {
    for (auto child : ast->else_body) {
      mCode_T _code = MerCompiler_compile_ast_id(child, glb);
      INSERT_VEC(else_body, _code);
      _code.prg_code.buff.clear();
    }

    INSERT_VEC(result, else_body);
  }

  PUSH(result, CADDRESS);
  PUSH(result, end_if);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_if] [pass]" << endl;
  #endif
  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_let(mAST_T *ast, __compiler_u &glb) {
  Mer_string name = strdup(ast->var_name.c_str());
  Mer_real_string real_name = ast->var_name;
  Mer_uint8_t address = NULL_UINT_8_T;
  bool found = false;

  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__name == real_name) {
      found = true;
      address = item->__Address;
    }
  }

  mCode_T var_val = MerCompiler_compile_ast_id(ast->var_value, glb);
  mCode_T result = NULL_CODE;

  if (!found) {
    address = create_label(glb);
    glb.is_in_func ? LOCAL_TABLE.push_back(CREAT_LOCAL_TABLE(address, name, real_name)) : GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(address, name, real_name));
  } else {
    string msg = "Variable '" + ast->var_name + "' already exists in scope";
    MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
  }

  INSERT_VEC(result, var_val);
  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, address);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_let] [pass]" << endl;
  #endif

  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_return(mAST_T *ast, __compiler_u &glb) {
  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_return] [building]" << endl;
  #endif

  if (!glb.is_in_func) {
    MerDebug_print_error(COMPILER_ERROR, "Return outside of function", glb.file, ast->true_line);
  }

  mCode_T result = NULL_CODE;
  mCode_T ret_val = MerCompiler_compile_ast_id(ast->return_v, glb);
  
  INSERT_VEC(result, ret_val);
  PUSH(result, CRETURN);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_return] [pass]" << endl;
  #endif

  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_identifier(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  Mer_uint8_t address;
  Mer_bool found = false;
  Mer_string name = strdup(ast->string_iden.c_str());
  if (name != ast->string_iden) {
    MerDebug_print_error(COMPILER_ERROR, "Invalid variable name", glb.file, ast->true_line);
  }

  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__name == name && item->is_let) {
      address = item->__Address;
      found = true;
      break;
    }
  }

  if (!found) {
    for (auto &item : GLOBAL_TABLE) {
      if (item->__name == name && !item->is_let) {
        address = item->__Address;
        found = true;
        break;
      }
    }
  }

  if (!found) {
    string msg = "Variable not found '" + ast->string_iden + "'";
    MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
    return NULL_CODE;
  }

  PUSH(result, CLOAD_GLOBAL);
  PUSH(result, address);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_identifier] [pass]" << endl;
  #endif
  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_program(mAST_T *ast, __compiler_u &glb) {
  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_program] [start]" << endl;
  #endif

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_program] [pass]" << endl;
  #endif

  return MerCompiler_compile_ast_id_expression_statment(ast, glb);
}

MERCURY_API mCode_T MerCompiler_compile_ast_string_var(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  Mer_string name = strdup(ast->str_var_name.c_str());
  Mer_real_string real_name = ast->str_var_name;
  glb.address += 0x0001;

  mCode_T str_val = MerCompiler_compile_ast_id(ast->str_var_value, glb);
  GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(glb.address, name, real_name));

  INSERT_VEC(result, str_val);
  PUSH(result, CSTORE_GLOBAL);
  PUSH(result, glb.address);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_string_var] [pass]" << endl;
  #endif

  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_function(mAST_T *ast, __compiler_u &glb) {
  mCode_T result = NULL_CODE;
  mCode_T body = NULL_CODE;
  Mer_uint8_t func_address = create_label(glb);
  Mer_real_string name = ast->func_name;
  Mer_string func_name = strdup(ast->func_name.c_str());
  Mer_uint8_t args_size = ast->args_size;
  size_t index_of_this = 0;

  for (auto &item : glb.is_in_func ? LOCAL_TABLE : GLOBAL_TABLE) {
    if (item->__name == func_name) {
      Mer_real_string msg = "Function already defined: '" + ast->func_name + "'";
      MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
    }
  }

  if (glb.is_in_class) {
    string this_name = "this";

    for (auto &item : LOCAL_TABLE) {
      if (item->__name == this_name) {
        Mer_real_string msg = "Function already defined: '" + ast->func_name + "'";
        MerDebug_print_error(COMPILER_ERROR, msg.c_str(), glb.file, ast->true_line);
      }
    }

    LOCAL_TABLE.push_back(CREAT_LOCAL_TABLE(0x00, this_name.c_str(), this_name));
    index_of_this = LOCAL_TABLE.size() - 1;
  }

  __global *glb_tab = CREAT_GLOBAL_TABLE(func_address, func_name, name);
  glb_tab->is_let = false; 
  glb_tab->args_size = args_size;

  vector<int> clear_index;

  if (ast->is_having_args) {
    for (auto &item : ast->args_idens) {
      LOCAL_TABLE.push_back(CREAT_LOCAL_TABLE(create_para(glb), item.c_str(), item));
      ++glb_tab->true_args_size;
      clear_index.push_back(LOCAL_TABLE.size() - 1);
    }
  }

  GLOBAL_TABLE.push_back(glb_tab);

  glb.is_in_func = true;
  for (auto child : ast->body) {
    mCode_T _code = MerCompiler_compile_ast_id(child, glb);

    if (is_ast_expression(child->type)) {
      PUSH(_code, CPOP_TOP);
    }

    INSERT_VEC(body, _code);
    _code.prg_code.buff.clear();
  }
  glb.is_in_func = false;

  PUSH(result, CMAKE_FUNCTION);
  
  PUSH(result, func_address);
  PUSH(result, args_size);

  INSERT_VEC(result, body);
  
  PUSH(result, CEND_FUNCTION);

  for (auto index : clear_index) {
    LOCAL_TABLE.erase(LOCAL_TABLE.begin() + index);
  }

  glb.para_address = NULL_UINT_8_T;

  LOCAL_TABLE.erase(LOCAL_TABLE.begin() + index_of_this);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_function] [pass]" << endl;
  #endif

  return result;
}

MERCURY_API mCode_T MerCompiler_compile_ast_comparison_expression(mAST_T *ast, __compiler_u &glb) {
  mCode_T _left = MerCompiler_compile_ast_id(ast->comp_left, glb);
  mCode_T _right = MerCompiler_compile_ast_id(ast->comp_right, glb);

  mCode_T result = NULL_CODE;
  Mer_uint8_t _oper;

  if (ast->comp_op == EQUAL) _oper = CEQUAL;
  else if (ast->comp_op == NOT_EQUAL) _oper = CNOT_EQUAL;
  else if (ast->comp_op == LESS) _oper = CLESS;
  else if (ast->comp_op == LESS_EQUAL) _oper = CLESS_EQUAL;
  else if (ast->comp_op == GREATER) _oper = CGREATER;
  else if (ast->comp_op == GREATER_EQUAL) _oper = CGREATER_EQUAL;
  else if (ast->comp_op == IS) _oper = CIS;

  INSERT_VEC(result, _left);
  INSERT_VEC(result, _right);
  PUSH(result, _oper);

  #ifdef SYSTEM_TEST
  cout << "[compiler.cpp] [MerCompiler_compile_ast_comparison_expression] [pass]" << endl;
  #endif

  return result;
}


__program_bytecode init_program_bytecode(mCode_T & code)
{
    __program_bytecode u = {code};
    u.iid = 0;
    u.oid = 0;
    u.icode = 0;
    u.ocode = 0;
    u.loop_size = 0;
    u.is_in_func = false;
    u.hash = 0x00;
    u.label_map = unordered_map<Mer_uint8_t, Mer_size_t>();
    u.glb_id = u.lc_id = 0;
    u.file = "stdin";
    return u;
}

unordered_map<Mer_uint8_t, Mer_size_t> __get_label_map(__program_bytecode &u, string mode) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [__get_label_map] [building...]" << endl;
    #endif

    Mer_uint8_t end = CPROGRAM_END;
    u.is_label = true;

    if (mode == "function") end = CEND_FUNCTION;

    Mer_uint8_t code = next_c(u);

    while (code != end) {
        if (code == CADDRESS) {
            Mer_uint8_t address = next_c(u);
            u.label_map[address] = u.iid;
        }

        code = next_c(u);
    }

    u.iid = 0;

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [__get_label_map] [pass]" << endl;
    #endif

    return u.label_map;
}

MERCURY_API Mer_uint8_t next_c(__program_bytecode &u) {
    return u.code.prg_code.buff[u.iid++];
}

MERCURY_API Mer_uint8_t next_o(__program_bytecode &u) {
    return u.code.out_code.buff[u.oid++];
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_program(mCode_T &code) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_program] [building...]" << endl;
    #endif

    __program_bytecode u_program = init_program_bytecode(code);
    stack *stk = MerCompiler_Stack_new();

    __get_label_map(u_program, "program");

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_program] [pass]" << endl;
    #endif

    return MerVM_evaluate_statement(u_program, stk);
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_statement(__program_bytecode &u, stack *stk) {
#ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_statement] [building...]" << endl;
#endif

    int counter = 0;

    for (;;) {
        Mer_uint8_t code = next_c(u);

        switch (code) {
            case CSTORE_ATTR:
                stk = MerVM_evaluate_STORE_ATTR(u, stk);
                break;
            
            case CCALL_METHOD:
                stk = MerVM_evaluate_CALL_METHOD(u, stk);
                break;

            case CLOAD_ATTR:
                stk = MerVM_evaluate_LOAD_ATTR(u, stk);
                break;

            case CGET_ITEM:
                stk = MerVM_evaluate_GET_ITEM(u, stk);
                break;

            case CSTORE_INDEX:
                stk = MerVM_evaluate_STORE_INDEX(u, stk);
                break;

            case CCLASS_BEGIN:
                stk = MerVM_evaluate_CLASS_BEGIN(u, stk);
                break;

            case CPUSH_FLOAT:
                stk = MerVM_evaluate_PUSH_FLOAT(u, stk);
                break;

            case CPUSH_NORMAL_MODE:
                stk = MerVM_evaluate_PUSH_NORMAL_MODE(u, stk);
                break;

            case CBUILD_LIST:
                stk = MerVM_evaluate_BUILD_LIST(u, stk);
                break;

            case CLOAD_GLOBAL:
                stk = MerVM_evaluate_LOAD_GLOBAL(u, stk);
                break;

            case CSTORE_GLOBAL:
                stk = MerVM_evaluate_STORE_GLOBAL(u, stk);
                break;

            case CMAKE_FUNCTION:
                stk = MerVM_evaluate_MAKE_FUNCTION(u, stk);
                break;

            case CFUNCTION_CALL:
                stk = MerVM_evaluate_FUNCTION_CALL(u, stk);
                break;

            case CBINARY_ADD:
            case CBINARY_SUB:
            case CBINARY_MUL:
            case CBINARY_DIV:
            case CBINARY_MOD:
            case CBINARY_POW:
                stk = MerVM_evaluate_BINARY_OPER(u, stk, code);
                break;

            case CGREATER:
            case CEQUAL:
            case CNOT_EQUAL:
            case CGREATER_EQUAL:
            case CLESS_EQUAL:
            case CLESS:
                stk = MerVM_evaluate_COMPARE(u, stk, code);
                break;

            case CJUMP_TO:
                u.iid = u.label_map[next_c(u)];
                break;

            case CPOP_JUMP_IF_FALSE: {
                table *top = POP();
                Mer_uint8_t address = next_c(u);

                if (IS_FALSE(top->cval)) {
                    u.iid = u.label_map[address];
                }

                push_to_gc(top);
                break;
            }

            case CNOT: {
                table *left = POP();

                if (left->cval) {
                    push_false_to_stack();
                } else {
                    push_true_to_stack();
                }
                break;
            }

            case CIS: {
                table *lhs = POP();
                table *rhs = POP();

                if (lhs == rhs) {
                    push_true_to_stack();
                } else {
                    push_false_to_stack();
                }
                break;
            }

            case CLEN: {
                table *obj = POP();
                push_to_gc(obj);

                if (obj->is_list) {
                    table* size = MER_VALUE(obj->list_v->size);
                    stack_push(size);
                }
                else if (obj->is_str) {
                    table* size = MER_VALUE(obj->f_str_v->size);
                    stack_push(size);
                }
                else {
                    table *size = MER_VALUE(obj->cval);
                    stack_push(size);
                }
                break;
            }

            case CPOP_TOP: {
#ifdef SYSTEM_TEST
                cout << "[ceval.cpp] [CPOP_TOP] [building...]" << endl;
#endif
                table *top = POP();
                push_to_gc(top);
#ifdef SYSTEM_TEST
                cout << "[ceval.cpp] [CPOP_TOP] [pass]" << endl;
#endif
                break;

            }

            case CLOAD_TRUE: {
                push_true_to_stack();
                break;
            }

            case CLOAD_FALSE: {
                push_false_to_stack();
                break;
            }

            case CAND: {
                table *cand_left = POP();
                table *cand_right = POP();

                if (cand_left->cval && cand_right->cval) {
                    push_true_to_stack();
                } else {
                    push_false_to_stack();
                }
                break;
            }

            case COR: {
                table *cor_left = POP();
                table *cor_right = POP();

                if (cor_left->cval || cor_right->cval) {
                    push_true_to_stack();
                } else {
                    push_false_to_stack();
                }
                break;
            }

            case CADDRESS:
                code = next_c(u);
                break;

            case CPROGRAM_START:
                continue;

            case CPROGRAM_END:
                goto program_end;
        }

        if (++counter >= GC_THRESHOLD) {
            GC_collect(GARBAGE_POOL, stk, u.file);
            counter = 0;
        }
    }

program_end:
#ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_statement] [pass]" << endl;
#endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_LOAD_METHOD(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_METHOD] [building...]" << endl;
    #endif

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_METHOD] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_CALL_METHOD(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_CALL_METHOD] [building...]" << endl;
    #endif

    table *func_obj = POP();
    table *class_obj = func_obj->class_p;

    if (!class_obj) {
        MerDebug_system_error(SYSTEM_ERROR, "Error while calling method", u.file);
    }

    if (func_obj->is_func) {
        Mer_uint8_t para_address = 0x00;
        vector<symtable*> _T;

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_CALL_METHOD] [pushing parameters... with size " << func_obj->func_obj_v->args_size << "]" << endl;
        #endif

        for (int i = 0; i < func_obj->func_obj_v->args_size; i++) {
            #ifdef SYSTEM_TEST
            cout << "[ceval.cpp] [MerVM_evaluate_CALL_METHOD] [pushing parameter " << i << " start]" << endl;
            #endif

            table *item = POP();

            #ifdef SYSTEM_TEST
            cout << "[ceval.cpp] [MerVM_evaluate_CALL_METHOD] [pushing parameter " << i << " pass]" << endl;
            #endif

            symtable *parameter = MerCompiler_symboltable_setup("", item->cval, "AUTO_T", NULL_UINT_8_T);  
            parameter->tab = item;
            parameter->tab->address = parameter->address;
            parameter->tab->ref_count++;

            _T.push_back(parameter);
        }

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_CALL_METHOD] [pushing parameters done!]" << endl;
        #endif

        reverse(_T.begin(), _T.end());

        for (auto &item : _T) {
            item->address = ++para_address;
        }

        mCode_T code = NULL_CODE;
        code.prg_code.buff = func_obj->func_obj_v->f_bc->buff;

        CallContext *ctx = new CallContext {
            .code = code,
            .caller = nullptr,
            .return_val = MerCompiler_Table_new(),
            .local = _T
        };

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_CALL_METHOD] [evaluating...]" << endl;
        #endif

        u.is_in_func = true;
        stk = MerVM_evaluate_call_context(ctx, u, stk);
        u.is_in_func = false;

        for (auto &item : ctx->local) {
            if (item->tab) {
                --item->tab->ref_count;
                push_to_gc(item->tab);
            }
        }

        std::vector<symtable*>().swap(ctx->local);
    } else {
        cerr << "Error: Call method is not a function" << endl;
        MER_BREAK_POINT;
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_CALL_METHOD] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_STORE_ATTR(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_STORE_ATTR] [building...]" << endl;
    #endif

    Mer_uint8_t address = next_c(u);

    table* value = POP();
    table* attr = POP();

    value->ref_count++;

    for (auto &item : attr->class_v->methods) {
        symtable *sym_item = (symtable *) item;
        if (sym_item->address == address) {
            if (--sym_item->tab->ref_count < 1) {
                push_to_gc(sym_item->tab);
            }

            sym_item->tab = value;
            sym_item->value = value->cval;
            break;
        }
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_STORE_ATTR] [pass]" << endl;
    #endif
    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_LOAD_ATTR(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_ATTR] [building...]" << endl;
    #endif

    Mer_uint8_t address = next_c(u);
    table *class_obj = POP();

    if (!class_obj->is_class || !class_obj->is_instance) {
        MerDebug_system_error(SYSTEM_ERROR, "Error while loading attribute", u.file);
    } 

    for (auto &item : class_obj->class_v->methods) {
        symtable *sym_item = (symtable *) item;
        if (sym_item->address == address) {
            table *tab = sym_item->tab;
            tab->cval = sym_item->value;
            tab->address = sym_item->address;
            tab->class_p = class_obj;
            stack_push(tab);
            break;
        }
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_ATTR] [pass]" << endl;
    #endif

    return stk;
}

__mer_core_data__ mClass_T *MerVM_class_evaluate_STORE_GLOBAL(__program_bytecode &u, stack *stk, mClass_T *cls) {
#ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_class_evaluate_STORE_GLOBAL] [building...]" << endl;
#endif
    Mer_uint8_t code = next_c(u);
    table *top = POP();

    symtable *sym_value = MerCompiler_SymbolTable_new();

    sym_value->value = top->cval;
    sym_value->address = code;
    sym_value->tab = top;
    sym_value->tab->cval = top->cval;
    sym_value->tab->address = code;

    cls->methods.push_back(sym_value);

#ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_class_evaluate_STORE_GLOBAL] [pass]" << endl;
#endif

    return cls;
}

__mer_core_data__ mClass_T *MerVM_class_evaluate_MAKE_FUNCTION(__program_bytecode &u, stack *stk, mClass_T *cls) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_class_evaluate_MAKE_FUNCTION] [building...]" << endl;
    #endif

    Mer_uint8_t code = next_c(u);
    Mer_uint8_t address = code;

    Mer_uint8_t args_size = next_c(u);
    
    symtable *func = MerCompiler_SymbolTable_new();

    vector<Mer_uint8_t> body;
    while (code != CEND_FUNCTION) {
        code = next_c(u);
        body.push_back(code);
    }

    body.push_back(CEND_FUNCTION);

    mFunc_object_T *func_obj = MerCompiler_func_object_new();
    
    func_obj->f_bc = MerCompiler_code_new_as_ptr();
    func_obj->f_bc->buff = body;
    func_obj->f_bc->raw = body;
    func_obj->raw_body = body;
    func_obj->body_size = body.size();
    func_obj->args_size = args_size;
    func_obj->is_return = true;
    func_obj->is_global = true;
    func_obj->f_value = 0.0;

    func->address = address;
    func->tab->func_obj_v = func_obj;
    func->tab->is_func = true;

    cls->methods.push_back(func);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_class_evaluate_MAKE_FUNCTION] [pass]" << endl;
    #endif

    return cls;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_CLASS_BEGIN(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_CLASS_BEGIN] [building...]" << endl;
    #endif
    Mer_uint8_t code = next_c(u);

    mClass_T *cls = MerCompiler_class_new();

    cls->address = code;

    code = next_c(u);

    table *class_obj = MerCompiler_Table_new();
    class_obj->is_class = true;

    while (code != CCLASS_END) {
        if (code == CPUSH_FLOAT) {
            stk = MerVM_evaluate_PUSH_FLOAT(u, stk);
        }

        else if (code == CLOAD_GLOBAL) {
            stk = MerVM_evaluate_LOAD_GLOBAL(u, stk);
        } 
        
        else if (code == CSTORE_GLOBAL) {
            cls = MerVM_class_evaluate_STORE_GLOBAL(u, stk, cls);
        } 
        
        else if (code == CMAKE_FUNCTION) {
            cls = MerVM_class_evaluate_MAKE_FUNCTION(u, stk, cls);
        } 
        
        else if (code == CFUNCTION_CALL) {
            stk = MerVM_evaluate_FUNCTION_CALL(u, stk);
        } 
        
        else if (code == CGREATER || code == CEQUAL || code == CNOT_EQUAL || code == CGREATER_EQUAL || code == CLESS_EQUAL || code == CLESS) {
            stk = MerVM_evaluate_COMPARE(u, stk, code);
        }

        else if (code == CBINARY_ADD || code == CBINARY_SUB || code == CBINARY_MUL || code == CBINARY_DIV || code == CBINARY_MOD || code == CBINARY_POW) {
            stk = MerVM_evaluate_BINARY_OPER(u, stk, code);
        } 
        
        else if (code == CJUMP_TO) {
            stk = MerVM_evaluate_JUMP_TO(u, stk);
        } 
        
        else if (code == CNOT) {
            stk = MerVM_evaluate_NOT(u, stk);
        }

        else if (code == CLEN) {
            stk = MerVM_evaluate_CLEN(u, stk);
        }

        else if (code == CBUILD_LIST) {
            stk = MerVM_evaluate_BUILD_LIST(u, stk);
        }
        
        else if (code == CPUSH_NORMAL_MODE) {
            stk = MerVM_evaluate_PUSH_NORMAL_MODE(u, stk);
        } 
        
        else if (code == CPOP_JUMP_IF_FALSE) {
            stk = MerVM_evaluate_POP_JUMP_IF_FALSE(u, stk);
        } 
        
        else if (code == CINC) {
            stk = MerVM_evaluate_INC(u, stk);
        }

        else if (code == CDEC) {
            stk = MerVM_evaluate_DEC(u, stk);
        }

        else if (code == CLOAD_TRUE) {
            stk = MerVM_evaluate_LOAD_TRUE(u, stk);
        }

        else if (code == CIS) {
            stk = MerVM_evaluate_IS(u, stk);
        }

        else if (code == CCLASS_END) {
            break;
        }
        
        else if (code == CLOAD_FALSE) {
            stk = MerVM_evaluate_LOAD_FALSE(u, stk);
        }
        
        else if (code == CGET_ITEM) {
            stk = MerVM_evaluate_GET_ITEM(u, stk);
        } 

        else if (code == CSTORE_INDEX) {
            stk = MerVM_evaluate_STORE_INDEX(u, stk);
        }

        else if (code == CDELETE) {
            stk = MerVM_evaluate_DELETE(u, stk);
        }

        else if (code == CADDRESS) {
            code = next_c(u);
        }

        else if (code == CAND) {
            stk = MerVM_evaluate_AND(u, stk);
        }

        else if (code == COR) {
            stk = MerVM_evaluate_OR(u, stk);
        }

        code = next_c(u);
    }

    class_obj->class_v = cls;

    symtable *sym_value = MerCompiler_SymbolTable_new();
    sym_value->tab = class_obj;
    sym_value->address = cls->address;
    
    _G.push_back(sym_value);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_CLASS_BEGIN] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_IS(__program_bytecode &u, stack *stk) {
    table *lhs = POP();
    table *rhs = POP();

    if (lhs == rhs) {
        push_true_to_stack();
    } else {
        push_false_to_stack();
    }

    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_DELETE(__program_bytecode &u, stack *stk) {
    table *del = POP();
    bool found = false;

    for (auto &item : u.is_in_func ? _L : _G) {
        if (item->address == del->address) {
            found = true;
            MerCompiler_free_symboltable(item);
        }
    }

    if (!found) {
        MerDebug_system_error(SYSTEM_ERROR, "no global variable to delete", u.file);
    }
    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_INC(__program_bytecode &u, stack *stk) {
    table *value = POP();
    value->cval += 1;
    value->value = value->cval;
    stack_push(value);
    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_DEC(__program_bytecode &u, stack *stk) {
    table *value = POP();
    value->cval -= 1;
    value->value = value->cval;
    stack_push(value);
    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_AND(__program_bytecode &u, stack *stk) {
    table *left = POP();
    table *right = POP();

    if (left->cval && right->cval) {
        push_true_to_stack();
    } else {
        push_false_to_stack();
    }

    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_OR(__program_bytecode &u, stack *stk) {
    table *left = POP();
    table *right = POP();

    if (left->cval || right->cval) {
        push_true_to_stack();
    } else {
        push_false_to_stack();
    }

    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_NOT(__program_bytecode &u, stack *stk) {
    table *left = POP();

    if (left->cval) {
        push_false_to_stack();
    } else {
        push_true_to_stack();
    }

    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_LOAD_TRUE(__program_bytecode &u, stack *stk) {
    push_true_to_stack();
    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_LOAD_FALSE(__program_bytecode &u, stack *stk) {
    push_false_to_stack();
    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_CLEN(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_GET_ITERATOR] [building...]" << endl;
    #endif

    table *obj = POP();

    push_to_gc(obj);

    if (obj->is_list) {
        table* size = MER_VALUE(obj->list_v->size);
        stack_push(size);
    }
    else if (obj->is_str) {
        table* size = MER_VALUE(obj->f_str_v->size);
        stack_push(size);
    }
    else {
        table *size = MER_VALUE(obj->cval);
        stack_push(size);
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_GET_ITERATOR] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_api__ __mer_core_data__ stack *MerVM_evaluate_STORE_INDEX(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_STORE_INDEX] [building...]" << endl;
    #endif

    table *item = POP();
    table *index = POP(); 
    table *value = POP();

    push_to_gc(index);

    if (value->is_list) {
        if (index->cval > value->list_v->size) {
            MerDebug_system_error(SYSTEM_ERROR, "Index out of range", u.file);
        }

        if (index->cval < 0) {
            index->cval += value->list_v->size;
        }
        table* existing_item = (table*)value->list_v->args[index->cval];
        existing_item->ref_count--;
        push_to_gc(existing_item);

        item->ref_count++;

        value->list_v->args[index->cval] = item;
    } else {
        MerDebug_system_error(SYSTEM_ERROR, "Can't store value to non-list", u.file);
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_STORE_INDEX] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_POP_JUMP_IF_FALSE(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_POP_JUMP_IF_FALSE] [building...]" << endl;
    #endif

    table *top = POP();
    Mer_uint8_t address = next_c(u);

    if (IS_FALSE(top->cval)) {
        u.iid = u.label_map[address];
    }

    push_to_gc(top);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_POP_JUMP_IF_FALSE] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_JUMP_IF_FALSE(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_JUMP_IF_FALSE] [building...]" << endl;
    #endif

    table *top = EAT_STACK(stk);
    Mer_uint8_t address = next_c(u);

    if (IS_FALSE(top->cval)) {
        u.iid = u.label_map[address];
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_JUMP_IF_FALSE] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_JUMP_TO(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_JUMP_TO] [building...]" << endl;
    #endif

    Mer_uint8_t address = next_c(u);
    u.iid = u.label_map[address];

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_JUMP_TO] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_api__ __mer_core_data__ stack *MerVM_evaluate_BUILD_LIST(__program_bytecode &u, stack *stk) {
    Mer_uint8_t csize = next_c(u);
    Mer_size_t size = csize;
    mList_T *list = MerCompiler_list_object_new();
    
    for (Mer_size_t i = 0; i < size; i++) {
        table *top = POP();
        top->ref_count++;

        back_insrt(list->args, top);
    }

    table *top = MerCompiler_Table_new();

    top->is_list = true;
    top->list_v = list;
    top->list_v->size = size;

    stack_push(top);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_BUILD_LIST] [pass]" << endl;
    #endif
    
    return stk;
};

MERCURY_API __mer_core_api__ __mer_core_data__ stack *MerVM_evaluate_PUSH_NORMAL_MODE(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_PUSH_NORMAL_MODE] [building...]" << endl;
    #endif

    Mer_uint8_t ssize = next_c(u);
    Mer_size_t size = ssize;
    Mer_uint8_t code = next_c(u);
    vector<Mer_uint8_t> result;

    Mer_size_t t = 0;

    while (t < size) {
        result.push_back(code);
        code = next_c(u);
        ++t;
    }

    --u.iid;

    mString_T *str_v = MerCompiler_string_new();

    str_v->buff = result;
    str_v->size = size;

    table *top = MerCompiler_Table_new();

    top->f_str_v = str_v;
    top->is_str = true;

    stack_push(top);
    
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_PUSH_NORMAL_MODE] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_GET_ITEM(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_GET_ITEM] [building...]" << endl;
    #endif
    
    table *extract_val = POP();
    table *obj = POP();

    push_to_gc(extract_val);
    push_to_gc(obj);

    if (!obj) {
        MerDebug_system_error(SYSTEM_ERROR, "Error while getting item from a list object", u.file);
    }

    if (!extract_val) {
        MerDebug_system_error(SYSTEM_ERROR, "Error while getting item from a list object, extract value", u.file);
    }

    if (obj->is_list) {
        if (extract_val->cval > obj->list_v->size) {
            MerDebug_system_error(SYSTEM_ERROR, "Index out of range", u.file);
        }

        if (extract_val->cval < 0) {
            extract_val->cval += obj->list_v->size;
        }

        table *value = (table *) obj->list_v->args[extract_val->cval];

        if (!value) {
            MerDebug_system_error(SYSTEM_ERROR, "Error while getting item from a list object", u.file);
        }
        
        stack_push(value);
    } else if (obj->is_str) {
        Mer_uint8_t code = obj->f_str_v->buff[extract_val->cval];
        mString_T *str = creat_char_obj(code);

        table *value = MerCompiler_Table_new();
        value->is_str = true;
        value->f_str_v = str;
        value->cval = static_cast<float>(str->hash);

        stack_push(value);
    } else {
        MerDebug_system_error(SYSTEM_ERROR, "Error while getting item from a list object", u.file);
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_GET_ITEM] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_COMPARE(__program_bytecode &u, stack *stk, Mer_uint8_t op) {
#ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_COMPARE] [building...]" << endl;
#endif

    table *right = POP();
    table *left = POP();

    push_to_gc(left);
    push_to_gc(right);

    auto compare_string = [](auto *a, auto *b) -> int {
        Mer_size_t min_size = std::min(a->size, b->size);
        for (Mer_size_t i = 0; i < min_size; ++i) {
            if (a->buff[i] < b->buff[i]) return -1;
            if (a->buff[i] > b->buff[i]) return 1;
        }
        if (a->size < b->size) return -1;
        if (a->size > b->size) return 1;
        return 0;
    };

    auto compare_list = [](auto *a, auto *b) -> int {
        Mer_size_t min_size = std::min(a->size, b->size);
        for (Mer_size_t i = 0; i < min_size; ++i) {
            table *ai = (table*)a->args[i];
            table *bi = (table*)b->args[i];
            if (ai->cval < bi->cval) return -1;
            if (ai->cval > bi->cval) return 1;
        }
        if (a->size < b->size) return -1;
        if (a->size > b->size) return 1;
        return 0;
    };

    int cmp = 0;
    if (left->is_str && right->is_str) {
        cmp = compare_string(left->f_str_v, right->f_str_v);
    } else if (left->is_list && right->is_list) {
        cmp = compare_list(left->list_v, right->list_v);
    } else {
        if (left->cval < right->cval) cmp = -1;
        else if (left->cval > right->cval) cmp = 1;
        else cmp = 0;
    }
    
    if (op == CLESS) {
        if (cmp < 0) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    }
    else if (op == CGREATER) {
        if (cmp > 0) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    }
    else if (op == CEQUAL) {
        if (cmp == 0) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    }
    else if (op == CNOT_EQUAL) {
        if (cmp != 0) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    }
    else if (op == CGREATER_EQUAL) {
        if (cmp >= 0) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    }
    else if (op == CLESS_EQUAL) {
        if (cmp <= 0) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    }

#ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_COMPARE] [pass]" << endl;
#endif
    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_BINARY_OPER(__program_bytecode &u, stack *stk, Mer_uint8_t op) {
    #ifdef SYSTEM_TEST    
    cout << "[ceval.cpp] [MerVM_evaluate_BINARY_OPER] [building...]" << endl;
    #endif

    table *right = POP();
    table *left = POP();

    push_to_gc(left);
    push_to_gc(right);

    if (op == CBINARY_ADD) {
        if (left->is_list && right->is_list) {
            table *list_obj = MerCompiler_Table_new();
            list_obj->list_v = add_list(left->list_v, right->list_v);
            list_obj->is_list = true;
            stack_push(list_obj);
        } else if (left->is_str && right->is_str) {
            table *str_obj = MerCompiler_Table_new();
            str_obj->f_str_v = add_string(left->f_str_v, right->f_str_v);
            str_obj->is_str = true;
            stack_push(str_obj);
        } else {
            table *result = MerCompiler_table_setup(MERCURY_BINARY_ADD(left->cval, right->cval));
            stack_push(result);
        }
    } else if (op == CBINARY_SUB) {
        table *result = MerCompiler_table_setup(MERCURY_BINARY_SUB(left->cval, right->cval));
        stack_push(result);
    } else if (op == CBINARY_MUL) {
        if (left->is_list && !right->is_list) {
            table *list_obj = MerCompiler_Table_new();
            list_obj->list_v = mul_list(left->list_v, right->cval);
            list_obj->is_list = true;
            stack_push(list_obj);
        } else if (left->is_str && !right->is_str) {
            table *str_obj = MerCompiler_Table_new();
            str_obj->f_str_v = mul_string(left->f_str_v, right->cval);
            str_obj->is_str = true;
            stack_push(str_obj);
        } else if (right->is_list && !left->is_list) {
            table *list_obj = MerCompiler_Table_new();
            list_obj->list_v = mul_list(right->list_v, left->cval);
            list_obj->is_list = true;
            stack_push(list_obj);
        } else if (right->is_str && !left->is_str) {
            table *str_obj = MerCompiler_Table_new();
            str_obj->f_str_v = mul_string(right->f_str_v, left->cval);
            str_obj->is_str = true;
            stack_push(str_obj);
        } else {
            table *result = MerCompiler_table_setup(MERCURY_BINARY_MUL(left->cval, right->cval));
            stack_push(result);
        }
    } else if (op == CBINARY_DIV) {
        table *result = MerCompiler_table_setup(MERCURY_BINARY_DIV(left->cval, right->cval));
        stack_push(result);
    } else if (op == CBINARY_MOD) {
        table *result = MerCompiler_table_setup(MERCURY_BINARY_MOD(static_cast<int>(left->cval), static_cast<int>(right->cval)));
        stack_push(result);
    } else if (op == CBINARY_POW) {
        table *result = MerCompiler_table_setup(MERCURY_BINARY_POW(left->cval, right->cval));
        stack_push(result);
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_BINARY_OPER] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_PUSH_FLOAT(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_PUSH_FLOAT] [building...]" << endl;
    #endif

    if (u.iid + 4 < u.code.prg_code.buff.size()) {
        Mer_uint32_t int_repr;
        Mer_float float_repr;
        memcpy(&int_repr, &u.code.prg_code.buff[u.iid], 4);
        memcpy(&float_repr, &int_repr, 4);
        table *float_obj = MerCompiler_table_setup(float_repr, NULL_UINT_8_T);
        stack_push(float_obj);
    } else {
        MerDebug_system_error(SYSTEM_ERROR, "Stack underflow", u.file);
    }
    u.iid += 4;

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_PUSH_FLOAT] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_LOAD_GLOBAL(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_GLOBAL] [building...]" << endl;
    #endif

    Mer_uint8_t code = next_c(u);
    bool found = false;

    for (auto &item : _L) {
        if (item->address == code) {
            item->tab->cval = item->value;
            item->tab->address = item->address;
            stack_push(item->tab);
            found = true;
            break;
        }
    }

    if (!found) {
        for (auto &item : _G) {
            if (item->address == code) {
                item->tab->cval = item->value;
                item->tab->address = item->address;
                stack_push(item->tab);
                found = true;
                break;
            }
        }

        if (!found) {
            cerr << "global var dont exist " << "0x" << hex << setfill('0') << setw(2) << (int)code << endl;
            cerr << "at id " << u.iid << endl;
            MER_BREAK_POINT;
        }
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_GLOBAL] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_STORE_GLOBAL(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_STORE_GLOBAL] [building...]" << endl;
    #endif

    Mer_uint8_t code = next_c(u);

    table *top = POP();
    top->ref_count++;

    for (auto &sym : u.is_in_func ? _L : _G) {
        if (sym->address == code) {
            if (sym->tab != top) {
                --sym->tab->ref_count;
                push_to_gc(sym->tab);
            }   

            sym->value = top->cval;
            sym->tab = top;
            sym->tab->cval = top->cval;
            sym->tab->address = code;

            return stk;
        }
    }

    symtable *sym_value = MerCompiler_SymbolTable_new();

    sym_value->value = top->cval;
    sym_value->address = code;
    sym_value->tab = top;
    sym_value->tab->cval = top->cval;
    sym_value->tab->address = code;

    u.is_in_func ? _L.push_back(sym_value) : _G.push_back(sym_value);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_STORE_GLOBAL] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_MAKE_FUNCTION(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_MAKE_FUNCTION] [building...]" << endl;
    #endif

    Mer_uint8_t code = next_c(u);
    Mer_uint8_t address = code;

    Mer_uint8_t args_size = next_c(u);
    
    symtable *func = MerCompiler_SymbolTable_new();

    vector<Mer_uint8_t> body;
    while (code != CEND_FUNCTION) {
        code = next_c(u);
        body.push_back(code);
    }

    body.push_back(CEND_FUNCTION);

    mFunc_object_T *func_obj = MerCompiler_func_object_new();
    
    func_obj->f_bc = MerCompiler_code_new_as_ptr();
    func_obj->f_bc->buff = body;
    func_obj->f_bc->raw = body;
    func_obj->raw_body = body;
    func_obj->body_size = body.size();
    func_obj->args_size = args_size;
    func_obj->is_return = true;
    func_obj->is_global = true;
    func_obj->f_value = 0.0;

    func->address = address;
    func->value = 0;
    func->cval = 0;

    func->tab->cval = 0;
    func->tab->address = address;
    func->tab->func_obj_v = func_obj;
    func->tab->is_func = true;
    func->tab->ref_count++;

    _G.push_back(func);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_MAKE_FUNCTION] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_call_context_evaluate_LOAD_LOCAL(CallContext *ctx, __program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_call_context_evaluate_LOAD_LOCAL] [building...]" << endl;
    #endif

    Mer_uint8_t code = next_c(u);
    bool found = false;

    for (auto &item : ctx->local) {
        if (item->address == code) {
            item->tab->cval = item->value;
            item->tab->address = item->address;
            stack_push(item->tab);
            found = true;
            break;
        }
    }

    if (!found) {
        for (auto &item : _G) {
            if (item->address == code) {
                item->tab->cval = item->value;
                item->tab->address = item->address;
                stack_push(item->tab);
                found = true;
                break;
            }
        }

        if (!found) {
            cerr << "global var dont exist at local " << "0x" << hex << setfill('0') << setw(2) << (int)code << endl;
            cerr << "at id " << u.iid << endl;
            MER_BREAK_POINT;
        }
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_call_context_evaluate_LOAD_LOCAL] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_call_context_evaluate_STORE_LOCAL(CallContext *ctx, __program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_call_context_evaluate_STORE_LOCAL] [building...]" << endl;
    #endif

    Mer_uint8_t code = next_c(u);
    table *top = POP();

    for (auto &item : ctx->local) {
        if (item->address == code) {
            item->value = top->cval;
            item->address = code;
            item->tab = top;
            return stk;
        }
    }

    symtable *sym_value = MerCompiler_symboltable_setup("", top->cval, "AUTO_T", code);
    sym_value->tab = top;
    ctx->local.push_back(sym_value);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_call_context_evaluate_STORE_LOCAL] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_call_context(CallContext *ctx, __program_bytecode &u, stack *stk) {
    __program_bytecode tmp = init_program_bytecode(ctx->code);    
    __get_label_map(tmp, "function");
    tmp.is_in_func = true;

    for (;;) {
        Mer_uint8_t code = next_c(tmp);

        if (code == CPUSH_FLOAT) {
            stk = MerVM_evaluate_PUSH_FLOAT(tmp, stk);
        }
        
        else if (code == CBINARY_ADD || code == CBINARY_SUB || code == CBINARY_MUL || code == CBINARY_DIV || code == CBINARY_MOD || code == CBINARY_POW) {
            stk = MerVM_evaluate_BINARY_OPER(tmp, stk, code);
        } 

        else if (code == CLOAD_GLOBAL) {
            stk = MerVM_call_context_evaluate_LOAD_LOCAL(ctx, tmp, stk);
        } 
        
        else if (code == CSTORE_GLOBAL) {
            stk = MerVM_call_context_evaluate_STORE_LOCAL(ctx, tmp, stk);
        } 
        
        else if (code == CFUNCTION_CALL) {
            stk = MerVM_evaluate_FUNCTION_CALL(tmp, stk);
        } 
        
        else if (code == CGREATER || code == CEQUAL || code == CNOT_EQUAL || code == CGREATER_EQUAL || code == CLESS_EQUAL || code == CLESS) {
            stk = MerVM_evaluate_COMPARE(tmp, stk, code);
        } 
        
        else if (code == CJUMP_TO) {
            stk = MerVM_evaluate_JUMP_TO(tmp, stk);
        } 
        
        else if (code == CNOT) {
            stk = MerVM_evaluate_NOT(tmp, stk);
        }

        else if (code == CLEN) {
            stk = MerVM_evaluate_CLEN(tmp, stk);
        }

        else if (code == CBUILD_LIST) {
            stk = MerVM_evaluate_BUILD_LIST(tmp, stk);
        }
        
        else if (code == CPUSH_NORMAL_MODE) {
            stk = MerVM_evaluate_PUSH_NORMAL_MODE(tmp, stk);
        } 
        
        else if (code == CPOP_JUMP_IF_FALSE) {
            stk = MerVM_evaluate_POP_JUMP_IF_FALSE(tmp, stk);
        }
        
        else if (code == CINC) {
            stk = MerVM_evaluate_INC(tmp, stk);
        }

        else if (code == CDEC) {
            stk = MerVM_evaluate_DEC(tmp, stk);
        }

        else if (code == CGET_ITEM) {
            stk = MerVM_evaluate_GET_ITEM(tmp, stk);
        } 

        else if (code == CLOAD_TRUE) {
            stk = MerVM_evaluate_LOAD_TRUE(tmp, stk);
        } 

        else if (code == CIS) {
            stk = MerVM_evaluate_IS(tmp, stk);
        }
        
        else if (code == CLOAD_FALSE) {
            stk = MerVM_evaluate_LOAD_FALSE(tmp, stk);
        }
        
        else if (code == CRETURN) {
            table *top = POP();
            ctx->return_val = top;
            break;
        }

        else if (code == CLOAD_ARGS) {
            stk = MerVM_evaluate_LOAD_ARGS(tmp, stk);
        }

        else if (code == CEND_FUNCTION) {
            break;
        }

        else if (code == CLOAD_ATTR) {
            stk = MerVM_evaluate_LOAD_ATTR(tmp, stk);
        }

        else if (code == CSTORE_ATTR) {
            stk = MerVM_evaluate_STORE_ATTR(tmp, stk);
        }
        
        else if (code == CSTORE_INDEX) {
            stk = MerVM_evaluate_STORE_INDEX(tmp, stk);
        }

        else if (code == CDELETE) {
            stk = MerVM_evaluate_DELETE(tmp, stk);
        }

        else if (code == CADDRESS) {
            code = next_c(tmp);
        }

        else if (code == CAND) {
            stk = MerVM_evaluate_AND(tmp, stk);
        }

        else if (code == COR) {
            stk = MerVM_evaluate_OR(tmp, stk);
        }
    }

    ctx->return_val->ref_count++;
    stk->s_table->table.push_back(ctx->return_val);
    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_LOAD_ARGS(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_ARGS] [building...]" << endl;
    #endif

    Mer_uint8_t address = next_c(u);

    bool found = false;

    for (auto &item : _L) {
        if (item->address == address) {
            item->tab->cval = item->value;
            item->tab->address = item->address;
            stack_push(item->tab);
            found = true;
            break;
        }
    }

    if (!found) {
        cerr << "local var dont exist " << "0x" << hex << setfill('0') << setw(2) << (int)address << endl;
        cerr << "at id " << u.iid << endl;
        MER_BREAK_POINT;
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_ARGS] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_FUNCTION_CALL(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [building...]" << endl;
    #endif

    table *func_obj = POP();

    if (func_obj->is_func) {
        Mer_uint8_t para_address = 0x00;
        vector<symtable*> _T;

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [pushing parameters... with size " << func_obj->func_obj_v->args_size << "]" << endl;
        #endif

        for (int i = 0; i < func_obj->func_obj_v->args_size; i++) {
            #ifdef SYSTEM_TEST
            cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [pushing parameter " << i << " start]" << endl;
            #endif

            table *item = POP();

            #ifdef SYSTEM_TEST
            cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [pushing parameter " << i << " pass]" << endl;
            #endif

            symtable *parameter = MerCompiler_symboltable_setup("", item->cval, "AUTO_T", NULL_UINT_8_T);  
            parameter->tab = item;
            parameter->tab->address = parameter->address;
            parameter->tab->ref_count++;
            parameter->value = item->cval;

            _T.push_back(parameter);
        }

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [pushing parameters done!]" << endl;
        #endif

        std::reverse(_T.begin(), _T.end());

        for (auto &item : _T) {
            item->address = ++para_address;
        }

        mCode_T code = NULL_CODE;
        code.prg_code.buff = func_obj->func_obj_v->f_bc->buff;

        CallContext *ctx = new CallContext {
            .code = code,
            .caller = nullptr,
            .return_val = MerCompiler_Table_new(),
            .local = _T
        };

        _T.clear();

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [evaluating...]" << endl;
        #endif

        u.is_in_func = true;
        stk = MerVM_evaluate_call_context(ctx, u, stk);
        u.is_in_func = false;

        for (auto &item : ctx->local) {
            if (item->tab) {
                --item->tab->ref_count;
                push_to_gc(item->tab);
            }
        }

        std::vector<symtable*>().swap(ctx->local);

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [evaluating done!]" << endl;
        #endif

    } else if (func_obj->is_class) {
        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [class]" << endl;
        #endif

        mClass_T *instance = MerCompiler_class_new();
        instance->address = func_obj->address;

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [class start]" << endl;
        #endif

        vector<void*> methods;
        for (auto &item : func_obj->class_v->methods) {
            symtable *method = (symtable *) item;
            symtable *copy = MerCompiler_symboltable_setup(method->name, method->value, method->type, method->address);

            #ifdef SYSTEM_TEST
            cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [class method]" << endl;
            #endif

            table_clone_shallow(copy->tab, method->tab);
            
            methods.push_back(copy);
        }

        instance->methods = methods;
        instance->inheritance = func_obj->class_v;

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [class pass]" << endl;
        #endif

        table *obj = MerCompiler_Table_new();
        obj->is_instance = true;
        obj->class_v = instance;

        stack_push(obj);

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [class done!]" << endl;
        #endif
    } else {

        Mer_uint8_t address = func_obj->address;

        for (auto &func : mer_core_libs) {
            if (func.address == address) {
                using FuncType = void (*)(stack *);
                FuncType func_ptr = (FuncType)(func.func);
                func_ptr(stk);
            }
        }
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [pass]" << endl;
    #endif

    return stk;
}

const char* show_opcode_name(uint8_t x) {
    if (x == CPUSH_FLOAT)         return "PUSH_FLOAT";
    else if (x == CPUSH_NORMAL_MODE) return "PUSH_NORMAL_MODE";
    else if (x == CBUILD_LIST)    return "BUILD_LIST";
    else if (x == CGET_ITEM)      return "GET_ITEM";
    else if (x == CSTORE_INDEX)   return "STORE_INDEX";
    else if (x == CBINARY_SUBSCRIBE) return "BINARY_SUBSCRIBE";
    else if (x == CLOAD_GLOBAL)   return "LOAD_GLOBAL";
    else if (x == CSTORE_GLOBAL)  return "STORE_GLOBAL";
    else if (x == CBINARY_ADD)    return "BINARY_ADD";
    else if (x == CLOAD_ARGS)     return "LOAD_ARGS";
    else if (x == CBINARY_SUB)    return "BINARY_SUB";
    else if (x == CBINARY_MUL)    return "BINARY_MUL";
    else if (x == CBINARY_DIV)    return "BINARY_DIV";
    else if (x == CBINARY_MOD)    return "BINARY_MOD";
    else if (x == TRUE_ADDRESS)   return "TRUE_ADDRESS";
    else if (x == FALSE_ADDRESS)  return "FALSE_ADDRESS";
    else if (x == CLOAD_TRUE)     return "LOAD_TRUE";
    else if (x == CLOAD_FALSE)    return "LOAD_FALSE";
    else if (x == CEQUAL)         return "EQUAL";
    else if (x == CNOT_EQUAL)     return "NOT_EQUAL";
    else if (x == CEND_FUNCTION)  return "END_FUNCTION";
    else if (x == CCLASS_BEGIN)   return "CLASS_BEGIN";
    else if (x == CPOP_TOP)       return "POP_TOP";
    else if (x == CCLASS_END)     return "CLASS_END";
    else if (x == CLESS)          return "LESS";
    else if (x == CCALL_METHOD)   return "CALL_METHOD";
    else if (x == CLESS_EQUAL)    return "LESS_EQUAL";
    else if (x == CGREATER)       return "GREATER";
    else if (x == CLOAD_ATTR)     return "LOAD_ATTR";
    else if (x == CGREATER_EQUAL) return "GREATER_EQUAL";
    else if (x == CNOT)           return "NOT";
    else if (x == CLEN)           return "LEN";
    else if (x == CJUMP_IF_FALSE) return "JUMP_IF_FALSE";
    else if (x == CJUMP_IF_TRUE)  return "JUMP_IF_TRUE";
    else if (x == CPOP_JUMP_IF_FALSE) return "POP_JUMP_IF_FALSE";
    else if (x == CPOP_JUMP_IF_TRUE)  return "POP_JUMP_IF_TRUE";
    else if (x == CJUMP_TO)       return "JUMP_TO";
    else if (x == CSTORE_ATTR)    return "STORE_ATTR";
    else if (x == CPROGRAM_START) return "PROGRAM_START";
    else if (x == CPROGRAM_END)   return "PROGRAM_END";
    else if (x == CMAKE_FUNCTION) return "MAKE_FUNCTION";
    else if (x == CFUNCTION_CALL) return "FUNCTION_CALL";
    else if (x == CRETURN)        return "RETURN";
    else if (x == CADDRESS)       return "ADDRESS";
    else                          return "UNKNOWN_OPCODE";
}

void print_bytecode(vector<uint8_t> &bytecode) {
    int i = 0;
    int line = 1;
    while (i < bytecode.size()) {
        string c = show_opcode_name(bytecode[i]);
        cout << dec << line++ << ": ";
        if (c == "PUSH_FLOAT") {
            uint8_t c1 = bytecode[++i];
            uint8_t c2 = bytecode[++i];
            uint8_t c3 = bytecode[++i];
            uint8_t c4 = bytecode[++i];

            cout << "PUSH_FLOAT ";
            cout << "0x" << hex << setfill('0') << setw(2) << (int)c1 << " ";
            cout << "0x" << hex << setfill('0') << setw(2) << (int)c2 << " ";
            cout << "0x" << hex << setfill('0') << setw(2) << (int)c3 << " ";
            cout << "0x" << hex << setfill('0') << setw(2) << (int)c4 << " ";
            cout << endl;
        } else if (c == "PUSH_NORMAL_MODE") {
            uint8_t mode = bytecode[++i];
            int size = mode;
            cout << "PUSH_NORMAL_MODE ";
            cout << "0x" << hex << setfill('0') << setw(2) << (int)mode << " ";

            while (i < bytecode.size() && size > 0) {
                cout << "0x" << hex << setfill('0') << setw(2) << (int)bytecode[i] << " ";
                ++i;
                --size;
            }
            cout << endl;
        } 
        else if (c == "STORE_GLOBAL" 
            || c == "LOAD_GLOBAL" 
            || c == "STORE_ATTR"
            || c == "CLASS_BEGIN"
            || c == "LOAD_ARGS"
            || c == "POP_JUMP_IF_FALSE" 
            || c == "JUMP_IF_FALSE" 
            || c == "POP_JUMP_IF_TRUE" 
            || c == "JUMP_IF_TRUE"
            || c == "LOAD_ATTR"
            || c == "JUMP_TO" 
            || c == "ADDRESS"
            || c == "BUILD_LIST") {
            uint8_t address = bytecode[++i];
            cout << c << " 0x" << hex << setfill('0') << setw(2) << (int)address << endl;
        } else if (c == "STORE_INDEX" 
            || c == "GET_ITEM" 
            || c == "FUNCTION_CALL"
            || c == "POP_TOP"
            || c == "CALL_METHOD"
            || c == "PROGRAM_START" 
            || c == "PROGRAM_END"
            || c == "RETURN"
            || c == "BINARY_ADD"
            || c == "BINARY_SUB"
            || c == "CLASS_END"
            || c == "END_FUNCTION"
            || c == "BINARY_MUL"
            || c == "LOAD_TRUE"
            || c == "LOAD_FALSE"
            || c == "BINARY_DIV"
            || c == "BINARY_MOD"
            || c == "LESS"
            || c == "EQUAL"
            || c == "NOT_EQUAL"
            || c == "GREATER"
            || c == "GREATER_EQUAL"
            || c == "LEN"
            || c == "STORE_INDEX"
            || c == ""
        ) {
            cout << c << endl;
        } else if (c == "MAKE_FUNCTION") {
            uint8_t address = bytecode[++i];
            uint8_t name_length = bytecode[++i];
            cout << c << " 0x" << hex << setfill('0') << setw(2) << (int)address << " " << "0x" << hex << setfill('0') << setw(2) << (int)name_length << endl;
        }
        ++i;
    }
}

void print_bytecode_index(vector<uint8_t> &bytecode) {
    cout << "Bytecode Index:" << endl;
    int index = 0;
    for (auto &item : bytecode) {
        cout << "0x" << hex << setfill('0') << setw(2) << (int)item << " ";
        if (index++ == 5) {
            cout << endl;
            index = 0;
        }
    }
}

void print_help() {
    cout << "MercuryLang CLI - Version " << CUSTOM_VERSION << ", by Dinh Son Hai" << endl;
    cout << "Usage: 'mer' or 'mer3' + [options] <filename>.mer\n";
    cout << "Options:\n";
    cout << "  -v\t\tShow version information\n";
    cout << "  -p\t\tStart the Mercury REPL\n";
    cout << "  -h\t\tShow this help message\n";
    cout << "  -m\t\tCompiled into readable bytecode\n";
}

string time_date() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%c", &tstruct);
    return string(buf); 
}

void prompt() {
    cout << LANGUAGE << " " << CUSTOM_VERSION << " Copyright (C) 2025-present, " << AUTHOR << endl;
    Mer_real_string input = "";
    Mer_real_string source = "";

    __compiler_u glb = compiler_init();

    MerCore_initialize();
    
    while (true) {
        bool first = true;
        string line;
        string full_line = "";
        while (true) {

            if (first) {
                cout << "> ";
                first = false;
            } else {
                cout << "... ";
            }
            getline(cin, line);
   
            full_line += line + "\n";
            if (line.empty() || line.back() == ';') {
                break;
            }
        }

        char* c_line = (char*)full_line.c_str();
        mLexer_T *lexer = _MerLexer_init(c_line);
        mParser_T *parser = _MerParser_init(lexer);
        mAST_T *ast = MerParser_parse_program(parser);
        mCode_T code = MerCompiler_compile_ast_program(ast, glb);
        stack *stk = MerVM_evaluate_program(code);

        _MerParser_free(parser);
        MerAST_free(ast);
    }

    MerCore_Finalize();
}

void MercuryRunSimpleString(char* buff) {
    mLexer_T *lexer = _MerLexer_init(buff);
    mParser_T *parser = _MerParser_init(lexer);
    mAST_T *ast = MerParser_parse_program(parser);
    __compiler_u u = compiler_init();
    mCode_T code = MerCompiler_compile_ast_program(ast, u);
    stack *stk = MerVM_evaluate_program(code);
}

mCode_T MercuryCompileSimpleString(char* buff) {
    MerCore_initialize();
    mLexer_T *lexer = _MerLexer_init(buff);
    mParser_T *parser = _MerParser_init(lexer);
    mAST_T *ast = MerParser_parse_program(parser);
    __compiler_u u = compiler_init();
    mCode_T code = MerCompiler_compile_ast_program(ast, u);
    MerCore_Finalize();
    
    return code;
}

#endif // MERCURY_2_2_1_HPP