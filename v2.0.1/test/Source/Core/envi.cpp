#include "envi.h"

RunTimeVal envi::declareVar(string name, RunTimeVal value) {
    if (this->var.find(name) != this->var.end()) {
        throw Mer_RuntimeError("Variable " + name + " already declared");
    }
    this->var[name] = value;
    return value;
}

RunTimeVal envi::assignVar(string name, RunTimeVal value) {
    envi* env = this->resolve(name);
    env->var[name] = value;
    return value;
}

RunTimeVal envi::lookupVar(string name) {
    envi* env = this->resolve(name);
    if (env->var.find(name) == env->var.end()) {
        throw Mer_RuntimeError("Variable " + name + " is not declared");
    }
    return env->var[name];
}

envi* envi::resolve(string var_name) {
    if (this->var.find(var_name) != this->var.end()) {
        return this;
    }

    if (this->parent == nullptr) {
        throw Mer_RuntimeError("Variable " + var_name + " is not declared");
    }

    return this->parent->resolve(var_name);
}
