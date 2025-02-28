#ifndef RUNTIME_H
#define RUNTIME_H

#include <iostream>
#include <string>
#include <vector>

#include "object.h"
#include "parser.h"
using namespace std;

#define Number "number"
#define Null "null"
#define String "string"

struct RunTimeVal {
    string type;
    float value;

    MerObject *ovalue;
    string string_iden;
};

RunTimeVal valuelize(string type, float value);
RunTimeVal *valuelize_as_ptr(string type, float value);

#endif // RUNTIME_H