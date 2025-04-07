#ifndef LEXER_TOKENIZE_HEADER_FILE
#define LEXER_TOKENIZE_HEADER_FILE

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include "C:\MercuryLang-main\v2.0.1\parser\lexer\tok.cpp"
using namespace std;

struct mLexer_T {
    const char* buf;        // line of buffer for the source code
    const char* inp;        // input buffer for the source code
    char* scr;              // source code this is what compiler need to read
    char* iden;             // identifier buffer for the source code 
    char* str;              // string buffer for the source code
    char* com;              // comment buffer for the source code
    char* sytx;             // syntax buffer for the source code
    char* num ;             // number buffer for the source code
    char* mmode;            // mode like :p, :string, :o
    
    char cstart;            // start of the buffer for the source code
    char cend;              // end of the buffer for the source code
    char cur;               // current character in the buffer
    char ncur;              // next character in the buffer

    int col;                // current column in the buffer
    int row;                // current row in the buffer
    int line;               // current line in the buffer
    int blk;                // check is block 1 is true 0 is false
    int size;               // size of the buffer
    int id;                 // current index in the buffer
    int level;              // level of parent () [] {} in the buffer
    int end;                // is end of the buffer 1 is true 0 is false
    int start;              // is start of the buffer 1 is true 0 is false

    size_t buf_size;        // size of the buffer
};

#define GET_NEXT_TOK(lexer) (lexer->cur = lexer->buf[lexer->id++])
#define PEEK(lexer) (lexer->buf[lexer->id])
#define LOOK_AHEAD(lexer, n) (lexer->buf[lexer->id + n])
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define IS_EOF(lexer) (lexer->buf[lexer->id] == '\0')
#define IS_EOL(lexer) (lexer->buf[lexer->id] == '\n')

mLexer_T *_MerLexer_init(char *buf);
mLexer_T *_MerLexer_get_next_char(mLexer_T *lexer);
mLexer_T *_MerLexer_peek_char(mLexer_T *lexer);
mLexer_T *_MerLexer_new(void);

mToken_T *_MerLexer_get_cur_tok(mLexer_T *lexer);
mToken_T *_MerLexer_get_next_tok(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_number(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_keyword(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_string(mLexer_T *lexer);
mToken_T *_MerLexer_tokenize_syntax(mLexer_T *lexer);

void _MerLexer_jump_to(mLexer_T *lexer, int n);
void _MerLexer_skip_whitespace(mLexer_T *lexer);
void _MerLexer_skip_comment(mLexer_T *lexer);

#endif // LEXER_TOKENIZE_HEADER_FILE