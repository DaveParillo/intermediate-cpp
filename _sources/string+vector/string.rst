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

   #include <string>
   
   using std::string;

   int main() {
     string greet = "Hello, World!";
     string hello  ("Hello, World!");
     string howdy  {"Hello, World!"};  // C++11 only
     return 0;
   }

Unlike a C-string, a std::string is a full-fledged *object*.
It knows it's own size, and comes with many convenience functions.





Subsection
----------

TBD

-----

.. admonition:: More to Explore

   TBD

