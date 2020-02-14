..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: std::function

The std::function template
==========================
The :utility:`std::function<functional/function>` wrapper provides a standard way to pass around lambda expressions,
function pointers, and function objects.
Introduced in C++11, its facilities are accessed from ``#include <functional>``.
The primary goal of ``std::function`` is clarity:
to simplify and standardize the way function pointers are moved within a program.

Starting with a simple function:

.. code-block:: cpp

   void print_num(int i) {
     std::cout << i << '\n';
   }

Before ``std::function``, we would declare a function pointer like this:

.. code-block:: cpp

   void (*print_func)(int val);

This defines a pointer to a function that returns ``void`` and take one ``int`` parameter.
The syntax is messy:

- The pointer operator requires surrounding parentheses to resolve order of operations problems
- The return type is 'far away' from the parameters
- The syntax is generally inconsistent with modern C++.

Compare the previous declaration with:

.. code-block:: cpp

   std::function<void (int)>  print_func;

This syntax is more consistent with other declarations:

- The variable type is listed first: it's a function pointer
- The function parameters and return type are all together as template parameters
  and the parameters look like a traditional function declaration.
- The name of the variable follows the type

We can store any function-like entity using a consistent syntax:

.. code-block:: cpp

   #include <functional>
   #include <iostream>

   void print_num(int i) {
     std::cout << i << '\n';
   }

   int main() {
     // store a free function
     std::function<void(int)> print_func = print_num;
     print_func(-9);

     // store a lambda
     std::function<void()> print_42 = []() { print_num(42); };
     print_42();

     return 0;
   }



-----

.. admonition:: More to Explore

   - From: cppreference.com: 

     - :utility:`std::function<functional/function>`

