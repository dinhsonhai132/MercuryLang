#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
using namespace std;

void playNote(int frequency, int duration) {
    Beep(frequency, duration);
    this_thread::sleep_for(chrono::milliseconds(duration / 2));
}

void MerSystem_sound(const vector<pair<int, int>>& system_sound) {
    for (const auto& note : system_sound) {
        playNote(note.first, note.second);
    }
}

vector<pair<int, int>> sound(string name) {
    if (name == "1") {
        vector<pair<int, int>> happyBirthday = {
            {264, 500}, {264, 500}, {297, 1000}, {264, 1000}, {352, 1000}, {330, 2000},
            {264, 500}, {264, 500}, {297, 1000}, {264, 1000}, {396, 1000}, {352, 2000},
            {264, 500}, {264, 500}, {528, 1000}, {440, 1000}, {352, 1000}, {330, 1000}, {297, 2000},
            {466, 500}, {466, 500}, {440, 1000}, {352, 1000}, {396, 1000}, {352, 2000}
        };
        return happyBirthday;
    } else if (name == "2") {
        std::vector<std::pair<int, int>> alphabetSong = {
            {440, 300}, 
            {494, 300}, 
            {523, 300}, 
            {587, 300}, 
            {659, 300}, 
            {698, 300}, 
            {784, 300}, 
            {830, 300}, 
            {880, 300}, 
            {932, 300}, 
            {988, 300}, 
            {1047, 300}, 
            {1109, 300}, 
            {1175, 300}, 
            {1245, 300}, 
            {1319, 300}, 
            {1397, 300}, 
            {1480, 300}, 
            {1568, 300}, 
            {1661, 300}, 
            {1760, 300}, 
            {1865, 300}, 
            {1976, 300}, 
            {2093, 300}, 
            {2217, 300}, 
            {2349, 500}  

        };
        return alphabetSong;
    } else if (name == "3") {
        vector<pair<int, int>> twinkleTwinkle = {
            {262, 500}, 
            {262, 500}, 
            {392, 500}, 
            {392, 500}, 
            {440, 500}, 
            {440, 500}, 
            {392, 1000},
            {349, 500}, 
            {349, 500}, 
            {330, 500}, 
            {330, 500}, 
            {294, 500}, 
            {294, 500}, 
            {262, 1000},
            {392, 500}, 
            {392, 500}, 
            {349, 500}, 
            {349, 500}, 
            {330, 500}, 
            {330, 500}, {294, 1000},
            {392, 500}, 
            {392, 500}, {349, 500}, {349, 500}, {330, 500}, 
            {330, 500}, 
            {294, 1000},
            {262, 500}, 
            {262, 500}, 
            {392, 500}, {392, 500}, {440, 500}, {440, 500}, {392, 1000},
            {349, 500}, 
            {349, 500}, 
            {330, 500}, 
            {330, 500}, {294, 500}, {294, 500}, {262, 1000}
        };
        return twinkleTwinkle;
    } else if (name == "4") {
        vector<pair<int, int>> maryHadALittleLamb = {
            {330, 500}, {294, 500}, {262, 500}, {294, 500}, {330, 500}, {330, 500}, {330, 1000},
            {294, 500}, {294, 500}, {294, 1000}, {330, 500}, {392, 500}, {392, 1000},
            {330, 500}, {294, 500}, {262, 500}, {294, 500}, {330, 500}, {330, 500}, {330, 500}, {330, 500},
            {294, 500}, {294, 500}, {330, 500}, {294, 500}, {262, 1000}
        };
        return maryHadALittleLamb;
    } else if (name == "5") {
        vector<pair<int, int>> oldMacDonald = {
            {294, 500}, {294, 500}, {294, 500}, {392, 500}, {392, 500}, {440, 500}, {440, 500}, {392, 1000},
            {349, 500}, {349, 500}, {330, 500}, {330, 500}, {294, 1000},
            {392, 500}, {392, 500}, {349, 500}, {349, 500}, {330, 500}, {330, 500}, {294, 1000},
            {294, 500}, {294, 500}, {294, 500}, {392, 500}, {392, 500}, {440, 500}, {440, 500}, {392, 1000},
            {349, 500}, {349, 500}, {330, 500}, {330, 500}, {294, 1000}
        };
        return oldMacDonald;
    }
    return vector<pair<int, int>>();
}

int main() {
    for (;;) {
        string name;
        cout << "Enter sound id: ";
        getline(cin, name);

        vector<pair<int, int>> system_sound = sound(name);
        MerSystem_sound(system_sound);
    }
    return 0;
}
