#pragma once

//
// Function to perform simple character rotations through an alphabet.
// 
// Be warned that these functions should NOT be used to encrypt sensitive data!!
// These functions are easily decrypted, even using pencil and paper.
//
// See: https://en.wikipedia.org/wiki/Caesar_cipher
//

#include <string>

// A pointer to the function that will transform a character
using transform = char (*)(const unsigned char c);

// Rotate a character 13 places in the alphabet.
//
// This function assumes a basic 26 letter Latin alphabet
//
// If the character received is not within the range [A-Z, a-z],
// then the character is returned unchanged.
char rot13(const unsigned char c);

// Rotate a character 47 places in the set of printable ASCII characters
//
// If the character received is not a 'printable' character (value < 33),
// then the character is returned unchanged.
char rot47(const unsigned char c);

// Use a 'character handler' (rot13 or rot47) to
// transform a message 1 character at a time.
void render_text(std::string message, transform handler);

