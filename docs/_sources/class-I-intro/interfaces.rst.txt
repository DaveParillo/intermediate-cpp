..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   single: interfaces and implementation

Interfaces and implementation
=============================
A class defines a :term:`type`.
When you design a type, some parts are hidden (private),
while others are visible (public).
The public parts of your type represent an *interface*.
The interface to your class determine how other functions
will interact with it.

Consider a simple ``date`` class.
This class does not allow direct access to y, m, and d.
These class members can only be set using the 3 arg constructor provided
and can only be retrieved using the functions provided.

.. code-block:: cpp

   class date {
     int y, m, d;

     public:
       date ()
         : y{1776}, m{7}, d{4}
       { }
       // Declare other constructors & functions
       date (int y, int m, int d);
       std::tuple<int,int,int> as_tuple ();
       int year ();
       int month ();
       int day ();
   };

Public member functions define the class interface.
Everything hidden are implementation details.
No one needs to know (or care) how things are actually implemented.

Keeping interface specifications separate from the implementation
is considered a best practice:

- As programs grow large, 
  the time it takes to compile grows proportionally.
  On large projects, this can be a serious impact on your productivity.
  It's even the `source of jokes <https://xkcd.com/303/>`__.
- It makes your code easier to maintain.
  You don't have to find *where* in a large file your code is
  when you can find the named file instead.

Declare interfaces in your header files (*date.h*):

.. code-block:: cpp

   #pragma once

   #include <tuple>

   class date {
       int y {1776};
       int m {7};
       int d {4};
     public:
       date () = default;
       date (int y, int m, int d);
       std::tuple<int,int,int> as_tuple ();
       int year ();
       int month ();
       int day ();
   };

Implement interfaces in your cpp files (*date.cpp*):

.. code-block:: cpp

   #include "date.h"
   #include <tuple>
      
   date::date (int year, int mon, int day)
     : y{year}, m{mon}, d{day}
   { }

   std::tuple<int,int,int> date::as_tuple () {
     return std::make_tuple(y, m,d);
   }

   int date::year ()  { return y; }
   int date::month () { return m; }
   int date::day ()   { return d; }

.. index:: 
   pair: file extensions; header
   pair: file extensions; compiler

File extensions
---------------
All source files are simply text files, 
however, by convention, different kinds of files have different extensions:

- Header files should end in ``.h``, ``.hpp``, or  ``.hxx``.
  
  The extension you use is mostly a matter of preference, but some
  organizations define explicit guidelines.

  Some code editors may assume ``.h`` headers are for C code and that ``.hpp``
  headers are C++ code and may apply different syntax highlighting rules.

  It won't matter to your compiler.

- C++ Source files should end in ``.cpp`` and 
- C Source files should end with ``.c``.

C and C++ source files *are* handled differently by your compiler.
That is when you compile your code, you need to compile the C files differently from the C++ files.
Having a simple convention to distinguish them is important.

-----

.. admonition:: More to Explore

   - `Include guards <https://en.wikipedia.org/wiki/Include_guard>`__ from wikipedia.
   - From cppreference.com

     - `Source file inclusion <https://en.cppreference.com/w/cpp/preprocessor/include>`__.
     - `#pragma directives <https://en.cppreference.com/w/cpp/preprocessor/impl>`__.

   - From C++ Core Guidelines

     - `Interfaces <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-interfaces>`__

