#ifndef ENVI_H
#define ENVI_H
#include "core.h"
#include "error.h"
#include <unordered_map>
using namespace std;

typedef class Environment {
private:
    Environment* parent;
    unordered_map<string, RunTimeVal> var;
public:
    Environment(Environment* parentENV = nullptr) 
        : parent(parentENV), var(unordered_map<string, RunTimeVal>()) {}
    RunTimeVal declareVar(string name, RunTimeVal value);
    RunTimeVal assignVar(string name, RunTimeVal value);
    RunTimeVal lookupVar(string name);
    Environment* resolve(string var_name);
} envi;

#endif