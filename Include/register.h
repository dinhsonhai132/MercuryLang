#ifndef MERCURY_REGISTER_HEADER_FILE
#define MERCURY_REGISTER_HEADER_FILE
#include "../Mercury/buitlin.cpp"

MERCURY_API __mer_core_api__ void __register_lib(Mer_uint8_t address, void *func, Mer_string name);
MERCURY_API __mer_core_api__ void __register_global(Mer_uint8_t address, Mer_string name);
MERCURY_API __mer_core_api__ void __register_global_data(symtable *item);
MERCURY_API __mer_core_api__ void __register_lib_to_global(Mer_uint8_t address, mFunc_T func);
MERCURY_API __mer_core_api__ void __register_global_variable(Mer_uint8_t address, float value);

#define BUILD_LIB_FUNC(name, func) \
    __register_global(lib_hashmap[name], name); \
    __register_lib(lib_hashmap[name], (void*) func, name); \
    __register_lib_to_global(lib_hashmap[name], (mFunc_T) func); \

#define BUILD_GLOBAL_VARIABLE(name, val) \
    __register_global_variable(lib_hashmap[name], val); \
    __register_global(lib_hashmap[name], name); \

#endif // MERCURY_REGISTER_HEADER_FILE