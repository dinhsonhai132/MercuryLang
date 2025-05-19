#ifndef MERCURY_ERROR_H
#define MERCURY_ERROR_H

#include <string>
#include <iostream>
using namespace std;

#define SYNTAX_ERROR "SyntaxError"
#define RUNTIME_ERROR "RuntimeError"
#define SYSTEM_ERROR "SystemError"
#define BREAK_POINT "BreakPoint"

void mer_run_time_error(string line, string error, string messages, string file);
void mer_error(string type, string msg);
void break_point();

#endif // MERCURY_ERROR_H