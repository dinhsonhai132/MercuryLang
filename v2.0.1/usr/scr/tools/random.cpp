#include <iostream>
#include <random>
#include <string.h>

int random(int a, int b) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(a, b);
    return dist(gen);
}


char random_hex_char() {
    const char hex_chars[] = "0123456789ABCDEF";
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 15);
    return hex_chars[dist(gen)];
}

char* random_address() {
    char *address = new char[11];
    strcpy(address, "0x");
    
    for (int i = 2; i < 10; i++) {
        address[i] = random_hex_char();
    }
    address[10] = '\0'; 
    return address;
}