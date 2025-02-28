#include "C:\Users\dinhs\Documents\Program Language\Mercury-Langluage-main\Mercury-Langluage-main\v2.0.1\test\Source\Mercury\include\core.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void Shell() {
    cout << "v2.0.1" << endl;
    for (;;) {
        string source;
        cout << ">> ";
        getline(cin, source);
        RunTimeVal result = MerShell_repl(source);
        cout << "{ type: " << result.type << ", value: " << result.value << " }" << endl;
    }
}