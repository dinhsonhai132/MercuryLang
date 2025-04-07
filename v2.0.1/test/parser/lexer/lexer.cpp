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

mToken_T *_MerLexer_get_next_tok(mLexer_T *lexer) {
    for (;;) {
        char c = _MerLexer_get_next_char(lexer)->cur;

        _MerLexer_skip_comment(lexer);
        _MerLexer_skip_whitespace(lexer);

        if (is_potential_identifier_char(c)) {
            return _MerLexer_tokenize_syntax(lexer);
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

        if (c == '\0') {
            break;
        }
    }
    
    return _MerInit_token(EOF_T, NULL_T, 0.0, (const char*)"", (const char*)"\n", (const char*)"");
}

mToken_T *_MerLexer_tokenize_number(mLexer_T *lexer) {
    string num = "";
    int dot_count = 0;
    while (is_potential_literal_char(lexer->cur)) {
        if (lexer->cur == '.') {
            dot_count++;
            if (dot_count > 1) {
                break;
            }
        }
        num += lexer->cur;
        lexer->cur = lexer->buf[lexer->id++];
    }

    
    float num_value = atof(num.c_str());
    return _MerInit_token(FLOAT_, FLOAT_T, num_value, NULL, NULL, NULL);
}

mToken_T *_MerLexer_tokenize_syntax(mLexer_T *lexer) {
    string keyword = "";
    keyword += lexer->cur;
    
    while (is_potential_identifier_char(lexer->cur)) {
        lexer->cur = lexer->buf[lexer->id++];
        keyword += lexer->cur;
    }

    const char* key = strdup(keyword.c_str());
    if (is_identifier(key)) {
        return _MerInit_token(GET_SYNTAX(key), NULL_T, 0.0, key, key, key);
    } else {
        return _MerInit_token(VARIABLE, NULL_T, 0.0, key, key, key);
    }
}

mToken_T *_MerLexer_tokenize_keyword(mLexer_T *lexer) {
    char* keyword = NULL;
    char c = lexer->cur;
    if (is_keywords(c)) {
        char c2 = lexer->buf[lexer->id + 1];
        if (is_keywords(c2) && c2 != ')') {
            return _MerInit_token(GET_2_CHAR(c, c2), NULL_T, 0.0, keyword, keyword, keyword);
        }
    }

    lexer->cur = lexer->buf[lexer->id++];
    if (lexer->id >= lexer->buf_size) {
        lexer->cur = '\0';
    } else {
        lexer->cur = lexer->buf[lexer->id];
    }
    char temp[2] = {c, '\0'};
    return _MerInit_token(GET_1_CHAR(c), NULL_T, 0.0, temp, temp, temp);
}

mToken_T *_MerLexer_tokenize_string(mLexer_T *lexer) {
    string str;
    lexer->cur = lexer->buf[lexer->id++];
    while (lexer->cur != '"') {
        str += lexer->cur;
        lexer->cur = lexer->buf[lexer->id++];
        if (lexer->cur == '\n') {
            lexer->row++;
            lexer->col = 0;
        } else {
            lexer->col++;
        }
    }

    const char* str_c = strdup(str.c_str());
    return _MerInit_token(STRING, STRING_T, 0.0, str_c, str_c, str_c);
}

void _MerLexer_jump_to(mLexer_T *lexer, int n) {
    while (lexer->id < n) {
        lexer->cur = lexer->buf[lexer->id++];
        if (lexer->cur == '\n') {
            lexer->row++;
            lexer->col = 0;
        } else {
            lexer->col++;
        }
    }

    lexer->cur = lexer->buf[lexer->id];
}

void _MerLexer_skip_whitespace(mLexer_T *lexer) {
    while (lexer->cur == ' ' || lexer->cur == '\t' || lexer->cur == '\r') {
        lexer->cur = lexer->buf[lexer->id++];
        if (lexer->cur == '\n') {
            lexer->row++;
            lexer->col = 0;
        } else {
            lexer->col++;
        }
    

    }
}

void _MerLexer_skip_comment(mLexer_T *lexer) {
    if (lexer->cur == '#') {
        while (lexer->cur != '\n' && lexer->cur != '\0') {
            lexer->cur = lexer->buf[lexer->id++];
            if (lexer->cur == '\n') {
                lexer->row++;
                lexer->col = 0;
            } else {
                lexer->col++;
            }
        
            if (lexer->id >= lexer->buf_size) {
                lexer->cur = '\0';
            } else {
                lexer->cur = lexer->buf[lexer->id];
            }
        }
    }
}