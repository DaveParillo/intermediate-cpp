..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: algorithms; refactoring


Refactoring to Algorithms
=========================
The primary objective of refactoring is to improve code.
Those improvements might take many forms.
In this section we are going to focus on refactoring a pair
of functions that at first glance do not appear
to be doing the same thing.
However, we will see the similarities and how refactoring is accomplished,
step-by-step.

Given two functions, each sums the values provided.

The first function adds all of the integers in a raw array:

.. code-block:: cpp

    int sum(int array[], int n) {
      int sum = 0;
      for (int i = 0; i < n; ++i ) {
        sum += array[i];
      }
      return sum;
    }

The second adds all of the elements in a simple,
home-grown linked list.

.. code-block:: cpp

    // create a simple node in a linked list
    struct node {
      int value = 0;
      node* next = nullptr;
    };

    int sum(node* first) {
      int s = 0;
      while (first) {        // first not false or zero
        s += first->value;
        first = first->next;
      }
      return s;
    }

How can we generalize and combine these two functions into one?
We can rewrite both functions in a form of pseudo-code.

.. code-block:: cpp

   // we need a generic type 'T'
   T sum(/* data */ )                   // somehow parameterize this
   {
     T s = 0;
     while (/* not at end */ ) {        // loop through all elements
       s = s + /* get value */;         // compute sum
       /* get next data element */;
     }
     return s;
   }

We need several generic operations on **data**:

- Determine if we are not at end of data
- Get value
- Get next element

.. tabbed:: sum

   .. tab:: Example

      The STL style supports both data structures.

      Like find, we define a pair of iterators. ``first`` and ``last``.
      The iterator type should support the requirements of 
      `InputIterator <https://en.cppreference.com/w/cpp/named_req/InputIterator>`__.

      A separate template parameter for the initial sum finishes the signature.

      The value must be a :term:`regular type` and the 
      dereferenced iterator must be convertible to the value type.
      
      The function signature becomes:

      .. literalinclude:: refactor.txt
         :language: cpp
         :lines: 9-13
         :dedent: 3

      The main loop checks whether we should continue
      and accumulates the sum:

      .. literalinclude:: refactor.txt
         :language: cpp
         :lines: 14-17
         :dedent: 5

   .. tab:: Run It

      And we can use this algorithm with either a raw array or a linked list.

      .. include:: refactor.txt

Removing a final assumption
---------------------------
Can we make ``sum`` even more generic?

Sum still has a hard-coded assumption that addition ( the ``operator+`` function)
is the operation that we always want to perform.

Might we want to perform **any** binary operation on a sequence?
If yes, then we can add one more template parameter allowing callers
to pass in a function pointer (or equivalent).

.. tabbed:: accumulate

   .. tab:: Example

      The function signature becomes:

      .. literalinclude:: accumulate.txt
         :language: cpp
         :start-after: // using
         :end-before: while
         :dedent: 3

      The main loop replaces the explicit ``+`` with
      a call to a provided binary operator:

      .. literalinclude:: accumulate.txt
         :language: cpp
         :start-after: while
         :end-before: ++first
         :dedent: 5

      This *could* be addition: ``operator+``, but can now support
      any binary operation that the type ``T`` supports.

      A default operation can be provided with a supporting template
      that calls accumulate with :cref:`std::plus`.

      .. literalinclude:: accumulate.txt
         :language: cpp
         :start-after: default operation
         :end-before: main
         :dedent: 3

   .. tab:: Run It

      .. include:: accumulate.txt


Note that 
we did not pass ``+`` or ``*`` to a function.
The symbol ``+`` is not a type.

The parameter passed through ``BinaryOp op`` **must** be a valid :term:`type`.

A function *can* take a pointer or a type as a parameter.
Function objects passed as parameters must satisfy the requirements 
of :cref:`std::function`.
Lambda expressions, function objects, and functions pointers are all acceptable.
The STL has a large collection of 
`operator types that can be passed to functions <https://en.cppreference.com/w/cpp/utility/functional>`.



-----

.. admonition:: More to Explore

   - From CPP Core Guidelines

     - `T.2 <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#t2-use-templates-to-express-algorithms-that-apply-to-many-argument-types>`__: Use templates to express algorithms that apply to many argument types

