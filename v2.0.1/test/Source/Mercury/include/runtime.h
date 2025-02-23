#ifndef RUNTIME_H
#define RUNTIME_H

#include <string>
#include "parser.h"
#include "ast.h"
#include "object.h"

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

#endif
