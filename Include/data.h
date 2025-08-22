#ifndef MERCURY_DATA_HEADER_FILE
#define MERCURY_DATA_HEADER_FILE

#include "stack.h"
#include "gc.h"

#include <vector>
using namespace std;

#define PRINT_ADDRESS                      0x71
#define IO_WRITE_ADDRESS                   0x72
#define EVAL_ADDRESS                       0x73
#define PAUSE_ADDRESS                      0x74
#define EXIT_ADDRESS                       0x75
#define CLS_ADDRESS                        0x76
#define HELP_ADDRESS                       0x77
#define PI_ADDRESS                         0x78
#define LIST_ADDRESS                       0x79
#define TAU_ADDRESS                        0x7A
#define GOLDEN_RATIO_ADDRESS               0x7B
#define EULER_ADDRESS                      0x7C
#define SLEEP_ADDRESS                      0x7D
#define INFINITY_ADDRESS                   0x7E
#define THE_TRUE_ADDRESS                   0x7F
#define TO_STRING_ADDRESS                  0x80
#define INPUT_ADDRESS                      0x81
#define TO_INT_ADDRESS                     0x82
#define THE_FALSE_ADDRESS                  0x83
#define SAME_STRING_ADDRESS                0x84
#define SIZE_ADDRESS                       0x85
#define PUSH_ADDRESS                       0x86
#define POP_ADDRESS                        0x87
#define PRINT_LIST_ADDRESS                 0x88
#define PUTS_ADDRESS                       0x89
#define ISDIGIT_ADDRESS                    0x8A
#define COS_ADDRESS                        0x8B
#define SIN_ADDRESS                        0x8C
#define TAN_ADDRESS                        0x8D
#define FFI_CHARR_ADDRESS                  0x8E
#define FFI_FLOAT_ADDRESS                  0x8F
#define FFI_ADDRESS                        0x90
#define CHANGE_ITEM_ADDRESS                0x91
#define TYPE_ADDRESS                       0x92
#define RANGE_ADDRESS                      0x93
#define DLL_LOAD_FUNC                      0xF9
#define SUB_STR                            0x95
#define SPLIT_ADDRESS                      0x96
#define HASH_ADDRESS                       0x97
#define EMPTY_ADDRESS                      0x98
#define FREE_ADDRESS                       0x99
#define TIME_ADDRESS                       0xFA

// system variable
#define __file__G                          0xE0
#define __Global_G                         0xE1
#define __Module__G                        0xE2
#define __Libs__G                          0xE3
#define __Ver__G                           0xE4
#define __name__G                          0xE5
#define __path__G                          0xE8
#define __cached__G                        0xE9

__mer_core_data__ vector<symtable *> _G = {};
__mer_core_data__ vector<symtable *> _L = {};
__mer_core_data__ vector<symtable *> _T = {};

__mer_core_data__ GlobalTable GLOBAL_TABLE = {};
__mer_core_data__ GlobalTable LOCAL_TABLE = {};
__mer_core_data__ GlobalTable ATTRIBUTE_TABLE = {};

__mer_core_data__ vector<void*> _EXIST = {};

__mer_core_data__ vector<table *> GC_TABLE = {};

__mer_core_data__ vector<Mer_string_entry*> STRING_ENTRY = {};

#endif // MERCURY_DATA_HEADER_FILE
