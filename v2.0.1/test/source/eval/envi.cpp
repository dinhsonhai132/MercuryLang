#include "./source/include/envi.h"

Envi::Envi (Envi *parentENV) {
    this->parent = parentENV;
    this->variables = vector<Variable>(); 
}

RunTimeVal *Envi::MerEnvi_declare_var(string name, RunTimeVal *value) {
    Variable *var = &declared(name, value, &this->variables);
    return var->value;
}

RunTimeVal *Envi::MerEnvi_assign_var(string name, RunTimeVal *value) {
    Envi env = MerEnvi_resolve(name);
    env.MerEnvi_declare_var(name, value);
}

Envi Envi::MerEnvi_resolve(string name) {
    if (is_declared(name, &this->variables)) {
        return *this;
    }

    if (this->parent) {
        return this->parent->MerEnvi_resolve(name);
    }

    throw runtime_error("Variable not found: " + name);
}

RunTimeVal *Envi::MerEnvi_lookup(string name) {
    for (auto& var : this->variables) {
        if (var.name == name) return var.value;
    }

    throw runtime_error("Variable not found: " + name);
}