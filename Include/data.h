#ifndef MERCURY_DATA_HEADER_FILE
#define MERCURY_DATA_HEADER_FILE

#include "..\Mercury\stack.cpp"

#include <vector>
using namespace std;

#define PRINT_ADDRESS               0xBB
#define IO_WRITE_ADDRESS            0xB2
#define EVAL_ADDRESS                0xF4
#define PAUSE_ADDRESS               0xF5
#define EXIT_ADDRESS                0xF6
#define CLS_ADDRESS                 0xF7
#define HELP_ADDRESS                0xF8
#define PI_ADDRESS                  0xF9
#define TAU_ADDRESS                 0xFA
#define GOLDEN_RATIO_ADDRESS        0xFB
#define EULER_ADDRESS               0xFC
#define INFINITY_ADDRESS            0xFD
#define THE_TRUE_ADDRESS            0xFE
#define THE_FALSE_ADDRESS           0xFF
#define SAME_STRING_ADDRESS         0xA1
#define SIZE_ADDRESS                0xA2
#define PUSH_ADDRESS                0xA3
#define POP_ADDRESS                 0xA4
#define PRINT_LIST_ADDRESS          0xA5
#define PUTS_ADDRESS                0xA6
#define COS_ADDRESS                 0xA7
#define SIN_ADDRESS                 0xA8
#define TAN_ADDRESS                 0xA9
#define COT_ADDRESS                 0xAA
#define SQRT_ADDRESS                0xAB
#define PRINT_GLOBAL_ADDRESS        0xAC
#define CHANGE_ITEM_ADDRESS         0xAD
#define TYPE_ADDRESS                0xAE
#define NULL_GLOBAL_ADDRESS         0xAF
#define RANGE_ADDRESS               0xB0
#define RANDOM_ADDRESS              0xB1
#define RANDINT_ADDRESS             0xB1
#define SUB_STR                     0xF1

MERCURY_API __mer_core_data__ vector<symtable *> _G = {};
MERCURY_API __mer_core_data__ vector<symtable *> _L = {};
MERCURY_API __mer_core_data__ vector<symtable *> _T = {};

MERCURY_API __mer_core_data__ GlobalTable GLOBAL_TABLE = {};
MERCURY_API __mer_core_data__ GlobalTable LOCAL_TABLE = {};

MERCURY_API __mer_core_data__ vector<Mer_string_entry*> STRING_ENTRY = {};

#endif // MERCURY_DATA_HEADER_FILE
