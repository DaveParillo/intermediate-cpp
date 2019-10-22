..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   single: const class functions

``const`` member functions
==========================
We have :doc:`previously mentioned <../function-intro/constants>` uses for ``const``,
and classes add another situation where the const keyword can be used.

An object can be created with the ``const`` *cv qualifier*, 
just like any other type:

.. code-block:: cpp

   const int x = 3;

   const Fibonacci foo = {5, 8, 13};


When created ``const``, then no changes are allowed to the object.
It is OK to call a *non-modifying member function*.

How does the compiler know that a function is a non-modifying member function?
When the function is declared as ``const``.

Create a const member function by inserting the const keyword after the
parameter list and before the function body:

.. code-block:: cpp

   bool verbose() const {
     return true;
   }

Here ``const`` tells the compiler this function **will not change** the object state.

It is a *promise*.
If a ``const`` function attempts to change **any** class member, 
then a compile error results.

.. note::

   Only class member functions can be marked ``const``.

   Attempting to mark a free function as ``const`` is a compile error.

.. mchoice:: mc-ex-4

   Given the following:
   
   .. code-block:: cpp

      #include <iostream>

      class Foo {
        int value_ = 0;
        public:
          Foo() {}
          void value (const int x) { 
            value_ = x; 
          }
          int value() { 
            return value_;
          }
      };
      int main () {
        const Foo a;
        a.value(13);
        std::cout << a.value() << '\n';
      }

   What is the output? Choose the **one** correct answer.

   - Program prints ``13``

     - It can't print 13 because changing ``value_`` is not allowed.

   - Does not compile

     + Calling a non-const function of an object declared ``const`` is a compile error.

   - Program runs, but does not reach the end of main

     - The program cannot run

   - Program behavior is undefined 

     - The program doesn't get this far. We know exactly what will happen.




-----

.. admonition:: More to Explore

   - From cppreference.com

     - `Const and volatile type qualifiers <https://en.cppreference.com/w/cpp/language/cv>`__.
     - `Const member functions <https://en.cppreference.com/w/cpp/language/member_functions>`__.

