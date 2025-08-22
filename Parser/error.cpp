#include "error.h"

void MerDebug_print_message(const char *msg, const char *file, int line) {
    cerr << "MercuryLang system message: " << msg << endl;
    cerr << "At file '" << file << "', line " << line << endl;
}

void MerDebug_print_error(const char *type, const char *msg, const char *file, int line) {
    cerr << type << ": " << msg << endl;
    cerr << "At file '" << file << "', line " << line << endl;
    BREAK_POINT
}

void MerDebug_system_error(const char *type, const char *msg, const char* file)
{
    cerr << type << ": " << msg << endl;
    cerr << "At file '" << file << "'" << endl;
    BREAK_POINT
}

void MerDebug_system_warning(const char* msg, const char* file) {
    cerr << "Warning: " << msg << endl;
    cerr << "At file '" << file << "'" << endl;
    BREAK_POINT
}

void MerDebug_print_warning(const char *msg, const char *file, int line, const char *c_line) {
    cerr << "Warning: " << msg << endl;
    cerr << "At file '" << file << "', line " << line << endl;
    cerr << c_line << endl;
    BREAK_POINT
}
