#include "../Include/sign.h"

__mer_core_data__ 
void __mer_sign(mObject_T *obj, Mer_uint8_t address, bool is_builtin)
{
    symtable *sign = MerCompiler_SymbolTable_new();

    sign->f_address = obj;
    sign->f_type = obj;
    sign->f_name = obj;
    sign->f_value = obj;
    sign->f_size = obj;
    sign->f_local = obj;
    sign->f_global = obj;
    sign->f_string = obj;
    sign->f_hash = obj;
    sign->f_error = obj;
    sign->address = address;
    sign->is_builtin = is_builtin;

    _G.push_back(sign);
}

int sign_in_mer_libs() {
    symtable *sign = MerCompiler_SymbolTable_new();
    sign->address = IO_WRITE_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_print;
    _G.push_back(sign);


    sign = MerCompiler_SymbolTable_new();
    sign->address = EVAL_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_eval;
    _G.push_back(sign);


    sign = MerCompiler_SymbolTable_new();
    sign->address = PAUSE_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_pause;
    _G.push_back(sign);


    sign = MerCompiler_SymbolTable_new();
    sign->address = EXIT_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__mer_builtin_exit;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = CLS_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_cls;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = HELP_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_help;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = SAME_STRING_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_same_string;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = SIZE_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_size;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = PUSH_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_push;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = POP_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_pop;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = PRINT_LIST_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_watch;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = PUTS_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_puts_val;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = COS_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_mer_cos;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = SIN_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_mer_sin;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = TAN_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_mer_tan;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = SQRT_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_mer_sqrt;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = PRINT_GLOBAL_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_print_global_stack;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = CHANGE_ITEM_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_change_item;
    _G.push_back(sign);

    sign = MerCompiler_SymbolTable_new();
    sign->address = TYPE_ADDRESS;
    sign->is_builtin = true;
    sign->func_v = (mFunc_T)__builtin_type;
    _G.push_back(sign);

    return 0;
}