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

#ifndef LEXER_TOKENIZE_HEADER_FILE
#define LEXER_TOKENIZE_HEADER_FILE

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include "C:\MercuryLang\Parser\lexer\tok.cpp"

using namespace std;

struct mLexer_T
{
    const char *buf;  // line of buffer for the source code
    const char *inp;  // input buffer for the source code
    const char *file; // file name
    char *scr;        // source code this is what compiler need to read
    char *iden;       // identifier buffer for the source code
    char *str;        // string buffer for the source code
    char *com;        // comment buffer for the source code
    char *sytx;       // syntax buffer for the source code
    char *num;        // number buffer for the source code
    char *mmode;      // mode like :p, :string, :o

    char cstart; // start of the buffer for the source code
    char cend;   // end of the buffer for the source code
    char cur;    // current character in the buffer
    char ncur;   // next character in the buffer

    int col;   // current column in the buffer
    int row;   // current row in the buffer
    int line;  // current line in the buffer
#ifdef DEBUG
    char c_cur;  // current character in the buffer (for debug)
    char *c_line;// current line in the buffer (for debug)
    int c_col;   // current line in the buffer (for debug)
    int c_row;   // current row in the buffer (for debug)
    int c_id;    // current index in the buffer (for debug)
    int c_start; // start of the buffer in the buffer (for debug)
    int c_end;   // end of the buffer in the buffer (for debug)
#endif
    int blk;   // check is block 1 is true 0 is false
    int size;  // size of the buffer
    int id;    // current index in the buffer
    int level; // level of parent () [] {} in the buffer
    int end;   // is end of the buffer 1 is true 0 is false
    int start; // is start of the buffer 1 is true 0 is false

    size_t buf_size; // size of the buffer
};

#define GET_NEXT_TOK(lexer) (lexer->cur = lexer->buf[lexer->id++])
#define PEEK(lexer) (lexer->buf[lexer->id])
#define LOOK_AHEAD(lexer, n) (lexer->buf[lexer->id + n])
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define IS_EOF(lexer) (lexer->buf[lexer->id] == '\0')
#define IS_EOL(lexer) (lexer->buf[lexer->id] == '\n')
#define IS_SPACE(lexer) (lexer->buf[lexer->id] == ' ' || lexer->buf[lexer->id] == '\t' || lexer->buf[lexer->id] == '\r')
#define LEX_ADVANCE(lexer) (lexer->col++, lexer->cur = lexer->buf[++lexer->id])
#define LEX_PRE_ADVANCE(lexer) (lexer->col++, lexer->cur = lexer->buf[lexer->id++])
#define LEX_DECR_ADVANCE(lexer) (lexer->col++, lexer->cur = lexer->buf[--lexer->id])
#define LEX_DECR_PRE_ADVANCE(lexer) (lexer->col++, lexer->cur = lexer->buf[lexer->id--])
#define LEX_RESET(lexer) (lexer->id = 0, lexer->col = 0)
#define LEX_NEWLINE(lexer) (lexer->col = 0, lexer->row++)
#define LEX_INCR(lexer) (lexer->id++, lexer->col++)
#define LEX_DECR(lexer) (lexer->id--, lexer->col--)
#define LEX_PEEK(lexer) (lexer->buf[lexer->id + 1])
#define LEX_STAY(lexer) (lexer->buf[lexer->id])
#define LEX_CUR(lexer) (lexer->cur);

mLexer_T *_MerLexer_init(char *buf);
mLexer_T *_MerLexer_get_next_char(mLexer_T *lexer);
mLexer_T *_MerLexer_peek_char(mLexer_T *lexer);
mLexer_T *_MerLexer_new(void);
int _MerLexer_free(mLexer_T *lexer);

mToken_T *_MerLexer_get_cur_tok(mLexer_T *lexer);
mToken_T *_MerLexer_get_next_tok(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_number(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_keyword(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_string(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_syntax(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_function_call(mLexer_T *lexer);

void _MerLexer_jump_to(mLexer_T *lexer, int n);
void _MerLexer_skip_whitespace(mLexer_T *lexer);
void _MerLexer_skip_comment(mLexer_T *lexer);

#ifdef DEBUG
#define C_GET_NEXT_TOK(lexer) (lexer->c_cur = lexer->buf[lexer->c_id++])
#define C_PEEK(lexer) (lexer->buf[lexer->c_id])
#define C_LOOK_AHEAD(lexer, n) (lexer->buf[lexer->c_id + n])
#define C_MAX(a, b) ((a) > (b) ? (a) : (b))
#define C_MIN(a, b) ((a) < (b) ? (a) : (b))
#define C_IS_EOF(lexer) (lexer->buf[lexer->c_id] == '\0')
#define C_IS_EOL(lexer) (lexer->buf[lexer->c_id] == '\n')
#define C_IS_SPACE(lexer) (lexer->buf[lexer->c_id] == ' ' || lexer->buf[lexer->c_id] == '\t' || lexer->buf[lexer->c_id] == '\r')
#define C_LEX_ADVANCE(lexer) (lexer->c_col++, lexer->c_cur = lexer->buf[++lexer->c_id])
#define C_LEX_PRE_ADVANCE(lexer) (lexer->c_col++, lexer->c_cur = lexer->buf[lexer->c_id++])
#define C_LEX_DECR_ADVANCE(lexer) (lexer->c_col++, lexer->c_cur = lexer->buf[--lexer->c_id])
#define C_LEX_DECR_PRE_ADVANCE(lexer) (lexer->c_col++, lexer->c_cur = lexer->buf[lexer->c_id--])
#define C_LEX_RESET(lexer) (lexer->c_id = 0, lexer->c_col = 0)
#define C_LEX_NEWLINE(lexer) (lexer->c_col = 0, lexer->c_row++)
#define C_LEX_INCR(lexer) (lexer->c_id++, lexer->c_col++)
#define C_LEX_DECR(lexer) (lexer->c_id--, lexer->c_col--)
#define C_LEX_PEEK(lexer) (lexer->buf[lexer->c_id + 1])
#define C_LEX_STAY(lexer) (lexer->buf[lexer->c_id])
#define C_LEX_c_cur(lexer) (lexer->c_cur);

mLexer_T *_MerLexer_get_next_char_c(mLexer_T *lexer);
mLexer_T *_MerLexer_peek_char_c(mLexer_T *lexer);

mToken_T *_MerLexer_get_cur_tok_c(mLexer_T *lexer);
mToken_T *_MerLexer_get_next_tok_c(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_number_c(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_keyword_c(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_string_c(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_syntax_c(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_function_call_c(mLexer_T *lexer);

void _MerLexer_jump_to_c(mLexer_T *lexer, int n);
void _MerLexer_skip_whitespace_c(mLexer_T *lexer);
void _MerLexer_skip_comment_c(mLexer_T *lexer);
#endif
#endif // LEXER_TOKENIZE_HEADER_FILE
