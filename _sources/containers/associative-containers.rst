..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   single: associative containers

Motivation
==========
If sequence containers like :cref:`vector` are so great,
then why would we need anything else?
In a word: search.

When we have millions a elements in a data structure and need to find
just one element, or a specific range or elements,
we *could* use a ``vector``.

Inserts are fast. 
No matter how many elements are already in a ``vector``
adding one more using :cref:`vector::push_back` takes
the same amount of time.
That is, the time cost of ``push_back`` is *constant* for a ``vector``.

A ``vector`` is default ordered only by its index position,
not by the values stored within it.
It's easy to keep throwing items in without paying any attention
to how they are ordered.

But always using ``push_back`` is analogous to a messy closet.
We could consider the closet to be ordered by *depth*:
the last things thrown in the closet are on the top of the pile.

.. image:: closet-messy.png
   :alt: An unsorted closet

This makes getting things back out slow.
If we only ever wan to to access the last item we added, 
then we know exactly where to go.
But if we want to find some arbitrary item,
we have to search the vector 1 element at a time until we find it.

Sometimes we may get lucky and find the desired element at index position 0.
If the data added to the vector is random, 
then this becomes increasingly less likely as the size grows.

We might sometimes get very unlucky and not find the element until the access
the last element.
Over many searches, on average, 
we will have to examine :math:`N / 2` elements.

It's easy to see that the more elements are added, 
the longer searches will take.

We need a tidy closet.

We could sort the ``vector``, which would speed up our search.
The basic idea is to sort the vector, 
then examine the value at position :math:`N / 2`.
If the value found is greater than the value we are looking for,
then examine the value at position :math:`N / 4`,
else examine the value at position :math:`3N / 4`.

At each step,
we eliminate the number of remaining elements we need
to search in our ``vector`` by half.
For large ``vector``\s, this save a lot of time.

.. image:: closet-neat.png
   :alt: A sorted closet

But if we want to keep the vector sorted,
because elements are added or removed frequently,
now adding data to our vector, which used to be fast,
is now slow.
We can either use :cref:`vector::push_back` followed by :cref:`vector::sort`,
or use :cref:vector::insert`.
*Every* insert is now a search and we are back to the original problem.
On average, it will take :math`N / 2` comparisons to add new data.

How can we solve this problem?

Can we make an :term:`ADT` whose performance does not degrade
as the number of elements in the :term:`ADT` grows large?

Yes, but we need a new idea.
Instead of a sequential container, we need a :term:`tree`.

The tree ADT
------------
A :term:`tree` is a *hierarchical* abstract data type.
Conceptually, it can be thought of as a collection of
*nodes* defined by parent-child relationships.

One node is the :term:`root`.
It serves as the 'trunk' of the tree and serves the same
function as the :term:`head` of a :term:`list`
The root node is the *only* node in a tree without a parent.
All other nodes in a :term:`tree` refer to exactly 1 parent.
In a :term:`binary tree`, 
the children are commonly referred to as the **left** and **right** nodes.

.. digraph:: a_tree
   :alt: A simple binary tree

   graph [
          labelloc=b;
          label="A simple binary tree";
       ];

   node [fontname = "Bitstream Vera Sans", fontsize=14,
                 style=filled, fillcolor=lightblue,
                 shape=record, width=0.5, height=.5]

   root -> left,right





-----

.. admonition:: More to Explore

   TBD

