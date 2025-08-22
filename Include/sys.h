#ifndef MERCURY_SYS_HEADER_FILE
#define MERCURY_SYS_HEADER_FILE

#include <cstdlib>

#ifdef _WIN32
    #include <direct.h>
    #define PLATFORM_WINDOWS 1
#else
    #include <sys/stat.h>
    #define PLATFORM_WINDOWS 0
#endif

#ifndef MER_SYSTEM
#define MER_SYSTEM 1
#endif

#define MER_PAUSE system("pause");
#define MER_CLEAR system("cls");
#define MER_EXIT exit(0)

#endif // MERCURY_SYS_HEADER_FILE
