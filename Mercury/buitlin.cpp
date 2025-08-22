#include "../include/buitlin.h"

__mer_core_data__ float __randint(int a, int b) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis;

    dis.param(std::uniform_int_distribution<int>::param_type(a, b));
    return static_cast<float>(dis(gen));
}

__mer_core_data__ float __random() {
    static std::random_device rd;
    static std::mt19937 gen(rd()); 
    static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
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

const int to_int(string c) {
    return int(to_float(c));
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

__mer_core_lib_api__ __builtin_func_t __builtin_mer_is_digit(stack *stk) {
    table *top = POP();
    
    if (top->is_str) {
        string str = __convert_to_string(top->f_str_v);
        if (ISDIGIT(str)) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    } else {
        push_false_to_stack();
    }
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
        mString_T *str_obj = creat_string_obj(str);
        table *str_tab = MerCompiler_Table_new();
        str_tab->is_str = true;
        str_tab->f_str_v = str_obj;
        str_tab->cval = static_cast<float>(str_obj->hash);
        stack_push(str_tab);
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_to_int(stack *stk) {
    table *top = POP();
    
    if (top->is_str) {
        string str = __convert_to_string(top->f_str_v);
        if (ISDIGIT(str)) {
            stack_push(MerCompiler_table_setup(to_int(str), NULL_UINT_8_T));
        } else {
            push_false_to_stack();
        }
    } else if (top->is_list) {
        push_false_to_stack();
    } else {
        stack_push(MerCompiler_table_setup(int(top->cval), NULL_UINT_8_T));
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_print_global_stack(stack *stk) {
    for (auto &item : _G) {
        cout << int(item->address) << endl;
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

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_random(stack *stk) {
    stack_push(MerCompiler_table_setup(__random(), NULL_UINT_8_T));
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
            val->ref_count++;
            back_insrt(list->args, val);
        }
    } else {
        for (Mer_size_t i = start_int; i < end_int; i++) {
            table *val = MerCompiler_table_setup(i, NULL_UINT_8_T);
            val->ref_count++;
            back_insrt(list->args, val);
        }
    }

    table *list_table = MerCompiler_Table_new();
    list_table->is_list = true;

    list_table->list_v = list;
    list_table->list_v->size = list->args.size();
    stack_push(list_table);

    push_to_gc(start);
    push_to_gc(end);
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
    table *item1 = POP();
    table *item2 = POP();

    if (item1->is_str && item2->is_str) {
        if (__same(item1->f_str_v->buff, item2->f_str_v->buff)) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    } else if (item1->is_list && item2->is_list) {
        if (item1->list_v->size == item2->list_v->size) {
            for (int i = 0; i < item1->list_v->size; i++) {
                if (item1->list_v->args[i] != item2->list_v->args[i]) {
                    push_false_to_stack();
                    return;
                }
            }

            push_true_to_stack();

        } else {
            push_false_to_stack();
        }
    } else if (item1->is_bool && item2->is_bool) {
        if (item1->bool_v->value == item2->bool_v->value) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    } else if (item1->cval == item2->cval) {
        push_true_to_stack();
    } else {
        push_false_to_stack();
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

    push_to_gc(top);

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
    } else if (top->is_class || top->is_instance) {
        cout << "<Address of object: " << "0x" << hex << setfill('0') << setw(2) << (int)top->class_v->address << ">" << endl;
    } else {
        __io_cout_stdout(top->cval);
        __io_cout_stdout("\n");
    }

    table* value = MER_VALUE(0);
    stack_push(value);
    
    #ifdef SYSTEM_TEST
    cout << "[buitlin.cpp] [__builtin_io_write] [pass]" << endl;
    #endif
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_puts_val(stack *stk) {
    table *top = POP();

    push_to_gc(top);

    if (top->is_str) {
        mString_T *str_v = top->f_str_v;
        __io_puts(str_v);
    } else {
        __io_cout_stdout(top->cval);
    }
    
    stack_push(MER_VALUE(0));
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
    } else if (top->is_bool) {
        STACK_PUSH(stk, MerCompiler_table_setup(MER_BOOL_TYPE, NULL_UINT_8_T));
    } else {
        STACK_PUSH(stk, MerCompiler_table_setup(MER_FLOAT_TYPE, NULL_UINT_8_T));
    }
}

MERCURY_API __mer_core_lib_api__ __builtin_func_t __builtin_pop(stack *stk) {
    table *list = POP();

    if (list->is_list) {
        list->list_v->size--;
        table *val = nullptr;

        if (list_size(list) <= 0) {
            set_size(list, 0);
        } else {
            val = (table *) list->list_v->args.back();
            list->list_v->args.pop_back();
        }

        STACK_PUSH(stk, val);
        return;
    }
    
    STACK_PUSH(stk, MerCompiler_table_setup(0, NULL_UINT_8_T));

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

typedef table*(*Function_ffi)(table*[]);

table* dll_load_func(string dll_path, string func, vector<table*> args) {
#ifdef _WIN32
    HMODULE hModule = LoadLibraryA(dll_path.c_str());

    if (!hModule) {
        cerr << "Failed to load DLL: " << dll_path << endl;
        FreeLibrary(hModule);
        return nullptr;
    }

    FARPROC pFunc = GetProcAddress(hModule, func.c_str());

    if (!pFunc) {
        cerr << "Failed to find function: " << func << endl;
        FreeLibrary(hModule);
        return nullptr;
    }

    Function_ffi sumFunc = (Function_ffi)pFunc;

    table* result = sumFunc(args.data());

    return result;

#else   
    cerr << "FFI is not supported on this platform." << endl;
#endif
}

MERCURY_API __mer_core_api__ __builtin_func_t __builtin_dll_load_func(stack *stk) {
    table *args = POP();
    table *func_to_call = POP();
    table *path_to_dll = POP();

    vector<table*> args_list;

    if (args->is_list) {
        for (auto &item : args->list_v->args) {
            table *val = (table *) item;
            args_list.push_back(val);
        }
    }

    if (!func_to_call->is_str || !path_to_dll->is_str) {
        return;
    }
    
    string dll_path = __convert_to_string(path_to_dll->f_str_v);
    string func = __convert_to_string(func_to_call->f_str_v);
    
    table* result = dll_load_func(dll_path, func, args_list);

    if (result) {
        stack_push(result);
    } else {
        stack_push(MerCompiler_table_setup(0, NULL_UINT_8_T));
    }

    push_to_gc(args);
    push_to_gc(func_to_call);
    push_to_gc(path_to_dll);
}