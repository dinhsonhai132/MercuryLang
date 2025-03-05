#include <string>
using namespace std;

#define _Number "Number"
#define _Null "Null"
#define _String "String"

struct RunTimeVal {
    float value;
    string type;
};

RunTimeVal valuelize(string type, float value) {
    return RunTimeVal{value, type};
}
RunTimeVal *valuelize_as_ptr(string type, float value) {
    return new RunTimeVal{value, type};
}