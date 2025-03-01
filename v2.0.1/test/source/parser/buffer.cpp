#include "buffer.h"

char *MerBuffer_read_file_source(string file_name, string &source) {
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

char *MerBuffer_read_file(string file_name) {
    string source;
    return MerBuffer_read_file_source(file_name, source);
}

void MerBuffer_free(char *buffer) {
    if (buffer == NULL) { cerr << FAILURE; return; };
    delete[] buffer;
    cerr << SUCCESS;
}