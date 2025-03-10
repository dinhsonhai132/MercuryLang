#ifndef MERCURY_RUNTIME_HEADER
#define MERCURY_RUNTIME_HEADER
#include <string>
using namespace std;

#define _Number "Number"
#define _Null "Null"
#define _String "String"

struct RunTimeVal {
    float value;
    string type;
};

#endif // MERCURY_RUNTIME_HEADER