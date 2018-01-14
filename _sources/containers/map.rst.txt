..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: associative containers; map

The map class
=============

A :term:`map` refers to any data structure that 'maps' :term:`keys <key>` to values.
All the containers discussed so far focused on storing 1 thing.
That is, each stores values of a single type.
Maps add a new wrinkle.
A ``map`` stores **pairs** of things.
Traditionally, the pair stored is referred to as a :term:`key-value pair`.\ [1]_

Nearly every programming language provides some kind of ``map`` implementation.
Some languages use the terms *associative array* or *dictionary List*,
but structurally, they are very similar.

**Values** are retrieved from a ``map`` using the **key**.
Each :term:`key` must be unique.
In other words, keys are members of a ``set``.
Like a :cref:`std::set`,
adding a second node with the same key replaces the old value.



.IT Also Known As
.i1 Associative array, Dictionary List
.IT Examples
.i1 Dictionary: <word, definition>
.i1 Symbol table: <identifier, object>


-----

.. admonition:: More to Explore

   - `STL containers library <http://en.cppreference.com/w/cpp/container>`_

.. topic:: Footnotes

   .. [1]  Sometimes this is abbreviated as 'KVP'.  
           On cppreference.com you'll see it shortened even further to just ``P``
