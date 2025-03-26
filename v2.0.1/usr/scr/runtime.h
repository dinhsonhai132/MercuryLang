#ifndef MERCURY_RUNTIME_HEADER
#define MERCURY_RUNTIME_HEADER
#include <string>
using namespace std;

#define _Mer_Number_ "_Mer_Number"
#define _Mer_Null_ "_Mer_Null"
#define _Mer_String "_Mer_String"

struct RunTimeVal {
    float value;
    string type;
};

#endif // MERCURY_RUNTIME_HEADER