#include "./include/buitlin.h"

MERCURY_API __mer_core_lib_api__ const char* to_char(Mer_uint8_t c) {
    static char s[1];
    s[0] = c;
    return s;
}

MERCURY_API __mer_core_lib_api__ void __builtin_print(mObject_T *str) {
    __io_write(str->type->str);
}

MERCURY_API __mer_core_lib_api__ void __io_write(mString_T *__string) {
    vector<Mer_uint8_t> cont = __string->buff;

    for (auto &item : cont) {
        fwrite(to_char(item), 1, 1, stdout);
    }

    fwrite("\n", 1, 1, stdout);

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__io_write] [pass]" << endl;
    #endif
}

__mer_core_lib_api__  Mer_real_string hash_to_string(mString_T *str) {
    Mer_real_string result = "";
    Mer_size_t size = str->size;
    vector<Mer_uint8_t> buff = str->buff;

    for (Mer_size_t i = 0; i < buff.size(); ++i) {
        result += buff[i];
    }

    return result;
}


MERCURY_API __mer_core_lib_api__ void __builtin_cls(stack *stk) {
    for (int i = 0; i < stk->s_table->table.size(); i++) {
        table *top = stk->s_table->table.back();
        stk->s_table->table.pop_back();
        free(top);
    }
}

MERCURY_API __mer_core_lib_api__ void __builtin_help(stack *stk) {

}

MERCURY_API __mer_core_lib_api__ void __builtin_io_write(stack *stk) {
    table *top = stk->s_table->table.back();
    mString_T *str_v = top->f_str_v;
    __io_write(str_v);
    top->f_str_v = NULL;
    delete str_v;
    stk->s_table->table.pop_back();

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_io_write] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ void __builtin_eval(stack *stk) {
    table *top = stk->s_table->table.back();
    stk->s_table->table.pop_back();
    mString_T *str_v = top->f_str_v;
    Mer_real_string str = hash_to_string(str_v);
    float value = eval(str);
    stk->s_table->table.push_back(MerCompiler_table_setup(value, NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ void __builtin_pause(stack *stk) {
    table *top = stk->s_table->table.back();
    stk->s_table->table.pop_back();
    if (top->cval == 0) {
        MER_PAUSE;
    }
}

MERCURY_API __mer_core_lib_api__ void __mer_builtin_exit(stack *stk) {
    exit(0);
}
