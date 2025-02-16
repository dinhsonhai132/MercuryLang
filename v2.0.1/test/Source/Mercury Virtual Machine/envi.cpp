#include "./mercury virtual machine/envi.h"

RunTimeVal *Envi::MerEnvi_declare_var(string name, RunTimeVal *value) {
    if (is_declared(name, &this->variables)) {
        throw runtime_error("Variable already declared: " + name);
    }
    return value;
}

