#ifndef VAR_J
#define VAR_J

#include <string>
#include <vector>
#include "./parser/parser.h"
#include "eval.h"

using namespace std;

struct Variable {
    string name;
    RunTimeVal *value;
};

bool is_declared(string name, vector<Variable> *variables);
Variable declared(string name, AST_node *value, vector<Variable> *variables);
RunTimeVal *lookup(string name, vector<Variable> *variables);

#endif