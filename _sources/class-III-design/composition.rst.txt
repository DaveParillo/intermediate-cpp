..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   single: class design
   pair: classes; composition

Composition
===========
Every class definition also defines a new :term:`type`
that becomes available for use anywhere a built in type
could be used.

Composition is also fundamental to *every* language.
Even if a language does not support composition,
people still think in terms of parts and components.
It would be impossible to break down complex problems into 
solvable chunks without composition.

The simplest way to incorporate a class is to just use the
type directly in another class.
A class can be made up of any number and type of other objects, 
in any combination needed to achieve the functionality 
desired in the new class. 
Because this results in composing a new class from existing classes,
this concept is called *composition*.
Composition is often described as a “has-a” relationship, 
as in “a car has an engine.”

Composition models the relation where two object lifetimes are linked:

- When a Car is created, it comes with an Engine.
- The Engine can exist only as long as the Car exists.
- The Engine exists solely for the benefit of the Car that contains the Engine
- No other car can use this engine.
- When the Car is destroyed, the Engine is destroyed.

Composition provides a great deal of flexibility.
Member objects are usually private,
making them inaccessible to the users of a type.
This enables changing those members without disturbing existing client code.
You can also change the member objects at runtime,
to dynamically change the behavior of your program.
Inheritance, which is described next,
does not have this flexibility since the compiler must place compile-time
restrictions on classes created with inheritance.

Because inheritance is so important in object-oriented programming
it is often highly emphasized,
and a new programmer might think that inheritance should be used everywhere.
This can result in awkward and overly-complicated designs.
Instead, prefer composition when creating new classes,
since it is simpler and more flexible.
If you take this approach, your designs will stay cleaner.


-----

.. admonition:: More to Explore

   - Effective C++ Item #40: Model HAS-A using composition
     Note that Meyers uses the term *layering* as a synonym for composition.
   - 

