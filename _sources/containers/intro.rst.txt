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
numbers, bank accounts, students, or even fruit, 
then the simplest approach is to put them in a container.
You should already be familiar with raw arrays,
which are part of the language 
and are not considered part of the STL.
There are two broad categories of STL containers:
*sequence containers* and *associative containers*.
In an :doc:`earlier section <../string+vector/vector>`, 
we briefly introduced ``std::vector``.
A vector is an example of a sequence container.

A :term:`sequence container` stores a sequence of elements of a given type.
The sequence containers can be further divided into two 'flavors':

list-like sequences
    Things stored in a sequence

stacks and queues
    Things listed in order to be processed

As you might imagine, :term:`associative containers <associative container>` 
do not store elements in sequential order, 
but rather use a container
element to determine where in the container data should be stored.
The associative containers can also be further divided into two 'flavors':

sets
    Unique things

maps
    Things stored with a unique ID

All the STL containers provide similar advantages over arrays:

- Add and remove data dynamically
- Bounds checking
- Work with data at a higher level of abstraction
- Manage subsets of data as a unit

Although all of the containers in the STL
share some core characteristics,
the different containers have different designs,
and have different trade-offs or costs.
This allows them to excel in specific situations,
where an 'all-purpose' container might fall short.

All containers support the same basic operations:

- Add objects to the container

  - And remove objects from it

- Find out if an object is in the container (or a group of objects)
- Retrieve an object without removing it
- Walk through the container, looking at each object in turn

The container manages the storage space that is allocated for its elements and 
provides member functions to access them,
either directly or through :doc:`iterators <../iterators/toctree>`
(objects with properties similar to pointers).

Ordered and sorted containers
-----------------------------
STL containers may be ordered, unordered, sorted or unsorted.
An **ordered** container simply means that
you can iterate through the container in a specific order.

We normally do not think of the sequence containers as having an order.
For example, a vector may contain the values ``{3, 1, 4, 1, 5, 9}``,
which clearly are not in the :term:`natural order` for integers.
A ``vector`` *is* ordered, however: by its index position.
As long as items are not added or removed from an ordered container,
two iterations over the same container will visit the same
elements in the same order.
So in our previous example, the vector containing ``{3, 1, 4, 1, 5, 9}``
is *ordered*, but *unsorted*.

A **sorted** container stores elements using rules defined when the container is created:
the sort order.
All of the sorted containers define a default sort order, 
determined by the ``operator<`` for the element type.

Containers can *never* be both sorted and unordered,
because sorting of any kind is by definition an ordering.


-----

.. admonition:: More to Explore

   - C++ Concepts: 
     
     - `Containers <http://en.cppreference.com/w/cpp/concept/Container>`_
     - `Sequence Containers <http://en.cppreference.com/w/cpp/concept/SequenceContainer>`_
     - `Associative Containers <http://en.cppreference.com/w/cpp/concept/AssociativeContainer>`_

