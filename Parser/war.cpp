#include "war.h"

void MerDebug_print_message(const char *msg, const char *file, int line) {
    cout << "MercuryLang system message: " << msg << endl;
    cout << "At file '" << file << "', line " << line << endl;
}

void MerDebug_print_error(const char *type, const char *msg, const char *file, int line) {
    cout << type << ": " << msg << endl;
    cout << "At file '" << file << "', line " << line << endl;
    while (1);
}

void MerDebug_system_error(const char *type, const char *msg, const char* file)
{
    cout << type << ": " << msg << endl;
    cout << "At file '" << file << "'" << endl;
    while (1);
}

void MerDebug_print_warning(const char *msg, const char *file, int line, const char *c_line) {
    cout << "MercuryLang warning: " << msg << endl;
    cout << "At file '" << file << "', line " << line << endl;
    cout << c_line << endl;
}
