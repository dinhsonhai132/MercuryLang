#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define SUCCESS 0;
#define FAILURE 1;

int MerBuffer_read_file(string file_name, string &source);

#endif // BUFFER_H