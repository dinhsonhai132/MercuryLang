#ifndef MERCURY_BYTECODE_TOKENIZE_HEADER
#define MERCURY_BYTECODE_TOKENIZE_HEADER

#include <bit>
#include <cstring>
#include <vector>
#include <iomanip>
#include <cstdint>
#include "C:\MercuryLang-main\v2.0.1\mercury\compile.cpp"

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
  vector<uint8_t> bbody;
  vector<BYTECODE_TOKENIZE> cbody;

  vector<uint8_t> buff;
  vector<BYTECODE_TOKENIZE> ctokens;
} ctoken;

ctoken MerByteCodeTokenize_tokenize_code(vector<uint8_t> code);

#endif // MERCURY_BYTECODE_TOKENIZE_HEADER
