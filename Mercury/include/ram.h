#ifndef MERCURY_RAM_HEADER_FILE
#define MERCURY_RAM_HEADER_FILE

#include "data.h"
#include <vector>
using namespace std;

#define RAM_SIZE 1024

#define REGISTER_1_ADDRESS 0x01
#define REGISTER_2_ADDRESS 0x02
#define REGISTER_3_ADDRESS 0x03

#define Err_stack_overflow 0
#define Err_stack_underflow 1
#define Err_stack_empty 2

MERCURY_API __mer_core_data__ vector<table*> _R1 = {}; // ram 1
MERCURY_API __mer_core_data__ vector<table*> _R2 = {}; // ram 2
MERCURY_API __mer_core_data__ vector<table*> _R3 = {}; // ram 3

MERCURY_API __mer_core_data__ vector<table*> __push_to_ram(table *t, Mer_uint8_t ram);
MERCURY_API __mer_core_data__ vector<table*> __pop_from_ram(Mer_uint8_t ram);

#define _PUSH(t) (do { \
    _R1 = __push_to_ram(t, 0x01); \
    return R1.back() \
} while (0) \)

#define _POP() __pop_from_ram(0x01) ( do { \
    table *t = _R1.back(); \
    __pop_from_ram(0x01); \
    return t; \
} while (0) \)

#endif // MERCURY_RAM_HEADER_FILE