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

#include "C:\MercuryLang\v2.0.1\mercury\ceval.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unordered_map>
#include <filesystem>

using namespace std;

void print_ast(mAST_T *node, int depth = 0) {
    if (!node) return;

    for (int i = 0; i < depth; ++i) std::cout << "  ";

    std::cout << "Type: " << node->type;
    if (!node->tok.empty()) std::cout << ", Token: " << node->tok;
    if (!node->var_name.empty()) std::cout << ", Variable: " << node->var_name;
    if (!node->func_name.empty()) std::cout << ", Function: " << node->func_name;
    if (!node->comp_op.empty()) std::cout << ", Operator: " << node->comp_op;
    if (node->value != 0.0) std::cout << ", Value: " << node->value;
    std::cout << std::endl;

    for (auto &child : node->children) {
        print_ast(child, depth + 1);
    }

    if (node->left) {
        for (int i = 0; i < depth + 1; ++i) std::cout << "  ";
        std::cout << "Left:" << std::endl;
        print_ast(node->left, depth + 2);
    }

    if (node->right) {
        for (int i = 0; i < depth + 1; ++i) std::cout << "  ";
        std::cout << "Right:" << std::endl;
        print_ast(node->right, depth + 2);
    }

    if (node->comp_left) {
        for (int i = 0; i < depth + 1; ++i) std::cout << "  ";
        std::cout << "Comparison Left:" << std::endl;
        print_ast(node->comp_left, depth + 2);
    }

    if (node->comp_right) {
        for (int i = 0; i < depth + 1; ++i) std::cout << "  ";
        std::cout << "Comparison Right:" << std::endl;
        print_ast(node->comp_right, depth + 2);
    }

    if (node->return_v) {
        for (int i = 0; i < depth + 1; ++i) std::cout << "  ";
        std::cout << "Return Value:" << std::endl;
        print_ast(node->return_v, depth + 2);
    }
}

int main() {
    const char *input = "1 + 1 < 4";
    mLexer_T *lexer = _MerLexer_init(input);
    mParser_T *parser = _MerParser_init(lexer);
    mAST_T *ast = MerParser_parse_program(parser);
    vector<uint8_t> code = MerCompiler_compile_ast_program(ast);
    stack *stk = MerCompilerBytecode_evaluate_program(code);


    return 0;    
}