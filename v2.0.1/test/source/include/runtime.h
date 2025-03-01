#ifndef RUNTIME_H
#define RUNTIME_H

#include <string>
using namespace std;

#define _Number "Number"
#define _Null "Null"
#define _String "String"

typedef struct MERCURY_RUNTIME_VALUE {
    float value;
    string type;
} RunTimeVal;

RunTimeVal valuelize(string type, float value);
RunTimeVal *valuelize_as_ptr(string type, float value);

#endif // RUNTIME_H