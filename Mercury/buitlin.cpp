#include "./include/buitlin.h"

MERCURY_API void __builtin_print(mObject_T *str) {
    vector<Mer_uint8_t> buf = str->type->str->str->raw;
    for (int i = 0; i < buf.size(); i++) {
        fputc(mer_to_string(buf[i]), stdout);
    }
}
