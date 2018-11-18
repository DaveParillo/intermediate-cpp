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

.. index:: unified modeling langauage; UML
   pair: class design; visualization 
   pair: class design; UML

Unified modeling language
==========================
The Unified Modeling Language, or UML, is an industry standard graphical
notation for describing and analysing software designs.
The symbols and graphs used in the UML are an outgrowth of efforts in the
1980's and early 1990's to devise standards for Computer-Aided
Software Engineering (CASE).
UML represents a **unification** of these efforts. 
In 1994 - 1995 several leaders in the development of modeling languages,
Grady Booch, Ivar Jacobson, and James Rumbaugh, attempted to unify
their work.
To eliminate the method fragmentation that they concluded was impeding 
commercial adoption of modeling tools, they developed UML, 
which provided a level playing field for all tool vendors. 

UML has been accepted as a standard by the Object Management Group [#]_ (OMG). 
The OMG is a non-profit organization with about 700 members that sets standards 
for distributed object-oriented computing.

UML was initially largely funded by the employer of Booch, Jacobson & Rumbaugh,
aka *the three amigos*, Rational Software, which was sold to IBM in 2002.

A software model is any textual or graphic representation of an aspect of a software
system.  This could include requirements, behavior, states or how the system is
installed.  The model is **not** the actual system, rather it describes different
aspects of the system to be developed.
UML defines a set of diagrams and corresponding rules that can be used 
to model a system.  The diagrams in the UML are generally divided into two
broad categories or *views*, **static** and **dynamic**.

This course does not provide anywhere near a comprehensive review of the UML.
The intent is to introduce you to the basics you need to understand the
designs presented in this course.  
Since there is an excellent chance you will encounter the UML or something
very similar to it in your professional career and the diagrams used in this
course are used not only in the UML, but in other modeling systems as well [#]_ [#]_ [#]_.

Static and Dynamic diagrams
---------------------------

Static diagrams emphasize the static structure of the system, its
objects' attributes, methods, and relationships.  
Static views include:

- Class diagrams and 
  
- Deployment diagrams

In this course we are primarily interested in class diagrams.

Dynamic diagrams emphasize the dynamic behavior of a system, its states or modes
and the collaborations between objects.  Dynamic views include:

- Sequence diagrams

- State diagrams

- Use Case diagrams

.. index::
   pair: graph; class diagram

Class diagrams
--------------
.. sidebar:: A simple class

   .. graphviz:: 
      :alt: The simplest class diagram

      digraph "simple"
      {
        simple  [fontname="BitstreamVeraSans",
                 fontsize="10",
                 label="{SimpleClass\n||}",
                 height=0.2,
                 width=0.4,
                 color="black",
                 fillcolor="lightblue",
                 shape=record,
                 style="filled"];
      }

The **class diagram** is one of the most commonly encountered diagrams.
It describes the types of objects in a system and the kinds of static 
relationships that exist among them.

.. index::
   pair: class diagram; visibility

In UML, a class is represented by a rectangle with one or more
horizontal compartments.
By convention, the class name starts with a capital letter.
Another convention is to italicize the class name if the class is an
*AbstractClass*.
The top compartment holds the name of the class. The name of the class
is the only required field in a class diagram. 
The middle compartment of the class rectangle holds the list of the
class attributes. 
The bottom compartment holds the list of methods.

Some editors will omit the middle and lower compartments if they are blank.

Attribute and method visibility is indicated using a single character
before the class member.
Static members are indicated by underlining the member name.
The UML term for static members is *classifier members*.

.. graphviz:: 
      :alt: Class attributes

      digraph "simple"
      {
        simple  [fontname="BitstreamVeraSans",
                 fontsize="10",
                 label="{Car\n|-speed: float = 0\l-direction: float = 90\l|+ speed(accelerationRate: float): void\l+ speed(): float\l+ heading(steeringRate: float): void\l+ heading(): float\l}}",
                 height=0.2,
                 width=0.4,
                 color="black",
                 fillcolor="lightblue",
                 shape=record,
                 style="filled"];
      }


The UML syntax for an attribute is:
*visibility name : type = defaultValue*

======    ==========
Symbol    Visibility
======    ==========
``+``     Public
``-``     Private
``#``     Protected
``/``     Derived
======    ==========

Class diagrams use different notational standards to display class inheritance,
class composition, and other associations.


.. index::
   pair: UML; inheritance
   pair: UML; generalization

**Inheritance relationships**

.. sidebar:: Inheritance

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
              fillcolor="white",
              shape=record,
              style="filled"];
        person [
          label="{Person\n}", fillcolor="lightblue"];
        person -> student;
        student [
          label="{Student\n}"];
        person -> teacher;
        teacher [label="{Teacher\n}"];
      }

   Generalization in action: 
   
   Students and Teachers are both People

In the UML, the Inheritance relationship is referred to as a *generalization*.

Inheritance is drawn as an empty arrow, 
pointing from the derived class to the base class.
The base class is considered a *generalization* of the derived class,
so it makes sense that the arrow should point to the base class.
The arrow is trying to say that the derived class **IS A** type of the base class.

In the example diagram, two classes inherit from the more general base class.
Some UML drawing tools draw each inheritance line as a separate straight line
to the base class, other merge lines when possible.  
This has no impact on the meaning of the relationship.
A merged line showing relationships does not imply that the two  derived classes
are in any way interdependent, other than they share a common ancestor.

.. index::
   pair: UML; realization

**Realization relationships**

A *realization* is a relationship between two model elements, 
in which one model element (the client) realizes (implements or executes) the 
behavior that the other model element (the supplier) specifies.

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
           style="dotted",
           color="midnightblue"];
     node [fontname="BitstreamVeraSans",
           fontsize="10",
           height=0.2,
           width=0.4,
           color="black",
           fillcolor="white",
           shape=record,
           style="filled"];
     person [
       label="{\<\<interface\>\>\nPerson\n|+firstName\l+lastName\l|getName(): string\l}", 
       fillcolor="lightblue"];
     person -> student;
     student [
       label="{Student\n|-major\l}"];
     person -> teacher;
     teacher [label="{Teacher\n|-salary\l}"];
   }

The UML graphical representation of a realization is a hollow triangle 
shape on the interface end of the dashed line (or tree of lines) that 
connects it to one or more implementers. 

In this course, we are primarily concerned with relationships between
classes.
Note the addition at the top of the **Person** class: ``<<interface>>``.
The angle brackets define a *stereotype*.
The stereotype allows UML modelers to extend the vocabulary of a model
element or to be more specific about the role or purpose of a model
element.
In this case, the stereotype ``<<interface>>`` tells us this is not
just any old class, but this class defines an *interface*.

Notice the similarity between the **generalization** relationship and
the **realization** relationship.
**Generalization** always models **inheritance** relationships between
classes.
**Realization** always models **interface implementation** 
relationships between classes.


.. index::
   pair: UML; association

**Association**

An association represents a relationship between two classes. 

.. sidebar:: Association

   .. graphviz:: 
      :alt: association

      digraph "association"
      {
        edge [fontname="BitstreamVeraSans",
              fontsize="10",
              labelfontname="BitstreamVeraSans",
              labelfontsize="10",
              arrowhead="vee",
              minlen=4,
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
        Author -> Book [constraint=false, headlabel="1..* ", taillabel=" 0..*"];
      }

An association between two classes is shown by a line joining the two classes. 
Association indicates that one class uses an attribute
or calls methods of another class. 
If there is no arrow on the line,
the association is taken to be bi-directional, 
that is, both classes hold information about the other class. 
A unidirectional association is indicated by an arrow pointing from the
object which holds to the object that is held. 

Association is the least specific type of association.
It is used when the classes each have their own life cycle 
and are independent of each other.
For example, two classes might be related because one or both takes the
other as a parameter to a method.

.. code-block:: cpp

   struct Author {
     void write(Book b) { 
       // do something with the Book
     }
   };


.. index::
   pair: association; multiplicity

*Multiplicity*

Associations have a multiplicity (sometimes called cardinality) that 
indicates how many objects of each class can legitimately be involved in a given relationship. 
Multiplicity is expressed using an ``n..m`` notation near one end of the association line, 
close to the class whose multiplicity in the association we want to show. 

Here ``n`` refers to the minimum number of class instances that may be involved
in the association, and ``m`` to the maximum number of such instances. 
If ``n = m`` only the ``n`` value is shown. 
An optional relationship is expressed by writing ``0`` as the minimum number.
The wildcard character ``*`` is used to represent the concept *zero or more*.

Example multiplicity values

============================================   ===================
Cardinality and modality                       Multiplicity Values
============================================   ===================
One-to-one and mandatory                       ``1``
One-to-one and optional                        ``0..1``
One-to-many and mandatory                      ``1..*``
One-to-many and optional                       ``*``
With lower bound ``l`` and upper bound ``u``   ``l..u``
With lower bound ``l`` and no upper bound      ``l..*``
============================================   ===================

.. index::
   pair: UML; aggregation

**Aggregation**

If an association conveys information that one object is part of another object,
but their lifetimes are independent (they could exist independently), then
this relationship is called aggregation. 


.. sidebar:: Aggregation

   .. graphviz:: 
      :alt: aggregation

      digraph "aggregation"
      {
        edge [fontname="BitstreamVeraSans",
              fontsize="10",
              labelfontname="BitstreamVeraSans",
              labelfontsize="10",
              arrowtail="odiamond",
              dir="back",
              minlen=4,
              style="solid",
              color="black"];
        node [fontname="BitstreamVeraSans",
              fontsize="10",
              height=0.2,
              width=0.4,
              color="black",
              fillcolor="lightblue",
              shape=box,
              style="filled"];
        Department -> Professor [constraint=false, headlabel="1..* "];
      }

For example, a university owns various departments (e.g., chemistry), 
and each department has a number of professors.
If the university closes, the departments will no longer exist,
but the professors in those departments will continue to exist.
Therefore, a University can be seen as a composition of departments,
whereas departments have an aggregation of professors. 
In addition, a Professor could work in more than one department,
but a department could not be part of more than one university.
For example:

.. code-block:: cpp

   struct Department {
     Professor* prof;    // non-owning pointer to a professor
   };

A ``Department`` **has-a** ``Professor``,
but the professor exists independently of any department.

.. index::
   pair: UML; composition

**Compositon**

.. sidebar:: Composiiton

   .. graphviz:: 
      :alt: composition

      digraph "composition"
      {
        edge [fontname="BitstreamVeraSans",
              fontsize="10",
              labelfontname="BitstreamVeraSans",
              labelfontsize="10",
              arrowtail="diamond",
              dir="back",
              minlen=4,
              style="solid",
              color="black"];
        node [fontname="BitstreamVeraSans",
              fontsize="10",
              height=0.2,
              width=0.4,
              color="black",
              fillcolor="lightblue",
              shape=box,
              style="filled"];
        Car -> Engine [constraint=false, headlabel="1..1 "];
      }


   A car not only *has* an engine, it *owns* it.

Composition is even more specific than aggregation.
Like aggregation, one class *has an* instance of another class,
but the child class's instance life cycle is dependent on the parent class's instance life cycle. 
In other words, when the parent dies, the child dies.

.. index::
   pair: UML; Martin Fowler


.. tip::  
   **Use aggregation judiciously**

   .. epigraph::

      Few things in the UML cause more consternation than aggregation and composition,
      in particular how they vary from regular association.

      The full story is muddled by history.
      In the pre-UML methods there was a common notation of defining some form
      of part --- whole relationships.
      The trouble was that each method defined different semantics for these
      relationships (although to be fair, some of these were pretty semantics free).

      So when the time came to standardize, lots of people wanted part --- whole
      relationships, but they couldn't agree on what they meant.
      So the UML introduced two relationships.
   
      **aggregation** (*white diamond*) has no semantics beyond a regular association.
      It is, as Jim Rumbaugh puts it, a modeling placebo.  People can, and do,
      use it --- but there are no standard meanings for it.
      I would advise not using it yourself without some form of explanation.

      **composition** (*black diamond*) does carry semantics.
      The most particular is that an object can only be part of one composition relationship.
      So even if both windows and panels can hold menu bars, any instance of menu bar
      must be held by only one whole.  This is a constraint you can't easily
      express with the regular multiplicity markers.

      -- Martin Fowler, `AggregationAndComposition blog post <http://martinfowler.com/bliki/AggregationAndComposition.html>`_  17 May 2003.


.. index::
   pair: UML; dependency

**Dependency**

Dependency is the weakest relationship.
It represents a reference to class passed in as 
a method parameter to a function in another class. 
For example, an instance of class Book is passed as a parameter
to a function in class Customer:

.. code-block:: cpp

   struct Book {};

   struct Customer {
      void purchase(Book b) {}
   };

The *Customer* class requires the *Book* class to function, but doesn't own it.
The caller of the purchase method is required to supply a *Book*.

This type of relationship is represented with a dashed line:

.. graphviz:: 
   :alt: dependency

   digraph "dependency"
   {
     edge [fontname="BitstreamVeraSans",
           fontsize="10",
           labelfontname="BitstreamVeraSans",
           labelfontsize="10",
           arrowhead="vee",
           minlen=4,
           style="dashed",
           color="black"];
     node [fontname="BitstreamVeraSans",
           fontsize="10",
           height=0.2,
           width=0.4,
           color="black",
           fillcolor="lightblue",
           shape=box,
           style="filled"];
     Customer -> Book [constraint=false];
   }

As discussed in the introduction to this section,
the UML is much more involved than simple class diagrams.
For our purposes, which currently are limited to visualizing
inheritance and composition, this is enough.

-----

.. admonition:: More to Explore

   - Scott Ambler has a good
     `introduction to object oriented programming in general and UML diagrams 
     <http://www.agiledata.org/essays/objectOrientation101.html>`__
   - More example diagrams and explanations can be viewed at `uml-diagrams.org 
     <http://www.uml-diagrams.org/class-diagrams-overview.html>`__.

.. topic:: Footnotes

   .. [#] `OMG Homepage <http://www.omg.org/>`_
   .. [#] `Data Flow Diagrams <http://www.infoarchgroup.com/qrdfd.htm>`_
   .. [#] `The Integration DEFinition (IDEF) model family <http://www.idef.com>`_
   .. [#] `DoD Architecture Framework <http://dodcio.defense.gov/Portals/0/Documents/DODAF/DoDAF_v2-02_web.pdf>`_

