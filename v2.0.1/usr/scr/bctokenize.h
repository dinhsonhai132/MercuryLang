#ifndef MERCURY_BYTECODE_TOKENIZE_HEADER
#define MERCURY_BYTECODE_TOKENIZE_HEADER

#include "bccompile.cpp"
#include <bit>
#include <cstring>
#include <iomanip>
using namespace std;

typedef struct BYTECODE_TOKENIZE {
  uint8_t code;
  uint8_t val;
  uint8_t cbyte;
  uint8_t cline;
  uint8_t address;
  float rval;
  size_t sidx;
  int sym_idx;
  size_t ctokens_idx;
  string scode;

  vector<uint8_t> bcode;
  vector<uint8_t> buff;
  vector<BYTECODE_TOKENIZE> ctokens;
} ctoken;

ctoken MerByteCodeTokenize_tokenize_code(vector<uint8_t> code);

#endif // MERCURY_BYTECODE_TOKENIZE_HEADER
