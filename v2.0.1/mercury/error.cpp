#ifndef MERCURY_ERROR_H
#define MERCURY_ERROR_H

#include <string>
#include <iostream>
using namespace std;

void mer_run_time_error(string line, string error, string messages, string file) {
    cout << file << ":" << line << ": " << error << endl;
    cout << line << " |" << "\t" << messages << endl;
    cout << string(line.length(), ' ') << " |" << endl;
    while (1);
}

#ifndef TEST_DEBUG
void break_point();
#endif

#endif