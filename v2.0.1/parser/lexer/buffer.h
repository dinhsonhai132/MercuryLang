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