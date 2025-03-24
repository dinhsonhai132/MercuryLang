#ifndef MERCURY_BYTECODE_COMPILER_HEADER
#define MERCURY_BYTECODE_COMPILER_HEADER

#include <cstdint>
#include <vector>
#include "parser.cpp"

using namespace std;

#define PUSH_FLOAT              0x01
#define PUSH_NORMAL_MODE        0x02
#define PUSH_TEMP_MODE          0x03

#define LOAD_GLOBAL             0x04
#define STORE_GLOBAL            0x05

#define POP_NORMAL_MODE         0x06
#define POP_TEMP_MODE           0x07

#define PROGRAM_START           0xA1
#define PROGRAM_END             0xFF

#define BINARY_ADD              0xB1
#define BINARY_SUB              0xB2
#define BINARY_MUL              0xB3
#define BINARY_DIV              0xB4

struct Program_status {
    uint8_t cline;
    uint8_t cbyte;
    uint8_t add;
    uint8_t symbol_idx;
    vector<Program_status> *status;
};

Program_status init_program_status();
vector<uint8_t> MerCompiler_compile_ast_program(AST_node *ast);
vector<uint8_t> MerCompiler_compile_ast_statement(AST_node *ast, Program_status &prog);
vector<uint8_t> MerCompiler_compile_ast(AST_node *ast, Program_status &prog);
vector<uint8_t> MerCompiler_compile_ast_literal(AST_node *ast, Program_status &prog);
vector<uint8_t> MerCompiler_compile_ast_identifer(AST_node *ast, Program_status &prog);
vector<uint8_t> MerCompiler_compile_ast_binary_expression(AST_node *ast, Program_status &prog);

#endif // MERCURY_BYTECODE_COMPILER_HEADER
