#include "ast.h"
#include "lexer.h"
#ifndef PARSE_H
#define PARSE_H

program parse::ast_program() {}

expression_statement parse::ast_statement() {}

expression parse::ast_expression() {}

identifier parse::ast_identifier() {}

literal parse::ast_literal() {}

#endif