#ifndef MERCURY_DATA_HEADER_FILE
#define MERCURY_DATA_HEADER_FILE

#include "C:\MercuryLang\Mercury\stack.cpp"

MERCURY_API __mer_core_data__ vector<symtable *> _G = {};
MERCURY_API __mer_core_data__ vector<symtable *> _L = {};
MERCURY_API __mer_core_data__ vector<symtable *> _T = {};

MERCURY_API __mer_core_data__ stack *_S;

MERCURY_API __mer_core_lib_api__ vector<Mer_Reg> mer_core_libs = {
    {IO_WRITE_ADDRESS, "write", (void*)__io_write},
}; 

#endif // MERCURY_DATA_HEADER_FILE
