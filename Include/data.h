#ifndef MERCURY_DATA_HEADER_FILE
#define MERCURY_DATA_HEADER_FILE

#include "..\Mercury\stack.cpp"

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
#define COT_ADDRESS                        0x8E
#define SQRT_ADDRESS                       0x8F
#define PRINT_GLOBAL_ADDRESS               0x90
#define CHANGE_ITEM_ADDRESS                0x91
#define TYPE_ADDRESS                       0x92
#define RANGE_ADDRESS                      0x93
#define RANDINT_ADDRESS                    0x94
#define SUB_STR                            0x95
#define SPLIT_ADDRESS                      0x96
#define HASH_ADDRESS                       0x97
#define EMPTY_ADDRESS                      0x98
#define FACTORIAL_ADDRESS                  0x99

MERCURY_API __mer_core_data__ vector<symtable *> _G = {};
MERCURY_API __mer_core_data__ vector<symtable *> _L = {};
MERCURY_API __mer_core_data__ vector<symtable *> _T = {};

MERCURY_API __mer_core_data__ GlobalTable GLOBAL_TABLE = {};
MERCURY_API __mer_core_data__ GlobalTable LOCAL_TABLE = {};

MERCURY_API __mer_core_data__ vector<Mer_string_entry*> STRING_ENTRY = {};

#endif // MERCURY_DATA_HEADER_FILE
