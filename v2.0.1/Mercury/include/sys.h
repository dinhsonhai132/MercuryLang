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

#endif // MERCURY_SYS_HEADER_FILE
