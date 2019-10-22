..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: associative containers; map

The set class
=============
A :term:`set` refers to any data structure in which
every member of the set is unique.
The integers define a set, because every number is unique.
The values ``{3, 1, 4, 1, 5, 9}`` do **not** define a proper set,
because the value ``1`` is repeated.

In C++, a :cref:`std::set` must also be sorted.
Like ``std::vector``, a ``set`` is a generic class
and declarations must include the object :term:`type`
stored in the class:

.. code-block:: cpp

   #include <set>

   std::set<int> x {2,7,1,8,2,8,1,8,2,8,4,5,9};

What will be stored in ``x`` after initialization?

.. reveal:: reveal_init

   The two defining characteristics of a ``set`` are:

   - A ``set`` is sorted.
   - A ``set`` may contain only unique values.

   Defining a set with non-unique values is not an error.
   The new object simply replaces the old.

   When initialized, ``x`` will contain: ``1 2 4 5 7 8 9``
   
Like the sequence containers,
each element in a set can be visited one at a time
using a :cref:`range for` loop.

.. code-block:: cpp

   #include <iostream>
   #include <set>

   int main()
   {
     std::set<int> x {2,7,1,8,4,5,9};

     for (const auto& i: x) {
       std::cout << i << ' ';
     }

     return 0;
   }

Because ``set`` does not provide ``operator[]``,
traditional for loops using an index are not possible:

.. code-block:: cpp

     std::set<int> x {2,7,1,8,4,5,9};

     for (int i=0; i < x.size(); ++i) {  // OK
       std::cout << x[i] << ' ';         // compile error
     }


Sets of any type can be created as long as the type is
:term:`comparable`.
The comparison operator (:term:`comparator`) 
used in sets by default is ``operator <``.
Any type used in a :cref:`std::set`
should overload ``operator <``.
All of the :cref:`fundamental types`
are :term:`comparable`.

Use :cref:`set::insert` to add a new element to a ``set`` or replace an existing element:

.. code-block:: cpp

     std::set<int> x {2,7,1,8,4,5,9};
     x.insert(6);

Because a ``set`` is not an indexed container,
every 'get' is a search:

.. code-block:: cpp

     std::set<int> x {2,7,1,8,4,5,9};
     auto it = x.find(8);

The :cref:`set::find` function returns an :term:`iterator` to the element
with a specific key.
We will discuss iterators in detail soon.
For now, you can treat the iterator as if it was a pointer to access the value
returned from find:


.. code-block:: cpp

     std::set<int> x {2,7,1,8,4,5,9};
     auto it = x.find(8);
     std::cout << *it;         // print the value returned from find()

The :cref:`set::erase` function is used to remove an element from a ``set``.
:cref:`set::erase` takes an iterator as the position in the ``set`` to remove:

.. code-block:: cpp

     std::set<int> x {2,7,1,8,4,5,9};
     auto it = x.find(8);
     if (it != x.end()) {
       x.erase(it);
     }

     it = x.find(8);
     assert ( it == x.end() );  // this should be true

Variations on std::set
----------------------
The STL provides 3 alternate forms of :cref:`std::set` class:

multiset
   A ``set`` in which duplicate keys are allowed.

unordered_set
   A ``set`` of unique objects stored based on the object :term:`hash function`.
   Added in C++11.
  
unordered_multiset
   An ``unordered_set`` in which duplicate keys are allowed.
  

-----

.. admonition:: More to Explore

   - `STL containers library <http://en.cppreference.com/w/cpp/container>`_
   - `Visualgo: binary heap <https://visualgo.net/en/heap?slide=1>`_

