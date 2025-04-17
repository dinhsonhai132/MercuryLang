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

    // Indentation for readability
    for (int i = 0; i < depth; ++i) cout << "  ";

    // Print the node type and basic information
    cout << "{\n";
    for (int i = 0; i < depth + 1; ++i) cout << "  ";
    cout << "\"Type\": \"" << node->type << "\"";

    if (!node->tok.empty()) cout << ", \"Token\": \"" << node->tok << "\"";
    if (!node->var_name.empty()) cout << ", \"Variable\": \"" << node->var_name << "\"";
    if (!node->func_name.empty()) cout << ", \"Function\": \"" << node->func_name << "\"";
    if (!node->comp_op.empty()) cout << ", \"Operator\": \"" << node->comp_op << "\"";
    if (node->value != 0.0) cout << ", \"Value\": " << node->value;

    cout << ",\n";

    // Print variable value if present
    if (node->var_value) {
        for (int i = 0; i < depth + 1; ++i) cout << "  ";
        cout << "\"Variable Value\": ";
        print_ast(node->var_value, depth + 2);
    }

    // Print comparison operation
    if (node->comp) {
        for (int i = 0; i < depth + 1; ++i) cout << "  ";
        cout << "\"Comparison\": ";
        print_ast(node->comp, depth + 2);
    }

    // Print the 'then' body
    if (!node->then_body.empty()) {
        for (int i = 0; i < depth + 1; ++i) cout << "  ";
        cout << "\"Then Body\": [\n";
        for (auto &child : node->then_body) {
            print_ast(child, depth + 2);
        }
        for (int i = 0; i < depth + 1; ++i) cout << "  ";
        cout << "],\n";
    }

    // Print the 'else' body
    if (!node->else_body.empty()) {
        for (int i = 0; i < depth + 1; ++i) cout << "  ";
        cout << "\"Else Body\": [\n";
        for (auto &child : node->else_body) {
            print_ast(child, depth + 2);
        }
        for (int i = 0; i < depth + 1; ++i) cout << "  ";
        cout << "],\n";
    }

    // Print left and right nodes for binary expressions
    if (node->left) {
        for (int i = 0; i < depth + 1; ++i) cout << "  ";
        cout << "\"Left\": ";
        print_ast(node->left, depth + 2);
    }

    if (node->right) {
        for (int i = 0; i < depth + 1; ++i) cout << "  ";
        cout << "\"Right\": ";
        print_ast(node->right, depth + 2);
    }

    // Print comparison left and right nodes
    if (node->comp_left) {
        for (int i = 0; i < depth + 1; ++i) cout << "  ";
        cout << "\"Comparison Left\": ";
        print_ast(node->comp_left, depth + 2);
    }

    if (node->comp_right) {
        for (int i = 0; i < depth + 1; ++i) cout << "  ";
        cout << "\"Comparison Right\": ";
        print_ast(node->comp_right, depth + 2);
    }

    // Print return value if present
    if (node->return_v) {
        for (int i = 0; i < depth + 1; ++i) cout << "  ";
        cout << "\"Return Value\": ";
        print_ast(node->return_v, depth + 2);
    }

    // Print children nodes
    if (!node->children.empty()) {
        for (int i = 0; i < depth + 1; ++i) cout << "  ";
        cout << "\"Children\": [\n";
        for (auto &child : node->children) {
            print_ast(child, depth + 2);
        }
        for (int i = 0; i < depth + 1; ++i) cout << "  ";
        cout << "]\n";
    }

    // Close the current node
    for (int i = 0; i < depth; ++i) cout << "  ";
    cout << "}\n";
}

int main() {
    string input;
    getline(cin, input);
    const char *input_cstr = input.c_str();
    mLexer_T *lexer = _MerLexer_init(input_cstr);
    mParser_T *parser = _MerParser_init(lexer);
    mAST_T *ast = MerParser_parse_program(parser);
    print_ast(ast);

    return 0;    
}