#ifndef ENVI_H
#define ENVI_H

#include <string>
#include <vector>
#include "runtime.h"
#include "variable.h"

using namespace std;

class Envi {
private:
    Envi *parent;
    vector<Variable> variables;

public:

    Envi(Envi *parent) {
        this->parent = parent;
    }

    RunTimeVal *MerEnvi_declare(string name, RunTimeVal *value);   
    RunTimeVal *MerEnvi_evaluate_identifier(string name);
    RunTimeVal *MerEnvi_lookup(string name, vector<Variable> *variables);
    Envi *MerEnvi_resolve(string name, RunTimeVal *value);
};

#endif