#include "include/envi.h"

RunTimeVal *Envi::MerEnvi_declare_var(string name, RunTimeVal *value, vector<Variable> *variables) {
    Variable var = declared(name, value, variables);
    return value;
}

