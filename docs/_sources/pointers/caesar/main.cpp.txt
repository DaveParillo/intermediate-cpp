
#include "caesar.h"
#include "help.h"

#include <cstring>    // strcmp
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    // Define a default a 'character handler'
    // the variable 'handler' provides an option to 
    // change the encryption function at runtime
    transform handler = rot13;

    for (int i=1; i < argc; ++i) {
        if (!std::strcmp(argv[i], "-h")) {            // call help and exit
            help(*argv);
        } else if (!std::strcmp(argv[i], "-l")) {     // use rot13 transform
            handler = rot13;
        } else if (!std::strcmp(argv[i], "-f")) {     // use rot47 transform
            handler = rot47;
        } else {
            usage(*argv);
            exit(-1);
        }
    }

    std::string message;
    while (getline(std::cin, message)) {
        render_text(message, handler);
    }
}


