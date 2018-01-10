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
   :scale: 50 %
   :align: center

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
   :scale: 50 %
   :align: center

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
   left -> root
   right -> root


.. digraph:: t
   
   // from graphviz faq

   a -> b0
   xb [label="",width=.1,style=invis]
   a -> xb [style=invis]
   a -> b1
   {rank=same b0 -> xb -> b1 [style=invis]}
   b0 -> c0
   xc [label="",width=.1,style=invis]
   b0 -> xc [style=invis]
   b0 -> c1
   {rank=same c0 -> xc -> c1 [style=invis]}

.. digraph:: larger

   graph[nodesep=0.25, ranksep=0.3, splines=line];
   node [fontname = "Bitstream Vera Sans", fontsize=14,
         style=filled, fillcolor=lightblue,
         shape=circle, fixedsize=true, width=0.3];
   edge [weight=1, arrowsize=0.5];

   a, b, am, c, d, bm, e, f, cm, g, h, dm, i, j, em, k, l, fm, m;
   am, bm, cm, dm, em, fm [style=invis, label=""];

   a->b,c;
   b->d [weight=2]; // nudge b: trees b & c are not balanced
   b->e;
   c->f,g;
   d->h,i;
   e->j,k;
   f->l,m;

   edge [style=invis, weight=100];
   d->dm; 
   e->em;
   b->bm;
   f->fm;
   c->cm;
   a->am;
   
.. graphviz::

   graph calc {
      graph[nodesep=0.25, ranksep=0.3, splines=line];
      node [fontname = "Bitstream Vera Sans", fontsize=14,
            style=filled, fillcolor=lightblue,
            shape=circle, fixedsize=true, width=0.3];
      // layout all nodes 1 row at a time
      // order matters on each line, but not the order of lines
      "+";
      "/", am, "**";
      "1", dm, "2";
      "*", bm, "3", "4", cm, "5";

      // make 'mid' nodes invisible
      am, bm, cm, dm [style=dotted, label=""];

      // layout all visible edges as parent -> left_child, right_child
      "+" -- "/","**";
      "/" -- "*","3"
      "**"-- "4","5";
      "*" -- "1","2";

      // link mid nodes with a larger weight:
      edge [style=dotted, weight=10];
      "+" -- am;
      "/" -- bm;
      "**"-- cm;
      "*" -- dm;
   }
   

.. digraph:: g

   node [shape = record, height=.1];
   node0[label = "<f0> |<f1> G|<f2> "];
   node1[label = "<f0> |<f1> E|<f2> "];
   node2[label = "<f0> |<f1> B|<f2> "];
   node3[label = "<f0> |<f1> F|<f2> "];
   node4[label = "<f0> |<f1> R|<f2> "];
   node5[label = "<f0> |<f1> H|<f2> "];
   node6[label = "<f0> |<f1> Y|<f2> "];
   node7[label = "<f0> |<f1> A|<f2> "];
   node8[label = "<f0> |<f1> C|<f2> "];

   "node0": f2->"node4":f1;
   "node0": f0->"node1":f1;
   "node1": f0->"node2":f1;
   "node1": f2->"node3":f1;
   "node2": f2->"node8":f1;
   "node2": f0->"node7":f1;
   "node4": f2->"node6":f1;
   "node4": f0->"node5":f1;



-----

.. admonition:: More to Explore

   TBD

