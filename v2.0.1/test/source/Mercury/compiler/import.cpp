#include "../include/import.h"

char *MerCompiler_read_source_bytecode_file(char *filename) {
    char *buffer = NULL;
    FILE *f = fopen(filename, "rb");
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