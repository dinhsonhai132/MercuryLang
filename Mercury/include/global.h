#ifndef MERCURY_GLOBAL_HEADER_FILE
#define MERCURY_GLOBAL_HEADER_FILE
#include "port.h"
#include "marco.h"
#include <vector>

using namespace std;

struct __global {
    Mer_uint8_t __Address;
    Mer_string __Name;
    Mer_real_string __name;
};

#define NULL_GLOBAL __global()
#define NULL_GLOBAL_PTR &NULL_GLOBAL

INLINE(__global) create_global_table(Mer_uint8_t __Address, const Mer_string &__Name, Mer_real_string __name);
INLINE(__global) *create_global_table_ptr(Mer_uint8_t __Address, const Mer_string &__Name, Mer_real_string __name);

typedef vector<__global *> __global_table;
#define CREAT_GLOBAL_TABLE(address, name, real_name) create_global_table_ptr(address, name, real_name)

#endif // MERCURY_GLOBAL_HEADER_FILE