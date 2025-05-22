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

#ifdef __cplusplus
extern "C" {
#endif

int __pass() { return 0; }
int __system_pause() { system("pause"); return 0; }
int __system_clear() { system("cls"); return 0; }
int __system_exec(const char *cmd);
int __system_open(const char *path);
int __system_mkdir(const char *dirname);

#ifdef __cplusplus
}
#endif

#define MER_PASS __pass()
#define MER_PAUSE __system_pause()
#define MER_CLEAR __system_clear()
#define MER_EXIT exit(0)
#define MER_EXEC __system_exec
#define MER_OPEN __system_open
#define MER_MKDIR __system_mkdir

#endif // MERCURY_SYS_HEADER_FILE
