#ifndef ENVI_H
#define ENVI_H

#include <map>
#include <string>
#include "eval.h"
#include "variable.h"

using namespace std;

class Envi {
private:
    Envi *parent;
    vector<Variable> variables;
public:

    Envi (Envi *parentENV) {
        this->parent = parentENV;
        this->variables = vector<Variable>();
    }

    RunTimeVal *MerEnvi_declare_var(string name, RunTimeVal *value, vector<Variable> *variables);
    RunTimeVal *MerEnvi_assign_var(string name, RunTimeVal *value, vector<Variable> *variables);
    Envi MerEnvi_resolve(string name, vector<Variable> &variables);
    RunTimeVal *MerEnvi_lookup(string name, vector<Variable> &variables);
};

#endif