#include "../include/bool.h"

mBool_T *make_bool(bool value) {
    mBool_T *boolen = MerCompiler_bool_new();
    if (value) {
        boolen->value = true;
    } else {
        boolen->value = false;
    }

    return boolen;
}