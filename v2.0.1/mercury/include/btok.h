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
