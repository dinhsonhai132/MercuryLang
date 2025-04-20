#ifndef MERCURY_HEADER_FILE
#define MERCURY_HEADER_FILE

#define BYTECODE_STACK_SIZE 10
#define BYTECODE_SYMTABLE_SIZE 10
#define BYTECODE_TABLE_SIZE 10

#define __SUCCESS__ 0
#define __FAILURE__ 1

#define check_version(ver, mver) (ver == mver)

#ifndef MERCURY_VERSION
#define MERCURY_VERSION "2.0.1"
#endif

#ifndef MERCURY_ERROR
#define MERCURY_ERROR 1
#include "C:\MercuryLang\v2.0.1\mercury\include\object.h"
#include "C:\MercuryLang\v2.0.1\Mercury\include\opcode.h"
#include "C:\MercuryLang\v2.0.1\Parser\parser.cpp" 
#endif

mObject_T *MerRunFromString(const char* scr, const char* file_name, mObject_T *stack, mObject_T *env);

#endif // MERCURY_HEADER_FILE