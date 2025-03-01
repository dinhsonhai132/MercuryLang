#include "./source/include/envi.h"

RunTimeVal *Envi::MerEnvi_declare_var(string name, RunTimeVal *value, vector<Variable> *variables) {
    Variable var = declared(name, value, variables);
    return value;
}

RunTimeVal *Envi::MerEnvi_assign_var(string name, RunTimeVal *value, vector<Variable> *variables) {
    const Envi env = MerEnvi_resolve(name, *variables);
    return {};
}

Envi Envi::MerEnvi_resolve(string name, vector<Variable> &variables) {
    if (is_declared(name, &variables)) {
        return *this;
    }

    throw runtime_error("Variable not found: " + name);
    return Envi::MerEnvi_resolve(name, variables);
}