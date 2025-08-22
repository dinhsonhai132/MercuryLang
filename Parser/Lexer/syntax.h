#ifndef MERCURY_STANDARD_SYNTAX_HEADER_FILE
#define MERCURY_STANDARD_SYNTAX_HEADER_FILE

#ifndef STANDARD_SYNTAX
#define STANDARD_SYNTAX
#endif

int is_syntax(const char* syn);

extern STANDARD_SYNTAX const char* LET_S;
extern STANDARD_SYNTAX const char* LOCAL_S;
extern STANDARD_SYNTAX const char* TRUE_S;
extern STANDARD_SYNTAX const char* FALSE_S;
extern STANDARD_SYNTAX const char* INCLUDE_S;
extern STANDARD_SYNTAX const char* LOOP_S;
extern STANDARD_SYNTAX const char* IMPORT_S;
extern STANDARD_SYNTAX const char* FUNCTION_S;
extern STANDARD_SYNTAX const char* FUNCTION2_S;
extern STANDARD_SYNTAX const char* RETURN_S;
extern STANDARD_SYNTAX const char* ELIF_S;
extern STANDARD_SYNTAX const char* DO_S;
extern STANDARD_SYNTAX const char* END_S;
extern STANDARD_SYNTAX const char* DEFINED_S;
extern STANDARD_SYNTAX const char* IF_S;
extern STANDARD_SYNTAX const char* AND_S;
extern STANDARD_SYNTAX const char* OR_S;
extern STANDARD_SYNTAX const char* NOT_S;
extern STANDARD_SYNTAX const char* ELSE_S;
extern STANDARD_SYNTAX const char* FOR_S;
extern STANDARD_SYNTAX const char* IS_S;
extern STANDARD_SYNTAX const char* IN_S;
extern STANDARD_SYNTAX const char* WHILE_S;
extern STANDARD_SYNTAX const char* BREAK_S;
extern STANDARD_SYNTAX const char* CONTINUE_S;
extern STANDARD_SYNTAX const char* CONST_S;
extern STANDARD_SYNTAX const char* STATIC_S;
extern STANDARD_SYNTAX const char* GLOBAL_S;
extern STANDARD_SYNTAX const char* ASSERT_S;
extern STANDARD_SYNTAX const char* STRING_S;
extern STANDARD_SYNTAX const char* STR_S;
extern STANDARD_SYNTAX const char* CLASS_S;
extern STANDARD_SYNTAX const char* INTERFACE_S;
extern STANDARD_SYNTAX const char* STRUCT_S;
extern STANDARD_SYNTAX const char* NEW_S;
extern STANDARD_SYNTAX const char* LIST_S;
extern STANDARD_SYNTAX const char* DELETE_S;
extern STANDARD_SYNTAX const char* CAST_S;
extern STANDARD_SYNTAX const char* FLOAT_S;
extern STANDARD_SYNTAX const char* DOUBLE_S;
extern STANDARD_SYNTAX const char* CHAR_S;
extern STANDARD_SYNTAX const char* SHORT_S;
extern STANDARD_SYNTAX const char* LONG_S;
extern STANDARD_SYNTAX const char* AUTO_S;
extern STANDARD_SYNTAX const char* VOID_S;
extern STANDARD_SYNTAX const char* THEN_S;
extern STANDARD_SYNTAX const char* BOOL_S;

#endif // MERCURY_STANDARD_SYNTAX_HEADER_FILE