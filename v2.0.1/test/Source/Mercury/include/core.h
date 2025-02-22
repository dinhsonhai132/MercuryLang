#include "envi.h"
#include "eval.h"
#include "object.h"
#include "variable.h"
#include "./Parser/Lexer/ast.h"
#include "./Parser/Lexer/lexer.h"
#include "./Parser/parser.h"
#include "./MVM/include/stack.h"
#include "./MVM/include/compiler.h"
#include "./MVM/include/oobject.h"

#include <string>
#include <vector>

#ifndef CORE_H
#define CORE_H

typedef ssize_t Merssize_t;

using namespace std;

#endif