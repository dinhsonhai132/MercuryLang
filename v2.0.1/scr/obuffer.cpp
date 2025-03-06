#include "obuffer.h"

char *MerObuffer_read_source_bytecode(string file_name) {
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