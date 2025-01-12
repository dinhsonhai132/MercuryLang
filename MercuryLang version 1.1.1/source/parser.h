#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "lexer.h"
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

vector<store_var> variables;
vector<store_var> tempotary_variables;
vector<store_list> lists;
vector<function> functions;

class parser {
private:
    size_t tok_idx;
    datatype cur_idx;
    vector<datatype> tokenize;
    string var;
    int val;
public:
    parser(vector<datatype> tokenize) : tokenize(tokenize), tok_idx(0) {}

    int get_tempotary_variable(string name);
    int get_variable(string name);
    vector<int> get_list(string name);
    datatype get_next_tok();
    datatype get_next_tok_to(int s);
    int factor();
    int extract();
    int term();
    int expr();
    void make_list();
    void make_var();
    int while_loop();
    void for_loop();
    void do_block();
    int comparison();
    int condition();
    void make_function();
    void call_function();
    void execute(vector<datatype> tokens, vector<Parameter> paras);
    auto make_return();
    vector<datatype> get_tokens(string name);
    vector<Parameter> get_para(string name);
    void print_func();
    void run_code();

};

#endif