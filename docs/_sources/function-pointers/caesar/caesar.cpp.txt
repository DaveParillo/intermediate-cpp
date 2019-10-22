#include "caesar.h"

#include <iostream>
#include <cctype>      // isalpha, islower
#include <string>

// TODO: add locale and extend non english alphabets

char rot13(const unsigned char c) {
    if (!std::isalpha(c)) return c;   // if not a Latin letter, 
                                      // then do nothing & return the current char

    // in order to rotate upper or lower case
    // need to know where the alphabet 'starts'
    const char start = std::islower(c) ? 'a' : 'A';
    return (c - start + 13) % 26 + start;
}

char rot47(const unsigned char c) {
    // first printable character = 33 = '!'
    static constexpr char start = '!';
    if (c < start) return c;
    return (c - start + 47) % 94 + start;
}

void render_text(std::string message, transform handler) {
    for (const auto& c: message) {  // extract each char from the string
        std::cout << handler(c);    // print transformed character
    }
    std::cout << std::endl;         // print newline and flush stream
}


