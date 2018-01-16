..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. |---| unicode:: U+2014 

.. index:: 
   single: iterators

Background
==========
How can we visit each :term:`element` in a :term:`container`
and remain ignorant of the underlying container implementation details?
For example, given:

.. code-block:: cpp


   array<string, 3> names = {{"Alice"}, {"Bob"}, {"Clara"}};;
   std::map<std::string, int> 
                    ages  = {{"Alice", 27}, {"Bob", 3}, {"Clara", 1}};

What options do we have for operating on each :term:`element` in ``names`` and ``ages``?
A traditional :cref:`for loop` or :cref:`while loop` works for ``names``:

.. code-block:: cpp

   for (int i=0; i < names.size(); ++i) {
     cout << names[i] << '\n';
   }

   int i = 0;
   while(i < names.size()) {
     cout << names[i++] << '\n';
   }

Traditional loops using an ``int`` index do not work with containers
that do not overload ``operator[]``.
We solve this problem by avoiding explicit indexing altogether.
The :cref:`range for loop` 
provides a more readable equivalent to the traditional for loop:

.. code-block:: cpp
   
   for (string s: names) {
     cout << s << '\n';
   }

   // better: avoids copying
   for (const auto& s: names) {
     cout << s << '\n';
   }

The same syntax can be used for any STL container:
   
.. code-block:: cpp

   std::map<std::string, int> 
   ages  = {{"Alice", 27}, {"Bob", 3}, {"Clara", 1}};

   for (const auto& a: ages) {
     cout << a.first << ' ' << a.second << '\n';
   }

When you need to loop over each element in a collection,
the :cref:`range for loop` has completely
abstracted away the idea of moving from one element to the next.

We say these containers are :term:`iterable`.

Iterator pattern
----------------
A :term:`design pattern` is a general repeatable solution
to a commonly occurring problem in software design.
A primary goal of design patterns is to quickly transfer the knowledge
gained by expert designers to newer programmers.
Another goal is to allow for efficient communication between
programmers.
Design patterns contribute to a shared vocabulary between programmers.

Because design patterns represent general ideas about solving
classes of problems, they are language independent.
In the case of :term:`iterators <iterator>`,
the idea has solutions in most modern languages, including C++.

Each STL container class provides an :term:`iterator` class
that clients can use to retrieve the correct 
:term:`element` from the :term:`container`.

.. digraph:: iterator
   :alt: Container iterators

   graph [
        fontname = "Bitstream Vera Sans"
        fontsize = 14
        labelloc = b
        label = "Begin and end iterators"
        nodesep = 0.5
   ];

   node [
        fontname = "Bitstream Vera Sans"
        style=filled, fillcolor=lightblue
        fontsize = 14, label=""
        shape = "box",  width=0.5, height=.25
   ];

   a -> b -> c -> d -> e -> f [constraint=false, arrowhead=vee, arrowsize=0.5];
   c [label=". . .", fillcolor=none, color=white];
   f [style=dotted];
    
   node [shape=none]
   begin [label="begin()", fillcolor=none]
   end [label="end()", fillcolor=none]
    
   begin -> a;
   begin -> b [weight=2, style=invis];
   end -> f;
   end -> e [weight=2, style=invis];

   {rank=same; a b c d e f};
   
The element defined by ``begin()`` is part of the sequence.

The element defined by ``end()`` is **not part** of the sequence.
In C++, the ``end`` iterator is always one past the end of the sequence.
Forgetting this is a common source of error.

Basic iterator operations
-------------------------
Iterators in C++ by design feel as if you are using pointers.
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

Iterator categories
...................
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
   Classes like :cref:`std::instream` provide this iterator.


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
   Before C++17 iterators of containers like :cref:`std::vector` and :cref:`std::array`
   were often treated as a separate category.
   This category simply formalizes what was happening in practice.

:cref:`Output Iterator`
   More of a 'sub category of all of the others.
   If the iterator allows writing to the element, it is also an :cref:`OutputIterator`

Using iterators
---------------
Assigning an iterator explicitly to a variable works much like any other type:

.. code-block:: cpp

   vector<int> nums = {1, 2, 3, 4, 5};
   vector<int>::iterator it = nums.begin();

The variable ``it`` now points to the beginning of the container ``nums``
and can used much like a pointer:

.. code-block:: cpp

   vector<int> nums = {1, 2, 3, 4, 5};
   vector<int>::iterator it = nums.begin();

   cout << *it;  // prints: 1

The iterator type always matches the value type of the enclosing container.
Just as with pointers, an iterator to a ``vector<int>``
is a different type from an iterator to a ``vector<string>``.

It is possible to declare an iterator and use it in a traditional for loop:

.. code-block:: cpp

   vector<int> nums = {1, 2, 3, 4, 5};
   cout << "nums contains:";

   for (vector<int>::iterator it = nums.begin(); 
        it != nums.end(); ++it) {
       std::cout << ' ' << *it;
   }

Which produces:

.. code-block:: none

   nums contains: 1 2 3 4 5

A while loop can produce equivalent results:

.. code-block:: cpp

   vector<int> nums = {1, 2, 3, 4, 5};
   cout << "nums contains:";

   vector<int>::iterator it = nums.begin(); 
   while (it != nums.end())
       std::cout << ' ' << *it;
       ++it;
   }

We can shorten either example with ``auto``, 
since the compiler can easily determine what type is returned from ``begin()``:

.. code-block:: cpp

   for (auto it = nums.begin(); it != nums.end(); ++it) {
       std::cout << ' ' << *it;
   }

Example code like one of the two previous examples is commonly found on the web,
even when the point of the example has nothing to do with iterators.
When you don't need an iterator, don't use it:

.. code-block:: cpp

   for (const auto& n: nums) {
       std::cout << ' ' << n;
   }

A common source of error for new programmers is confusion about the types used in these two loops:

``begin()``
    **Always** returns an iterator that must be dereferenced in order to access the element value.

The range for declaration
    **Always** is assigned a value from the container.
    Unless the container is a container of pointers, no dereferencing is needed.


Limits of Range-based for loops
...............................
The :cref:`Range-for loop`, while convenient, has limitations.

Any situation in which you do not need or want to visit every element
requires a traditional loop:

.. code-block:: cpp

   for (int i=n; i>0; i/=2) {
     // do something with i . . .
   }

Similarly, if you need to iterate through multiple containers in a single loop,
possibly at different rates, then you need a traditional for loop:

.. code-block:: cpp

   for (int i=n, j=0; i>0; i/=2, j++) {
     // do something with i and j . . .
   }

If you need to :term:`traverse` a container and remove items,
then you need an explicit iterator so that you can call the container ``erase`` method:

.. code-block:: cpp

   vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   // Erase all even numbers 
   for (auto it = nums.begin(); it != nums.end(); ) {
     if (*it % 2 == 0) {
       it = nums.erase(it);
     } else {
       ++it;
     }
   }

Things to note about this example:

- ``it`` is not incremented in the for loop iteration expression
- If an element is erased, the current iterator is *invalidated*.
  Any further use would be an error in a ``vector``.
  The :cref:`vector::erase` function returns the iterator to the next element
  in the container.

Container functions that require iterators
------------------------------------------
Most container functions that use position information do not use an index like ``operator[]``.
Most of them express position using iterators.

insert
   Inserts elements at the specified location in the container.

.. activecode:: ac_iterator_insert
   :language: cpp
   :compileargs: ['-Wall', '-Wextra', '-pedantic', '-std=c++11']

   #include <iostream>
   #include <vector>
    
   void print(const std::vector<int>& v) {
     for (auto x: v) {
       std::cout << ' ' << x;
     }
     std::cout << '\n';
   }
    
   int main () {
       std::vector<int> nums(3,100);
       print(nums);
    
       auto it = nums.begin();
       it = nums.insert(it, 200);
       print(nums);
    
       nums.insert(it,2,300);
       print(nums);
    
       // 'it' no longer valid, get a new one:
       it = nums.begin();
    
       std::vector<int> vec2(2,400);
       nums.insert(it+2, vec2.begin(), vec2.end());
       print(nums);
    
       int arr[] = { 501,502,503 };
       nums.insert(nums.begin(), arr, arr+3);
       print(nums);
   }


erase
   Removes specified elements from the container.
   ``erase`` may remove a single element or a contiguous range of elements.


.. activecode:: ac_iterator_erase
   :language: cpp
   :compileargs: ['-Wall', '-Wextra', '-pedantic', '-std=c++11']

   #include <vector>
   #include <iostream>
 
 
   void print(const std::vector<int>& v) {
     for (auto x: v) {
       std::cout << ' ' << x;
     }
     std::cout << '\n';
   }

   int main( ) { 
     std::vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
     print(nums);
 
     nums.erase(nums.begin());
     print(nums);
 
 
     nums.erase(nums.begin()+2, nums.begin()+5);
     print(nums);

     return 0;
   }



-----

.. admonition:: More to Explore

  - `Iterator Library <http://en.cppreference.com/w/cpp/iterator>`_ at cppreference.com

