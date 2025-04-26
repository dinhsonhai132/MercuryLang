#ifndef MERCURY_HEADER_FILE
#define MERCURY_HEADER_FILE

#define __SUCCESS__ 0
#define __FAILURE__ 1

#include "C:\MercuryLang\v2.0.1\Mercury\include\sys.h"
#include "C:\MercuryLang\v2.0.1\mercury\include\object.h"
#include "C:\MercuryLang\v2.0.1\Mercury\include\opcode.h"
#include "C:\MercuryLang\v2.0.1\Mercury\include\define.h"

#define MERCURY_VERSION_1_5_0   "1.5.0"
#define MERCURY_VERSION_2_0_1   "2.0.1"
#define MERCURY_VERSION_2_1_0   "2.1.0"

#ifdef MER_SYSTEM
#define MER_PASS                __pass();
#define MER_PAUSE               __pause();
#define MER_EXIT                _exit();
#define STACK_MAX_SIZE          1024
#define STACK_DEFAULT_SIZE      1024
#define HEAP_DEFAULT_SIZE       1024
#define HEAP_MAX_SIZE           1024
#else
#define MER_PASS                NULL_MARCO
#define MER_PAUSE               NULL_MARCO
#define MER_EXIT                NULL_MARCO
#endif

#endif // MERCURY_HEADER_FILE