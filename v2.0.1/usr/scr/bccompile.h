#ifndef MERCURY_BYTECODE_COMPILER_HEADER
#define MERCURY_BYTECODE_COMPILER_HEADER

#include <cstdint>
#include <string>
#include <cstring>
#include <iomanip>
#include "compile.cpp"

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

struct Program_status {
    uint8_t cline;
    uint8_t cbyte;
    uint8_t address;
    string name;
    vector<Program_status> status;
};

Program_status init_program_status(void);

vector<uint8_t> MerCompiler_compile_ast_program(AST_node *ast);
vector<uint8_t> MerCompiler_compile_ast_statement(AST_node *ast, Program_status &prog);
vector<uint8_t> MerCompiler_compile_ast(AST_node *ast, Program_status &prog);
vector<uint8_t> MerCompiler_compile_ast_let_statement(AST_node *ast, Program_status &prog);
vector<uint8_t> MerCompiler_compile_ast_literal(AST_node *ast, Program_status &prog);
vector<uint8_t> MerCompiler_compile_ast_identifer(AST_node *ast, Program_status &prog);
vector<uint8_t> MerCompiler_compile_ast_binary_expression(AST_node *ast, Program_status &prog);
vector<uint8_t> MerCompiler_compile_ast_function(AST_node *ast, Program_status &prog);
vector<uint8_t> MerCompiler_compile_ast_function_call(AST_node *ast, Program_status &prog);
vector<uint8_t> MerCompiler_compile_ast_return_statement(AST_node *ast, Program_status &prog);

#endif // MERCURY_BYTECODE_COMPILER_HEADER
