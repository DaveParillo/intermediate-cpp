..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: pointers; class members

Pointers to classes
===================

When we create a pointer to a class,
member access changes.
Given a simple :term:`POD`:

.. code-block:: cpp

  struct Fibonacci {
    short f5; short f6; short f7;
  };

Access to members of any objects created uses the *member access operator*
``operator .``:

.. code-block:: cpp

   // create foo with initial values
   Fibonacci foo = {5, 8, 13};

   // use member access operator to get values
   std::cout << "The fifth, sixth and seventh Fibonacci numbers are: " 
     << foo.f5 << ", "
     << foo.f6 << ", and "
     << foo.f7 << ".\n";

When you need to access members through a pointer,
the operator precedence rules for pointer dereference
and member access are a common source of error.
Let's add a pointer to ``foo``:

.. code-block:: cpp

   // create foo with initial values
   Fibonacci foo = {5, 8, 13};
   Fibonacci* bar = &foo;

It seems that if ``foo.f5`` works, then
given a pointer to a ``foo``, that ``*bar.f5``
should work, but it does not.
The member access operator has higher precedence than
the dereference operator.
The code ``*bar.f5`` is equivalent to ``*(bar.f5)``.
This is almost always a bug.
In this case, ``f5`` is not a pointer type and cannot be dereferenced.

Explicit use of parentheses is one way to fix this problem:

.. code-block:: cpp

   (*bar).f5

This works, but the syntax is ugly.
For this reason, the ``operator ->`` is used to 
access members of a pointer to an object.
The code ``bar->f5`` is easier to read than ``(*bar).f5``.

Putting it all together:

.. code-block:: cpp

   // create foo with initial values
   Fibonacci foo = {5, 8, 13};
   Fibonacci* bar = &foo;

   // This does not compile!
   // member access operator has higher precedence than
   // dereference operator
   std::cout << "F5: " << *bar.f5;   // can't dereference f5

   // Use this:
   std::cout << "F6: " << (*bar).f6;

   // or even better, this:
   std::cout << "F7: " << bar->f7;



-----

.. admonition:: More to Explore

   - From cppreference.com

     - `C++ Operator precedence <https://en.cppreference.com/w/cpp/language/operator_precedence>`__ and
       `member access operators <https://en.cppreference.com/w/cpp/language/operator_member_access#Built-in_member_access_operators>`__.


