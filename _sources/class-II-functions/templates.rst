..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: templates; class

Class templates
===============
C++ allows writing class templates using the same syntax used to write function templates.
We use templates in classes for the same reason we use templates in functions:
when we want to use variables without making a commitment to a fixed type.
A class template is **not** a class.
It defines instructions the compiler uses to create classes as needed.
No code is generated from a source file that contains only template definitions. 
In order for any code to appear, a template must be instantiated: 
the template arguments must be provided so that the compiler can generate an actual class.
Class template type cannot be deduced from the passed parameters
in the way that function templates may.

.. code-block:: cpp

   template <class T, class U>
   struct pair {
     T first;
     U second;
   };

   int main() {
     pair<char, int> symbol = {'A', 65};
     return symbol.second;
   }

A class template allows to define a family of classes that performs the same
behaviors on many different types.
Container classes are the canonical examples of how templates
can make code maintenance easier.
The following class is a 'bag' - a general purpose container.

.. code-block:: cpp

   template <class T>
   class bag {
       std::vector<T> data;

     public:
       void add(T item);
       void erase(bag<T>::iterator item);
       void swap(bag<T> item);
   };



-----

.. admonition:: More to Explore

   TBD

