..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".
   
.. index::
   pair: keyword; const

Keyword: ``const``
==================

Use :cref:`const` to instruct the compiler to hold something constant.
The ``const`` keyword can modify the behavior of anything, depending on where it is used:

- fundamental types
- structs or classes
- functions and function parameters
- pointers and references 

  - or the values stored in pointers and references

Programs typically use a lot of constants.
Mathematical constants like :math:`\pi`, or :math:`e`, and unit conversions are common.
Obviously, it would be bad if a program changed the value of :math:`\pi` in the middle
of its execution.
As programmers, we can make a promise to never change those variables that should
not change.
But the language allows a way to enforce the idea.

A ``const`` is a named constant.
It can't be assigned a new value after initialization.
For example:

.. code-block:: cpp

   const double pi = 3.14159265359;

   double area = pi * r * r;           // OK to read pi like any other variable

   pi = 3;                             // this is a compile error

.. index::
   pair: parameter passing; const reference

Returning to our by_reference function from the previous section,
we have seen that pass by reference makes passing data to functions cheap:

.. code-block:: cpp

   void by_reference (int& x) {
     std::cout << "in by_ref the address of x is   " << &x << '\n';
     x = -1;
   }

But one of the side-effects of making passing cheap, 
is that now the called function might change the value provided.
As programmers, we could promise to not change values in functions that shouldn't,
but generally, we don't like promises.
Programmers prefer contracts.
Fortunately, ``const`` allows us to define just such a contract in the declaration:

.. code-block:: cpp

   void by_reference (const int& x) {
     std::cout << "in by_ref the address of x is   " << &x << '\n';
     x = -1;  // this is now a compile error
   }

This is called **passing by constant reference**, or "const ref", for short.
Passing by const ref allows us to enforce our intentions.
If a variable is declared as ``const``, it is a compile error to change it.
Any callers can use this function and rest assured that their data cannot change.
The more time you spend programming, 
the more you will appreciate how powerful that guarantee is.

C99 added the ``const`` keyword, so now it's in both languages,
but you don't see it nearly as often in C.
Many programmers use ``#define`` instead.

.. index:: const vs define

Prefer ``const`` to ``#define`` 
-------------------------------

We also prefer :cref:`inline specifier` and :cref:`enum declaration` over 
:cref:`define`.

There are good reasons to avoid ``#define`` where alternatives exist.

``#define`` is parsed by the *preprocessor*, not the compiler.
This mean that effectively, all ``#define`` directives are literally strings.
Fundamentally they are no different from any other pre-processor directive (``#include``, ``#ifdef``, etc.),
except that people commonly use ``#define`` as a placeholder for a numeric :term:`type`,
or a function.

For example:

.. code-block:: cpp

   #define ASPECT_RATIO 1.653

is an old fashioned way to define a constant, but you'll likely see it 'in the wild'.
The pre-processor literally copies the value '1.653' every place in the source code
it encounters the string 'ASPECT_RATIO'.
Then the program is compiled.


Prefer this instead:

.. code-block:: cpp

   const double ASPECT_RATIO = 1.653;

This version preserves the name 'ASPECT_RATIO' which can simplify debugging.
It is possible to also preserve macro names using
certain debugging compiler switches, such as ``-g3``.

.. index::
   pair: #define; function-like macro
   
Function-like macros using ``#define``
......................................

If you use ``#define`` to create a function-like macro, then unexpected behaviors are possible.
For example, 
a macro to call some function ``f()`` with the larger of either ``a`` or ``b``:

.. code-block:: cpp

    #include <iostream>

    #define CALL_WITH_MAX(a,b) f((a) > (b) ? (a) : (b))

    int f(const int x) {
      return x;
    }

    int main() {
      int a = -5; 
      const int b = 0;

      for (int i = 1; i < 11; ++i) {
        CALL_WITH_MAX(++a, b);                  // call f, but throw away the result
        std::cout << i << ", a: " << a << '\n'; // a is one larger each iteration
      }

      a = -5; 
      for (int i = 1; i < 11; ++i) {
        CALL_WITH_MAX(++a, b+10);
        std::cout << i << ", a: " << a << '\n';
      }
    }

The number of times ``a`` is incremented depends on **how** ``CALL_WITH_MAX`` is called. 
In this case, the value of ``b`` affects whether ``a`` is incremented once or twice.
**Ouch!**

Step through `example 17 <http://pythontutor.com/cpp.html#code=%23include%20%3Ciostream%3E%0A%23define%20CALL_WITH_MAX%28a,b%29%20f%28%28a%29%20%3E%20%28b%29%20%3F%20%28a%29%20%3A%20%28b%29%29%0A%0Aint%20f%28const%20int%20x%29%20%7B%0A%20%20return%20x%3B%0A%7D%0Aint%20main%28%29%20%7B%0A%20%20int%20a%20%3D%20-5%3B%20%0A%20%20const%20int%20b%20%3D%200%3B%0A%0A%20%20for%20%28int%20i%20%3D%201%3B%20i%20%3C%2011%3B%20%2B%2Bi%29%20%7B%0A%20%20%20%20CALL_WITH_MAX%28%2B%2Ba,%20b%29%3B%0A%20%20%20%20std%3A%3Acout%20%3C%3C%20i%20%3C%3C%20%22,%20a%3A%20%22%20%3C%3C%20a%20%3C%3C%20'%5Cn'%3B%0A%20%20%7D%0A%20%20a%20%3D%20-5%3B%20%0A%20%20for%20%28int%20i%20%3D%201%3B%20i%20%3C%2011%3B%20%2B%2Bi%29%20%7B%0A%20%20%20%20CALL_WITH_MAX%28%2B%2Ba,%20b%2B10%29%3B%0A%20%20%20%20std%3A%3Acout%20%3C%3C%20i%20%3C%3C%20%22,%20a%3A%20%22%20%3C%3C%20a%20%3C%3C%20'%5Cn'%3B%0A%20%20%7D%0A%7D&curInstr=63&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D>`_ and see for yourself.

``#define`` may seem like a shortcut.
It's not.

Use it when no better alternative exists.


.. index:: 
   pair: keyword; constexpr

Keyword: ``constexpr``
----------------------

The keyword :cref:`constexpr` was added in C++11.

The fundamental difference between ``const`` and ``constexpr`` is that
``constexpr`` must be able to be determined at compile time.
So while this is OK:

.. code-block:: cpp

   constexpr double pi = 3.14159265359;

   // and so is this
   constexpr double pi = acos(-1);

   // and so is this
   constexpr double area (const double radius) {
      return pi * radius * radius;
   }


This is not OK in C++11:

.. code-block:: cpp

   constexpr double area (const double radius) {
      assert (radius > 0);
      return pi * radius * radius;
   }

Adding a simple assertion causes this function to no longer compile:

.. code-block:: text

   g++ -std=c++11 -Wall -Wextra -pedantic     area.cpp   -o area
   area.cpp: In function ‘constexpr double area(double)’:
   area.cpp:8:1: error: body of constexpr function ‘constexpr double area(double)’ not a return-statement
     }
     ^


On compilers that support C++14, if you compile with ``-std=c++11`` you may see a warning like:

.. code-block:: text

   warning: use of this statement in a constexpr function is a C++14 extension [-Wc++14-extensions]
     assert (radius > 0);


There are some exceptions, but in C++11, 
any function more complex than ``return (some_expression)``
is not able to be evaluated at compile time,
therefore, it won't compile as a ``constexpr`` expression.
You should still use it when you can.

The rules for ``constexpr`` changed in C++14 and more in C++17.
Although not available on the Mesa server, you should still
`read the docs <http://en.cppreference.com/w/cpp/language/constexpr>`_
and be aware of what is and is not a valid constant expression
for whatever environment you are working in.

.. index::
   pair: const; guidelines

Guidelines for now
------------------

- When creating local variables

  - Ask: "Does this variable ever change?"
  - If not, consider ``const`` or ``constexpr`` 

- Recall ``constexpr`` is more restrictive

  - Constant expression is evaluated at *compile time*

- When passing parameters to functions

  - Consider passing by ``const`` reference

    - Applies only to object types

      - Pass fundamental types by ``const`` value if they should not change

    - Avoids making an extra (unneeded) copy
    - Prevents unintended modification

.. admonition:: Try This!

   Given the following:

   .. code-block: cpp

      #include <iostream>
      #include <cmath>
      constexpr double pi = 3.14159265359;

      constexpr double area (const double radius) {
        return pi * radius * radius;
      }

      int main() {
        double r = 2.0;
        std::cout << pi << '\n';
        std::cout << "area: " << area(r) << '\n';
      }

   How many simple changes can you make to the function ``area`` that are valid 
   if the function signature is 
   
   .. code-block:: cpp

      const double area (const double radius)

   but invalid if the function signature is unchanged?
   


-----

.. admonition:: More to Explore

  - From: cppreference.com: 
    `const qualifier <http://en.cppreference.com/w/cpp/language/cv>`_ and 
    `constexpr <http://en.cppreference.com/w/cpp/language/constant_expression>`_
  - `C++ Core Guidelines for constexpr 
    <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Rconst-constexpr>`_
    from GitHub





