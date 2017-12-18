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




Converting a std::string to C-string 
------------------------------------

You cannot use std::string in a function 
that expects const char* - you must convert it
to a null terminated character array.

.. code-block:: cpp

   auto my_name = "Alice"s;


  printf ("Hello again, %s\n", my_name);       // compile error!

  // the c_str() function converts a string into a c string
  printf ("Hello again, %s\n", my_name.c_str());


-----

.. admonition:: More to Explore

   - YoLinux `String class tutorial <http://www.yolinux.com/TUTORIALS/LinuxTutorialC++StringClass.html>`_
   - http://www.c-jump.com/CIS62/L07slides/lecture.html
   - http://www.c-jump.com/bcc/c255c/c255syllabus.htm

