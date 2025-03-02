#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <vector>
using namespace std;
#define SUCCESS 0;
#define FAILURE 1;

char* MerBuffer_read_file_source(string file_name, string &source);
char* MerBuffer_read_file(string file_name);
void MerBuffer_free(char *buffer);

#endif // BUFFER_H