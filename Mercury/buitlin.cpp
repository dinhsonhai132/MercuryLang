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

__mer_core_api__ int __same(vector<Mer_uint8_t> a, vector<Mer_uint8_t> b) {
    if (a.size() != b.size()) {
        cerr << "Error: The two strings are not the same size" << endl;
        break_point();
    }

    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }

    return 1;
}

MERCURY_API __mer_core_lib_api__ void __builtin_same_string(stack *stk) {
    table *top = stk->s_table->table.back();
    stk->s_table->table.pop_back();
    if (top->is_str) {
        table *top1 = stk->s_table->table.back();
        stk->s_table->table.pop_back();
        if (__same(top->f_str_v->buff, top1->f_str_v->buff)) {
            stk->s_table->table.push_back(MerCompiler_table_setup(1, NULL_UINT_8_T));
        } else {
            stk->s_table->table.push_back(MerCompiler_table_setup(0, NULL_UINT_8_T));
        }

        free(top);
        free(top1);
    }
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

bool is_float(float value) {
    return (value - static_cast<int>(value)) != 0;
}

MERCURY_API __mer_core_lib_api__ void __builtin_cls(stack *stk) {
    for (int i = 0; i < stk->s_table->table.size(); i++) {
        table *top = stk->s_table->table.back();
        stk->s_table->table.pop_back();
        free(top);
    }
}

MERCURY_API __mer_core_lib_api__ void __builtin_help(stack *stk) {
    cout << "MercuryLang CLI - Version " << MERCURY_VERSION << endl;
    cout << "Usage: mercury [options] <filename>.mer\n";
    cout << "Options:\n";
    cout << "  -v\t\tShow version information\n";
    cout << "  -p\t\tStart the Mercury REPL\n";
    cout << "  -h\t\tShow this help message\n";
    cout << "  -o <filename> <target>\tCompile to a specific output file\n";
    cout << "  -m\t\tCompiled into readable mercury bytecode\n";
}

MERCURY_API __mer_core_lib_api__ void __builtin_io_write(stack *stk) {
    table *top = stk->s_table->table.back();
    stk->s_table->table.pop_back();

    if (top->is_str) {
        mString_T *str_v = top->f_str_v;
        __io_write(str_v);
    } else {
        __io_cout_int(top->cval);
    }


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
    MER_PAUSE;
}

MERCURY_API __mer_core_lib_api__ void __mer_builtin_exit(stack *stk) {
    MER_EXIT;
}
