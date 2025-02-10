#include "parse.h"
using namespace std;

AST_Program parse::AST_tokenize(string source) {
    vector<token> tokens = tokenize(source);
    AST_Program prog;
    
    token tok = get_current_token();
    while (!is_CurTokEOF(tok.tok)) {
        prog.statements.push_back(parse_statment());
        tok = get_next_token();
    }
    return prog;
}

AST_node parse::AST_nodeize(token tok) {
    AST_node node;
    if (is_Tok_identifier(tok.tok)) {
        return node = {
            .type = Identifier,
            .iden = tok.tok
        };
    } else if (is_Tok_Literal(tok.tok)) {
        return node = {
            .type = Literal,
            .value = tok.value
        };
    }
}

AST_Statement parse::parse_statment() {
    token tok = get_current_token();
    if (tok.tok == PRINT) {
        return parse_print();
    } else if (tok.tok == LET) {
        
    }
}

AST_BinExpression parse::parse_expr() {
    token tok = get_current_token();
    AST_BinExpression binexpr;
    while (!is_CurTokEOF(tok.tok) || is_Tok_BinExpression(tok.tok)) {
        binexpr.exprs.push_back(AST_nodeize(tok));
        tok = get_next_token();
    }
    return binexpr;
}

AST_PrintState parse::parse_print() {
    token tok = get_current_token();
    if (tok.tok == PRINT) {
        tok = get_next_token();
        if (tok.tok == STRING) {
            AST_PrintState print;
            print.output = tok.string_iden;
            return print;
        } else {
            AST_PrintState print;
            print.exprs = parse_expr();
            return print;
        }
    } else {
        throw runtime_error("Expected PRINT");
    }
}
