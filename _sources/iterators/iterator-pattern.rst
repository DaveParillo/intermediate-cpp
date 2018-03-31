..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. |---| unicode:: U+2014 

.. index:: 
   single: iterator pattern

Iterator pattern
================
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

-----

.. admonition:: More to Explore

  - `Iterator Library <http://en.cppreference.com/w/cpp/iterator>`_ at cppreference.com
  - C++ Concepts: `Iterator <http://en.cppreference.com/w/cpp/concept/Iterator>`_
