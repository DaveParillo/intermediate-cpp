..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. |---| unicode:: U+2014 

.. index:: 
   single: iterator operations
   pair: iterator; operations

Basic iterator operations
=========================
By design, iterators in C++ feel as if you are using pointers.
Most iterators support the same operations as pointers.

+--------------+--------------------------------------------------------+
| Operation    |  Result                                                |
+==============+========================================================+
| ``p == q``   | ``true`` if and only if ``p`` and ``q``                |
|              | point to the same element or both point to ``end``     |
+--------------+--------------------------------------------------------+
| ``p != q``   | negation of above                                      |
+--------------+--------------------------------------------------------+
| ``*p``       | refers to the element pointed to by ``p``              |
+--------------+--------------------------------------------------------+
| ``*p = val`` | writes ``val`` to the element pointed to by ``p``      |
+--------------+--------------------------------------------------------+
| ``val = *p`` | reads from the element pointed to by ``p`` and         |
|              | writes to ``val``                                      |
+--------------+--------------------------------------------------------+
| ``++p``      | increment the iterator, making it point to the next    |
|              | element in the container or to ``end``                 |
+--------------+--------------------------------------------------------+

.. index:: 
   single: iterator categories
   single: mutable iterator

Iterator categories
-------------------
Different containers need different capabilities from their iterators.

Instead of being defined by specific types, 
each category of iterator is defined by the operations that can be performed on it. 
This definition means that any type that supports the necessary operations 
can be used as an iterator |---| for example, 
a pointer supports all of the operations required by :cref:`Random Access Iterator`,
so a pointer can be used anywhere a :cref:`Random Access Iterator` is expected.

All of the iterator categories (except :cref:`Output Iterator`) can be organized into a hierarchy, 
where more powerful iterator categories (e.g. :cref:`Random Access Iterator`) 
support the operations of less powerful categories (e.g. :cref:`Input Iterator`). 
If an iterator falls into one of these categories and also satisfies the 
requirements of :cref:`Output Iterator`, 
then it is called a *mutable iterator* and supports both input and output. 
Non-mutable iterators are called *constant iterators*.

.. digraph:: iter_categories
   :alt: Iterator categories

    graph [
        splines= ortho
        fontname = "Bitstream Vera Sans"
        fontsize = 14
        labelloc = b
        label = "Iterator categories"
        nodesep = 1.0
        ranksep = 0.3
    ];

    node [
        fontname = "Bitstream Vera Sans"
        style=filled, fillcolor=lightblue
        fontsize = 14,
        shape = "box",  width=0.5, height=.25
    ];
    edge [dir=back, arrowsize=0.5];

    input [label="Input Iterator", URL="http://en.cppreference.com/w/cpp/concept/InputIterator"];
    fwd [label="Forward Iterator", URL="http://en.cppreference.com/w/cpp/concept/ForwardIterator"];
    bi [label="Bidirectional Iterator", URL="http://en.cppreference.com/w/cpp/concept/BidirectionalIterator"];
    random [label="RandomAccess Iterator", URL="http://en.cppreference.com/w/cpp/concept/RandomAccessIterator"];
    contiguous [label="Contiguous Iterator", URL="http://en.cppreference.com/w/cpp/concept/ContiguousIterator"];
 
    output [label="Output Iterator", URL="http://en.cppreference.com/w/cpp/concept/OutputIterator"];

    input -> fwd -> bi -> random -> contiguous [weight=100];
    edge [style=dotted, dir=none];
    input, fwd, bi, random, contiguous -> output;
    {rank=same; output bi};


:cref:`Input Iterator`
   Read elements and increments using ``operator++``, without multiple passes.
   Classes like :cref:`std::basic_istream` provide this iterator.


:cref:`Forward Iterator`
   :cref:`InputIterator`, plus increment using ``operator++``, with multiple passes.  
   The :cref:`std::forward_list` container provides this iterator.

:cref:`Bidirectional Iterator`
   :cref:`ForwardIterator`, plus decrement using ``operator--``
   Containers like :cref:`std::list`, :cref:`std::map`, and :cref:`std::set`
   provide this iterator.


:cref:`Random Access Iterator`
   :cref:`BidirectionalIterator`, plus access using ``operator[]``
   Before C++17, containers like :cref:`std::vector`, :cref:`std::array`, and :cref:`std::string`
   provided this iterator.
   It is still used for unordered collections like 
   :cref:`std::unordered_map` and :cref:`std::unordered_set`


:cref:`Contiguous Iterator`
   :cref:`RandomAccessIterator`, plus the container make a continuous storage guarantee.
   This category was added in C++17.
   Before C++17, iterators of containers like :cref:`std::vector` and :cref:`std::array`
   were often treated as a separate category.
   This category simply formalizes what was happening in practice.

:cref:`Output Iterator`
   More of a 'sub category of all of the others.
   If the iterator allows writing to the element, it is also an :cref:`OutputIterator`
   An output iterator can **only** be dereferenced on the left-hand side of an expression:

   .. code-block:: cpp

      vector<int> v = {1,2,3};
      auto it = v.begin();
      *it = 0;

-----

.. admonition:: More to Explore

  - `Iterator Library <http://en.cppreference.com/w/cpp/iterator>`_ at cppreference.com
  - C++ Concepts: `Iterator <http://en.cppreference.com/w/cpp/concept/Iterator>`_
