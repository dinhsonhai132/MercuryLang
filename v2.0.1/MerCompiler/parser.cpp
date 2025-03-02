#include <vector>
#include <string>
#include <iostream>
#include "lexer.cpp"
#include "ast.cpp"
using namespace std;

struct AST_node {
    string type;
    string tok;
    float value = 0.0;
    string string_iden;
    AST_node *poutput;

    bool is_constant;
    bool is_global;
    bool is_local;
    bool is_list;
    string var_name;
    string data_type;
    AST_node *var_value;
    vector<AST_node*> elements;
    bool is_None;

    string func_name;
    vector<AST_node*> body;
    vector<AST_node*> args;
    int args_size;
    AST_node *calle;
    float return_value;
    string func_type;

    string func_call;

    string op;
    AST_node* left;
    AST_node* right;
    bool condtion;

    string list_name;
    string list_type;
    vector<AST_node*> list;

    vector<AST_node*> children;
};

AST_node *MerAST_make(string type, string tok, float value, string dt, string name) {
    AST_node* node = new AST_node();
    node->tok = tok;
    node->value = value;
    node->data_type = dt;
    node->type = type;
    node->string_iden = name;
    return node;
}

AST_node *MerAST_make_parent(string type) {
    AST_node* node = new AST_node();
    node->type = type;
    return node;
}

bool Is_tok_eof(token tok) {
    return tok.tok == EOF_T;
}

bool Is_tok_type(token tok) {
    for (auto &tk : TYPE) {
        if (tk == tok.tok) {
            return true;
        }
    }
    return false;
}

bool Is_tok_literal(string tok) {
    for (auto &tk : LITERAL) {
        if (tk == tok) {
            return true;
        }
    }
    return false;
}

bool Is_tok_identifier(string tok) {
    for (auto &tk : IDENTIFIER) {
        if (tk == tok) {
            return true;
        }
    }
    return false;
}

bool Is_tok_expression(string tok) {
    for (auto &tk : EXPR) {
        if (tk == tok) {
            return true;
        }
    }
    return false;
}

// Parser
class Parser {
private:
    vector<token> tokens;
    int idx;
    token cur_tok;
    AST_node *program;

public:
    Parser(vector<token> tokens) : tokens(tokens), idx(0) {}

    bool look_ahead(string tok, int n);

    token get_ctok();
    token get_ntok();
    token jump_tok(int n);

    AST_node *MerParser_program();
    AST_node *MerParser_primary();
    AST_node *MerParser_additive_expression();
    AST_node *MerParser_multiplicative_expression();
    AST_node *MerParser_function_call_statement();
    AST_node *MerParser_let_statement();
    AST_node *MerParser_statement();
    AST_node *MerParser_binary_expression(AST_node *left, AST_node *right, string op);
};

token Parser::get_ctok() {
    if (idx >= tokens.size()) {
        return tokens[tokens.size() - 1];
    }
    return cur_tok = tokens[idx];
}

token Parser::get_ntok() {
    idx++;
    if (idx >= tokens.size()) {
        return tokens[tokens.size() - 1];
    }
    return cur_tok = tokens[idx];
}

token Parser::jump_tok(int n) {
    idx += n;
    if (idx >= tokens.size()) {
        return tokens[tokens.size() - 1];
    }

    return cur_tok = tokens[idx];
}

bool Parser::look_ahead(string tok, int n) {
    return tokens[idx + n].tok == tok;
}

AST_node *Parser::MerParser_program() {
    program = MerAST_make_parent(Program);
    cur_tok = get_ctok();

    program->children.push_back(MerParser_statement());
    return program;
}

AST_node *Parser::MerParser_statement() {
    AST_node *node = MerAST_make_parent(ExpressionStatement);
    cur_tok = get_ctok();
    while (!Is_tok_eof(cur_tok)) {
        if (cur_tok.tok == LET) {
            node->children.push_back(MerParser_let_statement());
            cur_tok = get_ntok();
        } else if (cur_tok.tok == FUNCTION_CALL) {
            node->children.push_back(MerParser_function_call_statement());
            cur_tok = get_ntok();
        } else {
            node->children.push_back(MerParser_additive_expression());
        }
    }
    return node;
}

AST_node *Parser::MerParser_primary() {
    cur_tok = get_ctok();
    
    if (Is_tok_identifier(cur_tok.tok)) {
        return MerAST_make(Identifier_, cur_tok.tok, cur_tok.value, cur_tok.type, cur_tok.name);
    } else if (Is_tok_literal(cur_tok.tok)) {
        return MerAST_make(Literal, cur_tok.tok, cur_tok.value, cur_tok.type, cur_tok.name);
    }
    cerr << "Lỗi: Token không hợp lệ!\n";
    return nullptr;
}

AST_node *Parser::MerParser_let_statement() {
    AST_node *node = MerAST_make_parent(LetStatement);
    cur_tok = get_ctok();
    
    if (cur_tok.tok == LET) {  
        node->is_local = true;
    } else if (cur_tok.tok == CONST_) {
        node->is_constant = true;
    } else {
        throw runtime_error("Error: Invalid token LET | CONST " + cur_tok.tok + "!");
    }

    cur_tok = get_ntok();
    if (Is_tok_identifier(cur_tok.tok)) {
        node->var_name = cur_tok.name;
        cur_tok = get_ntok();
        if (cur_tok.tok == ASSIGN) {
            cur_tok = get_ntok();
            if (cur_tok.tok == LEFT_BRACE) {
                node->is_list = true;
                while (cur_tok.tok != RIGHT_BRACE) {
                    if (cur_tok.tok == COMMA) {
                        cur_tok = get_ntok();
                    } else {
                        node->elements.push_back(MerParser_additive_expression());
                        cur_tok = get_ntok();
                    }
                }
            } else {
                node->var_value = MerParser_additive_expression();
            }
        } else {
            node->is_None = true;
            node->var_value = nullptr;
        }
    }
    node->data_type = AUTO_T;
    return node;
}

AST_node *Parser::MerParser_function_call_statement() {
    AST_node *node = MerAST_make_parent(FunctionCallExpression);
    cur_tok = get_ctok();
    if (cur_tok.tok == FUNCTION_CALL) {
        node->func_call = cur_tok.name;
        cur_tok = get_ntok();
        if (cur_tok.tok == LEFT_PAREN) {
            cur_tok = get_ntok();
            while (cur_tok.tok != RIGHT_PAREN) {
                if (cur_tok.tok == COMMA) {
                    cur_tok = get_ntok();
                } else {
                    node->args.push_back(MerParser_additive_expression());
                    cur_tok = get_ntok();
                }
            }
        }
    }
    node->func_type = AUTO_T;
    return node;
}

AST_node *Parser::MerParser_additive_expression() {
    AST_node *left = MerParser_multiplicative_expression();

    while (cur_tok.tok == PLUS || cur_tok.tok == MINUS) {
        string op = cur_tok.tok;
        cur_tok = get_ntok();

        if (Is_tok_eof(cur_tok)) {
            cout << "Lỗi: Phép toán " << op << " thiếu toán hạng bên phải!\n";
            return left;
        }

        AST_node *right = MerParser_multiplicative_expression();
        left = MerParser_binary_expression(left, right, op);
    }
    return left;
}

AST_node *Parser::MerParser_multiplicative_expression() {
    AST_node *left = MerParser_primary();

    cur_tok = get_ntok();
    while (cur_tok.tok == TIME || cur_tok.tok == DIV || cur_tok.tok == MOD) {
        string op = cur_tok.tok;
        cur_tok = get_ntok();

        if (Is_tok_eof(cur_tok)) {
            cout << "Lỗi: Phép toán " << op << " thiếu toán hạng bên phải!\n";
            return left;
        }

        AST_node *right = MerParser_primary();
        left = MerParser_binary_expression(left, right, op);
        cur_tok = get_ntok();
    }
    return left;
}

AST_node *Parser::MerParser_binary_expression(AST_node *left, AST_node *right, string op) {
    if (!left || !right) {
        cout << "Lỗi: Biểu thức nhị phân " << op << " bị thiếu toán hạng!\n";
        return nullptr;
    }

    AST_node *node = MerAST_make_parent(BinaryExpression);
    node->left = left;
    node->right = right;
    node->op = op;
    return node;
}

AST_node *MerAST_make_ast(vector<token> tokens) {
    Parser parser(tokens);
    return parser.MerParser_program();
}

// object

#define SUCCESS 0;
#define FAILURE 1;

struct MerObject {
    
    string file_name;
    string objtype;
    int ovalue;

    bool is_mom;
    string mom_name;
    string mom_t;

    string iden;
    float rvalue;
    float fvalue;
    string svalue;
    double dvalue;
    bool bvalue;

    float args_value;
    string args_type;
    bool is_func_v;

    bool is_constant;
    bool is_args;
    bool is_kwargs;
    bool is_global;
    bool iserrt;
    MerObject *objv;
};

MerObject *MerObject_new(void);
int MerObject_free(MerObject *obj);


MerObject *MerObject_new(void) {
    MerObject *obj = (MerObject *)malloc(sizeof(MerObject));
    obj->objtype = "";
    obj->file_name = "";
    obj->ovalue = 0;
    obj->is_mom = false;
    obj->mom_name = "";
    obj->mom_t = "";
    obj->iden = "";
    obj->rvalue = 0.0;
    obj->fvalue = 0.0;
    obj->svalue = "";
    obj->dvalue = 0.0;
    obj->bvalue = false;
    obj->args_value = 0.0;
    obj->args_type = "";
    obj->is_func_v = false;
    obj->is_constant = false;
    obj->is_args = false;
    obj->is_kwargs = false;
    obj->is_global = false;
    obj->iserrt = false;
    obj->objv = NULL;
    return obj;
}


int MerObject_free(MerObject *obj) {
    if (obj->iserrt) {
        return FAILURE
    }

    free(obj);
    return SUCCESS;
}