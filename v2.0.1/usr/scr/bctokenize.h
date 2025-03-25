#ifndef MERCURY_BYTECODE_TOKENIZE_HEADER
#define MERCURY_BYTECODE_TOKENIZE_HEADER

#include "bccompile.cpp"

typedef struct BYTECODE_TOKENIZE {
  uint8_t code;
  uint8_t val;
  uint8_t cbyte;
  uint8_t cline;
  uint8_t address;
  float rval;
  size_t sidx;
  size_t ctokens_idx;

  vector<uint8_t> bcode;
  vector<uint8_t> buff;
  vector<BYTECODE_TOKENIZE> ctokens;
} ctoken;

ctoken MerByteCodeTokenize_make_new_token(void);
ctoken MerByteCodeTokenize_tokenize_program(vector<uint8_t> code);
ctoken MerByteCodeTokenize_tokenize_statement(vector<uint8_t> code, ctoken tokens);

#endif // MERCURY_BYTECODE_TOKENIZE_HEADER
