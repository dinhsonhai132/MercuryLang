#include <Mercury.h>

START_DLL 

__mer_core_lib_api__ __builtin_func_t __io_puts_value(mString_T *__string) {
    vector<Mer_uint8_t> cont = __string->buff;

    for (auto &item : cont) {
        fwrite(to_char(item), 1, 1, stdout);
    }
}

DLL_EXPORT table* builtin_puts(table* args[]) {
    table *obj = args[0];

    if (obj->is_str) {
        __io_puts_value(obj->f_str_v);
    } else {
        __io_cout_stdout(obj->cval);
    }

    return value(0);
}

END_DLL