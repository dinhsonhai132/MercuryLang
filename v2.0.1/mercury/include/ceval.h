// Copyright (c) 2025-present Dinh Son Hai

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef MECURY_EVALUATE_H
#define MECURY_EVALUATE_H

#include "C:\MercuryLang-main\v2.0.1\mercury\btok.cpp"
#include "C:\MercuryLang-main\v2.0.1\mercury\stack.cpp"

#include <stdlib.h>
using namespace std;

#define MERCURY_BINARY_SUB(c1, c2) ((c1) - (c2))
#define MERCURY_BINARY_ADD(c1, c2) ((c1) + (c2))
#define MERCURY_BINARY_DIV(c1, c2) ((c2) != 0 ? ((c1) / (c2)) : 0)
#define MERCURY_BINARY_MUL(c1, c2) ((c1) * (c2))

stack *MerCompilerBytecode_evaluate_program(vector<uint8_t> code);
stack *MerCompilerBytecode_evaluate_statement(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_POP_NORMAL_MODE(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_PUSH_FLOAT(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_LOAD_GLOBAL(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_STORE_GLOBAL(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_BINARY_ADD(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_BINARY_DIV(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_BINARY_MUL(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_BINARY_SUB(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_MAKE_FUNCTION(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_FUNCTION_CALL(ctoken ptoken, stack *stk);
stack *MerCompilerBytecode_evaluate_RETURN(ctoken ptoken, stack *stk);

#endif //MECURY_EVALUATE_H
