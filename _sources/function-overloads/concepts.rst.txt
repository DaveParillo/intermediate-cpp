..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: templates; concepts

Concepts overview
=================

One of the pitfalls when using templates,
especially templates in unfamiliar libraries,
is that C++ templates can be *too generic*.
When you declare a template with either a ``class`` or ``typename``,
literally **any** ``class`` or ``typename`` could be passed in.

What if your template assumes one of the provided types has a
``push_back`` function?
C++ has a mechanism to resolve this ambiguity and enforce
additional requirements on template arguments used as parameters.

- Concepts
- The ``requires`` keyword

Concepts
........

Without resorting to the 
`experimental technical specification <http://en.cppreference.com/w/cpp/language/constraints>`_
you can still get some of the readability improvements from concepts,
just by defining an alias for the type your template expects:

.. code-block:: cpp

   #include <iostream>
   // A 'concept' for a numeric type
   #define NumericType typename

   // Same template as before
   // 'typename' replaced with 'NumericType'
   template <NumericType T, int N> T multiply (T val) {
     return val * N;
   }

We haven't actually made any functional change here.
We have simply made a change that allows our source code to 
indicate our *intent*.

Until the Concepts/Constraints Technical Specification is implemented, 
expressing our intent is about all we can do.

.. code-block:: cpp

   #include <iostream>
   #include <sstream>
   #include <string>

   #define Streamable typename

   namespace mesa {
     // T must overload operator >>
     template <InputIterator T>
       T get(std::string prompt = "Enter a single value: ") {
         while(true) {
           std::cout << prompt;
           std::string line;
           std::getline(std::cin, line);

           // If we can't stream into our type T
           // then the input was not valid for that type.
           std::istringstream buf(line);
           T result;
           if(buf >> result) {
             // check for any extra input and reject input if found
             char junk;
             if(buf >> junk) {
               std::cerr << "Unexpected character.\n";
             } else {
               return result;
             }
           } else {
             std::cerr << "Not a valid input.\n";
           }
         }
       }
   }

   int main() {
     auto a = mesa::get<int>();
     auto b = mesa::get<int>("Enter an integer: ");
     auto c = mesa::get<float>("Enter a float: ");

     std::cout << "Values: " << a << ", "
                             << b << ", "
                             << c << '\n';
     return 0;
   }



.. index:: requires

Keyword: ``requires``
.....................

A *requires clause* is an additional constraint on template arguments or a function.
It is planned for release in C++20.

You will sometimes encounter *named requirements* in C++ code.

The named requirements listed `on this page <https://en.cppreference.com/w/cpp/named_req>`_
are the named requirements used in the normative text of the C++ standard to define the 
expectations of the standard library.

Some of these requirements are being formalized in C++20 using the concepts language feature. 
Until then, the burden is on the programmer to ensure that library templates are 
instantiated with template arguments that satisfy these requirements. 
Failure to do so may result in very complex compiler errors and warnings.

Even though they do not enforce any specific compiler rule or constraint (yet),
they can improve the intent of expected template types.

-----

.. admonition:: More to Explore

   - `a bit of background for concepts and C++17 <https://isocpp.org/blog/2016/02/a-bit-of-background-for-concepts-and-cpp17-bjarne-stroustrup>`_ Bjarne Stroustrup
   - `Concepts C++ <https://en.wikipedia.org/wiki/Concepts_(C%2B%2B)>`_ from Wikipedia
   - From cppreference.com

       - `Constraints and concepts <http://en.cppreference.com/w/cpp/concept>`_ 
       - `Named requirements <https://en.cppreference.com/w/cpp/named_req>`_


