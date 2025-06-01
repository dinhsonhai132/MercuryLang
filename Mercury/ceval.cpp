#include "../Include/ceval.h"

__program_bytecode init_program_bytecode(mCode_T & code)
{
    __program_bytecode u = {code};
    u.iid = 0;
    u.oid = 0;
    u.icode = 0;
    u.ocode = 0;
    u.loop_size = 0;
    u.is_in_func = false;
    u.hash = 0x00;
    u.label_map = {};
    u.glb_id = u.lc_id = 0;
    u.file = code.cfile;
    return u;
}

unordered_map<Mer_uint8_t, Mer_size_t> __get_label_map(__program_bytecode &u) {

    Mer_uint8_t code = __get_next_code_in_prg_code(u);

    while (code != CPROGRAM_END) {
        if (code == CADDRESS) {
            Mer_uint8_t address = __get_next_code_in_prg_code(u);
            u.label_map[address] = u.iid;
        }
        code = __get_next_code_in_prg_code(u);
    }

    u.iid = 0; // reset it

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [__get_label_map] [pass]" << endl;
    #endif

    return u.label_map;
}

MERCURY_API Mer_uint8_t __get_next_code_in_prg_code(__program_bytecode &u) {
    return u.code.prg_code.buff[u.iid++];
}

MERCURY_API Mer_uint8_t __get_next_code_in_out_code(__program_bytecode &u) {
    return u.code.out_code.buff[u.oid++];
}

MERCURY_API stack *eval_program(mCode_T &code) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_program] [building...]" << endl;
    #endif

    __program_bytecode u_program = init_program_bytecode(code);
    stack *stk = MerCompiler_Stack_new();
    __get_label_map(u_program);


    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_program] [pass]" << endl;
    #endif

    return eval_statement(u_program, stk);
}

MERCURY_API __mer_core_api__ stack *eval_STORE_INDEX(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_STORE_INDEX] [building...]" << endl;
    #endif

    table *item = POP_STACK(stk);
    table *index = POP_STACK(stk); 
    table *value = POP_STACK(stk);

    if (value->is_list) {
        mValue_T *vvalue = (mValue_T *)value->list_v->args[index->cval];
        vvalue->f_value = item->cval;
        vvalue->value_t.float_value = item->cval;
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_STORE_INDEX] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API stack *eval_POP_JUMP_IF_FALSE(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_POP_JUMP_IF_FALSE] [building...]" << endl;
    #endif

    table *top = POP_STACK(stk);
    if (IS_FALSE(top->cval)) {
        Mer_uint8_t address = __get_next_code_in_prg_code(u);
        u.iid = u.label_map[address];
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_POP_JUMP_IF_FALSE] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API stack *eval_JUMP_IF_FALSE(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_JUMP_IF_FALSE] [building...]" << endl;
    #endif

    table *top = EAT_STACK(stk);
    if (IS_FALSE(top->cval)) {
        Mer_uint8_t address = __get_next_code_in_prg_code(u);
        u.iid = u.label_map[address];
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_JUMP_IF_FALSE] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API stack *eval_JUMP_TO(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_JUMP_TO] [building...]" << endl;
    #endif

    CONST(Mer_uint8_t) address = __get_next_code_in_prg_code(u);
    u.iid = u.label_map[address];

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_JUMP_TO] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_api__ stack *eval_BUILD_LIST(__program_bytecode &u, stack *stk) {
    Mer_uint8_t csize = __get_next_code_in_prg_code(u);
    Mer_size_t size = csize;
    mList_T *list = MerCompiler_list_object_new();
    
    for (Mer_size_t i = 0; i < size; i++) {
        table *top = POP_STACK(stk);
        mValue_T *v = MerCompiler_val_new();
        get_f(v) = top->cval;
        get_v(v) = top->cval;
        back_insrt(list->args, v);
        free(top);
    }

    table *top = MerCompiler_Table_new();
    top->is_list = true;
    top->list_v = list;
    top->list_v->size = size;
    top->cval = MERCURY_LIST_VALUE;

    stk->s_table->table.push_back(top);


    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_BUILD_LIST] [pass]" << endl;
    #endif
    
    return stk;
};

MERCURY_API __mer_core_api__ stack *eval_PUSH_NORMAL_MODE(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_PUSH_NORMAL_MODE] [building...]" << endl;
    #endif

    Mer_uint8_t ssize = __get_next_code_in_prg_code(u);
    Mer_size_t size = ssize;
    Mer_uint8_t code = __get_next_code_in_prg_code(u);
    vector<Mer_uint8_t> result;

    Mer_size_t t = 0;

    while (t < size) {
        result.push_back(code);
        code = __get_next_code_in_prg_code(u);
        ++t;
    }

    --u.iid;

    mString_T *str_v = MerCompiler_string_new();
    str_v->buff = result;
    str_v->hash = u.hash;
    u.hash += 0x01;
    str_v->size = size;

    hash_t hash = __hash(str_v);

    Mer_string_entry *entry = new Mer_string_entry();
    entry->hash_key = hash;
    entry->contents = str_v->buff;
    STRING_ENTRY.push_back(entry);
    
    table *top = MerCompiler_Table_new();
    top->f_str_v = str_v;
    top->cval = MERCURY_STRING_VALUE;
    top->is_str = true;

    stk->s_table->table.push_back(top);
    
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_PUSH_NORMAL_MODE] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API stack *eval_GET_ITEM(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_GET_ITEM] [building...]" << endl;
    #endif
    
    table *extract_val = POP_STACK(stk);
    table *obj = POP_STACK(stk);

    if (extract_val->cval >= obj->list_v->size) {
        MerDebug_system_error(SYSTEM_ERROR, "Index out of range", u.file);
    }

    if (obj->is_list) {
        mValue_T *value = (mValue_T *) obj->list_v->args[extract_val->cval];
        stk->s_table->table.push_back(MerCompiler_table_setup(value->f_value, NULL_UINT_8_T));
    } else {
        MerDebug_system_error(SYSTEM_ERROR, "Error while getting item from a list object", u.file);
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_GET_ITEM] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API stack *eval_statement(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_statement] [building...]" << endl;
    #endif

    for (;;) {
        Mer_uint8_t code = __get_next_code_in_prg_code(u);
        if (code == CPUSH_FLOAT) {
            stk = eval_PUSH_FLOAT(u, stk);
        } 
        
        else if (code == CBINARY_ADD 
            || code == CBINARY_SUB 
            || code == CBINARY_MUL 
            || code == CBINARY_DIV 
            || code == CBINARY_MOD) {
            stk = eval_BINARY_OPER(u, stk, code);
        } 
        
        else if (code == CLOAD_GLOBAL) {
            stk = eval_LOAD_GLOBAL(u, stk);
        } 
        
        else if (code == CSTORE_GLOBAL) {
            stk = eval_STORE_GLOBAL(u, stk);
        } 
        
        else if (code == CMAKE_FUNCTION) {
            stk = eval_MAKE_FUNCTION(u, stk);
        } 
        
        else if (code == CFUNCTION_CALL) {
            stk = eval_FUNCTION_CALL(u, stk);
        } 
        
        else if (code == CGREATER 
            || code == CEQUAL 
            || code == CNOT_EQUAL 
            || code == CGREATER_EQUAL 
            || code == CLESS_EQUAL 
            || code == CLESS) {
            stk = eval_COMPARE(u, stk, code);
        } 
        
        else if (code == CJUMP_TO) {
            stk = eval_JUMP_TO(u, stk);
        } 
        
        else if (code == CPRINT) {
            stk = eval_PRINT(u, stk);
        } 
        
        else if (code == CBUILD_LIST) {
            stk = eval_BUILD_LIST(u, stk);
        } 
        
        else if (code == CPUSH_NORMAL_MODE) {
            stk = eval_PUSH_NORMAL_MODE(u, stk);
        } 
        
        else if (code == CMAKE_BLOCK) {
            stk = eval_MAKE_BLOCK(u, stk);
        } 
        
        else if (code == CPOP_JUMP_IF_FALSE) {
            stk = eval_POP_JUMP_IF_FALSE(u, stk);
        } 
        
        else if (code == CGET_ITEM) {
            stk = eval_GET_ITEM(u, stk);
        } 
        
        else if (code == CRETURN || code == CEND_BLOCK || code == CPROGRAM_END) {
            break;
        } 
        
        else if (code == CSTORE_INDEX) {
            stk = eval_STORE_INDEX(u, stk);
        }
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_statement] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API stack *eval_COMPARE(__program_bytecode &u, stack *stk, Mer_uint8_t op) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_COMPARE] [building...]" << endl;
    #endif

    table *right = POP_STACK(stk);
    table *left = POP_STACK(stk);

    
    if (left == nullptr || right == nullptr) {
        MerDebug_system_error(SYSTEM_ERROR, "Stack underflow", u.file);
    }

    if (op == CLESS) {
        stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_LESS(left->cval, right->cval)));
    } else if (op == CGREATER) {
        stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_GREATER(left->cval, right->cval)));
    } else if (op == CEQUAL) {
        stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_EQUAL(left->cval, right->cval)));
    } else if (op == CNOT_EQUAL) {
        stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_NOT_EQUAL(left->cval, right->cval)));
    } else if (op == CGREATER_EQUAL) {
        stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_GREATER_EQUAL(left->cval, right->cval)));
    } else if (op == CLESS_EQUAL) {
        stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_LESS_EQUAL(left->cval, right->cval)));
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_COMPARE] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API stack *eval_BINARY_OPER(__program_bytecode &u, stack *stk, Mer_uint8_t op) {
    #ifdef SYSTEM_TEST    
    cout << "[ceval.cpp] [eval_BINARY_OPER] [building...]" << endl;
    #endif

    table *right = POP_STACK(stk);
    table *left = POP_STACK(stk);
    if (left == nullptr || right == nullptr) {
        MerDebug_system_error(SYSTEM_ERROR, "Stack underflow", u.file);
    }

    if (op == CBINARY_ADD) {
        stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_ADD(left->cval, right->cval)));
    } else if (op == CBINARY_SUB) {
        stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_SUB(left->cval, right->cval)));
    } else if (op == CBINARY_MUL) {
        stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_MUL(left->cval, right->cval)));
    } else if (op == CBINARY_DIV) {
        stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_DIV(left->cval, right->cval)));
    } else if (op == CBINARY_MOD) {
        stk->s_table->table.push_back(MerCompiler_table_setup(MERCURY_BINARY_MOD(static_cast<int>(left->cval), static_cast<int>(right->cval))));
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_BINARY_OPER] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API stack *eval_PUSH_FLOAT(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_PUSH_FLOAT] [building...]" << endl;
    #endif

    if (u.iid + 4 < u.code.prg_code.buff.size()) {
        Mer_uint32_t int_repr;
        Mer_float float_repr;
        memcpy(&int_repr, &u.code.prg_code.buff[u.iid], 4);
        memcpy(&float_repr, &int_repr, 4);
        stk->s_table->table.push_back(MerCompiler_table_setup(float_repr, NULL_UINT_8_T));
    }
    u.iid += 4;

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_PUSH_FLOAT] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API stack *eval_LOAD_GLOBAL(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_LOAD_GLOBAL] [building...]" << endl;
    #endif

    Mer_uint8_t code = __get_next_code_in_prg_code(u);

    for (Mer_size_t i = 0; i < _G.size(); i++) {
        if (_G[i]->address == code) {
            _G[i]->tab->cval = _G[i]->value;
            _G[i]->tab->address = _G[i]->address;
            stk->s_table->table.push_back(_G[i]->tab);
            return stk;
        }
    }

    return stk;
}

MERCURY_API stack *eval_STORE_GLOBAL(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_STORE_GLOBAL] [building...]" << endl;
    #endif

    Mer_uint8_t code = __get_next_code_in_prg_code(u);

    table *top = POP_STACK(stk);

    for (auto &sym : _G) {
        if (sym->address == code) {
            sym->value = top->cval;
            sym->tab = top;
            sym->tab->cval = top->cval;
            sym->tab->address = code;
            return stk;
        }
    }

    symtable *sym_value = MerCompiler_SymbolTable_new();

    sym_value->value = top->cval;
    sym_value->address = code;
    sym_value->tab = top;
    sym_value->tab->cval = top->cval;
    sym_value->tab->address = code;

    _G.push_back(sym_value);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_STORE_GLOBAL] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API stack *eval_MAKE_FUNCTION(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_MAKE_FUNCTION] [building...]" << endl;
    #endif

    Mer_uint8_t code = __get_next_code_in_prg_code(u);
    Mer_uint8_t address = code;

    symtable *func = MerCompiler_SymbolTable_new();

    vector<Mer_uint8_t> body;
    while (code != CRETURN) {
        code = __get_next_code_in_prg_code(u);
        body.push_back(code);
    }

    body.push_back(CRETURN);

    mFunc_object_T *func_obj = MerCompiler_func_object_new();
    
    func_obj->f_bc = MerCompiler_code_new_as_ptr();
    func_obj->f_bc->buff = body;
    func_obj->f_bc->raw = body;
    func_obj->raw_body = body;
    func_obj->body_size = body.size();
    func_obj->args_size = 0;
    func_obj->is_return = true;
    func_obj->is_global = true;
    func_obj->f_value = 0.0;

    func->address = address;
    func->value = MERCURY_FUNCTION_VALUE;
    func->cval = MERCURY_FUNCTION_VALUE;

    func->tab->cval = MERCURY_FUNCTION_VALUE;
    func->tab->address = address;
    func->tab->func_obj_v = func_obj;
    func->tab->is_func = true;

    _G.push_back(func);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_MAKE_FUNCTION] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API stack *eval_FUNCTION_CALL(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_FUNCTION_CALL] [building...]" << endl;
    #endif

    table *func = POP_STACK(stk);

    Mer_uint8_t func_address = func->address;

    if (func->is_func) {
        vector<Mer_uint8_t> body = func->func_obj_v->f_bc->buff;
        
        mCode_T code = NULL_CODE;
        code.prg_code.buff = body;
        code.csize = body.size();
        code.cfile = u.file;
        code.raw = body;

        __program_bytecode u_func = init_program_bytecode(code);
        u_func.is_in_func = true;
        __get_label_map(u_func);
        stk = eval_statement(u_func, stk);
    } else {
        Mer_uint8_t address = func->address;

        for (auto &func : mer_core_libs) {
            if (func.address == address) {
                using FuncType = void (*)(stack *);
                FuncType func_ptr = (FuncType)(func.func);
                func_ptr(stk);
                return stk;
            }
        }
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_FUNCTION_CALL] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API stack *eval_MAKE_BLOCK(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_MAKE_BLOCK] [building...]" << endl;
    #endif

    Mer_uint8_t code = __get_next_code_in_prg_code(u);
    symtable *block = MerCompiler_symboltable_setup("<address...>", 0, "AUTO_T", code);
    while (code != CEND_BLOCK) {
        code = __get_next_code_in_prg_code(u);
        block->tbody.push_back(code);
    }
    block->tbody.push_back(CEND_BLOCK);
    return stk;
}

MERCURY_API stack *eval_PRINT(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eval_PRINT] [building...]" << endl;
    #endif

    table *top = POP_STACK(stk);
    cout << top->cval << endl;
    free(top);
    return stk;

}

MERCURY_API __mer_core_api__ stack *eval_function(mFunc_object_T *func_obj, stack *stk, __program_bytecode &u) {
    vector<Mer_uint8_t> func_body = func_obj->raw_body;
    mCode_T body_c;
    body_c.prg_code.buff = func_body;
    return eval_statement(u, stk);
}