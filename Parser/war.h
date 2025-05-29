#ifndef MERCURY_WARNING_HEADER_FILE
#define MERCURY_WARNING_HEADER_FILE

using namespace std;

#ifndef MER_DEBUG
#define MER_DEBUG 1
#define ERROR_TYPE 1
#endif

#include <iostream>

#ifdef MER_DEBUG

#define SYNTAX_ERROR "SyntaxError"
#define RUNTIME_ERROR "RuntimeError"
#define RUNTIME_WARNING "RuntimeWarning"
#define SYSTEM_WARNING "SystemWarning"
#define SYSTEM_ERROR "SystemError"
#define COMPILER_WARNING "CompilerWarning"
#define COMPILER_ERROR "CompilerError"

#define DEBUG(x) cout << x << endl;

void MerDebug_print_message(const char *msg, const char *file, int line);
void MerDebug_print_warning(const char* msg, const char* file, int line, const char* c_line);
void MerDebug_print_error(const char *type, const char *msg, const char *file, int line);
void MerDebug_system_error(const char *type, const char *msg, const char* file);

#else
#define DEBUG(x)
#endif
#endif // MERCURY_WARNING_HEADER_FILE