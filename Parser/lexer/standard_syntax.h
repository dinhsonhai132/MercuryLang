#ifndef MERCURY_SYNTAX_HEADER_FILE
#define MERCURY_SYNTAX_HEADER_FILE

#ifndef __STANDARD_SYNTAX
#define __STANDARD_SYNTAX
#endif

#ifdef MERCURY_LANG3
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_if = "if";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_else = "else";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_end = "end";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_while = "while";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_do = "do";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_for = "for";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_break = "break";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_continue = "continue";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_return = "return";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_try = "try";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_catch = "catch";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_throw = "throw";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_finally = "finally";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_switch = "switch";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_case = "case";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_default = "default";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_print = "print";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_import = "import";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_class = "class";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_interface = "interface";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_struct = "struct";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_new = "new";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_delete = "delete";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_cast = "cast";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_float = "float";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_double = "double";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_char = "char";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_short = "short";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_long = "long";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_auto = "auto";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_void = "void";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_bool = "bool";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_list = "list";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_func = "func";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_this = "this";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_str = "str";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_string = "string";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_include = "include";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_const = "const";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_let = "let";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_then = "then";
#else
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_if = "IF";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_else = "ELSE";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_end = "END";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_while = "WHILE";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_do = "DO";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_for = "FOR";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_break = "BREAK";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_continue = "CONTINUE";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_return = "RETURN";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_try = "TRY";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_catch = "CATCH";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_throw = "THROW";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_finally = "FINALLY";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_switch = "SWITCH";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_case = "CASE";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_default = "DEFAULT";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_print = "PRINT";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_import = "IMPORT";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_class = "CLASS";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_interface = "INTERFACE";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_struct = "STRUCT";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_new = "NEW";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_delete = "DELETE";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_cast = "CAST";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_float = "FLOAT";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_double = "DOUBLE";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_char = "CHAR";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_short = "SHORT";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_long = "LONG";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_auto = "AUTO";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_void = "VOID";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_bool = "BOOL";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_list = "LIST";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_func = "FUNC";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_this = "THIS";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_str = "STR";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_string = "STRING";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_include = "INCLUDE";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_const = "CONST";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_let = "LET";
const char* __STANDARD_SYNTAX STANDARD_SYNTAX_then = "THEN";
#endif

#endif