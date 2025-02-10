#include "error.h"

Mer_RuntimeError::Mer_RuntimeError(const string& msg) : fullMsg("Runtime Error: " + msg) {}
const char *Mer_RuntimeError::what() const throw() { 
    return fullMsg.c_str();
}

Mer_Error::Mer_Error(const string& msg) : fullMsg("Error: " + msg) {}
const char *Mer_Error::what() const throw() { 
    return fullMsg.c_str();
}