..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: templates; concepts

Concepts Overview
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
you can still get the readability improvements from concepts,
just by defining an alias for the type your template expects:

.. code-block:: cpp

   #include <iostream>
   // A 'concept' for a numeric type
   #define Number typename

   // Same template as before
   // 'typename' replaced with 'Number'
   template <Number T, int N> T multiply (T val) {
     return val * N;
   }

We haven't actually made any functional change here.
We have simply made a change that allows our source code to 
indicate our *intent*.

.. index:: requires

Keyword: ``requires``
.....................

A *requires clause* is an additional constraint on template arguments or a function.

-----

.. admonition:: More to Explore

   - `a bit of background for concepts and C++17 <https://isocpp.org/blog/2016/02/a-bit-of-background-for-concepts-and-cpp17-bjarne-stroustrup>`_ Bjarne Stroustrup
   - `Concepts C++ <https://en.wikipedia.org/wiki/Concepts_(C%2B%2B)>_ from Wikipedia
   - `Constraints and concepts <http://en.cppreference.com/w/cpp/concept>`_ from cppreference.com


