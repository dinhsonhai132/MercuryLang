#include "lexer.h"
using namespace std;

mLexer_T *_MerLexer_init(const char *buf) {
    mLexer_T *lexer = _MerLexer_new();
    lexer->buf = buf;
    lexer->inp = buf;
    lexer->buf_size = strlen(buf);
    lexer->iden = NULL;
    lexer->cstart = buf[0];
    lexer->cend = buf[lexer->buf_size - 1];
    lexer->str = NULL;
    lexer->com = NULL;
    lexer->sytx = NULL;
    lexer->cur = '\0';
    lexer->ncur = '\0';
    lexer->col = 0;
    lexer->row = 0;
    lexer->line = 0;
    lexer->blk = 0;
    lexer->size = 0;
    lexer->id = 0;
    lexer->level = 0;
    return lexer;
}

mLexer_T *_MerLexer_new(void) {
    mLexer_T *lexer = (mLexer_T *)malloc(sizeof(mLexer_T));
    lexer->buf = NULL;
    lexer->inp = NULL;
    lexer->scr = NULL;
    lexer->buf_size = 0;
    lexer->iden = NULL;
    lexer->cstart = '\0';
    lexer->cend = '\0';
    lexer->str = NULL;
    lexer->com = NULL;
    lexer->sytx = NULL;
    lexer->cur = '\0';
    lexer->ncur = '\0';
    lexer->col = 0;
    lexer->row = 0;
    lexer->line = 0;
    lexer->blk = 0;
    lexer->size = 0;
    lexer->id = 0;
    lexer->level = 0;
    return lexer;
}

mLexer_T *_MerLexer_get_next_char(mLexer_T *lexer) {
    if (lexer->id >= lexer->buf_size) {
        lexer->cur = '\0';
        return lexer;
    }
    lexer->cur = lexer->buf[lexer->id++];
    if (lexer->cur == '\n') {
        lexer->row++;
        lexer->col = 0;
    } else {
        lexer->col++;
    }
    return lexer;
}

mLexer_T *_MerLexer_peek_char(mLexer_T *lexer) {
    if (lexer->id >= lexer->buf_size) {
        lexer->cur = '\0';
        return lexer;
    }
    lexer->ncur = lexer->buf[lexer->id];
    return lexer;
}


mToken_T *_MerLexer_get_cur_tok(mLexer_T *lexer) {
    for (;;) {
        lexer->cur = lexer->buf[lexer->id];
        char c = lexer->cur;
        
        if (is_potential_identifier_char(c)) {
            return _MerLexer_tokenize_syntax(lexer);
        }
        if (c == '"') {
            return _MerLexer_tokenize_string(lexer);
        }

        if (c == '!' && isalpha(lexer->buf[lexer->id + 1])) {
            return _MerLexer_tokenize_function_call(lexer);
        }

        if (is_digit(c)) {
            return _MerLexer_tokenize_number(lexer);
        }
        if (is_keywords(c)) {
            return _MerLexer_tokenize_keyword(lexer);
        }

        if (c == '\0') {
            break;
        }
    }
    return _MerInit_token(EOF_T, NULL_T, 0.0, (const char*)"", (const char*)"\n", (const char*)"");
}


mToken_T *_MerLexer_get_next_tok(mLexer_T *lexer)
{
    for (;;) {
        _MerLexer_skip_whitespace(lexer);
        _MerLexer_skip_comment(lexer);
        
        char c = _MerLexer_get_next_char(lexer)->cur;

        if (is_potential_identifier_char(c)) {
            return _MerLexer_tokenize_syntax(lexer);
        }

        if (c == '!' && isalpha(lexer->buf[lexer->id + 1])) {
            return _MerLexer_tokenize_function_call(lexer);
        }

        if (c == '"') {
            return _MerLexer_tokenize_string(lexer);
        }

        if (is_digit(c)) {
            return _MerLexer_tokenize_number(lexer);
        }

        if (is_keywords(c)) {
            return _MerLexer_tokenize_keyword(lexer);
        }

        if (c == '(') {
            return _MerInit_token(LEFT_PAREN, NULL_T, 0.0, "(", ")", ")");
        } 
        
        if (c == ')') {
            return _MerInit_token(RIGHT_PAREN, NULL_T, 0.0, ")", ")", ")");
        }

        if (c == '\0') {
            break;
        }
    }
    
    return _MerInit_token(EOF_T, NULL_T, 0.0, (const char*)"", (const char*)"\n", (const char*)"");
}

mToken_T *_MerLexer_tokenize_function_call(mLexer_T *lexer) {
    lexer->cur = lexer->buf[lexer->id++];
    string func_name = "";
    while (isalpha(lexer->cur)) {
        func_name += lexer->cur;
        LEX_PRE_ADVANCE(lexer);
    }

    LEX_DECR(lexer);
    const char* func_name_c = strdup(func_name.c_str());
    return _MerInit_token(FUNCTION_CALL, "AUTO_T", 0.0, func_name_c, func_name_c, func_name_c);
}

mToken_T *_MerLexer_tokenize_number(mLexer_T *lexer) {
    string num = "";
    int dot_count = 0;
    num += lexer->cur;
    while (is_potential_literal_char(lexer->cur)) {
        if (lexer->cur == '.') {
            dot_count++;
            if (dot_count > 1) {
                break;
            }
        }
        LEX_PRE_ADVANCE(lexer);
        
        if (is_potential_literal_char(lexer->cur)) {
            num += lexer->cur;
        } else {
            break;
        }
    }   

    LEX_DECR(lexer);
    float num_value = atof(num.c_str());
    return _MerInit_token(FLOAT_, FLOAT_T, num_value, NULL, NULL, NULL);
}

mToken_T *_MerLexer_tokenize_syntax(mLexer_T *lexer) {
    string keyword = "";
    
    LEX_DECR_ADVANCE(lexer);
    while (is_potential_identifier_char(lexer->cur)) {
        if (IS_SPACE(lexer)) {
            break;
        }

        if (is_potential_identifier_char(lexer->cur)) {
            keyword += lexer->cur;
        } else {
            mer_run_time_error(to_string(lexer->line), "Syntax error: invalid syntax: " + to_string(lexer->id) + " Char starter: " + lexer->buf[lexer->id], lexer->inp, "main.mer");
        }
        LEX_ADVANCE(lexer);
    }

    const char* key = strdup(keyword.c_str());
    if (is_identifier(key)) {
        return _MerInit_token(GET_SYNTAX(key), NULL_T, 0.0, key, key, key);
    } else {
        return _MerInit_token(VARIABLE, NULL_T, 0.0, key, key, key);
    }
}

mToken_T *_MerLexer_tokenize_keyword(mLexer_T *lexer) {
    string keyword = "";
    char c = lexer->cur;
    if (is_keywords(c)) {
        keyword += c;
        char c2 = LEX_STAY(lexer);
        if (is_keywords(c2)) {
            keyword += c2;
            const char* temp = strdup(keyword.c_str());
            LEX_INCR(lexer);
            return _MerInit_token(GET_2_CHAR(c, c2), NULL_T, 0.0, temp, temp, temp);
        }
    }

    const char* temp = strdup(keyword.c_str());
    return _MerInit_token(GET_1_CHAR(c), NULL_T, 0.0, temp, temp, temp);
}


mToken_T *_MerLexer_tokenize_string(mLexer_T *lexer) {
    string str;
    LEX_PRE_ADVANCE(lexer);
    while (lexer->cur != '"') {
        str += lexer->cur;
        LEX_ADVANCE(lexer);
        if (lexer->cur == '\n') {
            LEX_NEWLINE(lexer);
        }
    }

    const char* str_c = strdup(str.c_str());
    return _MerInit_token(STRING, STRING_T, 0.0, str_c, str_c, str_c);
}

void _MerLexer_jump_to(mLexer_T *lexer, int n) {
    while (lexer->id < n) {
        LEX_ADVANCE(lexer);
        if (lexer->cur == '\n') {
            LEX_NEWLINE(lexer);
        }
    }

    lexer->cur = lexer->buf[lexer->id];
}

void _MerLexer_skip_whitespace(mLexer_T *lexer) {
    lexer->cur = lexer->buf[lexer->id];
    while (IS_SPACE(lexer)) {
        LEX_ADVANCE(lexer);
    }
}

void _MerLexer_skip_comment(mLexer_T *lexer) {
    if (lexer->cur == '#') {
        while (IS_SPACE(lexer)) {
            LEX_ADVANCE(lexer);
            if (lexer->id >= lexer->buf_size) {
                LEX_RESET(lexer);
            }
        }
    }
}