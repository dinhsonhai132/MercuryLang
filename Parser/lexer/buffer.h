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

#ifndef MERCURY_BUFFER_HEADER_FILE
#define MERCURY_BUFFER_HEADER_FILE
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cstdint>
using namespace std;

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h> 
#define mkdir _mkdir
#else
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

bool MerBuffer_create_folder(const string& folderName);
char* MerBuffer_read_file_source(const string& file_name, string &source);
const char* MerBuffer_read_file(const string& file_name);
void MerBuffer_make_and_write_file(const string& filename, const char* content);
void MerBuffer_make_and_write_file_bytecode(const string& filename, const vector<uint8_t>& data);

#endif // MERCURY_BUFFER_HEADER_FILE