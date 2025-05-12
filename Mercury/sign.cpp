#include "./include/sign.h"

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

int sign_in_io_write() {
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
    return 0;
}