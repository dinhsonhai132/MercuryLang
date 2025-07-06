#include "buffer.h"
#include <fstream>
#include <iostream>
#include <filesystem>
using namespace std;

bool MerBuffer_create_folder(const string &folderName)
{
    mkdir(folderName.c_str());
    return true;
}

char *MerBuffer_read_file_source(const string &file_name, string &source)
{
    char *buffer = NULL;
    FILE *f = fopen(file_name.c_str(), "rb");
    if (f == NULL) return NULL;
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

const char *MerBuffer_read_file(const string &file_name)
{
    char *buffer = NULL;
    FILE *f = fopen(file_name.c_str(), "rb");
    if (f == NULL) return NULL;
    fseek(f, 0, SEEK_END);
    size_t length = ftell(f);
    rewind(f);
    buffer = new char[length + 1];
    fread(buffer, 1, length, f);
    buffer[length] = '\0';
    fclose(f);
    return buffer;
}

void MerBuffer_make_and_write_file(const string &filename, const char *content)
{
    ofstream outFile(filename);

    if (!outFile)
    {
        cerr << "Error: Could not create file " << filename << endl;
        return;
    }

    outFile << content << endl;

    outFile.close();
}

void MerBuffer_make_and_write_file_bytecode(const string &filename, const vector<uint8_t> &data)
{
    ofstream file(filename, ios::binary);
    file.write(reinterpret_cast<const char *>(data.data()), data.size());
    file.close();
}

vector<uint8_t> MerBuffer_read_file_bytecode(const string &file_name)
{
    vector<uint8_t> data;
    ifstream file(file_name, ios::binary);
    if (!file)
    {
        cerr << "Error: Could not open file " << file_name << endl;
        return data;
    }
    file.seekg(0, ios::end);
    size_t size = file.tellg();
    file.seekg(0, ios::beg);
    data.resize(size);
    file.read(reinterpret_cast<char *>(data.data()), size);
    file.close();
    return data;
}

vector<string> list_files_in_folder(const string& folder_path) {
    vector<string> file_names;

    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.is_regular_file()) {
            file_names.push_back(entry.path().filename().string());
        }
    }

    return file_names;
}