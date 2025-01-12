#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "lexer.h"
using namespace std;

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
