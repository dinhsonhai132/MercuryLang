#include "variable.h"

Variable declared(string name, RunTimeVal *value, vector<Variable> *variables) {
    if (is_declared(name, variables)) {
        throw runtime_error("Variable already declared: " + name);
    }

    if (value == NULL) {
        throw runtime_error("Variable value is null: " + name);
    }

    Variable variable {
        .name = name,
        .value = value
    };

    variables->push_back(variable);
    return variable;
}

RunTimeVal *lookup(string name, vector<Variable> *variables) {
    for (int i = 0; i < variables->size(); i++) {
        if (variables->at(i).name == name) {
            return variables->at(i).value;
        }
    }
    return NULL;
}

bool is_declared(string name, vector<Variable> *variables) {
    for (int i = 0; i < variables->size(); i++) {
        if (variables->at(i).name == name) {
            return true;
        }
    }
    return false;
}