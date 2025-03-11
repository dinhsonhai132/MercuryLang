#ifndef MERCURY_COMPILER_EVALUATE_HEADER_FILE
#define MERCURY_COMPILER_EVALUATE_HEADER_FILE

#include <iostream>
#include <string>
#include <vector>
#include "runtime.cpp"
#include "stack.cpp"
#include "olexer.cpp"

using namespace std;

#define MERCURY_BINARY_ADD(c1, c2) ((c1) + (c2))
#define MERCURY_BINARY_SUB(c1, c2) ((c1) - (c2))
#define MERCURY_BINARY_MUL(c1, c2) ((c1) * (c2))
#define MERCURY_BINARY_DIV(c1, c2) ((c1) / (c2))
#define MERCURY_BINARY_MOD(c1, c2) ((c1) % (c2))
#define MERCURY_BINARY_POW(c1, c2) ((c1) ** (c2))
#define MERCURY_BINARY_INCREMENT(c1) ((c1)++)
#define MERCURY_BINARY_DECREMENT(c1) ((c1)--)

char *MerBuffer_take_bytecode_from_file(char *file_name);
char *MerBuffer_take_bytecode_from_promt(char *line);

class MerCompile_evaluate {
private:
    int bytecode_idx;
    stack *st;
    vector<bytecode_token> ctoks;
    bytecode_token ctok;
    char *bcode;
public:
    MerCompile_evaluate(char *bytecode) {
        bcode = bytecode;
        ctoks = MerCompile_bytecode_tokenizer(bcode);
        st = MerCompiler_Stack_new();
        ctok = bytecode_token_new();
        bytecode_idx = 0;
    }

    stack *MerCompile_evaluate_program();
    stack *MerCompile_evaluate_statement();

    stack *MerCompile_evaluate_bytecode(bytecode_token ctok);
    
    stack *MerCompile_evaluate_bytecode_PUSH_FLOAT(bytecode_token ctok);
    stack *MerCompile_evaluate_bytecode_POP(bytecode_token ctok);
    stack *MerCompile_evaluate_bytecode_LOAD_GLOBAL(bytecode_token ctok);
    stack *MerCompile_evaluate_bytecode_STORE_GLOBAL(bytecode_token ctok);
    stack *MerCompile_evaluate_bytecode_CALL_FUNCTION(bytecode_token ctok);
    stack *MerCompile_evaluate_bytecode_RETURN_VALUE(bytecode_token ctok);
    
    stack *MerCompiler_evauate_bytecode_BINARY_ADD(bytecode_token ctok);
    stack *MerCompiler_evauate_bytecode_BINARY_SUB(bytecode_token ctok);
    stack *MerCompiler_evauate_bytecode_BINARY_MUL(bytecode_token ctok);
    stack *MerCompiler_evauate_bytecode_BINARY_DIV(bytecode_token ctok);
};

RunTimeVal *MerCompile_evaluate_bytecode();

#endif // MERCURY_COMPILER_EVALUATE_HEADER_FILE