#include <iostream>
#include <string>
using namespace std;

void repl() {
    for (;;) {
        string line;
        getline(cin, line);
        if (cin.eof()) {
            break;
        }
        cout << ">> ";
    }
}

