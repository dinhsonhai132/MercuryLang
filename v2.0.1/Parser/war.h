#ifndef MERCURY_WARNING_HEADER_FILE
#define MERCURY_WARNING_HEADER_FILE

using namespace std;

#ifndef MER_DEBUG
#define MER_DEBUG 1
#define ERROR_TYPE 1
#endif



#ifdef MER_DEBUG

#define DEBUG(x) cout << x << endl;

void MerDebug_print_message(const char* msg, const char* file, int line, const char* c_line);
void MerDebug_print_error(const char* msg, const char* file, int line, const char* c_line);
void MerDebug_print_warning(const char* msg, const char* file, int line, const char* c_line);

#else
#define DEBUG(x)
void MerDebug_print_message(const char* msg, const char* file, int line, const char* c_line);
#endif
#endif // MERCURY_WARNING_HEADER_FILE