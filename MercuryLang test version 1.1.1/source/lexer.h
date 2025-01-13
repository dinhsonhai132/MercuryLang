#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "parser.h"
using namespace std;

enum VerType {
    INT, PLUS, MINUS, TIME, DIV, NONE, MEMORY, PRINT, STRING, 
    TEMPORARY_MEMORY, BIGGER, SMALLER, EQUAL, BE, SE, DIFFERENCES, IF, ELSE, ELIF, PARAMATER_KWARGS,
    THEN, LP, RP, FOR, PP, MM, WHILE, LET, ASSIGN, GOTO, INPUT, LIST, BLOCK, RETURN_FUNC,
    FUNCTION, PARAMATER, FUNCTION_CALL, COMMA, DOUBLE_COLON, COMMAND, CIN, COMMAND_START, COMMAND_END,
    DO, VECTOR, SPARE_LP, SPARE_RP, LIST_NAME, EXTRACT, RANGE, FOR_LOOP, IN, TO, END
};

enum Mercury_type {
    INT_TYPE, FLOAT_TYPE, STRING_TYPE
};

struct store_var {
    string name;
    int val;
};

struct Parameter {
    string name;
    int val;
};

struct Parameter_kwargs {
    string name;
    vector<int> vec;
};

struct datatype {
    VerType type;
    int value;
    string name;
};

struct store_list {
    string name;
    vector<int> list;
};

struct function {
    string function_name;
    vector<Parameter> Parameters;
    vector<datatype> store_tokens;
    vector<Parameter_kwargs> parameter_kwargs;
    int value = 0;
};

class lexer {

private:
    string input;
    size_t pos;
    char cur;
    vector<datatype> tokens;
    vector<Parameter> paaaas;
    
public:
    void advance();
    void advance_to(int a);
    vector<datatype> token();
    lexer(string input) : input(input), pos(0) {}
};

#endif
