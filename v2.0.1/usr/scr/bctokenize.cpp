#include "bctokenize.h"

using namespace std;

ctoken MerByteCodeTokenize_make_new_token(void) {
  ctoken token = ctoken();
  token.cline = 0x0000;
  token.cbyte = 0x0000;
  token.address = 0x0000;
  token.code = 0x00;
  token.val = 0x00;
  token.rval = 0;
  token.scode = "";
  token.sidx = 0;
  token.ctokens_idx = 0;
  token.buff[0] = 0x00;
  token.bcode[0] = 0x00;
  return token;
}

ctoken MerByteCodeTokenize_tokenize_program(vector<uint8_t> code) {
  ctoken token = MerByteCodeTokenize_make_new_token();
  return MerByteCodeTokenize_tokenize_statement(code, token);
}

ctoken MerByteCodeTokenize_tokenize_statement(vector<uint8_t> code, ctoken tokens) {
  size_t global_idx = 0;
  while (global_idx < code.size()) {
    uint8_t cbyte = code[global_idx];
    if (cbyte == PUSH_FLOAT) {
      tokens.code = cbyte;
      tokens.scode = "PUSH_FLOAT";
      tokens.cbyte += 0x0002;
      tokens.ctokens_idx += 0x0001;
    
      float rval;
      ++global_idx;
      if (global_idx + 4 < code.size()) {
        uint32_t int_repr;
        memcpy(&int_repr, &code[global_idx], sizeof(uint32_t));
        global_idx += 4;

        float rval;
        memcpy(&rval, &int_repr, sizeof(float));
        tokens.rval = rval;
      }

      tokens.ctokens.push_back(tokens);
    } else if (cbyte == BINARY_ADD || cbyte == BINARY_SUB || cbyte == BINARY_DIV || cbyte == BINARY_MUL) {
      switch (cbyte) {
        case BINARY_ADD: tokens.scode = "BINARY_ADD"; break;
        case BINARY_MUL: tokens.scode = "BINARY_MUL"; break;
        case BINARY_DIV: tokens.scode = "BINARY_DIV"; break;
        case BINARY_SUB: tokens.scode = "BINARY_SUB"; break;
      }

      tokens.cbyte += 0x0001;
      tokens.cline += 0x0001;
      tokens.code = cbyte;
      tokens.ctokens_idx += 0x0001;
      tokens.ctokens.push_back(tokens);
    }

    ++global_idx;
  }
}