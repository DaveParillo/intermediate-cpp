.. Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
   and/or modify this document under the terms of the GNU Free Documentation
   License, Version 1.3 or any later version published by the Free Software
   Foundation; with Invariant Sections being Forward, and Preface,
   no Front-Cover Texts, and no Back-Cover Texts.  A copy of
   the license is included in the section entitled "GNU Free Documentation
   License".

.. Content in this section adapted from the OpenDSA eTextbook project. 
   See http://algoviz.org/OpenDSA for details.
   Copyright (c) 2014-2016 by the OpenDSA Project Contributors, and
   distributed under an MIT open source license.

.. index:: object-oriented programming; oo concepts

Object-oriented concepts
========================
Object-oriented programming (OOP) is a programming paradigm based on the 
concept of :term:`objects <object>`, which are :term:`data structures
<data structure>` that contain data,
in the form of fields (or attributes) 
and code, in the form of procedures, (or functions, or methods). 
A distinguishing feature of objects is that an object's procedures 
provide access to and modify its fields.

In object-oriented programming, computer programs are created
out of objects that interact with one another. 
There is significant diversity in object-oriented programming, 
but most popular languages are class-based, 
meaning that objects are instances of classes, 
which typically also determines their type.

Object orientation is an outgrowth of procedural programming.
Procedural programming is based upon the concept of the procedure call.
Procedures, also known as functions, subroutines, 
or methods define the computational steps to be carried out.

Any given procedure might be called at any point during a program's execution, 
including by other procedures or itself. 
Procedural programming is a list or set of instructions telling a 
computer what to do step by step and how to perform from the first 
code to the second code. 
Procedural programming languages include C, Fortran, Pascal, and BASIC.

The focus of procedural programming is to break down a programming task into 
a collection of variables, data structures, and functions. 
In object-oriented programming the primary effort
involves breaking down a programming task into 
**classes**.
Each class defines data that is commonly private.
The private data is manipulated using the publicly available functions.
The public functions define the class **interface**.

The most important distinction is that 
while procedural programming uses procedures to operate on data structures,
object-oriented programming bundles the two together, 
so an **object**, which is an **instance of a class**,
manipulates its own data.


.. index:: encapsulation, inheritance, polymorphism, abstraction
   pair: SOLID; object oriented concepts
   
Object-oriented programming principles
--------------------------------------
There are many views on the main features and motivations for object
oriented programming [#]_ [#]_.
There are 4 principles that apply to most:

:Encapsulation:
    
    Encapsulation refers to the creation of self-contained modules (classes)
    that bind processing functions to its data members. 
    The data within each class is kept private.
    Each class defines rules for what is publicly visible and
    what modifications are allowed.

:Inheritance:
    
    Classes may be created in hierarchies, and inheritance lets the 
    structure and methods in one class pass down the :term:`class hierarchy`. 
    By *inheriting* code, complex behaviors emerge
    through the reuse of code in a parent class.
    If a step is added at the bottom of a hierarchy, 
    only the processing and data associated with that unique step must be added. 
    Everything else above that step may be inherited. 
    Reuse is considered a major advantage of object orientation.


:Polymorphism:
    
    Object oriented programming lets programmers create procedures for 
    objects whose exact type is not known until runtime. 
    For example, a screen cursor may change its shape from an arrow to a 
    line depending on the program mode. 
    The routine to move the cursor on screen in response to mouse movement can 
    be written for "cursor", and polymorphism lets the right version
    for the given shape be called.

:Abstraction:
    
    An abstraction denotes the essential characteristics of an object
    that distinguish it from all other kinds of objects and thus
    provide crisply defined conceptual boundaries, relative to the
    perspective of the viewer.

    Abstraction denotes a model, a view, or some other focused representation 
    for an actual item.
    It's the development of a software object to represent 
    an object we can find in the real world. 
    Encapsulation hides the details of that implementation.

.. index:: 
   pair: encapsulation; class invariants
   pair: oo concepts; encapsulation

Encapsulation
-------------
Consider the following example:

.. code-block:: cpp

   #include <string>
   
   // A class with no encapsulation 
   struct BadShipping {
     int weight;      // in pounds
     int distance;    // in miles
     std::string address;
   };

   int main() 
   {
       BadShipping bad;
       bad.weight = -3;  // Nothing prevents me from doing this
   }


It's clearly a bad idea to allow people to set the shipping weight to
a negative value.
In this case, we say our class has *invariants*:
constraints on data that must be preserved for the class to remain valid.
In this case, the shipping weight of items must be > 0.

How can you change this class to prevent problems like this from happening?
One solution is to make the ``weight`` private and write a method
that allows the class to set limits on weight.
Unfortunately, if we had already delivered our BadShipping code, then
as you make this 'fix', you break every class that currently uses it,
including those that already obey the class invariant.
It would have been much better to deliver code that could have been more easily
changed in the first place.

The ability to change your code without breaking every class that uses
it is one of the key benefits of encapsulation.
By limiting access and hiding the implementation details of your class
to the maximum extent possible, you make it possible to change, fix,
extend, or rework your class without requiring changes in any of the
code that uses your class.

How do we ensure our code remains flexible and maintainable?

- Keep fields hidden using a *private* access modifier
- Make *public accessor methods* and force callers to use them
  by hiding your fields.
- Encourage programming to *interfaces* instead of *implementation*.
  More on this later.

Compare our first example with the following:

.. code-block:: cpp

   // A class with simple encapsulation 
   class BetterShipping {
     public:
       unsigned weight()   { return weight_; }
       void weight(int value) { 
         weight_ = value; 
       }

       unsigned distance() { return distance_; }
       std::string address() {
         return address_;
       }
       // other mutators ommitted . . .
     private:
       unsigned weight_;      // in pounds
       unsigned distance_;    // in miles
       std::string address_;
   };


You might be thinking 
"Hey! How is this any better than the first example?"
We added methods to set and get the weight, but added no new
capability.
What have we gained?

We have gained quite a bit.
Now we are free to change our minds about how weight values are set
and retrieved.
Even though we aren't doing anything now, we are free to change the
implementation later and no calling class will know.

Good OO design demands thinking about the future.
Which brings us to our final example.
No classes would need to be modified to add the new capability below.

.. code-block:: cpp

   #include <algorithm>
   #include <string>

   static constexpr int min_weight = 1;

   class EvenBetterShipping {
     public:
       EvenBetterShipping() = default;
       EvenBetterShipping(int w, int d, std::string a) :
         weight_{std::max(min_weight, w)}, distance_{d}, address_{a}
       {}

       int  weight()          { return weight_; }
       void weight(int value) { 
         weight_ = std::max(min_weight, value);  // no upper limit on weight
       }


       int distance() { return distance_; }
       std::string address() {
         return address_;
       }
     private:
       int weight_ = 2;        // in pounds
       int distance_ = 100;    // in miles
       std::string address_ = "My mom's house";
   };


.. index::
   pair: oo concepts; inheritance

Inheritance
-----------
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

It is common to draw inheritance relationships like this:

.. index::
   pair: graph; shape inheritance

.. graphviz:: 
   :alt: Shape inheritance

   digraph "shape"
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
           fillcolor="white",
           shape=record,
           style="filled"];
     shape [
       label="{shape\n||+ ~shape()\l+ draw()\l+ erase()\l+ move()\l}",
       fillcolor="lightblue"];
     shape -> circle;
     circle [
       label="{circle\n||+ draw()\l+ erase()\l}"];
     shape -> rect;
     rect [label="{rectangle\n||+ draw()\l+ erase()\l}"];
     shape -> tri;
     tri [label="{triangle\n||+ draw()\l+ erase()\l}"];
   }

This is different from extending classes through :term:`composition`.
More comparisons between inheritance and composition will be made in 
later sections.


.. index:: runtime polymorphism; compile-time polymorphism
   pair: oo concepts; polymorphism
   
Polymorphism
------------

:term:`Polymorphism` is often referred to as the third pillar 
of object-oriented programming, after encapsulation and inheritance. 
Polymorphism is a Greek word that means "many-shaped" and polymorphism 
itself comes in two distinct forms:

- :term:`Runtime polymorphism`

  Base classes may define and implement abstract, or virtual methods, 
  and derived classes can override them, which means they provide their own 
  definition and implementation. 
  At runtime, when client code calls the method, the type is resolved and invokes 
  that override of the virtual method. 
  Thus in your source code you can call a method on a base class, and cause a derived 
  class's version of the method to be executed.

  At run time, objects of a derived class may be treated as objects of a base class 
  in places such as method parameters and collections or arrays. 
  When this occurs, the object's declared type is no longer identical to its 
  runtime type.

  Note that a derived class may be treated as any type in its inheritance hierarchy.
  Also, it is perfectly valid for an overloaded method to be overridden.

- :term:`Compile-time polymorphism`

  Compile-time polymorphism is simply method overloading. 
  **Overloaded** methods have the same method name but 
  different number of arguments or different types of arguments or both.

.. index::
   pair: oo concepts; polymorphism

Abstraction
-----------

One of the key advantages of object oriented languages over :term:`procedural` 
languages is that objects act as metaphors for the real-world. 
In other words, objects *model* the real world.
In a procedural language, tasks are executed in functions or procedures and the
data that the functions operate on is stored elsewhere.
A better way to manage the complexity of large programs is to 
keep the data in a program and the operations allowed on that data 
in a cohesive logical unit.  
A program describing a car might perform basic tasks: 
steer, speed up, slow down,
but also needs to store information about the car:
current speed, direction, cruise control setting, etc.

If you wrote your car driving program in a procedural language, you
would likely require different functions to control each of the car
behaviors.
You might create functions for ``turnCarOn()``, ``turnCarOff()``,
``accelerate()``, ``steer()``, and others.
You would also need variables to store the current state of the car.
Although it's perfectly valid to construct such a car in a procedural
language, these functions and variables we have created only exist as
a whole entity, a *car* in the mind of the programmer who created it.  
The idea that individual units within a program each have a specific
role or responsibility is called :term:`cohesion` and is difficult to
achieve in procedural programs.

For very large programs, which might contain hundreds or even
thousands of entities, lack of cohesion can introduce errors, make
programs more difficult to understand and maintain, and complicate the
development of very large programs.


-----

.. admonition:: More to Explore

   - TBD

.. topic:: Footnotes

   .. [#] `Wikipedia OO fundamental concepts <https://en.wikipedia.org/wiki/Object-oriented_programming#Fundamental_features_and_concepts>`_
   .. [#] `SOLID <http://en.wikipedia.org/wiki/SOLID_%28object-oriented_design%29>`_ Object oriented design

