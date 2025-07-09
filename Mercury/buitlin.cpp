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

float get_current_time() {
    auto now = std::chrono::high_resolution_clock::now();
    auto sec = std::chrono::duration<float>(now.time_since_epoch());
    return sec.count();
}

__mer_core_lib_api__ __builtin_func_t __builtin_mer_whats_time_is_it(stack *stk) {
    float __value = get_current_time();
    stack_push(MerCompiler_table_setup(__value, NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_read_line(stack *stk) {
    string input_line;
    getline(cin, input_line);

    mString_T* str = MerCompiler_string_new();
    for (char ch : input_line) {
        str->buff.push_back(ch);
    }
    str->size = str->buff.size();
    str->hash = __hash(str);

    table* tab = MerCompiler_Table_new();
    tab->is_str = true;
    tab->f_str_v = str;
    tab->cval = static_cast<float>(str->hash);

    stack_push(tab);
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

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_print(mObject_T *str) {
    return;
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __io_write(mString_T *__string) {
    vector<Mer_uint8_t> cont = __string->buff;

    for (auto &item : cont) {
        fwrite(to_char(item), 1, 1, stdout);
    }

    fwrite("\n", 1, 1, stdout);

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__io_write] [pass]" << endl;
    #endif
}

__mer_core_lib_api__ __builtin_func_t __io_puts(mString_T *__string) {
    vector<Mer_uint8_t> cont = __string->buff;

    for (auto &item : cont) {
        fwrite(to_char(item), 1, 1, stdout);
    }

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__io_write] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_to_string(stack *stk) {
    table *top = POP();
    
    if (top->is_str) {
        stack_push(top);
    } else {
        string str = to_string(top->cval);
        mString_T *str_obj = make_str_obj(str);
        table *str_tab = MerCompiler_Table_new();
        str_tab->is_str = true;
        str_tab->f_str_v = str_obj;
        str_tab->cval = static_cast<float>(str_obj->hash);
        stack_push(str_tab);
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_hash(stack *stk) {
    table *top = POP();
    if (top->is_str) {
        table *str_tab = MerCompiler_Table_new();
        str_tab->cval = top->cval;
        str_tab->value = str_tab->cval;
        stack_push(str_tab);
    } else {
        stack_push(top);
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_to_int(stack *stk) {
    table *top = POP();
    
    if (top->is_str) {
        string str = __convert_to_string(top->f_str_v);
        if (ISDIGIT(str)) {
            stack_push(MerCompiler_table_setup(to_float(str), NULL_UINT_8_T));
        } else {
            push_false_to_stack();
        }
    } else if (top->is_list) {
        push_false_to_stack();
    } else {
        stack_push(top);
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_print_global_stack(stack *stk) {
    for (auto &item : _G) {
        cout << int(item->address) << endl;
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_is_digit(stack *stk) {
    table *tab = POP();
    
    if (tab->is_str) {
        string str = __convert_to_string(tab->f_str_v);
        if (ISDIGIT(str)) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    } else {
        push_false_to_stack();
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_list(stack *stk) {
    table *list = POP();
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
            str_tab->cval = __hash(str);
            str_tab->value = str_tab->cval;

            val->list_v->args.push_back(str_tab);
            val->list_v->size++;
        }

        stack_push(val);
    }
    
    stack_push(val);
}

int __ContainsOnlySpaces(const vector<Mer_uint8_t>& cont) {
    for (const auto &item : cont) {
        if (item != 0x20) {
            return 0;
        }
    }
    return 1;
}


MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_empty(stack *stk) {
    table *list = POP();
    if (list->is_list) {
        if (list->list_v->size == 0) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    } else if (list->is_str) {
        if (__ContainsOnlySpaces(list->f_str_v->buff)) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    } else {
        push_true_to_stack();
    }
}

__mer_core_lib_api__ __builtin_func_t __builtin_mer_factorial(stack *stk) {
    table *num = POP();
    table *result = MerCompiler_Table_new();
    result = num;
    result->cval = ffactorial(num->cval);
    result->value = result->cval;
    stack_push(result);
}

vector<string> __split(string a, char b) {
    vector<string> result;
    string temp = "";

    for (char ch : a) {
        if (ch == b) {
            result.push_back(temp);
            temp.clear();
        } else {
            temp += ch;
        }
    }

    result.push_back(temp);
    return result;
}

mString_T *make_str_obj(string str) {
    mString_T *str_obj = MerCompiler_string_new();
    str_obj->buff.insert(str_obj->buff.end(), str.begin(), str.end());
    str_obj->size = str.size();
    str_obj->hash = __hash(str_obj);
    return str_obj;
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_split(stack *stk) {
    table *charac = POP();
    table *str = POP();

    string charac_str = __convert_to_string(charac->f_str_v);
    string str_str = __convert_to_string(str->f_str_v);
    char char_split = charac_str[0];
    vector<string> str_split = __split(str_str, char_split);
    table *list = MerCompiler_Table_new();
    list->is_list = true;
    list->list_v = MerCompiler_list_object_new();

    for (auto &item : str_split) {
        mString_T *str_obj = make_str_obj(item);
        table *str_tab = MerCompiler_Table_new();
        str_tab->is_str = true;
        str_tab->f_str_v = str_obj;
        str_tab->cval = static_cast<float>(str_obj->hash);
        list->list_v->args.push_back(str_tab);
        list->list_v->size++;
    }

    stack_push(list);
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_sub(stack *stk) {
    table *lstr = POP();
    table *rstr = POP();

    if (!lstr || !rstr) {push_false_to_stack();}

    if (lstr->is_str && lstr->is_str) {
        rstr->f_str_v->buff.insert(rstr->f_str_v->buff.end(),
        lstr->f_str_v->buff.begin(),
        lstr->f_str_v->buff.end());
        
        rstr->f_str_v->size += lstr->f_str_v->size;
        stack_push(rstr);
        return;
    } else if (lstr->is_list && lstr->is_list) {
        rstr->list_v->args.insert(rstr->list_v->args.end(),
        lstr->list_v->args.begin(), 
        lstr->list_v->args.end());

        rstr->list_v->size += lstr->list_v->size;
        stack_push(rstr);
        return;
    } else {
        rstr->cval += lstr->cval;
        rstr->value += lstr->value;
        stack_push(rstr);
        return;
    }
}

__builtin_func_t sleep_ms(int num) {
    num *= 1000;
    this_thread::sleep_for(chrono::milliseconds((num)));
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_sleep(stack *stk) {
    table *num = POP();
    sleep_ms(num->cval);
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_sqrt(stack *stk) {
    table *num = POP();
    stack_push(MerCompiler_table_setup(fsqrt(num->cval), NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_cos(stack *stk) {
    table *num = POP();
    stack_push(MerCompiler_table_setup(fcos(num->cval), NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_tan(stack *stk) {
    table *num = POP();
    stack_push(MerCompiler_table_setup(ftan(num->cval), NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_cot(stack *stk) {
    table *num = POP();
    stack_push(MerCompiler_table_setup(fcot(num->cval), NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_random(stack *stk) {
    stack_push(MerCompiler_table_setup(__randint(0 - INT_MAX, INT_MAX), NULL_UINT_8_T));    
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_randint(stack *stk) {
    table *start = POP();
    table *end = POP();
    int num1 = (int) start->cval;
    int num2 = (int) end->cval;
    int value = __randint(num2, num1);
    stack_push(MerCompiler_table_setup(value, NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_mer_sin(stack *stk) {
    table *num = POP();
    stack_push(MerCompiler_table_setup(fsin(num->cval), NULL_UINT_8_T));
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_is_my_fav_number(stack *stk) {
    table *my_fav_num = POP();

    if (my_fav_num->cval == 7) {
        __io_cout_stdout("Wow, you are true! 7 is my favorite number! Such a lucky programmer!\n");
        push_true_to_stack();
    } else {
        push_false_to_stack();
    }

}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_range(stack *stk) {
    table *start = POP();
    table *end = POP();

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
    stack_push(list_table);
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

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_same_string(stack *stk) {
    table *top = POP();
    if (top->is_str) {
        table *new_list = POP();
        if (__same(top->f_str_v->buff, new_list->f_str_v->buff)) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    } else if (top->is_list) {
        table *new_list = POP();
        bool same = false;

        if (top->list_v->size != new_list->list_v->size) {
            push_false_to_stack();
            return;
        }

        for (auto &item : top->list_v->args) {
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

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_cls(stack *stk) {
    for (int i = 0; i < stk->s_table->table.size(); i++) {
        table *top = POP();
        free(top);
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_date(stack *stk) {
    table *top = POP();

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

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_help(stack *stk) {
    cout << "MercuryLang CLI - Version " << CUSTOM_VERSION << ", by Dinh Son Hai" << endl;
    cout << "Usage: mercury [options] <filename>.mer\n";
    cout << "Options:\n";
    cout << "  -v\t\tShow version information\n";
    cout << "  -p\t\tStart the Mercury REPL\n";
    cout << "  -h\t\tShow this help message\n";
    cout << "  -o <filename> <target>\tCompile to a specific output file\n";
    cout << "  -m\t\tCompiled into readable mercury bytecode\n";
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_size(stack *stk) {
    table *top = POP();

    if (top->is_list) {
        stack_push(MerCompiler_table_setup(top->list_v->size, NULL_UINT_8_T));
    } else if (top->is_str) {
        stack_push(MerCompiler_table_setup(top->f_str_v->size, NULL_UINT_8_T));
    } else {
        stack_push(MerCompiler_table_setup(4, NULL_UINT_8_T));
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_io_write(stack *stk) {
    table *top = POP();

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
        if (top->bool_v->value) {
            __io_cout_stdout("true");
        } else {
            __io_cout_stdout("false");
        }
        __io_cout_stdout("\n");
    } else {
        __io_cout_stdout(top->cval);
        __io_cout_stdout("\n");
    }
    
    stack_push(value(0));
    
    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_io_write] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_puts_val(stack *stk) {
    table *top = POP();
    if (top->is_str) {
        mString_T *str_v = top->f_str_v;
        __io_puts(str_v);
    } else {
        __io_cout_stdout(top->cval);
    }
    
    stack_push(value(0));
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_watch(stack *stk) {
    table *top = POP();

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

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_eval(stack *stk) {
    table *top = POP();
    mString_T *str_v = top->f_str_v;
    Mer_real_string str = hash_to_string(str_v);
    float value = eval(str);
    stack_push(MerCompiler_table_setup(value, NULL_UINT_8_T));
    MerCompiler_free_string(str_v);
}


MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_push(stack *stk) {
    table *value = POP();
    table *list = POP();

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

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_type(stack *stk) {
    table *top = POP();
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

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_change_item(stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_change_item] [start]" << endl;
    #endif

    table *item = POP();
    table *index = POP();
    table *value = POP();

    if (value->is_list) {
        table *vvalue = (table *)value->list_v->args[index->cval];
        vvalue = item;
    }

    STACK_PUSH(stk, value);

    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_change_item] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_pop(stack *stk) {
    table *list = POP();

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

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_pause(stack *stk) {
    MER_PAUSE;
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __mer_builtin_exit(stack *stk) {
    MER_EXIT;
}