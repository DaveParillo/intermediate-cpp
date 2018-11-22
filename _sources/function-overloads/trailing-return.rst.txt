..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index::
   pair: keyword; auto
   pair: auto; trailing return type

Trailing return types
=====================

Problem:

- You created a template, but the return type needs to be a type other than one of the template parameters.

You'd like to be able to use auto to simply:

.. code-block:: cpp

   template<class T, class U>
   auto mystery_function(T t, U u);

Starting in C++17, this syntax works much more often than in previous version of the standard,
because the rules for deducing types have expanded.
Earlier version of C++ need to resort to a **trailing return type**.

Even in C++17, depending on what a function does, return type deduction may not always work.
If it is possible for our function to return different types,
then a simple auto return will not compile:

.. code-block:: cpp

   auto f(bool val)
   {
       if (val) return 123; // deduces return type int
       else return 3.14f;   // error: deduces return type float
   }

You can use ``auto``, together with the ``decltype`` type specifier, 
to delay the evaluation of a function return value until after the function parameters have been declared.

Use ``auto`` and ``decltype`` to declare a function whose return type depends on the types of its arguments. 

To understand what's going on, first we have to understand ``decltype``.

.. index::
   pair: keyword; decltype

Keyword: decltype
-----------------

Added in C++11,
the ``decltype`` type specifier yields the **type** of a specified expression, object, or literal value. 
We use :cref:`decltype` when we want to define a variable based on the result of an expression,
but we don't want to use the expression to initialize the variables value.
For example:

.. code-block:: cpp

   int i = 42;
   decltype(i) j = i * 2.0;

Similarly, there is a symmetry between the :cref:`auto specifier` and :cref:`decltype`:

.. code-block:: cpp

   auto a = 3u;       // a is unsigned;
   decltype(a) b = a; // same as auto b = a;  b is also unsigned


Trailing return type syntax
---------------------------

Since the :cref:`auto specifier` and :cref:`decltype` are complimentary operators,
they work well together to help write generic functions that avoid
committing to a specific type.

To declare a trailing return type for a function,
use this general form:

.. code-block:: cpp

   auto function_name () -> return_type
   {
     // function body
   }

The ``->`` is required to inform the compiler that a trailing return type follows.

Note that the return type is inserted after function parameters and
before the function body.

.. code-block:: cpp

   auto f(const bool val) -> float
   {
       if (val) return 123; // return widens int to float
       else return 3.14f;   // return type float
   }


.. code-block:: cpp

   template<typename T, typename U>
   auto add(const& T rhs, const& U lhs) -> decltype(rhs + lhs)
   {
       return rhs+lhs;
   }

Calling this add function like so:

.. code-block:: cpp

   auto val = numeric_limits<unsigned short>::max(); // typically 65,536
   auto sum = add(val, val);

Even though a variable of type ``unsigned short`` was used in both parameters,
the return type can't be unsigned short,
because the returned value is too large to fit.
If we had committed to a type, or used one of the generic types provided in the template,
our result would overflow.
Instead, the compiler used ``decltype`` to determine in this case, 
the return type should be ``int``.

Do trailing return types seem like a lot of trouble?
Prior to C++11, when trailing return type syntax was introduced,
you could use :cref:`decltype` and :cref:`declval` instead:

.. code-block:: cpp

   template<typename T, typename U>
     decltype(std::declval<T>() + std::declval<U>()) 
     add(const& T lhs, const& U rhs) {
       return lhs + rhs;
     }

This get unreadable fairly quickly.
For this reason, trailing return types are preferred.

-----

.. admonition:: More to Explore

   - :doc:`../function-intro/auto`
   - From: cppreference.com: 
     The `auto specifier <http://en.cppreference.com/w/cpp/language/auto>`_ and 
     `decltype specifier <http://en.cppreference.com/w/cpp/language/decltype>`_. 


