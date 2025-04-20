#ifndef MERCURY_ERROR_H
#define MERCURY_ERROR_H

#include <string>
#include <iostream>
using namespace std;

#define STACK_OVERFLOW "STACK_OVERFLOW"
#define STACK_UNDERFLOW "STACK_UNDERFLOW"
#define SYNTAX_ERROR "SYNTAX_ERROR"
#define RUNTIME_ERROR "RUNTIME_ERROR"
#define BREAK_POINT "BREAK_POINT"
#define UNDEFINED_ERROR "UNDEFINED_ERROR"   
#define UNDEFINED_FUNCTION "UNDEFINED_FUNCTION"

void mer_run_time_error(string line, string error, string messages, string file);
void mer_error(string type, string line);
void break_point();

#ifndef MER_DEBUG
#define MER_DEBUG 1
#endif

#endif 