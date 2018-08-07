..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   single: classes

Classes
=======

Up until now, we have emphasized :term:`procedural` programming;
in which programs are composed of *procedures*.
The program executes procedures (functions) one at a time,
placing unfinished functions on the call stack, if needed,
working towards a desired end state.
Functions usually exist independently from each other.
C++ does provide some tools to make working with free functions easier.
Function can be grouped in a :cref:`namespace declaration`,
or in a single compilation unit.
Function overloads allow functions that perform the same task,
but on different types to be given the same name.

When procedural programs run,
data is passed around or returned from functions.
On very large programs, even these tools can fall short.

Every function, is effectively public.
Every function has access to every other function,
even if there is no good reason to call them.

In contrast to :term:`procedural` programming,
:term:`object-oriented programming` allows programmers to hide
data and functions within a :term:`class`.

A class defines a specific abstraction:

- A meaningful representation of data 

**and**

- The operations associated with the data

Together, the data and operations form an :term:`abstract data type`.
In other words, when you create a new class,
You are creating a new :term:`type`.

Don't let the new terms scare you.
You have been working with classes since chapter 2.
The types :cref:`std::string`, and all the sequential and associative containers,
are classes.
When designed correctly,
a class can be manipulated with the same operations as the built-in types.
Any class you create allows you to define a new type that works
with the rest of C++ and the STL as if it were built into C++.

While many classes manage their own data,
just as many classes store no data at all.
This is normal.
Because the data in a class is normally hidden,
there is no way to know if a class even **has** data without looking at the source code.

Part of the beauty of the object-oriented abstraction is that you, 
the user of the class do not need to care.
We use classes in the same way we use any built-in type: 
to get something specific done in a clear, efficient manner.


Relationship to ``struct``
--------------------------
In C++, a ``struct`` **is a** ``class`` with default public access:

.. tabbed:: talk-struct

   .. tab:: Example

      This program works because everything in a ``struct`` is publicly visible 
      to any other component in the program.

      .. literalinclude:: talk-struct.txt
         :language: cpp
         :lines: 5-
         :dedent: 3

      .. note::
      
         Two things:
        
         #. Notice the trailing semi-colon (``;``) after the definition of ``struct Talk``?

            This is required for a ``class`` or ``struct`` to compile and
            forgetting to include a trailing ``;`` is a common source of error.
         
         #. The function ``main`` accesses the function ``hello`` using the 
            `member access operator <https://en.cppreference.com/w/cpp/language/operator_member_access>`__.

            The general format is *object name* . *member name*.

   .. tab:: Run It

      .. include:: talk-struct.txt


Here we have a very similar program, but with one important change.

.. tabbed:: talk-class

   .. tab:: Example

      This program does not compile because everything in a ``class`` is **private** by default.
      Only objects of type ``Talk`` may use or even know about its private data.

      .. literalinclude:: talk-class.txt
         :language: cpp
         :lines: 5-
         :dedent: 3

   .. tab:: Run It

      .. include:: talk-class.txt

We can fix our broken ``class Talk`` by adding ``public:`` to the class.
The :cref:`access specifiers` *public* and *private* are used in a class or a struct to control
what parts of the class may be accessed from outside the class.

.. code-block:: cpp

   class Example {
     public:             // all declarations after this point are public
       void add(int x) { // member "add" has public access
         n += x;         // OK: private Example::n can be accessed from Example::add
       }
     private:            // all declarations after this point are private
       int n = 0;        // member "n" is private
   };

.. admonition:: Try this!

   - Add an access specifier to ``class Talk`` so that it compiles and runs.
   - Add an access specifier to ``struct Talk`` so that it fails with a similar error 
     as ``class Talk`` did before you modified it.
   

-----

.. admonition:: More to Explore

   - From cppreference.com

     - :cref:`Access specifiers`.

   - From C++ Core Guidelines

     - `C.1: Organize related data into structures (structs or classes)
       <http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-org>`__
     - `C.2: Use class if the class has an invariant; use struct if the data members can vary independently
       <http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-struct>`__
     - `C.3: Represent the distinction between an interface and an implementation using a class
       <http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-interface>`__
     - `C.8: Use class rather than struct if any member is non-public
       <http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-class>`__



