#include "bctokenize.h"

using namespace std;

ctoken MerByteCodeTokenize_tokenize_code(vector<uint8_t> code) {
  ctoken token;
  size_t global_code_idx = 0;

  while (global_code_idx < code.size()) {
    uint8_t c = code[global_code_idx++];
    if (c == PUSH_FLOAT) {
      token.code = c;
      token.scode = "PUSH_FLOAT";
      token.cbyte += 0x0002;
      token.cline += 0x0001;
      token.sidx += 1;
      token.ctokens_idx += 1;
      float rval;
      token.address = 0x0001;
      if (global_code_idx + 4 < code.size()) {
        uint32_t int_repr;
        memcpy(&int_repr, &code[global_code_idx], sizeof(uint32_t));
        global_code_idx += 4;
        
        memcpy(&rval, &int_repr, sizeof(float));
      }

      token.rval = rval;
      token.ctokens.push_back(token);
      token.bcode.push_back(c);
    } else if (c == BINARY_ADD || c == BINARY_SUB || c == BINARY_DIV || c == BINARY_MUL) {
      token.code = c;
      switch (c) {
        case BINARY_ADD: token.scode = "BINARY_ADD"; break;
        case BINARY_SUB: token.scode = "BINARY_SUB"; break;
        case BINARY_DIV: token.scode = "BINARY_DIV"; break;
        case BINARY_MUL: token.scode = "BINARY_MUL"; break;
      }

      token.cbyte += 0x0001;
      token.cline += 0x0001;
      token.sidx += 1;
      token.ctokens_idx += 1;
      token.address = 0x0001;
      token.rval = 0.0;
      token.ctokens.push_back(token);
      token.bcode.push_back(c);
    } else if (c == LOAD_GLOBAL) {
      token.code = c;
      token.scode = "LOAD_GLOBAL";
      token.cbyte += 0x0001;
      token.cline += 0x0001;
      token.sidx += 1;
      token.ctokens_idx += 1;
      token.rval = 0.0;
      token.bcode.push_back(c);
      token.address = code[global_code_idx];
      token.ctokens.push_back(token);
      ++global_code_idx;
    } else if (c == STORE_GLOBAL) {
      token.code = c;
      token.scode = "STORE_GLOBAL";
      token.cbyte += 0x0001;
      token.cline += 0x0001;
      token.rval = 0.0;
      token.bcode.push_back(c);
      token.address = code[global_code_idx];
      token.ctokens.push_back(token);
      ++global_code_idx;
    }
  }

  return token;
}