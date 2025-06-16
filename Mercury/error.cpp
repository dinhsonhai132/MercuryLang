#include "../include/error.h"

void mer_run_time_error(string line, string error, string messages, string file)
{
    cout << file << ":" << line << ": " << error << endl;
    cout << line << " |" << "\t" << messages << endl;
    cout << string(line.length(), ' ') << " |" << endl;
    while (1);
}

void mer_error(string type, string msg)
{
    cout << type << ": " << msg << endl;
    while (1);
}

void break_point()
{
    while (1);
}