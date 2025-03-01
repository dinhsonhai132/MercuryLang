#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include <iostream>

#include "runtime.h"

using namespace std;

struct Variable {
    string name;
    RunTimeVal *value;
};

bool is_declared(string name, vector<Variable> *variables);
Variable declared(string name, RunTimeVal *value, vector<Variable> *variables);
RunTimeVal *lookup(string name, vector<Variable> *variables);
Variable make_variable(string name, RunTimeVal *value);

#endif // VARIABLE_H