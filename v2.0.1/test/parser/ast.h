#ifndef MERCURY_ABSTRACT_SYNTAX_TREE_HEADER_FILE
#define MERCURY_ABSTRACT_SYNTAX_TREE_HEADER_FILE

#include <vector>
#include <string>
using namespace std;

#define Program "Program"
#define LetStatement "LetStatement"
#define ExpressionStatement "ExpressionStatement"
#define IfStatement "IfStatement"
#define WhileStatement "WhileStatement"
#define ForStatement "ForStatement"
#define ImportStatement "ImportStatement"
#define BlockStatement "BlockStatement"
#define ReturnStatement "ReturnStatement"
#define Expression "Expression"
#define FunctionStatement "FunctionStatement"
#define FunctionCallExpression "FunctionCallExpression"
#define Identifier_ "Identifier"
#define ComparisonExpression "ComparisonExpression"
#define Literal "Literal"
#define IntegerLiteral "IntegerLiteral"
#define BinaryExpression "BinaryExpression"
#define StringExpression "StringExpression"

struct mAST_T {
    string type;
    string tok;
    float value = 0.0;
    string string_iden;
    mAST_T *poutput;

    bool is_var;
    bool is_constant;
    bool is_global;
    bool is_local;
    bool is_mom;
    bool is_list;
    bool is_None;
    string var_name;
    string data_type;

    vector<mAST_T*> elements;
    mAST_T *var_value;
    vector<mAST_T*> mom_mems;

    string func_name;
    vector<mAST_T*> body;
    vector<string> args_idens;
    string kwargs_name;
    bool is_kwargs;
    int args_size;
    mAST_T *calle;
    mAST_T *memobject;
    mAST_T *property;
    bool computed;
    float return_value;
    string func_type;

    string func_call;
    vector<mAST_T*> args;

    string mom_name;
    string mom_type;
    string son_name;
    string son_type;
    vector<mAST_T*> son_mems; 
    mAST_T *son_mem;


    string op;
    mAST_T* left;
    mAST_T* right;
    bool condtion;

    string list_name;
    string list_type;
    vector<mAST_T*> list;

    vector<mAST_T*> children;
};

mAST_T *_MerAST_new(void);
mAST_T *_MerAST_make_parent(string type);
mAST_T *_MerAST_make(string type, string tok, float value, const char* dt, const char* iden);

#endif // MERCURY_ABSTRACT_SYNTAX_TREE_HEADER_FILE