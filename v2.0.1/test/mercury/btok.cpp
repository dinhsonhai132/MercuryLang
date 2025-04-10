#include "./include/btok.h"

using namespace std;

ctoken MerByteCodeTokenize_tokenize_code(vector<uint8_t> code) {
  ctoken token;
  size_t global_code_idx = 0;

  while (global_code_idx < code.size()) {
    uint8_t c = code[global_code_idx++];
    if (c == CPUSH_FLOAT) {
      token.code = c;
      token.scode = "PUSH_FLOAT";
      token.cbyte += 0x0002;
      token.cline += 0x0001;
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
    } else if (c == CBINARY_ADD || c == CBINARY_SUB || c == CBINARY_DIV || c == CBINARY_MUL) {
      token.code = c;
      switch (c) {
        case CBINARY_ADD: token.scode = "CBINARY_ADD"; break;
        case CBINARY_SUB: token.scode = "CBINARY_SUB"; break;
        case CBINARY_DIV: token.scode = "CBINARY_DIV"; break;
        case CBINARY_MUL: token.scode = "CBINARY_MUL"; break;
      }

      token.cbyte += 0x0001;
      token.cline += 0x0001;
      token.ctokens_idx += 1;
      token.address = 0x0001;
      token.rval = 0.0;
      token.ctokens.push_back(token);
      token.bcode.push_back(c);
    } else if (c == CLOAD_GLOBAL) {
      token.code = c;
      token.scode = "LOAD_GLOBAL";
      token.cbyte += 0x0002;
      token.cline += 0x0001;
      token.ctokens_idx += 1;
      token.rval = 0.0;
      token.bcode.push_back(c);
      token.address = code[global_code_idx];
      token.ctokens.push_back(token);
      ++global_code_idx;
    } else if (c == CSTORE_GLOBAL) {
      token.code = c;
      token.scode = "STORE_GLOBAL";
      token.cbyte += 0x0002;
      token.cline += 0x0001;
      token.sidx += 1;
      token.rval = 0.0;
      token.bcode.push_back(c);
      token.address = code[global_code_idx];
      token.ctokens.push_back(token);
      ++global_code_idx;
    } else if (c == CMAKE_FUNCTION) {
      token.code = c;
      token.scode = "MAKE_FUNCTION";
      token.cbyte += 0x0002;
      token.cline += 0x0001;
      token.rval = 0.0;
      token.address = code[global_code_idx];
      token.bcode.push_back(c);
      vector<uint8_t> bbody;
      while (c != CRETURN) {
        c = code[++global_code_idx];
        bbody.push_back(c);
      }
      token.bbody = bbody;
      token.ctokens.push_back(token);
    } else if (c == CFUNCTION_CALL) {
      token.code = c;
      token.scode = "CALL_FUNCTION";
      token.cbyte += 0x0001;
      token.cline += 0x0001;
      token.rval = 0.0;
      token.bcode.push_back(c);

      c = code[global_code_idx];
      ctoken bodytok;
      bodytok.cline = token.cline;
      bodytok.sidx = token.sidx;
      token.ctokens.push_back(token);
    } else if (c == CRETURN) {
      token.code = c;
      token.scode = "RETURN";
      token.cbyte += 0x0001;
      token.cline += 0x0001;
      token.rval = 0.0;
      token.bcode.push_back(c);
      token.ctokens.push_back(token);
    }
  }

  return token;
}