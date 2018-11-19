..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   single: design patterns
   pair: classes; patterns

Design patterns
===============
A software design pattern is a general, 
reusable solution to a common software problem.
It is not an actual implementation,
but rather an idea.

Design patterns gained popularity in computer science after the book 
*Design Patterns: Elements of Reusable Object-Oriented Software*
was published in 1994 by (Gamma et al.).
The book had 4 authors and together they became known as the
"Gang of Four", or even more briefly the "GoF". 

Design patterns are useful for several reasons:

- They provide useful solutions to common problems
- They provide a common vocabulary between programmers when discussing a design
- They exploit lessons learned by other developers


.. epigraph::

   ... with patterns you get *experience* reuse.

   -- Head First Design Patterns, Freeman and Robson, 2014, p. 1.

.. index:: 
   pair: inheritance; strategy pattern

Fixing an inheritance problem
-----------------------------
Recall our flying penguin problem from the section on :doc:`inheritance`:

.. graphviz:: 
   :alt: Bird inheritance

   digraph "bird"
   {
     edge [fontname="BitstreamVeraSans",
           fontsize="10",
           labelfontname="BitstreamVeraSans",
           labelfontsize="10",
           dir="back",
           arrowtail="onormal",
           style="solid",
           color="midnightblue"];
     node [fontname="BitstreamVeraSans",
           fontsize="10",
           height=0.2,
           width=0.4,
           color="black",
           fillcolor="lightblue",
           shape=box,
           style="filled"];
     bird [shape=record,
       label="{\<\<interface\>\>\nbird\n||fly(): void\l}"];
     bird -> hawk;
     bird -> owl;
     bird -> penguin;
     bird -> robin;
   }

This type of design error is actually common.

It's easy to overlook a design error, in this case flying penguins.
Part of what makes these errors problematic is that design errors
that actually get delivered in the final product are among the most
expensive software errors to fix.

So how do we fix our bird design?

We **could** just override the ``fly`` method for penguins
and have the override do nothing.
This might solve our immediate problem, but it's not a general
solution to this problem:

- It doesn't work as well for non-void functions.
  In this case, ``fly`` -- a void function -- really could do nothing
  A non-void function **must** return something.
  If the function returns something, but that 'something' actually means
  'nothing', then we have another design problem.
  This value now represents a marker that every caller of the function
  might need to handle and understand that no action was taken.
- What happens when we need behaviors other than ``fly``?
  If every time we have an exception case for a derived type
  and we create overrides that do nothing,
  then it can become difficult to understand the true capabilities
  of any object in the hierarchy just by looking that the interface.

  You have to examine the *code* to see how each (or if) an 
  interface was *implemented*.

  Any design that requires us to look at the source code before we can
  completely understand it is not a design we want to use.

Another problem with the existing design is that it encourages
duplication in derived classes.
For example, let's assume we need to model bird flying behavior.
Most birds don't just 'fly'.
They soar, flock, flit about, dive, or don't fly at all.
There are many thousands of different kinds of birds,
but relatively few ways of flying.







-----

.. admonition:: More to Explore

   - `OO Design <http://www.oodesign.com/>`__ 
   - `Software design pattern <https://en.wikipedia.org/wiki/Software_design_pattern>`__ on Wikipedia
   - `Evil design patterns <https://javaranch.com/patterns/>`__ by Paul Wheaton.
     A very short critique of pattern overuse.
   - `Revenge of the Nerds <http://www.paulgraham.com/icad.html>`__
     an excellent article written by Paul Graham in 2002.
     About the evolution of language and how modern languages are becoming more
     like Lisp -- which was discovered in 1958.
     The end has a short criticism of patterns.

     Keep this date in mind when he uses phrases like 'recently invented':
     that's still over 20 years ago!


