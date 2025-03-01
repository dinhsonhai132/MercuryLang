#include "./source/include/variable.h"

Variable make_variable(string name, RunTimeVal *value) {
    if (!value) {
        throw runtime_error("Variable value is null: " + name);
    }
    return { name, value };
}

Variable declared(string name, RunTimeVal *value, vector<Variable> *variables) {
    if (is_declared(name, variables)) {
        throw runtime_error("Variable already declared: " + name);
    }
    
    Variable variable = make_variable(name, value);
    variables->push_back(variable);
    return variable;
}
bool is_declared(string name, vector<Variable> *variables) {
    for (const auto& var : *variables) {
        if (var.name == name) return true;
    }
    return false;
}