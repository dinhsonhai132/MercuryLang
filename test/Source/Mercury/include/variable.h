#ifndef VAR_J
#define VAR_J

#include <string>
#include <vector>
#include "eval.h"
#include "object.h"

using namespace std;

struct Variable {
    string name;
    RunTimeVal *value;
    AST_node *nvalue;
    string v_type;
    MerObject *v_object;
};

bool is_declared(string name, vector<Variable> *variables);
Variable declared(string name, AST_node *value, vector<Variable> *variables);
RunTimeVal *lookup(string name, vector<Variable> *variables);
Variable make_variable(string name, RunTimeVal *value);

#endif