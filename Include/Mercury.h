#ifndef MERCURY_HEADER_FILE
#define MERCURY_HEADER_FILE

#define __SUCCESS__ 0
#define __FAILURE__ 1

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0601
    #endif

    #include <windows.h>
    #include <timezoneapi.h> 
    #include <winbase.h>   
#endif


#include "opcode.h"
#include "math.h"
#include "sys.h"
#include "define.h"
#include "error.h"
#include "gc.h"
#include "..\Mercury\math.cpp"

#include <filesystem>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <unordered_map>
#include <filesystem>
#include <random>
#include <functional>

const char* CUSTOM_VERSION = "2.1.1";
const char* AUTHOR = "dinhsonhai132";
const char* LANGUAGE = "MercuryLang";

#define __iter__ "__iter__version_2_5_0_global_variable"
#define __i__ "__i__version_2_5_0_global_variable"

#ifdef _WIN32
    #ifndef __API
        #define MERCURY_API             __declspec(dllexport)
    #endif
    #ifndef __mer_core_data__
        #define __mer_core_data__       __declspec(dllexport)
    #endif
    #ifndef __mer_core_api__
        #define __mer_core_api__        __declspec(dllexport)
    #endif
    #ifndef __mer_core_lib_api__
        #define __mer_core_lib_api__    __declspec(dllexport)
    #endif
#else
    #define MERCURY_API             extern
    #define __mer_core_data__       extern
    #define __mer_core_api__        extern
    #define __mer_core_lib_api__    extern
#endif

#ifdef SYSTEM_TEST
#define SYSTEM_TEST 1
#endif

#define MERCURY_FUNCTION_VALUE           0
#define MERCURY_LIST_VALUE               1
#define MERCURY_STRING_VALUE             2
#define MERCURY_OPCODE_VALUE             3
#define MERCURY_OBJECT_VALUE             4
#define MERCURY_ITERATOR_VALUE           5

#ifdef MER_SYSTEM
    // #define MER_PASS                __pass();
    // #define MER_PAUSE               __system_pause();
    // #define MER_EXIT                exit(0);
#else
    #define MER_PASS                NULL_MARCO
    #define MER_PAUSE               NULL_MARCO
    #define MER_EXIT                NULL_MARCO
#endif

#endif // MERCURY_HEADER_FILE