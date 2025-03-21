#ifndef MERCURY_ABSTRACT_SYNTAX_TREE_HEADER_FILE
#define MERCURY_ABSTRACT_SYNTAX_TREE_HEADER_FILE

#include <vector>
#include <string>
using namespace std;

#define Program "Program"
#define LetStatement "LetStatement"
#define ExpressionStatement "ExpressionStatement"
#define BlockStatement "BlockStatement"
#define ReturnStatement "ReturnStatement"
#define Expression "Expression"
#define FunctionStatement "FunctionStatement"
#define FunctionCallExpression "FunctionCallExpression"
#define CallExpression "CallExpression"
#define Identifier_ "Identifier"
#define Literal "Literal"
#define IntegerLiteral "IntegerLiteral"
#define StringLiteral "StringLiteral"
#define BinaryExpression "BinaryExpression"
#define StringExpression "StringExpression"

struct AST_node {
    string type;
    string tok;
    float value = 0.0;
    string string_iden;
    AST_node *poutput;

    bool is_var;
    bool is_constant;
    bool is_global;
    bool is_local;
    bool is_mom;
    bool is_list;
    bool is_None;
    string var_name;
    string data_type;

    vector<AST_node*> elements;
    AST_node *var_value;
    vector<AST_node*> mom_mems;

    string func_name;
    vector<AST_node*> body;
    vector<string> args_idens;
    string kwargs_name;
    bool is_kwargs;
    int args_size;
    AST_node *calle;
    AST_node *memobject;
    AST_node *property;
    bool computed;
    float return_value;
    string func_type;

    string func_call;
    vector<AST_node*> args;

    string mom_name;
    string mom_type;
    string son_name;
    string son_type;
    vector<AST_node*> son_mems; 
    AST_node *son_mem;


    string op;
    AST_node* left;
    AST_node* right;
    bool condtion;

    string list_name;
    string list_type;
    vector<AST_node*> list;

    vector<AST_node*> children;
};

AST_node *MerAST_new(void);
AST_node *MerAST_make_parent(string type);
AST_node *MerAST_make(string type, string tok, float value, string dt, string iden);

#endif // MERCURY_ABSTRACT_SYNTAX_TREE_HEADER_FILE