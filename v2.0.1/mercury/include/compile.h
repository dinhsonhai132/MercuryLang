#ifndef MERCURY_BYTECODE_COMPILER_HEADER
#define MERCURY_BYTECODE_COMPILER_HEADER

#include <cstdint>
#include <string>
#include <cstring>
#include <iomanip>
#include "C:\MercuryLang-main\v2.0.1\parser\parser.cpp"

using namespace std;

#define CPUSH_FLOAT              0x01
#define CPUSH_NORMAL_MODE        0x02
#define CPUSH_TEMP_MODE          0x03

#define CLOAD_GLOBAL             0x04
#define CSTORE_GLOBAL            0x05

#define CPOP_NORMAL_MODE         0x06
#define CPOP_TEMP_MODE           0x07

#define CPROGRAM_START           0xA1
#define CPROGRAM_END             0xFF

#define CBINARY_ADD              0xB1
#define CBINARY_SUB              0xB2
#define CBINARY_MUL              0xB3
#define CBINARY_DIV              0xB4

#define CMAKE_FUNCTION           0xC1
#define CFUNCTION_CALL           0xC2

#define CRETURN                  0xF1

struct bc_mode_tok {
    uint8_t cline;
    uint8_t code;
    uint8_t cbyte;
    uint8_t address;
    string name;
    vector<uint8_t> buff;
    vector<bc_mode_tok> status;
};

bc_mode_tok init_bc_mode_tok(void);

vector<uint8_t> MerCompiler_compile_ast_program(mAST_T *ast);
vector<uint8_t> MerCompiler_compile_ast_statement(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_let_statement(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_literal(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_identifer(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_binary_expression(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_function(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_function_call(mAST_T *ast, bc_mode_tok &prog);
vector<uint8_t> MerCompiler_compile_ast_return_statement(mAST_T *ast, bc_mode_tok &prog);

#endif // MERCURY_BYTECODE_COMPILER_HEADER
