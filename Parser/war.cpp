#include "war.h"

void MerDebug_print_message(const char *msg, const char *file, int line, const char *c_line) {
    cout << "MercuryLang system message: " << msg << endl;
    cout << "At file " << file << ", line " << line << endl;
}

void MerDebug_print_error(const char *msg, const char *file, int line, const char *c_line) {
    
}

void MerDebug_print_warning(const char *msg, const char *file, int line, const char *c_line) {

}
