#include "./include/envi.h"
#include "envi.h"

RunTimeVal *Envi::MerEnvi_declare(string name, RunTimeVal *value) {
    Variable var = make_variable(name, value);
    this->variables.push_back(var);
    return value;
}

RunTimeVal *Envi::MerEnvi_lookup(string name, vector<Variable> *variables) {
    for (int i = 0; i < variables->size(); i++) {
        if (variables->at(i).name == name) {
            return variables->at(i).value;
        }
    }

    return new RunTimeVal {
        .type = Null_t,
        .value = 0
    };
}

RunTimeVal *Envi::MerEnvi_evaluate_identifier(string name) {
    RunTimeVal *val = MerEnvi_lookup(name, &this->variables);
    if (val->type == Null_t) {
        throw runtime_error("Variable not found: " + name);
    }

    return val;
}

Envi *Envi::MerEnvi_resolve(string name, RunTimeVal *value) {
    if (is_declared(name, &this->variables)) {
        return this;
    }

    if (!this->parent) {
        throw runtime_error("Variable not found: " + name); 
    }

    return this->parent->MerEnvi_resolve(name, value);
}