#include "buffer.h"
#include <fstream>
#include <iostream>
using namespace std;

char* MerBuffer_read_file_source(string file_name, string &source) {
    char *buffer = NULL;
    FILE *f = fopen(file_name.c_str(), "rb");
    if (f == NULL)
        return NULL;
    fseek(f, 0, SEEK_END);
    size_t length = ftell(f);
    rewind(f);
    buffer = new char[length + 1];
    fread(buffer, 1, length, f);
    buffer[length] = '\0';
    fclose(f);
    source = buffer;
    return buffer;
}

char* MerBuffer_read_file(string file_name) {
    char *buffer = NULL;
    FILE *f = fopen(file_name.c_str(), "rb");
    if (f == NULL)
        return NULL;
    fseek(f, 0, SEEK_END);
    size_t length = ftell(f);
    rewind(f);
    buffer = new char[length + 1];
    fread(buffer, 1, length, f);
    buffer[length] = '\0';
    fclose(f);
    return buffer;
}

void MerBuffer_make_and_write_file(const char* filename, const char* content) {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Error: Could not create file " << filename << endl;
        return;
    }

    outFile << content << endl;

    outFile.close();

    cout << "Content written to " << filename << endl;
}