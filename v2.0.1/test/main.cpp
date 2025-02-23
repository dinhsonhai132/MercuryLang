#include <iostream>
#include <string>
#include "./Shell/shell.cpp"

using namespace std;

void repl() {
    cout << "v2.0.1" << endl;
    for (;;) {
        cout << ">> ";
        string line;
        getline(cin, line);
        if (line == "exit") {
            break;
        } else {
            MercuryLang(line);
        }
    }
}

