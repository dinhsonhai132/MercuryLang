#include "../Include/buitlin.h"

__mer_core_data__ float __randint(int a, int b) {
    static random_device rd;
    static mt19937 gen(rd()); 
    uniform_int_distribution<> dis(a, b);
    return dis(gen);
}

 __mer_core_lib_api__ const char* to_char(Mer_uint8_t c) {
    static char s[1];
    s[0] = c;
    return s;
}

const float to_float(string c) {
    int idx = 0;
    float value = 0.0f;
    bool is_negative = false;
    if (c[idx] == '-') {
        is_negative = true;
        idx++;
    }
    for (; idx < c.length(); idx++) {
        value = value * 10 + (c[idx] - '0');
    }
    if (is_negative) {
        value = -value;
    }
    return value;
}

MERCURY_API __mer_core_lib_api__ void __builtin_mer_read_line(stack *stk) {
    string input_line;
    getline(cin, input_line);

    mString_T* str = MerCompiler_string_new();
    for (char ch : input_line) {
        str->buff.push_back(ch);
    }
    str->size = str->buff.size();

    table* tab = MerCompiler_Table_new();
    tab->is_str = true;
    tab->f_str_v = str;

    stk->s_table->table.push_back(tab);
}

int ISDIGIT(string str) {
    for (auto &ch : str) {
        if (!isdigit(ch)) {
            return 0;
        }
    }
    return 1;
}

__mer_core_lib_api__ string __convert_to_string(mString_T *__string) {
    string value = "";
    vector<Mer_uint8_t> cont = __string->buff;

    for (auto &item : cont) {
        value += to_char(item);
    }

    return value;
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

__mer_core_lib_api__ void __io_puts(mString_T *__string) {
    vector<Mer_uint8_t> cont = __string->buff;

    for (auto &item : cont) {
        fwrite(to_char(item), 1, 1, stdout);
    }

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__io_write] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ void __builtin_to_string(stack *stk) {
    table *top = pop_stack(stk);
    
    if (top->is_str) {
        stk->s_table->table.push_back(top);
        return;
    }
}

MERCURY_API __mer_core_lib_api__ void __builtin_to_int(stack *stk) {
    table *top = pop_stack(stk);
    
    if (top->is_str) {
        string str = __convert_to_string(top->f_str_v);
        if (ISDIGIT(str)) {
            stk->s_table->table.push_back(MerCompiler_table_setup(to_float(str), NULL_UINT_8_T));
        } else {
            stk->s_table->table.push_back(MerCompiler_table_setup(0, NULL_UINT_8_T));
        }
    } else if (top->is_list) {
        stk->s_table->table.push_back(MerCompiler_table_setup(0, NULL_UINT_8_T));
    } else {
        stk->s_table->table.push_back(top);
    }
}

MERCURY_API __mer_core_lib_api__ void __builtin_print_global_stack(stack *stk) {
    for (auto &item : _G) {
        cout << int(item->address) << endl;
    }
}

MERCURY_API __mer_core_lib_api__ void __builtin_mer_is_digit(stack *stk) {
    table *tab = pop_stack(stk);
    
    if (tab->is_str) {
        string str = __convert_to_string(tab->f_str_v);
        if (ISDIGIT(str)) {
            stk->s_table->table.push_back(MerCompiler_table_setup(1, NULL_UINT_8_T));
        } else {
            stk->s_table->table.push_back(MerCompiler_table_setup(0, NULL_UINT_8_T));
        }
    } else {
        stk->s_table->table.push_back(MerCompiler_table_setup(0, NULL_UINT_8_T));
    }
}

MERCURY_API __mer_core_lib_api__ void __builtin_mer_split(stack *stk) {
    table *list = pop_stack(stk);
    table *val = MerCompiler_Table_new();

    if (list->is_str) {
        val->is_list = true;
        val->list_v = MerCompiler_list_object_new();

        for (auto &charr : list->f_str_v->buff) {
            mString_T *str = MerCompiler_string_new();
            str->buff.push_back(charr);
            str->size = 1;

            table *str_tab = MerCompiler_Table_new();
            str_tab->is_str = true;
            str_tab->f_str_v = str;

            val->list_v->args.push_back(str_tab);
            val->list_v->size++;
        }

        stk->s_table->table.push_back(val);
    }
    
    stk->s_table->table.push_back(val);
}

MERCURY_API __mer_core_lib_api__ void __builtin_mer_sub(stack *stk) {
    table *lstr = pop_stack(stk);
    table *rstr = pop_stack(stk);

    if (!lstr || !rstr) stk->s_table->table.push_back(MerCompiler_table_setup(0, NULL_UINT_8_T));

    if (lstr->is_str && lstr->is_str) {
        rstr->f_str_v->buff.insert(rstr->f_str_v->buff.end(),
        lstr->f_str_v->buff.begin(),
        lstr->f_str_v->buff.end());
        
        rstr->f_str_v->size += lstr->f_str_v->size;
        stk->s_table->table.push_back(rstr);
        return;
    } else if (lstr->is_list && lstr->is_list) {
        rstr->list_v->args.insert(rstr->list_v->args.end(),
        lstr->list_v->args.begin(), 
        lstr->list_v->args.end());

        rstr->list_v->size += lstr->list_v->size;
        stk->s_table->table.push_back(rstr);
        return;
    } else {
        rstr->cval += lstr->cval;
        rstr->value += lstr->value;
        stk->s_table->table.push_back(rstr);
        return;
    }
}

void sleep_ms(int num) {
    num *= 1000;
    this_thread::sleep_for(chrono::milliseconds((num)));
}

MERCURY_API __mer_core_lib_api__ void __builtin_mer_sleep(stack *stk) {
    table *num = pop_stack(stk);
    sleep_ms(num->cval);
}

MERCURY_API __mer_core_lib_api__ void __builtin_mer_sqrt(stack *stk) {
    table *num = pop_stack(stk);
    stk->s_table->table.push_back(MerCompiler_table_setup(fsqrt(num->cval), NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ void __builtin_mer_cos(stack *stk) {
    table *num = pop_stack(stk);
    stk->s_table->table.push_back(MerCompiler_table_setup(fcos(num->cval), NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ void __builtin_mer_tan(stack *stk) {
    table *num = pop_stack(stk);
    stk->s_table->table.push_back(MerCompiler_table_setup(ftan(num->cval), NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ void __builtin_mer_cot(stack *stk) {
    table *num = pop_stack(stk);
    stk->s_table->table.push_back(MerCompiler_table_setup(fcot(num->cval), NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ void __builtin_random(stack *stk) {
    stk->s_table->table.push_back(MerCompiler_table_setup(__randint(0 - INT_MAX, INT_MAX), NULL_UINT_8_T));    
}

MERCURY_API __mer_core_lib_api__ void __builtin_randint(stack *stk) {
    table *start = pop_stack(stk);
    table *end = pop_stack(stk);
    stk->s_table->table.push_back(MerCompiler_table_setup(__randint(start->cval, end->cval), NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ void __builtin_mer_sin(stack *stk) {
    table *num = pop_stack(stk);
    stk->s_table->table.push_back(MerCompiler_table_setup(fsin(num->cval), NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ void __builtin_is_my_fav_number(stack *stk) {
    table *my_fav_num = pop_stack(stk);

    if (my_fav_num->cval == 7) {
        __io_cout_stdout("Wow, you are true! 7 is my favorite number! Such a lucky programmer!\n");
        stk->s_table->table.push_back(MerCompiler_table_setup(1, NULL_UINT_8_T));
    } else {
        stk->s_table->table.push_back(MerCompiler_table_setup(0, NULL_UINT_8_T));
    }

}

MERCURY_API __mer_core_lib_api__ void __builtin_range(stack *stk) {
    table *start = pop_stack(stk);
    table *end = pop_stack(stk);

    Mer_size_t start_int = start->cval;
    Mer_size_t end_int = end->cval;

    mList_T *list = MerCompiler_list_object_new();

    if (start_int > end_int) {
        for (Mer_size_t i = start_int; i > end_int; i--) {
            table *val = MerCompiler_table_setup(i, NULL_UINT_8_T);
            back_insrt(list->args, val);
        }
    } else {
        for (Mer_size_t i = start_int; i < end_int; i++) {
            table *val = MerCompiler_table_setup(i, NULL_UINT_8_T);
            back_insrt(list->args, val);
        }
    }

    table *list_table = MerCompiler_Table_new();
    list_table->is_list = true;
    list_table->list_v = list;
    list_table->list_v->size = list->args.size();
    list_table->cval = MERCURY_LIST_VALUE;
    stk->s_table->table.push_back(list_table);
}

__mer_core_api__ int __same(vector<Mer_uint8_t> a, vector<Mer_uint8_t> b) {
    if (a.size() != b.size()) {
        return 0;
    }

    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }

    return 1;
}

MERCURY_API __mer_core_lib_api__ void __builtin_same_string(stack *stk) {
    table *top = pop_stack(stk);
    if (top->is_str) {
        table *new_list = pop_stack(stk);
        if (__same(top->f_str_v->buff, new_list->f_str_v->buff)) {
            stk->s_table->table.push_back(MerCompiler_table_setup(1, NULL_UINT_8_T));
        } else {
            stk->s_table->table.push_back(MerCompiler_table_setup(0, NULL_UINT_8_T));
        }
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
        table *top = pop_stack(stk);
        free(top);
    }
}

MERCURY_API __mer_core_lib_api__ void __builtin_date(stack *stk) {
    table *top = pop_stack(stk);

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
    cout << "MercuryLang CLI - Version " << CUSTOM_VERSION << ", by Dinh Son Hai" << endl;
    cout << "Usage: mercury [options] <filename>.mer\n";
    cout << "Options:\n";
    cout << "  -v\t\tShow version information\n";
    cout << "  -p\t\tStart the Mercury REPL\n";
    cout << "  -h\t\tShow this help message\n";
    cout << "  -o <filename> <target>\tCompile to a specific output file\n";
    cout << "  -m\t\tCompiled into readable mercury bytecode\n";
}

MERCURY_API __mer_core_lib_api__ void __builtin_size(stack *stk) {
    table *top = pop_stack(stk);

    if (top->is_list) {
        stk->s_table->table.push_back(MerCompiler_table_setup(top->list_v->size, NULL_UINT_8_T));
    } else if (top->is_str) {
        stk->s_table->table.push_back(MerCompiler_table_setup(top->f_str_v->size, NULL_UINT_8_T));
    } else {
        stk->s_table->table.push_back(MerCompiler_table_setup(4, NULL_UINT_8_T));
    }

}

MERCURY_API __mer_core_lib_api__ void __builtin_io_write(stack *stk) {
    table *top = pop_stack(stk);

    if (top->is_str) {
        mString_T *str_v = top->f_str_v;
        __io_write(str_v);
    } else if (top->is_list) {
        __io_cout_stdout("[")

        if (top->list_v->size == 1) {
            table *value = (table *) top->list_v->args[0];
            if (value->is_str) {
                mString_T *str_v = value->f_str_v;
                __io_cout_stdout("\"");
                __io_puts(str_v);
                __io_cout_stdout("\"");
            } else {
                __io_cout_stdout(value->cval);
            }
        } else {
            for (Mer_size_t i = 0; i < top->list_v->size; i++) {
                table *value = (table *) top->list_v->args[i];
                if (value->is_str) {
                    mString_T *str_v = value->f_str_v;
                    __io_cout_stdout("\"");
                    __io_puts(str_v);
                    __io_cout_stdout("\"");
                } else {
                    __io_cout_stdout(value->cval);
                }
                if (i != top->list_v->size - 1) {
                    __io_cout_stdout(", ");
                }
            }
        }
        
        __io_cout_stdout("]");
        __io_cout_stdout("\n");
    } else if (top->is_bool) {
        __io_cout_stdout(top->bool_v->value ? "true" : "false");
        __io_cout_stdout("\n");
    } else {
        __io_cout_stdout(top->cval);
        __io_cout_stdout("\n");
    }

    stk->s_table->table.push_back(MerCompiler_table_setup(0, NULL_UINT_8_T));
    
    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_io_write] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ void __builtin_puts_val(stack *stk) {
    table *top = pop_stack(stk);
    if (top->is_str) {
        mString_T *str_v = top->f_str_v;
        __io_puts(str_v);
        stk->s_table->table.push_back(MerCompiler_table_setup(0, NULL_UINT_8_T));
    } else {
        __io_cout_stdout(top->cval);
        stk->s_table->table.push_back(top);
    }
}

MERCURY_API __mer_core_lib_api__ void __builtin_watch(stack *stk) {
    table *top = pop_stack(stk);

    if (top->is_list) {
        __io_cout_stdout("[")

        if (top->list_v->size == 1) {
            mValue_T *value = (mValue_T *)top->list_v->args[0];
            __io_cout_stdout(value->value_t.float_value);
        } else {
            for (Mer_size_t i = 0; i < top->list_v->size; i++) {
                table *value = (table *) top->list_v->args[i];
                __io_cout_stdout(value->cval);
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
    table *top = pop_stack(stk);
    mString_T *str_v = top->f_str_v;
    Mer_real_string str = hash_to_string(str_v);
    float value = eval(str);
    stk->s_table->table.push_back(MerCompiler_table_setup(value, NULL_UINT_8_T));
    MerCompiler_free_string(str_v);
}


MERCURY_API __mer_core_lib_api__ void __builtin_push(stack *stk) {
    table *value = pop_stack(stk);
    table *list = pop_stack(stk);

    if (list->is_list) {
        list->list_v->args.push_back(value);
        list->list_v->size++;
        STACK_PUSH(stk, list);
    } else {
        STACK_PUSH(stk, list);
    }

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_push] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ void __builtin_type(stack *stk) {
    table *top = pop_stack(stk);
    if (top->is_list) {
        STACK_PUSH(stk, MerCompiler_table_setup(MER_LIST_TYPE, NULL_UINT_8_T));
    } else if (top->is_str) {
        STACK_PUSH(stk, MerCompiler_table_setup(MER_STRING_TYPE, NULL_UINT_8_T));
    } else if (top->is_func) {
        STACK_PUSH(stk, MerCompiler_table_setup(MER_FUNCTION_TYPE, NULL_UINT_8_T));
    } else if (top->is_code) {
        STACK_PUSH(stk, MerCompiler_table_setup(MER_CODE_TYPE, NULL_UINT_8_T));
    } else {
        STACK_PUSH(stk, MerCompiler_table_setup(MER_FLOAT_TYPE, NULL_UINT_8_T));
    }
}

MERCURY_API __mer_core_lib_api__ void __builtin_change_item(stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_change_item] [start]" << endl;
    #endif

    table *item = pop_stack(stk);
    table *index = pop_stack(stk);
    table *value = pop_stack(stk);

    if (value->is_list) {
        table *vvalue = (table *)value->list_v->args[index->cval];
        vvalue = item;
    }

    STACK_PUSH(stk, value);

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_change_item] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ void __builtin_pop(stack *stk) {
    table *list = pop_stack(stk);

    if (list->is_list) {
        list->list_v->size--;

        if (list->list_v->size <= 0) {
            list->list_v->size = 0;
        } else {
            list->list_v->args.pop_back();
        }

        STACK_PUSH(stk, list);
    }
    
    STACK_PUSH(stk, list);

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_pop] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ void __builtin_pause(stack *stk) {
    MER_PAUSE;
}

MERCURY_API __mer_core_lib_api__ void __mer_builtin_exit(stack *stk) {
    MER_EXIT;
}