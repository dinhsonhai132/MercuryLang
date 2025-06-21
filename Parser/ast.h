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

#ifndef MERCURY_ABSTRACT_SYNTAX_TREE_HEADER_FILE
#define MERCURY_ABSTRACT_SYNTAX_TREE_HEADER_FILE

#include <vector>
#include <string>
#include <iostream>
using namespace std;

#define _SUCCESS 1
#define _FAILURE 0

#define Program "Program"
#define LetStatement "LetStatement"
#define ExpressionStatement "ExpressionStatement"
#define IfStatement "IfStatement"
#define AssignStatement "AssignStatement"
#define WhileStatement "WhileStatement"
#define ForStatement "ForStatement"
#define ImportStatement "ImportStatement"
#define BlockStatement "BlockStatement"
#define ReturnStatement "ReturnStatement"
#define StoreIndexStatement "StoreIndexStatement"
#define ExtractExpression "ExtractExpression"
#define StringExpression "StringExpression"
#define ExtractExpression "ExtractExpression"
#define ArrayExpression "ArrayExpression"
#define StringIdentifier "StringIdentifier"
#define Expression "Expression"
#define FunctionStatement "FunctionStatement"
#define FunctionCallExpression "FunctionCallExpression"
#define Identifier_ "Identifier"
#define ComparisonExpression "ComparisonExpression"
#define StringVariableStatement "StringVariableStatement"
#define Literal "Literal"
#define TrueExpression "TrueExpression"
#define FalseExpression "FalseExpression"
#define IntegerLiteral "IntegerLiteral"
#define LoopStatement "LoopStatement"
#define BreakStatement "BreakStatement"
#define ContinueStatement "ContinueStatement"
#define BinaryExpression "BinaryExpression"
#define StringExpression "StringExpression"
#define ListStatement "ListStatement"
#define ListExpression "ListExpression"
#define ArrayStoreElementExpression "ArrayStoreElementExpression"
#define ForInStatement "ForInStatement"
#define AndExpression "AndExpression"
#define OrExpression "OrExpression"
#define NotExpression "NotExpression"
#define IncrementExpression "IncrementExpression"
#define DecrementExpression "DecrementExpression"
#define FunctionWithArgsStatement "FunctionWithArgsStatement"
#define FunctionCallWithArgsExpression "FunctionCallWithArgsStatement"
#define ClassStatement "ClassStatement"
#define DeleteStatement "DeleteStatement"
#define AssertStatement "AssertStatement"

#define is_ast_expression(type) \
    ((type) == BinaryExpression                 || \
     (type) == Literal                          || \
     (type) == Identifier_                      || \
     (type) == ComparisonExpression             || \
     (type) == ArrayExpression                  || \
     (type) == FunctionCallExpression           || \
     (type) == FunctionCallWithArgsExpression   || \
     (type) == IncrementExpression              || \
     (type) == AndExpression                    || \
     (type) == OrExpression                     || \
     (type) == NotExpression                    || \
     (type) == ExtractExpression                || \
     (type) == TrueExpression                   || \
     (type) == FalseExpression                  || \
     (type) == StringIdentifier)

struct mAST_T
{
    const char* file; // for ast program

    string type;
    string tok;
    float value = 0.0;
    string string_iden;
    mAST_T *poutput;

    int true_line;

    bool is_at_start;
    bool is_if;
    bool is_while;
    bool is_for;
    bool is_import;
    bool is_block;

    // For if statement
    mAST_T *comp;
    vector<mAST_T *> then_body;
    vector<mAST_T *> else_body;
    bool has_else = false;

    // incr expr
    bool is_inc;
    bool is_dec;
    mAST_T *inc_dec_value;

    // assginment
    string assign_iden;
    mAST_T *assign_value;
    bool is_assign_operator;
    bool is_plus_assign;
    bool is_minus_assign;
    bool is_mul_assign;
    bool is_div_assign;
    bool is_mod_assign;

    // not expr
    mAST_T *not_expr;
    
    // for break and continue
    bool is_break;
    bool is_continue;

    // for built-in function
    string built_in_func_name;
    bool is_built_in_func;

    // for while loop
    mAST_T *while_cond;
    bool is_inf;
    vector<mAST_T *> while_body;

    // for string
    bool is_string;
    string str_v;
    vector<mAST_T *> str_children;

    // for string statement
    string str_iden;
    mAST_T *str_value;

    //for print
    string str_print_v;
    bool is_print;
    mAST_T *print_v;

    // For literal
    bool is_var;
    bool is_constant;
    bool is_global;
    bool is_local;
    bool is_mom;
    bool is_list;
    bool is_None;

    // for class
    string class_name;
    bool is_class;
    vector<mAST_T *> class_body;

    // for attr System.out.println("hello");
    mAST_T *attr;
    mAST_T *attr_value;
    bool is_dad;

    // for delete
    bool is_del_element_from_list;
    string del_iden;
    mAST_T *del_index;

    // for comparison expression
    string comp_op;
    mAST_T *comp_left;
    mAST_T *comp_right;

    // for do while loop
    vector<mAST_T *> do_body;

    // for in statement
    string in_iden;
    mAST_T *in_value;
    vector<mAST_T *> in_body;   
    bool for_is_having_else;
    vector<mAST_T *> in_else_body; 

    // For variable
    string var_name;
    string data_type;
    mAST_T *var_value;

    // For function
    string func_name;
    vector<mAST_T *> body;
    vector<string> args_idens;
    string func_type;

    // for return
    mAST_T *return_v;
    bool is_return;
    bool is_void;

    // For function call
    string func_call;
    bool is_having_args;
    vector<mAST_T *> args;

    // For binary expression
    string op;
    mAST_T *left;
    mAST_T *right;
    bool cond;

    // For list
    string list_name;
    string list_type;
    vector<mAST_T *> list;
    bool is_alone_val;
    size_t list_size;

    // for extract expression and statement
    string extract_name;
    mAST_T *extract_value;
    mAST_T *extract_assign;
    bool is_extract;
    bool is_string_extract;
    bool is_extract_statement;

    // for string variable
    string str_var_name;
    string str_var_type;
    mAST_T *str_var_value;

    // for array store
    mAST_T *array_store;
    mAST_T *array_store_value;
    

    vector<mAST_T *> children;
};

mAST_T *MerAST_new(void);
mAST_T *MerAST_make_parent(string type);
mAST_T *MerAST_make(string type, string tok, float value, const char *dt, const char *iden, int row);
void MerAST_print_ast(mAST_T *ast, int indent = 0);
int MerAST_free(mAST_T *ast);

#endif // MERCURY_ABSTRACT_SYNTAX_TREE_HEADER_FILE