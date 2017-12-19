..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".


The string class
================

In standard C, the only way to work with a batch of characters was by making an array:

.. code-block:: c

   char a[] = {'h', 'e', 'l', 'l', 'o', '\0'};  // the char array must be null terminated
   char b[] = {'h', 'e', 'l', 'l', 'o', 0};     // null == 0
   char* c = "hello";                           // a string is just a special case of a char array

Arrays of ``char`` that are null terminated are commonly called *C-strings*.

C-Strings have an advantage of being extremely lightweight and simple.
Their main disadvantage is that they are too simple for many applications.
Their simplicity makes them a pain to work with,
which is why the Standard Template Library (STL) contains the ``string`` class.

Like a C-string, a std::string is simply a sequence of characters:

.. code-block:: cpp

   #include <string>        // access std::string functions
   
   using std::string;       // just use 'string' for type std::string 

   int main() {
     string greet = "Hello, World!";
     string hello  ("Hello, World!");
     string howdy  {"Hello, World!"};  // C++11 only
     return 0;
   }

Unlike a C-string, a std::string is a full-fledged *object*.
It knows it's own size, and comes with many convenience functions.

.. code-block:: cpp

   #include <string>
   #include <iostream>
   #include <cstdio>

   using std::string;

   int main() {
     string a = "hello";
     a += ", world!";        // joining strings is pretty easy

     // Copying or creating one string from another feels as natural
     // as a fundamental type.
     string b = a;

     if (a == b)             // Same goes for comparisons
     {
       b[0] = 'H';           // and a string feels like an 'array of char' 
       b[7] = 'W';
     }

     std::cout << a << '\n'; // and has stream support
     std::cout << b << '\n';

     return 0;
   }


Using the ``operator[]`` to access select characters in a string is,
like an array,
not range checked.
This means that if you use an index referring to an invalid position,
then your program might have undefined behavior, or fail unexpectedly.
You can use the function ``at()`` anywhere ``operator[]`` is allowed.
The ``at`` function is range checked.
While there is a cost associated with this check, 
if the index provided is out of range, 
then an ``std::out_of_range`` exception is thrown,
which must be caught,
otherwise the program will terminate.

.. code-block:: cpp

   if (a == b)
   {
     b.at(0)  = 'H';   // might be OK
     b.at(-1) = 'W';   // never OK.  throws exception
   }


Remember that a ``std::string`` is **not** a C-String.
Declarations like this are a common source of confusion for new programmers:

.. code-block:: cpp

   auto my_string = "Howdy!";


What type is ``my_string``?

.. reveal:: reveal_my_string

   ``my_string`` is **not** a std::string.

   The default type for characters enclosed in double quotes is ``const char*``.

This is one of those situations where ``auto`` may not be deducing the type
you actually want.
There are several simple ways to to still use auto and get the type
deduced to be a std::string.

In C++14, you can simply append a ``s`` to the end of the string literal.
This identifies the literal as type std::string.

.. code-block:: cpp

   auto my_string = "Howdy!"s;

Alternatively, you can call the string constructor explicitly, which
works for C++ versions older than C++14.

.. code-block:: cpp

   auto my_string = string("Howdy!");

   auto your_str  = string{"Howdy!"};  // C++11 initialization syntax


Getting information out of a string
-----------------------------------

A ``string`` knows its own size and can provide other useful information.

.. code-block:: cpp
   
   #include <cassert>
   #include <string>
   using std::string;
   int main() {
     string my_string = "Hello";

     assert( my_string.size() == 5 );  // .length() is available also
     if (!my_string.empty()) {
       my_string += ", there.";       // my_string == "Hello, there."
     }
     return 0;
   }

And the string class provides many functions dedicated to finding substrings
within a string.

.. code-block:: cpp
   
   #include <iostream>
   #include <string>

   int main() {
     auto us = "team"s;
     std::size_t pos = us.find('i');       // auto pos is less typing
     if(pos == std::string::npos) {        // true
       std::cout << "no 'i' in 'team'\n";
     }
     auto hi = "Hello world"s;
     pos = hi.find("wor");                 // pos == 6
     pos = hi.find('o');                   // pos == 4
     pos = hi.rfind('o');                  // pos == 7
     pos = hi.find_first_of("aeiou");      // pos == 1  (e)
     pos = hi.find_first_not_of("aeiou");  // pos == 0  (H)

     return 0;
   }

The special value ``std::string::npos`` is used both as an end of string indicator
by functions that expect a string and
as an indicator of *not found* by functions that return an index (like find).


Converting a std::string to C-string 
------------------------------------

You cannot use std::string in a function 
that expects ``const char*`` - you must convert it
to a null terminated character array.

.. code-block:: cpp

   auto my_name = "Alice"s;


  printf ("Hello again, %s\n", my_name);       // compile error!

  // the c_str() function converts a string into a c string
  printf ("Hello again, %s\n", my_name.c_str());

Final words
-----------
This was a very brief introduction and barely captures what std::string
is capable of.
Check out the documentation at cppreference.com to get a feel for the functions
and capabilities available.

-----

.. admonition:: More to Explore

   - cppreference.com `std::string <http://en.cppreference.com/w/cpp/string>`_
   - YoLinux `String class tutorial <http://www.yolinux.com/TUTORIALS/LinuxTutorialC++StringClass.html>`_

