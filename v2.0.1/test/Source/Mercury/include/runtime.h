#ifndef RUNTIME_H
#define RUNTIME_H

#include <string>
#include "parser.h"
#include "C:\Users\dinhs\Documents\Program Language\Mercury-Langluage-main\Mercury-Langluage-main\v2.0.1\test\Source\Parser\Lexer\ast.h"
#include "object.h"

using namespace std;

#define Number_t "number_type"
#define Null_t "null_type"
#define String_t "string_type"

struct RunTimeVal {
    string type;
    float value;

    MerObject *ovalue;
    string string_iden;
};

RunTimeVal valuelize(string type, float value);
RunTimeVal *valuelize_as_ptr(string type, float value);

#endif