#ifndef VAR_H
#define VAR_H

#include <string>
#include <vector>

#include "runtime.h"

using namespace std;

struct Variable {
    string name;
    RunTimeVal *value;
    AST_node *nvalue;
    MerObject *ovalue;
};

bool is_declared(string name, vector<Variable> *variables);
Variable declared(string name, RunTimeVal *value, vector<Variable> *variables);
Variable make_variable(string name, RunTimeVal *value);

#endif