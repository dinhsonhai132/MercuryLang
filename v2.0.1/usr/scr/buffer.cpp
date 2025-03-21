#include "buffer.h"
#include <fstream>
#include <iostream>
#include <filesystem>
using namespace std;

bool MerBuffer_create_folder(const std::string& folderName) {
    mkdir(folderName.c_str());
    return true;
}
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
}

void MerBuffer_bytecode(const std::string& filename, const std::vector<uint8_t>& data) {
    std::ofstream file(filename, std::ios::binary);
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
    file.close();
}
