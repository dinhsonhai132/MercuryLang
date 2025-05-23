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

MERCURY_API __mer_core_data__ void __push_to_ram(table *t, Mer_uint8_t ram);
MERCURY_API __mer_core_data__ void __pop_from_ram(Mer_uint8_t ram);

#define __push(t) do { \
    __push_to_ram(t, REGISTER_1_ADDRESS); \
    __push_to_ram(t, REGISTER_2_ADDRESS); \
    __push_to_ram(t, REGISTER_3_ADDRESS); \
} while (0)

#define __pop() do { \
    __pop_from_ram(REGISTER_1_ADDRESS); \
    __pop_from_ram(REGISTER_2_ADDRESS); \
    __pop_from_ram(REGISTER_3_ADDRESS); \
} while (0)

#define __reg_no1 _R1
#define __reg_no2 _R2
#define __reg_no3 _R3

#endif // MERCURY_RAM_HEADER_FILE