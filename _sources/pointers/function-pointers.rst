..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: function pointers; pointers to functions

Function pointers
=================

In C++ you can point to anything with an address:
- Global variables
- Stack and free store variables
- Functions

Recall that when called, 
an activation record for a function is pushed onto the execution stack
This means every function has an address.

Consider the following code:

.. code-block:: cpp

   #include <iostream>
   int foo() {
     return 5;
   }
   int main() {
     std::cout << foo;
   }


What does this program print?

Hint: It doesn't call the function foo

.. reveal:: reveal-fp1

   It prints the *address* of the function ``foo()``

When a function is called using ``operator()``,
execution jumps to the *address* of the function being called.
We can make use of this to store the address of the function.

To declare a pointer to a function that returns an ``int`` and takes no parameters:

.. code-block:: cpp

   int (*ptr)();

The parentheses around ``(*ptr)`` are required due to operator precedence.

To declare a pointer to a function that returns an ``double`` and takes two parameters:

.. code-block:: cpp

   double (*func)(int x, int y);


Once you have a valid definition, 
you can assign functions to it:

.. code-block:: cpp

   double add     (int x, int y) { return x+y;}
   double multiply(int x, int y) { return x*y;}
   double pi      ()             { return 3.14159265;}

   int main () {
     double (*func)(int x, int y) = add;

     cout << (*func)(2,3); // prints 4

     func = multiply;
     cout << (*func)(2,3); // prints 6

     func = pi;            // error: pointer to function with
                           // wrong number of arguments

     func = add();         // error: can't assign
                           // function return value to function pointer
   }

A downside to traditional function pointer initialization is 
that this doesn't look like the initialization syntax we are used to.
This is a legacy of the C language C++ was originally based on.

The C++11 ``using`` alias allows defining a name that refers to a previously defined type:

.. code-block:: cpp

   double (*func)(int x, int y);          // old syntax

   using func = double(*)(int x, int y);  // new syntax


A simple, but real example.

A simple substitution cipher, called `ROT13 <https://en.wikipedia.org/wiki/ROT13>`_, short for 'rotate 13 places'
can be used to obfuscate text by replacing each letter with the letter 13 letters after it in the alphabet.
It is a spacial case of the `Caesar cipher <https://en.wikipedia.org/wiki/Caesar_cipher>`_, 
developed in ancient Rome.
A related variation called ROT47 extends the idea of ROT13 to include numbers and common symbols.

Suppose we want to create a program that allows users to run either ROT13 or ROT47?
There are many ways to implement such a program.
This example demonstrates using function pointers to dynamically 
control at run time which function is called within a loop.

.. code-block:: cpp

   #include <iostream>
   #include <string>

   // a pointer to the function that will transform a character
   using transform = char (*)(const char c);

   // forward declarations
   static void usage(const char* name);
   static void help (const char* name);

   // rotate a character 13 places in the alphabet
   // This function assumes a basic 26 letter Latin alphabet
   char rot13(const char c) {
     if (!std::isalpha(c)) return c;   // if not a Latin letter, do nothing & return the current char

     // in order to rotate upper or lower case
     // need to know where the alphabet 'starts'
     const char start = std::islower(c) ? 'a' : 'A';
     return (c - start + 13) % 26 + start;
   }

   // rotate a character 47 places in the set of printable ASCII characters
   char rot47(const char c) {
     // first printable character = 33 = '!'
     static constexpr char start = '!';
     if (c < start) return c;
     return (c - start + 47) % 94 + start;
   }

   // Use a 'character handler' (rot13 or rot47) to
   // transform a message 1 character at a time.
   void render_text(std::string message, transform handler) {
     for (const auto& c: message) {  // extract each char from the string
       std::cout << handler(c);      // print transformed character
     }
     std::cout << std::endl;         // print newline and flush stream
   }

   int main(int argc, char** argv) {
     // Define a default a 'character handler'
     // the variable 'handler' provides an option to swap in different encryption function
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
     while (getline(std::cin,message)) {
            render_text(message, handler);
     }
   }

   static void usage(const char* name) {
     std::cerr << "Encrypt or decrypt a single line of text "
               << "read from standard input\n"
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


-----

.. admonition:: More to Explore

   TBD

