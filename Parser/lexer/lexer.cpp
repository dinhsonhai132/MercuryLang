#include "lexer.h"
using namespace std;

#define D(x) (x) 

mLexer_T *_MerLexer_init(const char *buf)
{
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
    lexer->file = "stdin";
    lexer->cur = '\0';
    lexer->ncur = '\0';
    lexer->col = 0;
    lexer->row = 0;
    lexer->line = 0;
    lexer->blk = 0;
    lexer->size = 0;
    lexer->id = 0;
    lexer->level = 0;
#ifdef DEBUG
    lexer->c_id = 0;
    lexer->c_row = 0;
    lexer->c_line = NULL;
    lexer->c_cur = '\0';
    lexer->c_col = 0;
#endif
    return lexer;
}

mLexer_T *_MerLexer_new(void)
{
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
    lexer->col = 1;
    lexer->row = 1;
    lexer->line = 1;
    lexer->blk = 0;
    lexer->size = 0;
    lexer->id = 0;
    lexer->level = 0;
#ifdef DEBUG
    lexer->c_id = 0;
    lexer->c_row = 0;
    lexer->c_line = NULL;
    lexer->c_cur = '\0';
    lexer->c_col = 0;
#endif
    return lexer;
}

int _MerLexer_free(mLexer_T *lexer)
{
    if (lexer->buf)
        free((char *)lexer->buf);
    if (lexer->inp)
        free((char *)lexer->inp);
    if (lexer->iden)
        free((char *)lexer->iden);
    if (lexer->str)
        free((char *)lexer->str);
    if (lexer->com)
        free((char *)lexer->com);
    if (lexer->sytx)
        free((char *)lexer->sytx);
    free(lexer);
    return 0;
}

mLexer_T *_MerLexer_get_next_char(mLexer_T *lexer)
{
    if (lexer->id >= lexer->buf_size)
    {
        lexer->cur = '\0';
        return lexer;
    }
    lexer->cur = lexer->buf[lexer->id++];
    if (lexer->cur == '\n')
    {
        lexer->row++;
        lexer->col = 0;
    }
    else
    {
        lexer->col++;
    }
    return lexer;
}

mLexer_T *_MerLexer_peek_char_c(mLexer_T *lexer)
{
    if (lexer->id >= lexer->buf_size)
    {
        lexer->cur = '\0';
        return lexer;
    }
    lexer->ncur = lexer->buf[lexer->id];
    return lexer;
}

mToken_T *_MerLexer_get_next_tok(mLexer_T *lexer)
{
    for (;;)
    {
        _MerLexer_skip_whitespace(lexer);
        _MerLexer_skip_comment(lexer);

        char c = _MerLexer_get_next_char(lexer)->cur;

        if (WEIRD_CHAR(c)) {
            MerDebug_print_error(SYNTAX_ERROR, "Invalid character", "stdin", lexer->row + 1);
        }
        
        if (is_potential_identifier_char(c))
        {
            mToken_T *token = _MerLexer_tokenize_syntax(lexer);
            token->index++;
            return token;
        }

        if (c == '!' && isalpha(lexer->buf[lexer->id + 1]))
        {
            mToken_T *token = _MerLexer_tokenize_function_call(lexer);
            token->index++;
            return token;
        }

        if (c == '$' && isalpha(lexer->buf[lexer->id + 1]))
        {
            mToken_T *token = _MerLexer_tokenize_extract(lexer);
            token->index++;
            return token;
        }

        if (c == '"')
        {
            mToken_T *token = _MerLexer_tokenize_string(lexer);
            token->index++;
            return token;
        }

        if (is_digit(c))
        {
            mToken_T *token = _MerLexer_tokenize_number(lexer);
            token->index++;
            return token;
        }

        if (is_keywords(c))
        {
            mToken_T *token = _MerLexer_tokenize_keyword(lexer);
            token->index++;
            return token;
        }

        if (is_keywords(c) && lexer->col == 1)
        {
            MerDebug_print_error(SYNTAX_ERROR, "Invalid character at start", "stdin", lexer->row);
        }

        if (c == '(')
        {
            mToken_T *token = _MerInit_token(LEFT_PAREN, NULL_T, 0.0, "(", "(", "(");
            token->index++;
            return token;
        }

        else if (c == ')')
        {
            mToken_T *token = _MerInit_token(RIGHT_PAREN, NULL_T, 0.0, ")", ")", ")");
            token->index++;
            return token;
        }

        else if (c == '\0')
        {
            break;
        }
    }

    return _MerInit_token(EOF_T, NULL_T, 0.0, (const char *)"", (const char *)"\n", (const char *)"");
}

mToken_T *_MerLexer_look_ahead(mLexer_T *lexer) {
    mLexer_T temp = *lexer;
    return _MerLexer_get_next_tok(&temp);
}

mToken_T *_MerLexer_tokenize_extract(mLexer_T *lexer)
{
    lexer->cur = lexer->buf[lexer->id++];
    string extract_name = "";
    while (is_potential_identifier_char(lexer->cur))
    {
        extract_name += lexer->cur;
        LEX_PRE_ADVANCE(lexer);
    }

    LEX_DECR(lexer);

    const char *extract_name_c = strdup(extract_name.c_str());
    return _MerInit_token(EXTRACT, "AUTO_T", 0.0, extract_name_c, extract_name_c, extract_name_c);
}

mToken_T *_MerLexer_tokenize_function_call(mLexer_T *lexer)
{
    lexer->cur = lexer->buf[lexer->id++];
    string func_name = "";
    while (is_potential_identifier_char(lexer->cur))
    {
        func_name += lexer->cur;
        LEX_PRE_ADVANCE(lexer);
    }

    LEX_DECR(lexer);

    const char *func_name_c = strdup(func_name.c_str());
    return _MerInit_token(FUNCTION_CALL, "AUTO_T", 0.0, func_name_c, func_name_c, func_name_c);
}

mToken_T *_MerLexer_tokenize_number(mLexer_T *lexer)
{
    string num = "";
    int dot_count = 0;
    num += lexer->cur;
    size_t idx = 0;
    while (is_potential_literal_char(lexer->cur))
    {
        
        ++idx;

        if (idx > 4300) {
            MerDebug_print_error(SYSTEM_WARNING, "The number of keyword in number is too large, this can cause a crash", "stdin", lexer->row);
        }

        if (lexer->cur == '.')
        {
            dot_count++;
            if (dot_count > 1)
            {
                break;
            }
        }
        LEX_PRE_ADVANCE(lexer);

        if (is_potential_literal_char(lexer->cur))
        {
            num += lexer->cur;
        }
        else
        {
            break;
        }
    }

    LEX_DECR(lexer);
    float num_value = atof(num.c_str());
    return _MerInit_token(FLOAT_, FLOAT_T, num_value, NULL, NULL, NULL);
}

mToken_T *_MerLexer_tokenize_syntax(mLexer_T *lexer)
{
    string keyword = "";

    LEX_DECR_ADVANCE(lexer);
    while (is_potential_identifier_char(lexer->cur))
    {
        if (IS_SPACE(lexer))
        {
            break;
        }

        if (is_potential_identifier_char(lexer->cur))
        {
            keyword += lexer->cur;
        }
        else
        {
            mer_run_time_error(to_string(lexer->line), "Syntax error: invalid syntax: " + to_string(lexer->id) + " Char starter: " + lexer->buf[lexer->id], lexer->inp, "main.mer");
        }
        LEX_ADVANCE(lexer);
    }

    const char *key = strdup(keyword.c_str());
    if (is_identifier(key))
    {
        return _MerInit_token(GET_SYNTAX(key), NULL_T, 0.0, key, key, key);
    }
    else
    {
        return _MerInit_token(VARIABLE, NULL_T, 0.0, key, key, key);
    }
}

mToken_T *_MerLexer_tokenize_keyword(mLexer_T *lexer)
{
    string keyword = "";
    char c = lexer->cur;
    int idx = 0;
    if (is_keywords(c))
    {
        keyword += c;
        ++idx;

        if (idx > 4300) {
            cout << idx << endl;
            MerDebug_print_error(SYSTEM_WARNING, "The number of keyword is too large, this can cause a crash", "stdin", lexer->row);
        }

        char c2 = LEX_STAY(lexer);
        if (is_keywords(c2))
        {
            keyword += c2;
            const char *temp = strdup(keyword.c_str());
            LEX_INCR(lexer);
            return _MerInit_token(GET_2_CHAR(c, c2), NULL_T, 0.0, temp, temp, temp);
        }
    }

    const char *temp = strdup(keyword.c_str());
    return _MerInit_token(GET_1_CHAR(c), NULL_T, 0.0, temp, temp, temp);
}

mToken_T *_MerLexer_tokenize_string(mLexer_T *lexer)
{
    string str;
    lexer->cur = lexer->buf[lexer->id];

    while (lexer->cur != '"') {
        str += lexer->cur;

        LEX_ADVANCE(lexer);
    }

    LEX_ADVANCE(lexer);
    const char *str_c = strdup(str.c_str());
    return _MerInit_token(STRING, STRING_T, 0.0, str_c, str_c, str_c);
}

void _MerLexer_jump_to(mLexer_T *lexer, int n)
{
    while (lexer->id < n)
    {
        LEX_ADVANCE(lexer);
        if (lexer->cur == '\n')
        {
            LEX_NEWLINE(lexer);
        }
    }

    lexer->cur = lexer->buf[lexer->id];
}

void _MerLexer_skip_whitespace(mLexer_T *lexer)
{
    lexer->cur = lexer->buf[lexer->id];
    while (IS_SPACE(lexer) || lexer->cur == ';')
    {
        LEX_ADVANCE(lexer);
    }
}

void _MerLexer_skip_comment(mLexer_T *lexer)
{
    char c = lexer->buf[lexer->id];
    if (c == '#') {
        while (c != '\n')
        {
            LEX_ADVANCE(lexer);
            c = lexer->buf[lexer->id];
        }
    }
}
