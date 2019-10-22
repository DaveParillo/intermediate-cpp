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


   array<string, 3> names = {{"Alice"}, {"Bob"}, {"Clara"}};
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

-----

.. admonition:: More to Explore

  - `Iterator Library <http://en.cppreference.com/w/cpp/iterator>`_ at cppreference.com
  - C++ Concepts: `Iterator <http://en.cppreference.com/w/cpp/concept/Iterator>`_
