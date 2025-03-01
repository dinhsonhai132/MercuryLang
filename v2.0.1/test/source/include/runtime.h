#ifndef RUNTIME_H
#define RUNTIME_H

#include <string>
using namespace std;

struct RunTimeVal {
    float value;
    string type;
};

RunTimeVal valuelize(string type, float value);
RunTimeVal *valuelize_as_ptr(string type, float value);

#endif // RUNTIME_H