#include "../include/vm.h"

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
    u.label_map = unordered_map<Mer_uint8_t, Mer_size_t>();
    u.glb_id = u.lc_id = 0;
    u.file = "stdin";
    return u;
}

unordered_map<Mer_uint8_t, Mer_size_t> __get_label_map(__program_bytecode &u, string mode) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [__get_label_map] [building...]" << endl;
    #endif

    Mer_uint8_t end = CPROGRAM_END;
    u.is_label = true;

    if (mode == "function") end = CEND_FUNCTION;

    Mer_uint8_t code = next_c(u);

    while (code != end) {
        if (code == CADDRESS) {
            Mer_uint8_t address = next_c(u);
            u.label_map[address] = u.iid;
        }

        code = next_c(u);
    }

    u.iid = 0;

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [__get_label_map] [pass]" << endl;
    #endif

    return u.label_map;
}

MERCURY_API Mer_uint8_t next_c(__program_bytecode &u) {
    return u.code.prg_code.buff[u.iid++];
}

MERCURY_API Mer_uint8_t next_o(__program_bytecode &u) {
    return u.code.out_code.buff[u.oid++];
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_program(mCode_T &code) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_program] [building...]" << endl;
    #endif

    __program_bytecode u_program = init_program_bytecode(code);
    stack *stk = MerCompiler_Stack_new();

    __get_label_map(u_program, "program");

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_program] [pass]" << endl;
    #endif

    return MerVM_evaluate_statement(u_program, stk);
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_statement(__program_bytecode &u, stack *stk) {
#ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_statement] [building...]" << endl;
#endif

    int counter = 0;

    for (;;) {
        Mer_uint8_t code = next_c(u);

        switch (code) {
            case CSTORE_ATTR:
                stk = MerVM_evaluate_STORE_ATTR(u, stk);
                break;
            
            case CCALL_METHOD:
                stk = MerVM_evaluate_CALL_METHOD(u, stk);
                break;

            case CLOAD_ATTR:
                stk = MerVM_evaluate_LOAD_ATTR(u, stk);
                break;

            case CGET_ITEM:
                stk = MerVM_evaluate_GET_ITEM(u, stk);
                break;

            case CSTORE_INDEX:
                stk = MerVM_evaluate_STORE_INDEX(u, stk);
                break;

            case CCLASS_BEGIN:
                stk = MerVM_evaluate_CLASS_BEGIN(u, stk);
                break;

            case CPUSH_FLOAT:
                stk = MerVM_evaluate_PUSH_FLOAT(u, stk);
                break;

            case CPUSH_NORMAL_MODE:
                stk = MerVM_evaluate_PUSH_NORMAL_MODE(u, stk);
                break;

            case CBUILD_LIST:
                stk = MerVM_evaluate_BUILD_LIST(u, stk);
                break;

            case CLOAD_GLOBAL:
                stk = MerVM_evaluate_LOAD_GLOBAL(u, stk);
                break;

            case CSTORE_GLOBAL:
                stk = MerVM_evaluate_STORE_GLOBAL(u, stk);
                break;

            case CMAKE_FUNCTION:
                stk = MerVM_evaluate_MAKE_FUNCTION(u, stk);
                break;

            case CFUNCTION_CALL:
                stk = MerVM_evaluate_FUNCTION_CALL(u, stk);
                break;

            case CBINARY_ADD:
            case CBINARY_SUB:
            case CBINARY_MUL:
            case CBINARY_DIV:
            case CBINARY_MOD:
            case CBINARY_POW:
                stk = MerVM_evaluate_BINARY_OPER(u, stk, code);
                break;

            case CGREATER:
            case CEQUAL:
            case CNOT_EQUAL:
            case CGREATER_EQUAL:
            case CLESS_EQUAL:
            case CLESS:
                stk = MerVM_evaluate_COMPARE(u, stk, code);
                break;

            case CJUMP_TO:
                u.iid = u.label_map[next_c(u)];
                break;

            case CPOP_JUMP_IF_FALSE: {
                table *top = POP();
                Mer_uint8_t address = next_c(u);

                if (IS_FALSE(top->cval)) {
                    u.iid = u.label_map[address];
                }

                push_to_gc(top);
                break;
            }

            case CNOT: {
                table *left = POP();

                if (left->cval) {
                    push_false_to_stack();
                } else {
                    push_true_to_stack();
                }
                break;
            }

            case CIS: {
                table *lhs = POP();
                table *rhs = POP();

                if (lhs == rhs) {
                    push_true_to_stack();
                } else {
                    push_false_to_stack();
                }
                break;
            }

            case CLEN: {
                table *obj = POP();
                push_to_gc(obj);

                if (obj->is_list) {
                    table* size = MER_VALUE(obj->list_v->size);
                    stack_push(size);
                }
                else if (obj->is_str) {
                    table* size = MER_VALUE(obj->f_str_v->size);
                    stack_push(size);
                }
                else {
                    table *size = MER_VALUE(obj->cval);
                    stack_push(size);
                }
                break;
            }

            case CPOP_TOP: {
                table *top = POP();
                push_to_gc(top);
                break;
            }

            case CLOAD_TRUE: {
                push_true_to_stack();
                break;
            }

            case CLOAD_FALSE: {
                push_false_to_stack();
                break;
            }

            case CAND: {
                table *cand_left = POP();
                table *cand_right = POP();

                if (cand_left->cval && cand_right->cval) {
                    push_true_to_stack();
                } else {
                    push_false_to_stack();
                }
                break;
            }

            case COR: {
                table *cor_left = POP();
                table *cor_right = POP();

                if (cor_left->cval || cor_right->cval) {
                    push_true_to_stack();
                } else {
                    push_false_to_stack();
                }
                break;
            }

            case CADDRESS:
                code = next_c(u);
                break;

            case CPROGRAM_START:
                continue;

            case CPROGRAM_END:
                goto program_end;
        }

        if (++counter >= GC_THRESHOLD) {
            GC_collect(GARBAGE_POOL, stk, u.file);
            counter = 0;
        }
    }

program_end:
#ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_statement] [pass]" << endl;
#endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_LOAD_METHOD(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_METHOD] [building...]" << endl;
    #endif

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_METHOD] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_CALL_METHOD(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_CALL_METHOD] [building...]" << endl;
    #endif

    table *func_obj = POP();
    table *class_obj = func_obj->class_p;

    if (!class_obj) {
        MerDebug_system_error(SYSTEM_ERROR, "Error while calling method", u.file);
    }

    if (func_obj->is_func) {
        Mer_uint8_t para_address = 0x00;
        vector<symtable*> _T;

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_CALL_METHOD] [pushing parameters... with size " << func_obj->func_obj_v->args_size << "]" << endl;
        #endif

        for (int i = 0; i < func_obj->func_obj_v->args_size; i++) {
            #ifdef SYSTEM_TEST
            cout << "[ceval.cpp] [MerVM_evaluate_CALL_METHOD] [pushing parameter " << i << " start]" << endl;
            #endif

            table *item = POP();

            #ifdef SYSTEM_TEST
            cout << "[ceval.cpp] [MerVM_evaluate_CALL_METHOD] [pushing parameter " << i << " pass]" << endl;
            #endif

            symtable *parameter = MerCompiler_symboltable_setup("", item->cval, "AUTO_T", NULL_UINT_8_T);  
            parameter->tab = item;
            parameter->tab->address = parameter->address;
            parameter->tab->ref_count++;

            _T.push_back(parameter);
        }

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_CALL_METHOD] [pushing parameters done!]" << endl;
        #endif

        reverse(_T.begin(), _T.end());

        for (auto &item : _T) {
            item->address = ++para_address;
        }

        mCode_T code = NULL_CODE;
        code.prg_code.buff = func_obj->func_obj_v->f_bc->buff;

        CallContext *ctx = new CallContext {
            .code = code,
            .caller = nullptr,
            .return_val = MerCompiler_Table_new(),
            .local = _T
        };

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_CALL_METHOD] [evaluating...]" << endl;
        #endif

        u.is_in_func = true;
        stk = MerVM_evaluate_call_context(ctx, u, stk);
        u.is_in_func = false;

        for (auto &item : ctx->local) {
            if (item->tab) {
                --item->tab->ref_count;
                push_to_gc(item->tab);
            }
        }

        std::vector<symtable*>().swap(ctx->local);
    } else {
        cerr << "Error: Call method is not a function" << endl;
        MER_BREAK_POINT;
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_CALL_METHOD] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_STORE_ATTR(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_STORE_ATTR] [building...]" << endl;
    #endif

    Mer_uint8_t address = next_c(u);

    table* value = POP();
    table* attr = POP();

    value->ref_count++;

    for (auto &item : attr->class_v->methods) {
        symtable *sym_item = (symtable *) item;
        if (sym_item->address == address) {
            if (--sym_item->tab->ref_count < 1) {
                push_to_gc(sym_item->tab);
            }

            sym_item->tab = value;
            sym_item->value = value->cval;
            break;
        }
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_STORE_ATTR] [pass]" << endl;
    #endif
    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_LOAD_ATTR(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_ATTR] [building...]" << endl;
    #endif

    Mer_uint8_t address = next_c(u);
    table *class_obj = POP();

    if (!class_obj->is_class || !class_obj->is_instance) {
        MerDebug_system_error(SYSTEM_ERROR, "Error while loading attribute", u.file);
    } 

    for (auto &item : class_obj->class_v->methods) {
        symtable *sym_item = (symtable *) item;
        if (sym_item->address == address) {
            table *tab = sym_item->tab;
            tab->cval = sym_item->value;
            tab->address = sym_item->address;
            tab->class_p = class_obj;
            stack_push(tab);
            break;
        }
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_ATTR] [pass]" << endl;
    #endif

    return stk;
}

__mer_core_data__ mClass_T *MerVM_class_evaluate_STORE_GLOBAL(__program_bytecode &u, stack *stk, mClass_T *cls) {
#ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_class_evaluate_STORE_GLOBAL] [building...]" << endl;
#endif
    Mer_uint8_t code = next_c(u);
    table *top = POP();

    symtable *sym_value = MerCompiler_SymbolTable_new();

    sym_value->value = top->cval;
    sym_value->address = code;
    sym_value->tab = top;
    sym_value->tab->cval = top->cval;
    sym_value->tab->address = code;

    cls->methods.push_back(sym_value);

#ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_class_evaluate_STORE_GLOBAL] [pass]" << endl;
#endif

    return cls;
}

__mer_core_data__ mClass_T *MerVM_class_evaluate_MAKE_FUNCTION(__program_bytecode &u, stack *stk, mClass_T *cls) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_class_evaluate_MAKE_FUNCTION] [building...]" << endl;
    #endif

    Mer_uint8_t code = next_c(u);
    Mer_uint8_t address = code;

    Mer_uint8_t args_size = next_c(u);
    
    symtable *func = MerCompiler_SymbolTable_new();

    vector<Mer_uint8_t> body;
    while (code != CEND_FUNCTION) {
        code = next_c(u);
        body.push_back(code);
    }

    body.push_back(CEND_FUNCTION);

    mFunc_object_T *func_obj = MerCompiler_func_object_new();
    
    func_obj->f_bc = MerCompiler_code_new_as_ptr();
    func_obj->f_bc->buff = body;
    func_obj->f_bc->raw = body;
    func_obj->raw_body = body;
    func_obj->body_size = body.size();
    func_obj->args_size = args_size;
    func_obj->is_return = true;
    func_obj->is_global = true;
    func_obj->f_value = 0.0;

    func->address = address;
    func->tab->func_obj_v = func_obj;
    func->tab->is_func = true;

    cls->methods.push_back(func);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_class_evaluate_MAKE_FUNCTION] [pass]" << endl;
    #endif

    return cls;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_CLASS_BEGIN(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_CLASS_BEGIN] [building...]" << endl;
    #endif
    Mer_uint8_t code = next_c(u);

    mClass_T *cls = MerCompiler_class_new();

    cls->address = code;

    code = next_c(u);

    table *class_obj = MerCompiler_Table_new();
    class_obj->is_class = true;

    while (code != CCLASS_END) {
        if (code == CPUSH_FLOAT) {
            stk = MerVM_evaluate_PUSH_FLOAT(u, stk);
        }

        else if (code == CLOAD_GLOBAL) {
            stk = MerVM_evaluate_LOAD_GLOBAL(u, stk);
        } 
        
        else if (code == CSTORE_GLOBAL) {
            cls = MerVM_class_evaluate_STORE_GLOBAL(u, stk, cls);
        } 
        
        else if (code == CMAKE_FUNCTION) {
            cls = MerVM_class_evaluate_MAKE_FUNCTION(u, stk, cls);
        } 
        
        else if (code == CFUNCTION_CALL) {
            stk = MerVM_evaluate_FUNCTION_CALL(u, stk);
        } 
        
        else if (code == CGREATER || code == CEQUAL || code == CNOT_EQUAL || code == CGREATER_EQUAL || code == CLESS_EQUAL || code == CLESS) {
            stk = MerVM_evaluate_COMPARE(u, stk, code);
        }

        else if (code == CBINARY_ADD || code == CBINARY_SUB || code == CBINARY_MUL || code == CBINARY_DIV || code == CBINARY_MOD || code == CBINARY_POW) {
            stk = MerVM_evaluate_BINARY_OPER(u, stk, code);
        } 
        
        else if (code == CJUMP_TO) {
            stk = MerVM_evaluate_JUMP_TO(u, stk);
        } 
        
        else if (code == CNOT) {
            stk = MerVM_evaluate_NOT(u, stk);
        }

        else if (code == CLEN) {
            stk = MerVM_evaluate_CLEN(u, stk);
        }

        else if (code == CBUILD_LIST) {
            stk = MerVM_evaluate_BUILD_LIST(u, stk);
        }
        
        else if (code == CPUSH_NORMAL_MODE) {
            stk = MerVM_evaluate_PUSH_NORMAL_MODE(u, stk);
        } 
        
        else if (code == CPOP_JUMP_IF_FALSE) {
            stk = MerVM_evaluate_POP_JUMP_IF_FALSE(u, stk);
        } 
        
        else if (code == CINC) {
            stk = MerVM_evaluate_INC(u, stk);
        }

        else if (code == CDEC) {
            stk = MerVM_evaluate_DEC(u, stk);
        }

        else if (code == CLOAD_TRUE) {
            stk = MerVM_evaluate_LOAD_TRUE(u, stk);
        }

        else if (code == CIS) {
            stk = MerVM_evaluate_IS(u, stk);
        }

        else if (code == CCLASS_END) {
            break;
        }
        
        else if (code == CLOAD_FALSE) {
            stk = MerVM_evaluate_LOAD_FALSE(u, stk);
        }
        
        else if (code == CGET_ITEM) {
            stk = MerVM_evaluate_GET_ITEM(u, stk);
        } 

        else if (code == CSTORE_INDEX) {
            stk = MerVM_evaluate_STORE_INDEX(u, stk);
        }

        else if (code == CDELETE) {
            stk = MerVM_evaluate_DELETE(u, stk);
        }

        else if (code == CADDRESS) {
            code = next_c(u);
        }

        else if (code == CAND) {
            stk = MerVM_evaluate_AND(u, stk);
        }

        else if (code == COR) {
            stk = MerVM_evaluate_OR(u, stk);
        }

        code = next_c(u);
    }

    class_obj->class_v = cls;

    symtable *sym_value = MerCompiler_SymbolTable_new();
    sym_value->tab = class_obj;
    sym_value->address = cls->address;
    
    _G.push_back(sym_value);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_CLASS_BEGIN] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_IS(__program_bytecode &u, stack *stk) {
    table *lhs = POP();
    table *rhs = POP();

    if (lhs == rhs) {
        push_true_to_stack();
    } else {
        push_false_to_stack();
    }

    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_DELETE(__program_bytecode &u, stack *stk) {
    table *del = POP();
    bool found = false;

    for (auto &item : u.is_in_func ? _L : _G) {
        if (item->address == del->address) {
            found = true;
            MerCompiler_free_symboltable(item);
        }
    }

    if (!found) {
        MerDebug_system_error(SYSTEM_ERROR, "no global variable to delete", u.file);
    }
    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_INC(__program_bytecode &u, stack *stk) {
    table *value = POP();
    value->cval += 1;
    value->value = value->cval;
    stack_push(value);
    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_DEC(__program_bytecode &u, stack *stk) {
    table *value = POP();
    value->cval -= 1;
    value->value = value->cval;
    stack_push(value);
    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_AND(__program_bytecode &u, stack *stk) {
    table *left = POP();
    table *right = POP();

    if (left->cval && right->cval) {
        push_true_to_stack();
    } else {
        push_false_to_stack();
    }

    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_OR(__program_bytecode &u, stack *stk) {
    table *left = POP();
    table *right = POP();

    if (left->cval || right->cval) {
        push_true_to_stack();
    } else {
        push_false_to_stack();
    }

    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_NOT(__program_bytecode &u, stack *stk) {
    table *left = POP();

    if (left->cval) {
        push_false_to_stack();
    } else {
        push_true_to_stack();
    }

    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_LOAD_TRUE(__program_bytecode &u, stack *stk) {
    push_true_to_stack();
    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_LOAD_FALSE(__program_bytecode &u, stack *stk) {
    push_false_to_stack();
    return stk;
}

MERCURY_API __mer_core_api__ stack *MerVM_evaluate_CLEN(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_GET_ITERATOR] [building...]" << endl;
    #endif

    table *obj = POP();

    push_to_gc(obj);

    if (obj->is_list) {
        table* size = MER_VALUE(obj->list_v->size);
        stack_push(size);
    }
    else if (obj->is_str) {
        table* size = MER_VALUE(obj->f_str_v->size);
        stack_push(size);
    }
    else {
        table *size = MER_VALUE(obj->cval);
        stack_push(size);
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_GET_ITERATOR] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_api__ __mer_core_data__ stack *MerVM_evaluate_STORE_INDEX(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_STORE_INDEX] [building...]" << endl;
    #endif

    table *item = POP();
    table *index = POP(); 
    table *value = POP();

    push_to_gc(index);

    if (value->is_list) {
        if (index->cval > value->list_v->size) {
            MerDebug_system_error(SYSTEM_ERROR, "Index out of range", u.file);
        }

        if (index->cval < 0) {
            index->cval += value->list_v->size;
        }
        table* existing_item = (table*)value->list_v->args[index->cval];
        existing_item->ref_count--;
        push_to_gc(existing_item);

        item->ref_count++;

        value->list_v->args[index->cval] = item;
    } else {
        MerDebug_system_error(SYSTEM_ERROR, "Can't store value to non-list", u.file);
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_STORE_INDEX] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_POP_JUMP_IF_FALSE(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_POP_JUMP_IF_FALSE] [building...]" << endl;
    #endif

    table *top = POP();
    Mer_uint8_t address = next_c(u);

    if (IS_FALSE(top->cval)) {
        u.iid = u.label_map[address];
    }

    push_to_gc(top);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_POP_JUMP_IF_FALSE] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_JUMP_IF_FALSE(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_JUMP_IF_FALSE] [building...]" << endl;
    #endif

    table *top = EAT_STACK(stk);
    Mer_uint8_t address = next_c(u);

    if (IS_FALSE(top->cval)) {
        u.iid = u.label_map[address];
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_JUMP_IF_FALSE] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_JUMP_TO(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_JUMP_TO] [building...]" << endl;
    #endif

    Mer_uint8_t address = next_c(u);
    u.iid = u.label_map[address];

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_JUMP_TO] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_api__ __mer_core_data__ stack *MerVM_evaluate_BUILD_LIST(__program_bytecode &u, stack *stk) {
    Mer_uint8_t csize = next_c(u);
    Mer_size_t size = csize;
    mList_T *list = MerCompiler_list_object_new();
    
    for (Mer_size_t i = 0; i < size; i++) {
        table *top = POP();
        top->ref_count++;

        back_insrt(list->args, top);
    }

    table *top = MerCompiler_Table_new();

    top->is_list = true;
    top->list_v = list;
    top->list_v->size = size;

    stack_push(top);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_BUILD_LIST] [pass]" << endl;
    #endif
    
    return stk;
};

MERCURY_API __mer_core_api__ __mer_core_data__ stack *MerVM_evaluate_PUSH_NORMAL_MODE(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_PUSH_NORMAL_MODE] [building...]" << endl;
    #endif

    Mer_uint8_t ssize = next_c(u);
    Mer_size_t size = ssize;
    Mer_uint8_t code = next_c(u);
    vector<Mer_uint8_t> result;

    Mer_size_t t = 0;

    while (t < size) {
        result.push_back(code);
        code = next_c(u);
        ++t;
    }

    --u.iid;

    mString_T *str_v = MerCompiler_string_new();

    str_v->buff = result;
    str_v->size = size;

    table *top = MerCompiler_Table_new();

    top->f_str_v = str_v;
    top->is_str = true;

    stack_push(top);
    
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_PUSH_NORMAL_MODE] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_GET_ITEM(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_GET_ITEM] [building...]" << endl;
    #endif
    
    table *extract_val = POP();
    table *obj = POP();

    push_to_gc(extract_val);
    push_to_gc(obj);

    if (!obj) {
        MerDebug_system_error(SYSTEM_ERROR, "Error while getting item from a list object", u.file);
    }

    if (!extract_val) {
        MerDebug_system_error(SYSTEM_ERROR, "Error while getting item from a list object, extract value", u.file);
    }

    if (obj->is_list) {
        if (extract_val->cval > obj->list_v->size) {
            MerDebug_system_error(SYSTEM_ERROR, "Index out of range", u.file);
        }

        if (extract_val->cval < 0) {
            extract_val->cval += obj->list_v->size;
        }

        table *value = (table *) obj->list_v->args[extract_val->cval];

        if (!value) {
            MerDebug_system_error(SYSTEM_ERROR, "Error while getting item from a list object", u.file);
        }
        
        stack_push(value);
    } else if (obj->is_str) {
        Mer_uint8_t code = obj->f_str_v->buff[extract_val->cval];
        mString_T *str = creat_char_obj(code);

        table *value = MerCompiler_Table_new();
        value->is_str = true;
        value->f_str_v = str;
        value->cval = static_cast<float>(str->hash);

        stack_push(value);
    } else {
        MerDebug_system_error(SYSTEM_ERROR, "Error while getting item from a list object", u.file);
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_GET_ITEM] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_COMPARE(__program_bytecode &u, stack *stk, Mer_uint8_t op) {
#ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_COMPARE] [building...]" << endl;
#endif

    table *right = POP();
    table *left = POP();

    push_to_gc(left);
    push_to_gc(right);

    auto compare_string = [](auto *a, auto *b) -> int {
        Mer_size_t min_size = std::min(a->size, b->size);
        for (Mer_size_t i = 0; i < min_size; ++i) {
            if (a->buff[i] < b->buff[i]) return -1;
            if (a->buff[i] > b->buff[i]) return 1;
        }
        if (a->size < b->size) return -1;
        if (a->size > b->size) return 1;
        return 0;
    };

    auto compare_list = [](auto *a, auto *b) -> int {
        Mer_size_t min_size = std::min(a->size, b->size);
        for (Mer_size_t i = 0; i < min_size; ++i) {
            table *ai = (table*)a->args[i];
            table *bi = (table*)b->args[i];
            if (ai->cval < bi->cval) return -1;
            if (ai->cval > bi->cval) return 1;
        }
        if (a->size < b->size) return -1;
        if (a->size > b->size) return 1;
        return 0;
    };

    int cmp = 0;
    if (left->is_str && right->is_str) {
        cmp = compare_string(left->f_str_v, right->f_str_v);
    } else if (left->is_list && right->is_list) {
        cmp = compare_list(left->list_v, right->list_v);
    } else {
        if (left->cval < right->cval) cmp = -1;
        else if (left->cval > right->cval) cmp = 1;
        else cmp = 0;
    }
    
    if (op == CLESS) {
        if (cmp < 0) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    }
    else if (op == CGREATER) {
        if (cmp > 0) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    }
    else if (op == CEQUAL) {
        if (cmp == 0) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    }
    else if (op == CNOT_EQUAL) {
        if (cmp != 0) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    }
    else if (op == CGREATER_EQUAL) {
        if (cmp >= 0) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    }
    else if (op == CLESS_EQUAL) {
        if (cmp <= 0) {
            push_true_to_stack();
        } else {
            push_false_to_stack();
        }
    }

#ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_COMPARE] [pass]" << endl;
#endif
    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_BINARY_OPER(__program_bytecode &u, stack *stk, Mer_uint8_t op) {
    #ifdef SYSTEM_TEST    
    cout << "[ceval.cpp] [MerVM_evaluate_BINARY_OPER] [building...]" << endl;
    #endif

    table *right = POP();
    table *left = POP();

    push_to_gc(left);
    push_to_gc(right);

    if (op == CBINARY_ADD) {
        if (left->is_list && right->is_list) {
            table *list_obj = MerCompiler_Table_new();
            list_obj->list_v = add_list(left->list_v, right->list_v);
            list_obj->is_list = true;
            stack_push(list_obj);
        } else if (left->is_str && right->is_str) {
            table *str_obj = MerCompiler_Table_new();
            str_obj->f_str_v = add_string(left->f_str_v, right->f_str_v);
            str_obj->is_str = true;
            stack_push(str_obj);
        } else {
            table *result = MerCompiler_table_setup(MERCURY_BINARY_ADD(left->cval, right->cval));
            stack_push(result);
        }
    } else if (op == CBINARY_SUB) {
        table *result = MerCompiler_table_setup(MERCURY_BINARY_SUB(left->cval, right->cval));
        stack_push(result);
    } else if (op == CBINARY_MUL) {
        if (left->is_list && !right->is_list) {
            table *list_obj = MerCompiler_Table_new();
            list_obj->list_v = mul_list(left->list_v, right->cval);
            list_obj->is_list = true;
            stack_push(list_obj);
        } else if (left->is_str && !right->is_str) {
            table *str_obj = MerCompiler_Table_new();
            str_obj->f_str_v = mul_string(left->f_str_v, right->cval);
            str_obj->is_str = true;
            stack_push(str_obj);
        } else if (right->is_list && !left->is_list) {
            table *list_obj = MerCompiler_Table_new();
            list_obj->list_v = mul_list(right->list_v, left->cval);
            list_obj->is_list = true;
            stack_push(list_obj);
        } else if (right->is_str && !left->is_str) {
            table *str_obj = MerCompiler_Table_new();
            str_obj->f_str_v = mul_string(right->f_str_v, left->cval);
            str_obj->is_str = true;
            stack_push(str_obj);
        } else {
            table *result = MerCompiler_table_setup(MERCURY_BINARY_MUL(left->cval, right->cval));
            stack_push(result);
        }
    } else if (op == CBINARY_DIV) {
        table *result = MerCompiler_table_setup(MERCURY_BINARY_DIV(left->cval, right->cval));
        stack_push(result);
    } else if (op == CBINARY_MOD) {
        table *result = MerCompiler_table_setup(MERCURY_BINARY_MOD(static_cast<int>(left->cval), static_cast<int>(right->cval)));
        stack_push(result);
    } else if (op == CBINARY_POW) {
        table *result = MerCompiler_table_setup(MERCURY_BINARY_POW(left->cval, right->cval));
        stack_push(result);
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_BINARY_OPER] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_PUSH_FLOAT(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_PUSH_FLOAT] [building...]" << endl;
    #endif

    if (u.iid + 4 < u.code.prg_code.buff.size()) {
        Mer_uint32_t int_repr;
        Mer_float float_repr;
        memcpy(&int_repr, &u.code.prg_code.buff[u.iid], 4);
        memcpy(&float_repr, &int_repr, 4);
        table *float_obj = MerCompiler_table_setup(float_repr, NULL_UINT_8_T);
        stack_push(float_obj);
    } else {
        MerDebug_system_error(SYSTEM_ERROR, "Stack underflow", u.file);
    }
    u.iid += 4;

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_PUSH_FLOAT] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_LOAD_GLOBAL(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_GLOBAL] [building...]" << endl;
    #endif

    Mer_uint8_t code = next_c(u);
    bool found = false;

    for (auto &item : _L) {
        if (item->address == code) {
            item->tab->cval = item->value;
            item->tab->address = item->address;
            stack_push(item->tab);
            found = true;
            break;
        }
    }

    if (!found) {
        for (auto &item : _G) {
            if (item->address == code) {
                item->tab->cval = item->value;
                item->tab->address = item->address;
                stack_push(item->tab);
                found = true;
                break;
            }
        }

        if (!found) {
            cerr << "global var dont exist " << "0x" << hex << setfill('0') << setw(2) << (int)code << endl;
            cerr << "at id " << u.iid << endl;
            MER_BREAK_POINT;
        }
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_GLOBAL] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_STORE_GLOBAL(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_STORE_GLOBAL] [building...]" << endl;
    #endif

    Mer_uint8_t code = next_c(u);

    table *top = POP();
    top->ref_count++;

    for (auto &sym : u.is_in_func ? _L : _G) {
        if (sym->address == code) {
            if (sym->tab != top) {
                --sym->tab->ref_count;
                push_to_gc(sym->tab);
            }   

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

    u.is_in_func ? _L.push_back(sym_value) : _G.push_back(sym_value);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_STORE_GLOBAL] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_MAKE_FUNCTION(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_MAKE_FUNCTION] [building...]" << endl;
    #endif

    Mer_uint8_t code = next_c(u);
    Mer_uint8_t address = code;

    Mer_uint8_t args_size = next_c(u);
    
    symtable *func = MerCompiler_SymbolTable_new();

    vector<Mer_uint8_t> body;
    while (code != CEND_FUNCTION) {
        code = next_c(u);
        body.push_back(code);
    }

    body.push_back(CEND_FUNCTION);

    mFunc_object_T *func_obj = MerCompiler_func_object_new();
    
    func_obj->f_bc = MerCompiler_code_new_as_ptr();
    func_obj->f_bc->buff = body;
    func_obj->f_bc->raw = body;
    func_obj->raw_body = body;
    func_obj->body_size = body.size();
    func_obj->args_size = args_size;
    func_obj->is_return = true;
    func_obj->is_global = true;
    func_obj->f_value = 0.0;

    func->address = address;
    func->value = 0;
    func->cval = 0;

    func->tab->cval = 0;
    func->tab->address = address;
    func->tab->func_obj_v = func_obj;
    func->tab->is_func = true;
    func->tab->ref_count++;

    _G.push_back(func);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_MAKE_FUNCTION] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_call_context_evaluate_LOAD_LOCAL(CallContext *ctx, __program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_call_context_evaluate_LOAD_LOCAL] [building...]" << endl;
    #endif

    Mer_uint8_t code = next_c(u);
    bool found = false;

    for (auto &item : ctx->local) {
        if (item->address == code) {
            item->tab->cval = item->value;
            item->tab->address = item->address;
            stack_push(item->tab);
            found = true;
            break;
        }
    }

    if (!found) {
        for (auto &item : _G) {
            if (item->address == code) {
                item->tab->cval = item->value;
                item->tab->address = item->address;
                stack_push(item->tab);
                found = true;
                break;
            }
        }

        if (!found) {
            cerr << "global var dont exist at local " << "0x" << hex << setfill('0') << setw(2) << (int)code << endl;
            cerr << "at id " << u.iid << endl;
            MER_BREAK_POINT;
        }
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_call_context_evaluate_LOAD_LOCAL] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_call_context_evaluate_STORE_LOCAL(CallContext *ctx, __program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_call_context_evaluate_STORE_LOCAL] [building...]" << endl;
    #endif

    Mer_uint8_t code = next_c(u);
    table *top = POP();

    for (auto &item : ctx->local) {
        if (item->address == code) {
            item->value = top->cval;
            item->address = code;
            item->tab = top;
            return stk;
        }
    }

    symtable *sym_value = MerCompiler_symboltable_setup("", top->cval, "AUTO_T", code);
    sym_value->tab = top;
    ctx->local.push_back(sym_value);

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_call_context_evaluate_STORE_LOCAL] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_call_context(CallContext *ctx, __program_bytecode &u, stack *stk) {
    __program_bytecode tmp = init_program_bytecode(ctx->code);    
    __get_label_map(tmp, "function");
    tmp.is_in_func = true;

    for (;;) {
        Mer_uint8_t code = next_c(tmp);

        if (code == CPUSH_FLOAT) {
            stk = MerVM_evaluate_PUSH_FLOAT(tmp, stk);
        }
        
        else if (code == CBINARY_ADD || code == CBINARY_SUB || code == CBINARY_MUL || code == CBINARY_DIV || code == CBINARY_MOD || code == CBINARY_POW) {
            stk = MerVM_evaluate_BINARY_OPER(tmp, stk, code);
        } 

        else if (code == CLOAD_GLOBAL) {
            stk = MerVM_call_context_evaluate_LOAD_LOCAL(ctx, tmp, stk);
        } 
        
        else if (code == CSTORE_GLOBAL) {
            stk = MerVM_call_context_evaluate_STORE_LOCAL(ctx, tmp, stk);
        } 
        
        else if (code == CFUNCTION_CALL) {
            stk = MerVM_evaluate_FUNCTION_CALL(tmp, stk);
        } 
        
        else if (code == CGREATER || code == CEQUAL || code == CNOT_EQUAL || code == CGREATER_EQUAL || code == CLESS_EQUAL || code == CLESS) {
            stk = MerVM_evaluate_COMPARE(tmp, stk, code);
        } 
        
        else if (code == CJUMP_TO) {
            stk = MerVM_evaluate_JUMP_TO(tmp, stk);
        } 
        
        else if (code == CNOT) {
            stk = MerVM_evaluate_NOT(tmp, stk);
        }

        else if (code == CLEN) {
            stk = MerVM_evaluate_CLEN(tmp, stk);
        }

        else if (code == CBUILD_LIST) {
            stk = MerVM_evaluate_BUILD_LIST(tmp, stk);
        }
        
        else if (code == CPUSH_NORMAL_MODE) {
            stk = MerVM_evaluate_PUSH_NORMAL_MODE(tmp, stk);
        } 
        
        else if (code == CPOP_JUMP_IF_FALSE) {
            stk = MerVM_evaluate_POP_JUMP_IF_FALSE(tmp, stk);
        }
        
        else if (code == CINC) {
            stk = MerVM_evaluate_INC(tmp, stk);
        }

        else if (code == CDEC) {
            stk = MerVM_evaluate_DEC(tmp, stk);
        }

        else if (code == CGET_ITEM) {
            stk = MerVM_evaluate_GET_ITEM(tmp, stk);
        } 

        else if (code == CLOAD_TRUE) {
            stk = MerVM_evaluate_LOAD_TRUE(tmp, stk);
        } 

        else if (code == CIS) {
            stk = MerVM_evaluate_IS(tmp, stk);
        }
        
        else if (code == CLOAD_FALSE) {
            stk = MerVM_evaluate_LOAD_FALSE(tmp, stk);
        }
        
        else if (code == CRETURN) {
            table *top = POP();
            ctx->return_val = top;
            break;
        }

        else if (code == CLOAD_ARGS) {
            stk = MerVM_evaluate_LOAD_ARGS(tmp, stk);
        }

        else if (code == CEND_FUNCTION) {
            break;
        }

        else if (code == CLOAD_ATTR) {
            stk = MerVM_evaluate_LOAD_ATTR(tmp, stk);
        }

        else if (code == CSTORE_ATTR) {
            stk = MerVM_evaluate_STORE_ATTR(tmp, stk);
        }
        
        else if (code == CSTORE_INDEX) {
            stk = MerVM_evaluate_STORE_INDEX(tmp, stk);
        }

        else if (code == CDELETE) {
            stk = MerVM_evaluate_DELETE(tmp, stk);
        }

        else if (code == CADDRESS) {
            code = next_c(tmp);
        }

        else if (code == CAND) {
            stk = MerVM_evaluate_AND(tmp, stk);
        }

        else if (code == COR) {
            stk = MerVM_evaluate_OR(tmp, stk);
        }
    }

    ctx->return_val->ref_count++;
    stk->s_table->table.push_back(ctx->return_val);
    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_LOAD_ARGS(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_ARGS] [building...]" << endl;
    #endif

    Mer_uint8_t address = next_c(u);

    bool found = false;

    for (auto &item : _L) {
        if (item->address == address) {
            item->tab->cval = item->value;
            item->tab->address = item->address;
            stack_push(item->tab);
            found = true;
            break;
        }
    }

    if (!found) {
        cerr << "local var dont exist " << "0x" << hex << setfill('0') << setw(2) << (int)address << endl;
        cerr << "at id " << u.iid << endl;
        MER_BREAK_POINT;
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_LOAD_ARGS] [pass]" << endl;
    #endif

    return stk;
}

MERCURY_API __mer_core_data__ stack *MerVM_evaluate_FUNCTION_CALL(__program_bytecode &u, stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [building...]" << endl;
    #endif

    table *func_obj = POP();

    if (func_obj->is_func) {
        Mer_uint8_t para_address = 0x00;
        vector<symtable*> _T;

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [pushing parameters... with size " << func_obj->func_obj_v->args_size << "]" << endl;
        #endif

        for (int i = 0; i < func_obj->func_obj_v->args_size; i++) {
            #ifdef SYSTEM_TEST
            cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [pushing parameter " << i << " start]" << endl;
            #endif

            table *item = POP();

            #ifdef SYSTEM_TEST
            cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [pushing parameter " << i << " pass]" << endl;
            #endif

            symtable *parameter = MerCompiler_symboltable_setup("", item->cval, "AUTO_T", NULL_UINT_8_T);  
            parameter->tab = item;
            parameter->tab->address = parameter->address;
            parameter->tab->ref_count++;
            parameter->value = item->cval;

            _T.push_back(parameter);
        }

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [pushing parameters done!]" << endl;
        #endif

        reverse(_T.begin(), _T.end());

        for (auto &item : _T) {
            item->address = ++para_address;
        }

        mCode_T code = NULL_CODE;
        code.prg_code.buff = func_obj->func_obj_v->f_bc->buff;

        CallContext *ctx = new CallContext {
            .code = code,
            .caller = nullptr,
            .return_val = MerCompiler_Table_new(),
            .local = _T
        };

        _T.clear();

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [evaluating...]" << endl;
        #endif

        u.is_in_func = true;
        stk = MerVM_evaluate_call_context(ctx, u, stk);
        u.is_in_func = false;

        for (auto &item : ctx->local) {
            if (item->tab) {
                --item->tab->ref_count;
                push_to_gc(item->tab);
            }
        }

        std::vector<symtable*>().swap(ctx->local);

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [evaluating done!]" << endl;
        #endif

    } else if (func_obj->is_class) {
        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [class]" << endl;
        #endif

        mClass_T *instance = MerCompiler_class_new();
        instance->address = func_obj->address;

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [class start]" << endl;
        #endif

        vector<void*> methods;
        for (auto &item : func_obj->class_v->methods) {
            symtable *method = (symtable *) item;
            symtable *copy = MerCompiler_symboltable_setup(method->name, method->value, method->type, method->address);

            #ifdef SYSTEM_TEST
            cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [class method]" << endl;
            #endif

            table_clone_shallow(copy->tab, method->tab);
            
            methods.push_back(copy);
        }

        instance->methods = methods;
        instance->inheritance = func_obj->class_v;

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [class pass]" << endl;
        #endif

        table *obj = MerCompiler_Table_new();
        obj->is_instance = true;
        obj->class_v = instance;

        stack_push(obj);

        #ifdef SYSTEM_TEST
        cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [class done!]" << endl;
        #endif
    } else {

        Mer_uint8_t address = func_obj->address;

        for (auto &func : mer_core_libs) {
            if (func.address == address) {
                using FuncType = void (*)(stack *);
                FuncType func_ptr = (FuncType)(func.func);
                func_ptr(stk);
            }
        }
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [MerVM_evaluate_FUNCTION_CALL] [pass]" << endl;
    #endif

    return stk;
}