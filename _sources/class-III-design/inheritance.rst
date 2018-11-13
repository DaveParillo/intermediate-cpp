..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: classes; inheritance

Inheritance
===========
Inheritance enables new classes to receive --- or inherit --- 
the properties and methods of existing classes. 
Inheritance is a programming strategy used to increase the flexibility
of your objects.
In particular, inheritance is **not** a code reuse strategy.
The purpose of inheritance in C++ is to express interface compliance 
(creating a subtype), not to reuse code.
In C++, code reuse usually comes via composition rather than 
via inheritance.
In other words, 
inheritance is mainly a specification technique rather than an 
implementation technique.

New programmers are generally eager to "do things the OO way"
and tend to overuse inheritance relationships.
This is especially true if starting with UML diagrams:
many diagram look 'too simple' without a lot of boxes
connected by generalization relations.

In general, however,
composition is a more powerful tool than inheritance.

.. admonition:: Guideline

   Prefer composition over inheritance.

Consider the following classes.

.. graphviz:: 
   :alt: Person inheritance

   digraph "person"
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

.. reveal:: r_class_inherit
   :showtitle: Is this OK?

   No.

   We have asserted that a penguin can fly.

   We might choose to implement ``fly()`` in our penguin class
   and simply do nothing, 
   but generally when we do that we are coing our way around a
   basic design problem.

It is very important when creating a class hierarchy using
inheritance that *every* derived class passes the **is a** test
for **all** of its bases.
For example:

.. code-block:: cpp

   struct oven: public kitchen { . . . };

This is not a proper relationship.
An oven is a thing commonly *found* in a kitchen,
but that does not mean an oven *is a* kitchen.
Because it fails this basic test,
it is likely that variables and functions that apply to the base:
``cupboards``, ``sink``, ``enter_room()``, etc
will fail to make sense when applied to the derived class.

This is an example better modelled through composition.
A kitchen **has a** sink in it.

.. index:: private inheritance

Private inheritance
-------------------
The default inheritiance model in C++ is *priavte inheritance*.
In private inheritance **all** of the base class members:
data and functions, public, protected, and private,
are treated as **private members** of the derived class.

A common question is "Why would we ever do this?"

If a derived class wants to reuse all of the code from a base class,
but *not* conform to the interface,
then private inheritance is how to achieve that.


.. index:: non-virtual functions; manatory interfaces; shadowing

Non-virtual base class functions
--------------------------------
Every non-virtual base class function defines a
**mandatory interface** for all derived classes.
The language allows a derived class to implement its own version.
For example:

.. code-block:: cpp

   struct B {
     void foo();
   };
   struct D: public B { 
     void foo();        // derived class D has its own version
   };

If class ``D`` implements its own version of ``foo``,
then this is **not** an ``override``.
This is called *shadowing* and is often a bug.

The problem is this:

- An instance of ``B`` will always call ``B::foo()``
- An instance of ``D`` will always call ``D::foo()``
- An instance of ``D`` in a container of pointers to ``B``
  will call ``B::foo()``.

  New programmers are often caught off guard by this behavior.

  Most modern compilers will warn about this.

Even if the programmer is careful to ensure the contract defined
by ``B::foo()`` is also met by struct D,
there is no guarantee this can't change in the future.
There is no way to know what else may depend on the contract 
defined by ``B::foo`` or any if its invariants.

In general, if a derived class can't use the existing mandatory
interface defined by a base class,
then it probably shouldn't be a derived class.

Muliple inheritance
-------------------
C++ allows for a single class to inherit capabilities from more than 1 class.


-----

.. admonition:: More to Explore

   - `Ineritance basics 
     <https://isocpp.org/wiki/faq/basics-of-inheritance>`__
     from the C++ FAQ
   - Effective C++ #35: Make sure public inheritance models "IS-A"
   - Effective C++ #36: Never redefine inherited non-virtual functions

