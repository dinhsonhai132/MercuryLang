#include "runtime.h"

RunTimeVal valuelize(string type, float value) {
    return RunTimeVal{value, type};
}
RunTimeVal *valuelize_as_ptr(string type, float value) {
    return new RunTimeVal{value, type};
}