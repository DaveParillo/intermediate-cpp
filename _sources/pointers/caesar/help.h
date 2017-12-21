#pragma once

#include <iostream>

static void usage(const char* name) {
    std::cerr << "Encrypt or decrypt text read from standard input\n"
        << "Usage: " << name << " [-h|l|f]\n";
}

static void help (const char* name) {
    usage(name);
    std::cerr << "Options:\n"
        << "  -h   Show this text and exit.\n"
        << "  -l   En(de)crypt using the Latin characters ([A-Z,a-z]\n"
        << "         (default)\n"
        << "  -f   En(de)crypt using the Full set of "
        << "printable ASCII characters\n"
        << "\nOnly 1 of any option can be meaningfully specified.\n"
        << "\nThe last of either '-l' or 'f' provided is used.\n"
        << "\nRunning with no input from standard in enters\n"
        << "'interactive mode':\n"
        << " - Text can be entered one message per line.\n"
        << " - The program runs until 'CTRL+C' is entered or "
        << "   EOF is reached.\n\n"
        << "Running on plain text creates cipher text\n"
        << "Running on cipher text creates plain text\n\n";
    exit(0);
}

