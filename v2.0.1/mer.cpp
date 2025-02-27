#include <vector>
#include <string>
#include <iostream>
using namespace std;

#define Program "Program"
#define PrintStatement "PrintStatement"
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

#define EOF_T "EOF"
#define ASSIGN "ASSIGN"
#define MOD "MOD"
#define INT_ "INT"
#define PLUS "PLUS"
#define MINUS "MINUS"
#define DIV "DIV"
#define TIME "TIME"
#define VARIABLE "VARIABLE"
#define STRING "STRING"
#define PRINT "PRINT"
#define LET "LET"
#define DOT "DOT"
#define COMMA "COMMA"
#define ASSIGN "ASSIGN"
#define IF "IF"
#define ELSE "ELSE"
#define FOR "FOR"
#define WHILE "WHILE"
#define RETURN "RETURN"
#define FUNCTION "FUNCTION"
#define LEFT_PAREN "LEFT_PAREN"
#define RIGHT_PAREN "RIGHT_PAREN"
#define LEFT_BRACKET "LEFT_BRACKET"
#define RIGHT_BRACKET "RIGHT_BRACKET"
#define LEFT_BRACE "LEFT_BRACE"
#define RIGHT_BRACE "RIGHT_BRACE"
#define EQUAL "EQUAL"
#define NOT_EQUAL "NOT_EQUAL"
#define LESS "LESS"
#define LESS_EQUAL "LESS_EQUAL"
#define GREATER "GREATER"
#define GREATER_EQUAL "GREATER_EQUAL"
#define AND "AND"
#define OR "OR"
#define NOT "NOT"
#define BREAK "BREAK"
#define CONTINUE "CONTINUE"
#define CLASS "CLASS"
#define INTERFACE_ "INTERFACE_"
#define STRUCT "STRUCT"
#define NEW "NEW"
#define DELETE_ "DELETE_"
#define CAST "CAST"
#define FLOAT_ "FLOAT"
#define DOUBLE_ "DOUBLE"
#define CHAR_ "CHAR"
#define SHORT_ "SHORT"
#define LONG_ "LONG"
#define AUTO_ "AUTO"
#define VOID_ "VOID"
#define BOOL_ "BOOL"
#define SEMICOLON "SEMICOLON"
#define COLON "COLON"
#define ARROW "ARROW"
#define COMMENT "COMMENT"
#define INCLUDE "INCLUDE"
#define EXTERN "EXTERN"
#define USING "USING"
#define POW "POW"
#define CONST_ "CONST"
#define ARG "ARG"
#define KWARG "KWARG"
#define FUNCTION_CALL "FUNCTION_CALL"

#define INT_T "INT_T"
#define FLOAT_T "FLOAT_T"
#define DOUBLE_T "DOUBLE_T"
#define STRING_T "STRING_T"
#define AUTO_T "AUTO_T"
#define NULL_T "NULL_T"
#define VOID_T "VOID_T"
#define BOOL_T "BOOL_T"
#define CHAR_T "CHAR_T"
#define SHORT_T "SHORT_T"
#define LONG_T "LONG_T"
#define LITERAL_T "LITERAL_T"
#define FUNCTION_T "FUNCTION_T"
#define ARRAY_T "ARRAY_T"
#define STRUCT_T "STRUCT_T"
#define POINTER_T "POINTER_T"
#define CLASS_T "CLASS_T"
#define INTERFACE__T "INTERFACE__T"

#define MAX 1024

#define LITERAL {INT_, FLOAT_, DOUBLE_}
#define IDENTIFIER {LET, PRINT, IF, ELSE, FOR, WHILE}
#define EXPR {PLUS, MINUS, DIV, TIME, MOD, INT_, FLOAT_, DOUBLE_}
#define TYPE {INT_T, FLOAT_T, DOUBLE_T, CHAR_T, SHORT_T, LONG_T, AUTO_T, VOID_T, BOOL_T, STRING_T, STRUCT_T, CLASS_T}

struct token {
    string tok;
    string type;
    float value;

    string name;
    string symbol;
    string string_iden;

    token() : tok(""), type(""), value(0.0), name(""), symbol(""), string_iden("") {};
    token(string tok, string type, float value, string name, string symbol, string string_iden) : tok(tok), type(type), value(value), name(name), symbol(symbol), string_iden(string_iden) {}
};


static inline bool isskippable(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
};

static inline bool is_potential_identifier_char(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

static inline string get_2_char(char c1, char c2)
{
    switch (c1)
    {
    case '=':
        if (c2 == '=')
            return EQUAL;
        break;
    case '<':
        if (c2 == '=')
            return LESS_EQUAL;
        if (c2 == '>')
            return NOT_EQUAL;
        break;
    case '>':
        if (c2 == '=')
            return GREATER_EQUAL;
        break;
    case '&':
        if (c2 == '&')
            return AND;
        break;
    case '|':
        if (c2 == '|')
            return OR;
        break;
    case '*':
        if (c2 == '*')
            return POW;
        break;
    case '!':
        if (c2 == '=')
            return NOT_EQUAL;
        break;
    }
    return "";
}

static inline string get_1_char(char c)
{
    switch (c) {
        case '=':
            return ASSIGN;
        case '<':
            return LESS;
        case '>':
            return GREATER;
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '/':
            return DIV;
        case '*':
            return TIME;
        case '!':
            return NOT;
        case '(':
            return LEFT_PAREN;
        case ')':
            return RIGHT_PAREN;
        case '{':
            return LEFT_BRACE;
        case '}':
            return RIGHT_BRACE;
        case '[':
            return LEFT_BRACKET;
        case ']':
            return RIGHT_BRACKET;
        case ',':
            return COMMA;
        case ';':
            return SEMICOLON;
        case ':':
            return COLON;
        case '.':
            return DOT;
        case '%':
            return MOD;
    }

    return "";
}

static inline bool is_identifier(string iden)
{
    vector<string> state = {"LET", "PRINT", "IF", "ELSE", "FOR",
                            "WHILE", "RETURN", "FUNC", "INT", "FLOAT", "DOUBLE", "CHAR",
                            "SHORT", "LONG", "AUTO", "VOID", "BOOL", "CHAR", "STRING",
                            "STRUCT", "CLASS", "INTER", "NEW", "DELETE_", "CAST",
                            "TRUE", "", "BREAK", "CONTINUE"};
    for (string s : state)
    {
        if (iden == s)
            return true;
    }
    return false;
}

static inline string return_identifier(string iden) {
    if (iden == "LET")
        return LET;
    else if (iden == "PRINT")
        return PRINT;
    else if (iden == "IF")
        return IF;
    else if (iden == "ELSE")
        return ELSE;
    else if (iden == "FOR")
        return FOR;
    else if (iden == "WHILE")
        return WHILE;
    else if (iden == "RETURN")
        return RETURN;
    else if (iden == "FUNC")
        return FUNCTION;
    else if (iden == "INT")
        return INT_;
    else if (iden == "FLOAT")
        return FLOAT_;
    else if (iden == "DOU")
        return DOUBLE_;
    else if (iden == "CHAR")
        return CHAR_;
    else if (iden == "SHORT")
        return SHORT_;
    else if (iden == "LONG")
        return LONG_;
    else if (iden == "AUTO")
        return AUTO_;
    else if (iden == "VOID")
        return VOID_;
    else if (iden == "BOOL")
        return BOOL_;
    else if (iden == "CHAR")
        return CHAR_;
    else if (iden == "STR")
        return STRING;
    else if (iden == "STRUCT")
        return STRUCT;
    else if (iden == "CLASS")
        return CLASS;
    else if (iden == "INTER")
        return INTERFACE_;
    else if (iden == "NEW")
        return NEW;
    else if (iden == "DEL")
        return DELETE_;
    else if (iden == "CAST")
        return CAST;
    else if (iden == "BRK")
        return BREAK;
    else if (iden == "CONT")
        return CONTINUE;
    else if (iden == "INC")
        return INCLUDE;
    else if (iden == "EXT")
        return EXTERN;
    else if (iden == "USING")
        return USING;
    else if (iden == "CONS")
        return CONST_;

    return "";
}

static inline bool is_keyword(char c)
{
    vector<char> keyword = {
        '+', '-', '*', '/', '(', ')', '{', '}',
        '[', ']', ',', ';', ':', '=', '!', '<',
        '>', '&', '|'};
    for (char k : keyword)
    {
        if (c == k)
            return true;
    }
    return false;
}


vector<token> MerLexer_tokenize(string source)
{
    int idx = 0;
    vector<token> tokens;
    while (idx < source.length())
    {
        char c = source[idx];

        if (is_potential_identifier_char(c))
        { // execute char identifier and syntax
            string iden = "";
            bool found = false;

            while (is_potential_identifier_char(c))
            {
                iden += c;
                idx++;
                if (idx >= source.length())
                    break;
                c = source[idx];
            }

            if (is_identifier(iden))
            {
                tokens.push_back(token(return_identifier(iden), NULL_T, 0.0, "", iden.c_str(), ""));
            }
            else
            {
                tokens.push_back(token(VARIABLE, NULL_T, 0.0, "", iden.c_str(), ""));
            }
        }
        else if (isdigit(c))
        { // execute number
            string num = "";
            int dot_count = 0;
            while (isdigit(c) || c == '.')
            {
                if (c == '.')
                {
                    dot_count++;
                    if (dot_count > 1)
                        break;
                }
                num += c;
                idx++;
                if (idx >= source.length())
                    break;
                c = source[idx];
            }

            float num_value = atof(num.c_str());
            tokens.push_back(token(dot_count == 0 ? INT_ : FLOAT_,
                                   dot_count == 0 ? INT_T : FLOAT_T, num_value, "", num.c_str(), ""));
        }
        else if (c == '"')
        { // execute string
            string str = "";
            idx++;
            while (source[idx] != '"')
            {
                str += source[idx];
                idx++;
            }
            tokens.push_back(token(STRING, STRING_T, 0.0, "", "", str.c_str()));
            idx++;
        } else if (c == '!')
        { //define function call
            char c2 = source[idx + 1];
            string name;
            if (is_potential_identifier_char(c2)) {
                while (is_potential_identifier_char(c2)) {
                    name += c2;
                    idx++;
                    if (idx >= source.length()) {
                        break;
                    }
                    c2 = source[idx];
                }
            }
            tokens.push_back(token(FUNCTION_CALL, AUTO_T, 0.0, name.c_str(), name.c_str(), name.c_str()));
        }
        else if (is_keyword(c))
        { // execute keyword
            char c2 = source[idx + 1];
            if (is_keyword(c2))
            {
                string keyword = string(1, c) + string(1, c2);
                tokens.push_back(token(get_2_char(c, c2), NULL_T, 0.0, "", keyword.c_str(), ""));
                idx += 2;
            }
            else
            {
                tokens.push_back(token(get_1_char(c), NULL_T, 0.0, "", string(1, c), ""));
                idx++;
            }
        }
        else if (isskippable(c))
        {
            idx++;
        }
        else
        {
            idx++;
        }
    }
    tokens.push_back(token(EOF_T, NULL_T, 0.0, "", "\n", ""));
    return tokens;
}

// ast
struct AST_node {
    string type;
    string tok;
    float value;
    string string_iden;
    AST_node *poutput;

    bool constant;
    bool global;
    bool local;
    string var_name;
    string data_type;
    AST_node *var_value;

    string func_name;
    vector<AST_node*> body;
    vector<AST_node*> args;
    AST_node *calle;
    float return_value;
    string func_type;

    string op;
    AST_node* left;
    AST_node* right;
    bool condtion;

    string list_name;
    string list_type;
    vector<AST_node*> list;

    vector<AST_node*> children;
};

AST_node *MerAST_new(void) {
    AST_node* node = new AST_node();
    if (!node) {
        cerr << "Memory allocation failed for AST_node!" << endl;
        exit(1);
    }

    node->type = "";
    node->tok = "";
    node->poutput = NULL;
    node->value = 0.0;
    node->string_iden = "";
    node->constant = false;
    node->global = false;
    node->local = false;
    node->var_name = "";
    node->data_type = "";
    node->func_name = "";
    node->var_value = NULL;
    node->body = vector<AST_node*>();
    node->args = vector<AST_node*>();
    node->return_value = 0.0;
    node->func_type = "";
    node->op = "";
    node->left = NULL;
    node->right = NULL;
    node->list_name = "";
    node->list_type = "";
    node->list = vector<AST_node*>();
    node->children = vector<AST_node*>();
    node->condtion = false;

    return node;
}


AST_node *MerAST_make(string type, string tok, float value, string dt) {
    AST_node* node = new AST_node();
    node->tok = tok;
    node->value = value;
    node->data_type = dt;
    node->type = type;
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

// parser
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
    AST_node *MerParser_statement();
    AST_node *MerParser_primary();
    AST_node *MerParser_additive_expression();
    AST_node *MerParser_multiplicative_expression();
    AST_node *MerParser_function_call();
    AST_node *MerParser_expression();
    AST_node *MerParser_binary_expression(AST_node *left, AST_node *right, string op);
};

token Parser::get_ctok() {
    return cur_tok = tokens[idx];
}

token Parser::get_ntok() {
    return cur_tok = tokens[idx++];
}

token Parser::jump_tok(int n) {
    return cur_tok = tokens[idx += n];
}

bool Parser::look_ahead(string tok, int n) {
    cur_tok = tokens[idx + n];
    return cur_tok.tok == tok;
}

AST_node *Parser::MerParser_program() {
    program = MerAST_make_parent(Program);
    cur_tok = get_ctok();
    while (!Is_tok_eof(cur_tok)) {
        program->children.push_back(MerParser_multiplicative_expression());
        cur_tok = get_ntok();
    }
    return program;
}

AST_node *Parser::MerParser_primary() {
    cur_tok = get_ctok();
    if (Is_tok_identifier(cur_tok.tok)) {
        return MerAST_make(Identifier_, cur_tok.tok, cur_tok.value, cur_tok.type);
    } else if (Is_tok_literal(cur_tok.tok)) {
        return MerAST_make(Literal, cur_tok.tok, cur_tok.value, cur_tok.type);
    }
    return NULL;
}

AST_node *Parser::MerParser_additive_expression() {
    AST_node *left = MerParser_multiplicative_expression();
    AST_node *right;

    cur_tok = get_ctok();
    while (cur_tok.tok == PLUS || cur_tok.tok == MINUS) {
        string op = get_ntok().tok;
        get_ntok();
        right = MerParser_multiplicative_expression();
        left = MerParser_binary_expression(left, right, op);
    }
    return left;
}

AST_node *Parser::MerParser_multiplicative_expression() {
    AST_node *left = MerParser_primary();
    AST_node *right;

    cur_tok = get_ctok();
    while (cur_tok.tok == TIME || cur_tok.tok == DIV || cur_tok.tok == MOD) {
        string op = get_ntok().tok;
        cur_tok = get_ntok();
        right = MerParser_primary();
        left = MerParser_binary_expression(left, right, op);
    }
    return left;
}

AST_node *Parser::MerParser_binary_expression(AST_node *left, AST_node *right, string op) {
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

void print_token(string source) {
    for (auto &tok : MerLexer_tokenize(source)) {
        cout << "{ tok: " << tok.tok << ", type: " << tok.type << ", value: " << tok.value << " }" << endl;
    }
}

void print_ast(AST_node *node, int indent = 0) {
    if (!node) return;

    cout << string(indent, ' ') << "{ type: " << node->type
         << ", tok: " << node->tok
         << ", value: " << node->value
         << ", left: " << node->left
         << ", op: " << node->op
         << ", right: " << node->right
         << " }" << endl;

    for (auto &child : node->children) {
        print_ast(child, indent + 2);
    }
}

void Shell() {
    cout << "v2.0.1" << endl;
    for (;;) {
        string source;
        cout << ">> ";
        getline(cin, source);
        if (source == "exit") {
            break;
        }
        vector<token> tokens = MerLexer_tokenize(source);
        AST_node *ast = MerAST_make_ast(tokens);
        print_ast(ast);
    }
}

int main() {
    Shell();
    return 0;
}
