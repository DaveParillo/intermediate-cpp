..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".
   
.. index:: auto

Keyword: ``auto``
=================

In C++11, the :cref:`auto specifier` meaning has changed significantly from
it's definition prior to C++11.
Prior to C++11, ``auto`` designated variables assigned to the 
`automatic storage class duration <http://en.cppreference.com/w/c/language/storage_duration>`_.
Every variable is assigned a storage duration which limits its lifetime.
The automatic duration applied to local variables in a block scope.
Because it was the default storage duration for variables in a block,
it was rarely, if ever, used.
It is still the default storage duration for block variables,
but no C++11 keyword is reserved for this behavior.

Since C++11, :cref:`auto specifier` instructs the compiler to automatically deduce the type
of a variable based on the initializer used.

.. code-block:: cpp

   auto new_variable = initial_value;

Since the initializer provides the information used to deduce the :term:`type`,
an initial value is required when using ``auto``:

.. code-block:: cpp

   auto x = 3;   // OK
   auto y;       // Not OK

   auto int z;   // Error in C++11
                 // This is how auto was used prior to C++11

You can use ``auto`` in nearly any statement that includes an initializer:

.. code-block:: cpp

   auto x = 3;          // x is an int
   auto q = '?';        // q is a char
   auto r = &x;         // r is an int 
                        //  - a reference to a variable is implicitly dereferenced

   auto i = 0, d = 0.0; // Error. 
                        // If using auto to deduce multiple types,
                        // then the types must all match
   auto i = 0, *p = &i; // OK. Both i and the pointer to i are int

This is a far better use for the keyword auto.
Later, we will see that some types are long and complicated -
having to type them out, as was required prior to C++11,
is a chore.
``auto`` frees us from having to declare a type the compiler already knows about.
Additionally, some types, such as those returned by :doc:`lambda expressions <../pointers/lambda>`,
are hidden from us - auto is the only option in these cases.

When variables are initialized using auto, 
they inherit the *type* from the initializer, but not its *constness*.

.. code-block:: cpp

   int          val = 0;
   int&         ir  = val;
   auto         x   = ir;

What type is x?

.. reveal:: reveal-auto-1
   :showtitle: Show Answer
   :hidetitle: Hide Answer

   If you said, ``int``, excellent job!

   ``ir`` is a reference to ``val``, 
   which makes ``ir`` just another name for ``val``. 
   ``auto x = ir;`` is exactly the same as if we had written 
   ``auto x = val;`` here.

Given the following code:

.. code-block:: cpp

   const double val = 3.14; 
   auto         y   = val;

What type is y?

.. reveal:: reveal-auto-2
   :showtitle: Show Answer
   :hidetitle: Hide Answer

   If you said, ``double``, excellent job!

   Just because ``val`` is ``const``, 
   it has nothing to do with whether ``y`` is ``const``.

   If we had wanted ``y`` to be ``const``, 
   then we would have needed to say so:

   .. code-block:: cpp

      const auto y = val;


The ``auto`` keyword is a simple way to declare a variable that has a complicated type. 
We will get into the details of using auto in this way in later sections.
But accept for now that 
you can use auto to declare a variable where the initialization 
expression involves iterators, templates, pointers to functions, or pointers to members.
You can also use ``auto`` to declare and initialize a variable to a lambda expression. 
You can't declare the type of a lambda yourself because the type of a 
:doc:`lambda expression <../pointers/lambda>` is known only to the compiler.

``auto`` is also commonly used when a type would be redundant, especially in
*range-for loops*:

.. code-block:: cpp

   std::vector<double> numbers = {1.1, 2.2, 3.3, 5.5, 8.8};
   for (const auto& n: numbers) {
     std::cout << n << '\n';
   }

In this case, the compiler already knows the type stored in the ``vector`` numbers.
It doesn't need to be told again.

When first introduced to ``auto``, many programmers balk.
It *feels* sloppy and imprecise, and it *seems* as if we are sacrificing clarity.
In fact using ``auto`` is just as strongly typed as a manual declaration
and it aids clarity because it forces delaying variable
declaration until you have a value to initialize it with.

.. admonition:: Guideline

   Prefer to declare local variables using ``auto x = expr;`` 
   when you don’t need to explicitly commit to a type. 
   It is efficient by default and guarantees that no implicit conversions 
   or temporary objects will occur.

It is important to note that ``auto`` may not always deduce 
the type you expect or the type you need.
For example:

.. code-block:: cpp

   auto s = "Hello, world!";
  
What type is s?

.. reveal:: reveal-string-confusion
   :showtitle: Show Answer
   :hidetitle: Hide Answer

   If you said, ``const char*``, excellent job!

   If you guessed ``string``, you are not alone.
   This is a common mistake and one that gives new C++ programmers a lot of headaches.
   String literals in C++ are **always** ``const char*``.

   If you need a ``std::string``, you have to explicitly declare it:

   .. code-block:: cpp

      std::string s = "Hello, world!";
      
One final note.

The ``auto`` keyword is a *placeholder* for a type, 
but it is **not** a type. 
Therefore, ``auto`` cannot be used in casts or operators such as ``sizeof`` and ``typeid``.


-----

.. admonition:: More to Explore

  - From: cppreference.com: 
    The `auto specifier <http://en.cppreference.com/w/cpp/language/auto>`_ and 
    `decltype specifier <http://en.cppreference.com/w/cpp/language/decltype>`_. 
  - Herb Sutter's GOTW blog

    - `#92 (auto part 1) <https://herbsutter.com/2013/06/05/gotw-92-auto-variables-part-1/>`_
    - `#93 (auto part 2) <https://herbsutter.com/2013/06/07/gotw-93-auto-variables-part-2/>`_
    - `#94 (almost always auto) <https://herbsutter.com/2013/06/13/gotw-94-special-edition-aaa-style-almost-always-auto/>`_




