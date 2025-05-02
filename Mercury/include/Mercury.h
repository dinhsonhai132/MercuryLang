#ifndef MERCURY_HEADER_FILE
#define MERCURY_HEADER_FILE

#define __SUCCESS__ 0
#define __FAILURE__ 1

#include "C:\MercuryLang\Mercury\object.cpp"
#include "opcode.h"
#include "define.h"

#define MERCURY_VERSION_1_5_0   "1.5.0"
#define MERCURY_VERSION_2_0_1   "2.0.1"
#define MERCURY_VERSION_2_1_0   "2.1.0"

#ifdef _WIN32
    #define MERCURY_API __declspec(dllexport)
#else
    #define MERCURY_API extern
#endif


#ifdef MER_SYSTEM
#define MER_SYSTEM 1
#else
#define MER_PASS                NULL_MARCO
#define MER_PAUSE               NULL_MARCO
#define MER_EXIT                NULL_MARCO
#endif

#endif // MERCURY_HEADER_FILE