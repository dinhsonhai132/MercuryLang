#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <cmath>
#include <ctime>
#include <variant>
using namespace std;

enum VerType {
    INT, PLUS, MINUS, TIME, DIV, NONE, MEMORY, PRINT, STRING, STRUCT, ENUM, BLOCK, PORT, DOT, TRUE, FALSE,
    TEMPORARY_MEMORY, BIGGER, SMALLER, EQUAL, BE, SE, DIFFERENCES, IF, ELSE, ELIF, PARAMATER_KWARGS, GLOBAL_VAR,
    THEN, LP, RP, FOR, PP, MM, WHILE, LET, ASSIGN, GOTO, INPUT, LIST, RETURN_FUNC, POP, PUSH, AT, REPAIR,
    FUNCTION, PARAMATER, FUNCTION_CALL, COMMA, DOUBLE_COLON, COMMAND, CIN, CLASS, LAMBDA, MAXTRIX, IMPORT, 
    DO, VECTOR, SPARE_LP, SPARE_RP, LIST_NAME, ARROW_TOKEN, RANGE, FOR_LOOP, IN, TO, END, NUM_TYPE, USER_TYPE,
    NULL_TOK, LOCAL, GLOBAL, HEAP, STACK, REGISTER, CONSTANT, LOCAL_VAR, HEAP_VAR, STACK_VAR, VOID_TOK, AUTO_TOK, 
    CONST_VAR, VOLATILE_TOK, STATIC_TOK, FLOAT, DOUBLE, CHAR, BOOL, LONG, SHORT, UNSIGNED, SIGNED, STR, F_STRING
};

enum VerLibrary_type {
    MERCURY_MATH, MERCURY_FILE, MERCURY_TIME, 
    MERCURY_RANDOM, MERCURY_INPUT_OUTPUT,
};

enum Mercury_type {
    FLOAT_TYPE, DOUBLE_TYPE, CHAR_TYPE, BOOL_TYPE, LONG_TYPE, SHORT_TYPE, UNSIGNED_TYPE, SIGNED_TYPE, 
    VOID, AUTO, CONST, VOLATILE, STATIC, EXTERN, REGISTER_, MUTABLE, STRING_TYPE, INT_TYPE, NULL_TYPE
};

enum port_address {
    PORT_1, PORT_2, PORT_3, PORT_4, PORT_5, PORT_6, PORT_7, PORT_8, PORT_9, PORT_10, PORT_NULL
};

struct port {
    string name = "";
    int value = 0;
    vector<int> values = {};
    port_address address = PORT_NULL;
};

struct enumerate {
    string name;
    int order;
    int value;
};

struct Mer_enum {
    string name;
    vector<enumerate> the_enums;
};

struct store_var {
    string name;
    Mercury_type type;
    int val;
    string string_val;
    bool bool_val;
    char char_val;
    float float_val;
    double double_val;
    long long_val;
    short short_val;
    unsigned unsigned_val;
    signed signed_val;
};

struct store_list {
    string name;
    vector<int> list;
    Mercury_type type = AUTO;
};

struct Parameter {
    string name;
    int val;
    Mercury_type type = AUTO;
};

struct Parameter_kwargs {
    string name;
    vector<int> vec;
    Mercury_type type = AUTO;
};

struct datatype {
    VerType type;
    int value;
    string name;
};

struct function_ {
    string function_name;
    Mercury_type type = AUTO;
    int value = 0;
    vector<Parameter> Parameters;
    vector<datatype> store_tokens;
    Parameter_kwargs parameter_kwargs;
    bool parameter_kwargs_found = false;
};

struct mom_type {
    string class_name;
    vector<store_var> variables;
    vector<store_list> lists;
    vector<function_> functions;
};

vector<store_var> variables;
vector<store_var> tempotary_variables;
vector<store_list> tempotary_list;
vector<store_list> lists;
vector<function_> functions;
vector<VerLibrary_type> libraries;
vector<Mer_enum> the_enums;
vector<mom_type> moms;
vector<string> user_datatype;