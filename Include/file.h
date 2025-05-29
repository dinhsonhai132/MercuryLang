#ifndef MERCURY_FILE_HEADER_FILE
#define MERCURY_FILE_HEADER_FILE

struct FILE {
    char *buffer;
    int size;
    int offset;
    int pos;
};

typedef struct FILE ZIO;

#endif // MERCURY_FILE_HEADER_FILE