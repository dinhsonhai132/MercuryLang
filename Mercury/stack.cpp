#include "../include/stack.h"
#include "../include/gc.h"

stack *MerCompiler_Stack_new(void) {
    stack *s = new stack;
    s->s_table = MerCompiler_Table_new();
    s->s_symtable = MerCompiler_SymbolTable_new();
    s->code_idx = 0; // Debug
    s->code_name = ""; // Debug
    s->raw_debug = NULL_UINT_8_T; // Debug
    return s;
}

table *MerCompiler_Table_new(void) {
    table *t = new table;
    t->ref_count = 0;
    t->cval = 0;
    t->cidx = 0;
    t->cbuf = 0;
    t->is_list = false;
    t->is_bool = false;
    t->is_str = false;
    t->is_code = false;
    t->is_builtin = false;
    t->is_same = false;
    t->is_local = false;
    t->is_obj = false;
    t->is_func = false;
    t->is_type = false;
    t->is_opcode = false;
    t->is_same = false;
    t->is_var = false;
    t->is_class = false;
    t->is_instance = false;
    t->value = 0;
    t->address = 0x01;
    t->size = 0;
    t->is_in_glb = false;
    t->f_value = 0;
    return t;
}

symtable *MerCompiler_SymbolTable_new(void) {
    symtable *s = new symtable;
    s->ref_count = 0;
    s->value = 0;
    s->is_str = false;
    s->is_code = false;
    s->is_list = false;
    s->is_bool = false;
    s->is_obj = false;
    s->is_func = false;
    s->is_type = false;
    s->is_opcode = false;
    s->is_same = false;
    s->is_var = false;
    s->is_builtin = false;
    s->is_local = false;
    s->is_in_glb = false;
    s->tbody = vector<uint8_t>();
    s->cidx = 0;
    s->address = 0x01;
    s->tab = MerCompiler_Table_new();
    return s;
}

table *push_stack(stack *stk, table *t) {
    if (!stk || !t) return nullptr;

    t->ref_count++;

    stk->s_table->table.push_back(t);
    return t;
}

int MerCompiler_free_stack(stack *s) {
    if (!s) return __FAILURE__;

    MerCompiler_free_table(s->s_table);
    MerCompiler_free_symboltable(s->s_symtable);
    MerCompiler_free_symboltable(s->s_global);
    MerCompiler_free_symboltable(s->s_local);

    delete s;
    return __SUCCESS__;
}

int MerCompiler_free_table(table *t) {
#ifdef GC_DEBUG
    cout << "[stack.cpp] [MerCompiler_free_table] [start] " << endl;
#endif
    if (!t) {
        cout << "Error: GC: NULL table passed to MerCompiler_free_table" << endl;
        MER_BREAK_POINT;
    }

    if (t->gc_freed) {
        return __SUCCESS__;
    }

    if (t->is_list) {
#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free list] " << endl;
#endif

        if (t->list_v->args.empty()) {
            delete t->list_v;
            delete t;
            return __SUCCESS__;
        }

        // for (auto it = t->list_v->args.begin(); it != t->list_v->args.end();) {
        //     table *item = (table *) *it;
        //     if (item && --item->ref_count < 1) {
        //         if (MerCompiler_free_table(item)) {
        //             cout << "failed to free table Error: GC1" << endl;
        //             MER_BREAK_POINT;
        //         }

        //         it = t->list_v->args.erase(it);
        //     } else {
        //         ++it;
        //     }
        // }

        delete t->list_v;
        delete t;

#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free list done] " << endl;
#endif
    }

    else if (t->is_str) {
#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free str] " << endl;
#endif
        delete t->f_str_v;
        delete t;
#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free str done] " << endl;
#endif
    }

    else if (t->is_bool) {
#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free bool] " << endl;
#endif
        MerCompiler_free_bool(t->bool_v);

        delete t;

#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free bool done] " << endl;
#endif
    } 
    
    else {
#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free table] " << endl;
#endif
        delete t;

#ifdef GC_DEBUG
        cout << "[stack.cpp] [MerCompiler_free_table] [free table done] " << endl;
#endif
    }

#ifdef GC_DEBUG
    cout << "[stack.cpp] [MerCompiler_free_table] [pass] " << endl;
#endif

    t->gc_freed = true;
    return __SUCCESS__;
}


int MerCompiler_free_symboltable(symtable *s) {
    if (!s) return __FAILURE__;

    if (s->list_v) delete s->list_v;
    if (s->f_str_v) delete s->f_str_v;
    if (s->code_v) delete s->code_v;
    if (s->func_obj_v) delete s->func_obj_v;
    if (s->obj_v) delete s->obj_v;
    if (s->opcode_v) delete s->opcode_v;
    if (s->tab) MerCompiler_free_table(s->tab);

    delete s;
    return __SUCCESS__;
}

stack *MerCompiler_stack_setup(stack *s, table *t, symtable *sy) {
    if (!s || !t || !sy) return NULL;
    s = MerCompiler_Stack_new();
    s->s_table = t;
    s->s_symtable = sy;
    return s;
}

table *MerCompiler_table_setup(float cval, uint8_t address) {
    table *t = MerCompiler_Table_new();
    t->cval = cval;
    t->address = address;
    return t;
}

symtable *MerCompiler_symboltable_setup(string name, float value, string type, uint8_t address) {
    symtable *s = MerCompiler_SymbolTable_new();
    s->name = name;
    s->value = value;
    s->type = type;
    s->address = address;
    return s;
}

void release_table_obj(table *obj) {
    if (obj == nullptr) return;

    obj->ref_count--;
    if (obj->ref_count == 0) {
        MerCompiler_free_table(obj);
    }
}

table *pop_stack(stack *stk) { 
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [pop_stack] [start]" << endl;
    #endif

    if (stk->s_table->table.empty()) {
        cerr << "Error: Stack is empty, can not pop while using pop_stack" << endl;
        MER_BREAK_POINT;
    }
    
    table *top = stk->s_table->table.back();

    if (!top) {
        cerr << "Error: Top of stack is NULL, cannot pop" << endl;
        MER_BREAK_POINT;
    }
    
    stk->s_table->table.pop_back();
    --top->ref_count;

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [pop_stack] [pass]" << endl;
    #endif

    return top;
}

table *pop_stack_no_ref(stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [pop_stack_no_ref] [start]" << endl;
    #endif

    if (stk->s_table->table.empty()) {
        cerr << "Error: Stack is empty, can not pop while using pop_stack_no_ref" << endl;
    }   
    table *top = stk->s_table->table.back();
    top->ref_count--;

    if (top->is_list && top->ref_count < 1) {
        for (auto it = top->list_v->args.begin(); it != top->list_v->args.end(); ++it) {
            table *item = (table *) *it;
            item->ref_count--;
        }
    }

    stk->s_table->table.pop_back();

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [pop_stack_no_ref] [pass]" << endl;
    #endif

    return top;
}

table *eat_stack(stack *stk) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eat_stack] [start]" << endl;
    #endif
    
    if (stk->s_table->table.empty()) {
        cerr << "Error: Stack underflow in eat_stack" << endl;
    }
    table *top = stk->s_table->table.back();

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [eat_stack] [pass]" << endl;
    #endif

    return top;
}

void reset_table(table *t) {
    if (!t) {
        cerr << "Error: NULL table passed to reset_table" << endl;
        MER_BREAK_POINT;
    }

    t->cval = 0;
    t->cidx = 0;
    t->cbuf = 0;
    t->is_list = false;
    t->is_bool = false;
    t->is_str = false;
    t->is_code = false;
    t->is_builtin = false;
    t->is_same = false;
    t->is_local = false;
    t->is_obj = false;
    t->is_func = false;
    t->is_type = false;
    t->is_opcode = false;
    t->is_same = false;
    t->is_var = false;
    t->is_class = false;
    t->is_instance = false;
    t->value = 0;
    t->address = 0x01;
    t->size = 0;
    t->is_in_glb = false;
    t->f_value = 0;
    t->f_str_v = nullptr;
    t->list_v = nullptr;
    t->func_obj_v = nullptr;
    t->bool_v = nullptr;
    t->obj_v = nullptr;
    t->opcode_v = nullptr;
}

table *table_clone_shallow(table *dst, table *src) {
    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [table_clone_shallow] [start]" << endl;
    #endif

    if (!src || !dst) {
        cerr << "Error: NULL pointer passed into table_clone_shallow" << endl;
        MER_BREAK_POINT;
    }

    dst->value = src->value;
    dst->cval = src->cval;
    dst->address = src->address;
    dst->ref_count = src->ref_count;

    dst->is_str = src->is_str;
    dst->is_list = src->is_list;
    dst->is_func = src->is_func;
    dst->is_class = src->is_class;
    dst->is_instance = src->is_instance;

    if (src->is_str && src->f_str_v) {
        mString_T *copy = MerCompiler_string_new();
        copy->hash = src->f_str_v->hash;
        copy->size = src->f_str_v->size;
        for (auto &ch : src->f_str_v->buff) {
            copy->buff.push_back(ch);
        }
        dst->f_str_v = copy;
    }

    else if (src->is_list && src->list_v) {
        dst->list_v = MerCompiler_list_object_new();

        dst->list_v->size = src->list_v->size;
        for (auto &item : src->list_v->args) {
            table *new_item = table_clone_shallow(MerCompiler_Table_new(), (table *) item);
            dst->list_v->args.push_back(new_item);
        }
    }

    else if (src->is_func) {
        dst->func_obj_v = MerCompiler_func_object_new();

        dst->func_obj_v->is_return = src->func_obj_v->is_return;
        dst->func_obj_v->is_global = src->func_obj_v->is_global;
        dst->func_obj_v->is_local = src->func_obj_v->is_local;
        dst->func_obj_v->o = src->func_obj_v->o;
        dst->func_obj_v->f_builtin = src->func_obj_v->f_builtin;
        dst->func_obj_v->sf = src->func_obj_v->sf;
        dst->func_obj_v->body_size = src->func_obj_v->body_size;
        dst->func_obj_v->args_size = src->func_obj_v->args_size;

        for (Mer_uint8_t opcode : src->func_obj_v->f_bc->buff) {
            dst->func_obj_v->f_bc->buff.push_back(opcode);
        }

        for (Mer_uint8_t opcode : src->func_obj_v->f_bc->raw) {
            dst->func_obj_v->f_bc->raw.push_back(opcode);
        }

        dst->func_obj_v->ref_count = src->func_obj_v->ref_count;
    }

    else if (src->is_class) {
        dst->class_v = MerCompiler_class_new();

        dst->class_v = src->class_v;
    }

    else if (src->is_instance) {
        dst->class_v = MerCompiler_class_new();

        dst->class_v = src->class_v;
    }

    #ifdef SYSTEM_TEST
    cout << "[ceval.cpp] [table_clone_shallow] [pass]" << endl;
    #endif

    return dst;
}
