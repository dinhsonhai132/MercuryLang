#include "../include/register.h"

MERCURY_API __mer_core_api__ void __register_lib(Mer_uint8_t address, void *func, Mer_string name) {
    mer_core_libs.push_back({address, name, func});
}

MERCURY_API __mer_core_api__ void __register_global(Mer_uint8_t address, Mer_string name) {
    GLOBAL_TABLE.push_back(CREAT_GLOBAL_TABLE(address, name, name));
}

MERCURY_API __mer_core_api__ void __register_global_data(symtable *item) {
    if (!item) return;
    _G.push_back(item);
}

MERCURY_API __mer_core_api__ void __register_lib_to_global(Mer_uint8_t address, mFunc_T func) {
    symtable *item = MerCompiler_SymbolTable_new();
    item->address = address;
    item->is_builtin = true;
    item->func_v = func;
    _G.push_back(item);
}

MERCURY_API __mer_core_api__ void __register_global_variable(Mer_uint8_t address, float value) {
    _G.push_back(MerCompiler_symboltable_setup("", value, "AUTO_T", address));
}