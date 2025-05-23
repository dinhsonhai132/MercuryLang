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
        table *new_list = stk->s_table->table.back();
        stk->s_table->table.pop_back();
        if (__same(top->f_str_v->buff, new_list->f_str_v->buff)) {
            stk->s_table->table.push_back(MerCompiler_table_setup(1, NULL_UINT_8_T));
        } else {
            stk->s_table->table.push_back(MerCompiler_table_setup(0, NULL_UINT_8_T));
        }

        free(top);
        free(new_list);
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

MERCURY_API __mer_core_lib_api__ void __builtin_date(stack *stk) {
    table *top = stk->s_table->table.back();
    stk->s_table->table.pop_back();

    if (top->cval == 1) {
        time_t t = time(0);
        tm *now = localtime(&t);
        cout << now->tm_year + 1900 << "-" << now->tm_mon + 1 << "-" << now->tm_mday << endl;
    } else if (top->cval == 2) {
        time_t t = time(0);
        tm *now = localtime(&t);
        cout << now->tm_year + 1900 << "-" << now->tm_mon + 1 << "-" << now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << endl;
    } else if (top->cval == 3) {
        time_t t = time(0);
        tm *now = localtime(&t);
        cout << now->tm_year + 1900 << "-" << now->tm_mon + 1 << "-" << now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " " << now->tm_wday << endl;
    }
}

MERCURY_API __mer_core_lib_api__ void __builtin_help(stack *stk) {
    cout << "MercuryLang CLI - Version " << MERCURY_VERSION << ", by Dinh Son Hai" << endl;
    cout << "Usage: mercury [options] <filename>.mer\n";
    cout << "Options:\n";
    cout << "  -v\t\tShow version information\n";
    cout << "  -p\t\tStart the Mercury REPL\n";
    cout << "  -h\t\tShow this help message\n";
    cout << "  -o <filename> <target>\tCompile to a specific output file\n";
    cout << "  -m\t\tCompiled into readable mercury bytecode\n";
}

MERCURY_API __mer_core_lib_api__ void __builtin_size(stack *stk) {
    table *top = stk->s_table->table.back();
    stk->s_table->table.pop_back();

    if (top->is_in_glb) {
        Mer_uint8_t address = top->address;

        for (auto &item : _G) {
            if (item->address == address) {
                top = item->tab;
                break;
            }
        }
    }

    Mer_size_t size = 0;
    if (top->is_list) {
        stk->s_table->table.push_back(MerCompiler_table_setup(top->list_v->size, NULL_UINT_8_T));
    } else if (top->is_str) {
        stk->s_table->table.push_back(MerCompiler_table_setup(top->f_str_v->size, NULL_UINT_8_T));
    }
}

MERCURY_API __mer_core_lib_api__ void __builtin_io_write(stack *stk) {
    table *top = stk->s_table->table.back();
    stk->s_table->table.pop_back();

    if (top->is_str) {
        mString_T *str_v = top->f_str_v;
        __io_write(str_v);

        stk->s_table->table.push_back(MerCompiler_table_setup(0, NULL_UINT_8_T));

        free(str_v);
    } else {
        __io_cout_stdout(top->cval);
        __io_cout_stdout("\n");
        stk->s_table->table.push_back(top);

        stk->s_table->table.push_back(MerCompiler_table_setup(0, NULL_UINT_8_T));

        free(top);
    }

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_io_write] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ void __builtin_watch(stack *stk) {
    table *top = stk->s_table->table.back();
    stk->s_table->table.pop_back();

    if (top->is_in_glb) {
        Mer_uint8_t address = top->address;

        for (auto &item : _G) {
            if (item->address == address) {
                top = item->tab;
                break;
            }
        }
    }

    if (top->is_list) {
        __io_cout_stdout("[")

        if (top->list_v->size == 1) {
            mValue_T *value = (mValue_T *)top->list_v->args[0];
            __io_cout_stdout(value->value_t.float_value);
        } else {
            for (Mer_size_t i = 0; i < top->list_v->size; i++) {
                mValue_T *value = (mValue_T *)top->list_v->args[i];
                __io_cout_stdout(value->value_t.float_value);
                if (i != top->list_v->size - 1) {
                    __io_cout_stdout(", ");
                }
            }
        }
        
        __io_cout_stdout("]");
        __io_cout_stdout("\n");
    }

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_print_list] [pass]" << endl;
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

MERCURY_API __mer_core_lib_api__ void __builtin_push(stack *stk) {
    table *value = stk->s_table->table.back();
    stk->s_table->table.pop_back();

    table *list = stk->s_table->table.back();
    stk->s_table->table.pop_back();

    if (list->is_in_glb) {
        Mer_uint8_t address = list->address;

        for (auto &item : _G) {
            if (item->address == address) {
                list = item->tab;
                break;
            }
        }
    } else {
        stk->s_table->table.push_back(MerCompiler_table_setup(0, NULL_UINT_8_T));
        return;
    }

    if (list->is_list) {
        list->list_v->size++;

        mValue_T *vvalue = MerCompiler_val_new();
        vvalue->f_value = value->cval;
        vvalue->value_t.float_value = value->cval;

        list->list_v->args.push_back((mValue_T *)vvalue);

        mList_T *new_list = MerCompiler_list_object_new();
        new_list->args = list->list_v->args;
        new_list->size = list->list_v->size;
        new_list->ui8_address = list->address;

        table *new_top = MerCompiler_Table_new();
        new_top->is_list = true;
        new_top->list_v = new_list;
        new_top->list_v->size = list->list_v->size;
        new_top->cval = MERCURY_LIST_VALUE;

        stk->s_table->table.push_back(new_top);
    }

    stk->s_table->table.push_back(list);

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_push] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ void __builtin_pop(stack *stk) {
    table *list = stk->s_table->table.back();
    stk->s_table->table.pop_back();

    if (list->is_in_glb) {
        Mer_uint8_t address = list->address;

        for (auto &item : _G) {
            if (item->address == address) {
                list = item->tab; // point to the list in global
                break;
            }
        }
    }

    if (list->is_list) {
        mList_T *new_list = MerCompiler_list_object_new();
        list->list_v->size--; // change the real list, this part got me 1 month to understand how pointer work

        if (list->list_v->size <= 0) {
            list->list_v->size = 0;
        } else {
            list->list_v->args.pop_back(); // change the list
        }

        new_list->args = list->list_v->args;
        new_list->size = list->list_v->size;
        new_list->ui8_address = list->address;

        table *new_table = MerCompiler_Table_new(); // creat a new list value because this function return a list value
        new_table->is_list = true;
        new_table->list_v = new_list;
        new_table->address = list->address;

        stk->s_table->table.push_back(new_table);
    }

    stk->s_table->table.push_back(list);
}

MERCURY_API __mer_core_lib_api__ void __builtin_pause(stack *stk) {
    MER_PAUSE;
}

MERCURY_API __mer_core_lib_api__ void __mer_builtin_exit(stack *stk) {
    MER_EXIT;
}
