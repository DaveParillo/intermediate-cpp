..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   single: algorithms

Background
==========

Recall from :doc:`../containers/intro` that a container
is a generic collection.
Containers allow us to store data using *well-known* data structures.
The STL containers provide the patterns we can use to make
custom containers, if needed.

Recall from :doc:`../iterators/background` that an iterator
is a :term:`type` that performs operations that *feel* like a pointer.
Although an iterator allows syntax very similar to a pointer,
it is not a pointer.
Each container 'owns' it's iterators.
When a container is created, it has the ability to create an iterator
that knows how to visit elements of the type stored in the container.

Now that we have these two great tools in the STL,
we want to use them to solve problems.
It turns out that many programming tasks fall into basic groups:

- find
- copy
- sum
- count
- sort

These are all *actions* that we perform on *sequences*.
The goal of the STL algorithms is to define these actions in a generic way.
The STL algorithms satisfy this goal using small, 
reusable functions that avoid writing repetitive code
and define a consistent, portable interface.

Consider that counting elements in a :term:`list` is not very different
from counting elements in a :term:`vector`.

.. index:: ISO C++ standard
   single: for_each
   single: count(_if)
   single: find(_if)
   single: search
   single: copy(_if)
   single: move
   single: transform
   single: generate
   single: is_partitioned
   single: partition_copy
   single: stable_partition
   single: is_sorted
   single: sort
   single: stable_partition
   single: lower_bound
   single: binary_search
   single: equal_range
   single: merge
   single: includes
   single: set_difference
   single: set_union
   single: is_heap
   single: make_heap
   single: sort_heap
   single: max
   single: min
   single: max_element
   single: clamp
   single: equal
   single: lexicographical_compare
   single: is_permutation
   single: next_permutation
   single: iota
   single: accumulate
   single: inner_product
   single: reduce
   single: uninitialized_copy
   single: uninitialized_fill
   single: destroy

STL Algorithms at a glance
--------------------------
The STL algorithms are part of the 
`ISO C++ Standard <https://isocpp.org/std/the-standard>`__.
Currently, it contains more than 150 algorithms for 
searching, counting, and manipulating ranges.
C++17 alone added 69 more algorithms to the library.
While most of these (but not all) were new overloads to existing algorithms,
it does demonstrate the dynamic nature of the STL and its growth.

The algorithms are organized into broad categories:

=================================== ==========================================================================
Algorithm operations                Example algorithms
=================================== ==========================================================================
Non-modifying sequence operations   :cref:`for_each`, :cref:`count_if`, :cref:`find_if`, :cref:`search`
Modifying sequence operations       :cref:`copy_if`, :cref:`move`, :cref:`transform`, :cref:`generate`
Partitioning operations             :cref:`is_partitioned`, :cref:`partition_copy`, :cref:`stable_partition`
Sorting operations                  :cref:`is_sorted`, :cref:`sort`, :cref:`stable_partition`
Binary search operations            :cref:`lower_bound`, :cref:`binary_search`, :cref:`equal_range`
Set operations                      :cref:`merge`, :cref:`includes`, :cref:`set_difference`, :cref:`set_union`
Heap operations                     :cref:`is_heap`, :cref:`make_heap`, :cref:`sort_heap`
Min/max operations                  :cref:`max`, :cref:`min`, :cref:`max_element`, :cref:`clamp`
Comparison operations               :cref:`equal`, :cref:`lexicographical_compare`
Permutation operations              :cref:`is_permutation`, :cref:`next_permutation`
Numeric operations                  :cref:`iota`, :cref:`accumulate`, :cref:`inner_product`, :cref:`reduce`
Uninitialized memory operations     :cref:`uninitialized_copy`, :cref:`uninitialized_fill`, :cref:`destroy`
=================================== ==========================================================================

Notice that only a single category of algorithms is considered 'numeric'.
In C++11, only 5 algorithms specifically do numeric computations.
C++17 adds 6 more.

.. index:: 
   pair: algorithms; loops


STL algorithms and loops
------------------------
TBD


-----

.. admonition:: More to Explore

   - From cppreference.com

     - Overview of the `algorithms <http://en.cppreference.com/w/cpp/algorithm>`_ library
     - `std::find <http://en.cppreference.com/w/cpp/algorithm/find>`_ (and find_if), 
       `std::count_if <http://en.cppreference.com/w/cpp/algorithm/count_if>`_
     - `for_each <http://en.cppreference.com/w/cpp/algorithm/for_each>`_ and 
       `make_heap <http://en.cppreference.com/w/cpp/algorithm/make_heap>`_

