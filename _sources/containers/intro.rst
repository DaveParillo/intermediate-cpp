..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   single: containers

Standard Template Library Containers
====================================

If a program needs to manage a collection of closely related things,
numbers, bank accounts, students, fruit, 
then the simplest approach is to put them in a container.
You should already be familiar with arrays,
which are part of the language.
In an :doc:`earlier section <../string+vector/vector>`, 
we briefly introduced vector.
This chapter takes a closer look.

Like a raw array and ``vector``, all of the containers in this chapter
store a sequence of elements of a given type.
All the STL containers provide similar advantages over arrays:

- Add and remove data dynamically
- Bounds checking
- Work with data at a higher level of abstraction
- Manage subsets of data as a unit

Although all of the 'sequence containers' in the STL
share some core characteristics,
the different containers have different designs,
and have different trade-offs (costs).
This allows them to excel is specific niches,
where an 'all-purpose' might fall short.

All containers support the same basic operations:

- Add objects to the container

  - And remove objects from it

- Find out if an object is in the container (or a group of objects)
- Retrieve an object without removing it
- Walk through the container, looking at each object in turn

The container manages the storage space that is allocated for its elements and 
provides member functions to access them,
either directly or through iterators (objects with properties similar to pointers).

We normally do not think of the sequence containers as having an order.
For example, a vector may contain the values ``{3, 1, 4, 1, 5, 9}``,
which clearly are not in the :term:`natural order` for integers.
A ``vector`` *is* ordered, however: by its index position.

-----

.. admonition:: More to Explore

   - `Sequence containers <http://en.cppreference.com/w/cpp/container>`_

