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
  int global_code_idx = 0;
  bool is_start = false;
  bool is_end = false;
  while (global_code_idx < code.size()) {
    uint8_t c = code[global_code_idx];
    if (c == PUSH_FLOAT && is_start) {
      c = code[++global_code_idx + 1];
      float rval;
      tokens.code = PUSH_FLOAT;
      tokens.val = c;
      memcpy(&rval, &tokens.val, sizeof(float));
      tokens.rval = rval;
      tokens.cline += 0x0001;
      tokens.cbyte += 0x0002;
      tokens.ctokens.push_back(tokens);
    } else if (c == PROGRAM_START || c == PROGRAM_END) {
      is_start = true;
      is_end = true;
      continue;
    } else if (c == BINARY_ADD || c == BINARY_SUB || c == BINARY_DIV || c == BINARY_MUL) {
      tokens.code = c;
      tokens.cline += 0x0001;
      tokens.cbyte += 0x0001;
      tokens.ctokens.push_back(tokens);
    } else if (c == STORE_GLOBAL) {
      c = code[++global_code_idx];
      tokens.code = STORE_GLOBAL;
      tokens.cline += 0x0001;
      tokens.cbyte += 0x0002;
      tokens.address = c;
      tokens.sidx += 1;
      tokens.ctokens.push_back(tokens);
    } else if (c == LOAD_GLOBAL) {
      c = code[++global_code_idx];
      tokens.code = LOAD_GLOBAL;
      tokens.cline += 0x0001;
      tokens.cbyte += 0x0002;
      tokens.address = c;
      tokens.ctokens.push_back(tokens);
    }
    global_code_idx += 1;
  }
  return tokens;
}
