..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: keyword; enum
   single: enumerated types

Enumerated types
================

An :cref:`enum` (enumerated type) is a distinct type whose value is restricted 
to a range of values (see below for details), 
which may include several explicitly named constants ("enumerators"). 
The values of the constants are values of an integral type known as the 
*underlying type* of the enumeration.

There are two distinct kinds of enumerations: 

unscoped enumeration
    declared with the keyword ``enum`` 
    
scoped enumeration
    declared with the enum-key ``enum class`` or ``enum struct`` 

Unscoped enumerations
---------------------

Each enumerator becomes a named constant of the enumeration's type 
(that is, name), 
visible in the enclosing scope, 
and can be used whenever constants are required.

.. code-block:: cpp

   enum color { red, green, blue };
   color r = red;
   switch(r)
   {
     case red  : std::cout << "red\n";   break;
     case green: std::cout << "green\n"; break;
     case blue : std::cout << "blue\n";  break;
   }

Each enumerator is associated with a value of the underlying type. 
When initializers are provided in the enumerator-list, 
the values of enumerators are defined by those initializers. 
If the first enumerator does not have an initializer, the associated value is zero. 
For any other enumerator whose definition does not have an initializer, 
the associated value is the value of the previous enumerator plus one.

Values of unscoped enumeration type are implicitly-convertible to integral types. 
If the underlying type is not fixed, the value is convertible to the first type 
from the following list able to hold their entire value range: 
``int``, ``unsigned int``, ``long``, ``unsigned long``, ``long long``, or ``unsigned long long``. 
If the underlying type is fixed, the values can be converted to their promoted underlying type.

.. code-block:: cpp

   enum color { red, yellow, green = 20, blue };
   color c = red; // c  implicitly converts to 0
   int n = blue;  // n == 21

Consider the following program:

.. code-block:: cpp

   #include <iostream>
   enum Direction { north, south, east, west };

   static void show_direction(const int direction) {
     std::cout << "Direction: " << direction << "\\n";
   }

   int main() {
     Direction dir = west;
     show_direction(dir);
     int num = dir;
     show_direction(num);

     for (int i = north; i < 8; ++i) show_direction(i);
     return 0;
   }

.. reveal:: reveal-enum-issues
   :showtitle: What problems does this program have?

   #. The unscoped enum ``Direction`` is not type safe

      - Any integral type can be assigned to it

   #. The line ``int num = dir;`` assigns a direction to an int
   #. The for loop is unaware that there are only 4 directions, not 8.
   #. Function ``show_direction`` implies it takes a direction as an argument,
      but any integral type will be processed without complaint
   #. The function ``show_direction`` can't print a human readable direction.
      It can only print a number.

Scoped enums were introduced to address these specific shortcomings.

Scoped enumerations
-------------------
Like unscoped enumerations,
each enumerator becomes a named constant of the enumeration's type 
visible in the enclosing scope, 
and can be used whenever constants are required.

Unlike unscoped enums, scoped enums do **not** implicitly convert to integral types,
but can be converted with a static or explicit cast.

.. code-block:: cpp

   enum class Color { red, green = 20, blue };
   Color r = Color::blue;
   switch(r)
   {
     case Color::red  : std::cout << "red\n";   break;
     case Color::green: std::cout << "green\n"; break;
     case Color::blue : std::cout << "blue\n";  break;
   }
   // int n = r;                // error: no implicit int conversion
   int n = static_cast<int>(r); // OK, n = 21


All the C++ enumerated types are very simple compared to the same types in other languages.
However, it is easy to add features as needed.
Given the following scoped enum:

.. code-block:: cpp

   // If this were declared enum struct, nothing in this example changes...
   //
   enum class Direction { NORTH, SOUTH, EAST, WEST };

We can implement a stream overload to allow printing enum members with 
human readable strings:

.. code-block:: cpp

   std::ostream& operator<<(std::ostream& os, const Direction& rhs) {
     std::string dir;
     switch (rhs) {
       case Direction::NORTH: dir = "NORTH"; break;
       case Direction::EAST:  dir = "EAST";  break;
       case Direction::SOUTH: dir = "SOUTH"; break;
       case Direction::WEST:  dir = "WEST";  break;
     }
     return os << dir;
   }


And an array allows the enum to be used in a range for loop:

.. code-block:: cpp

   const std::array<Direction,4> directions =
   {
     {
       Direction::NORTH,
       Direction::EAST,
       Direction::SOUTH,
       Direction::WEST
     }
   };

Now the show directions program looks like this:

.. code-block:: cpp

   #include "Direction.h"
   #include <iostream>

   void show_direction(const Direction d) {
     std::cout << "Direction: " << d << std::endl;
   } 
     
   int main() {
     Direction dir = Direction::WEST;
     std::cout << "Show one direction: " << std::endl;
     show_direction(dir);
     
     std::cout << "Loop through all directions: " << std::endl;
     for (const auto& d: directions) {
       show_direction(d);
     }
     return 0;
   } 



Another example uses the same techniques to build a deck of cards.

.. tabbed:: cards

   .. tab:: Source

      .. literalinclude:: cards.txt
         :language: cpp
         :lines: 5-
         :dedent: 3

   .. tab:: Run it

      .. include:: cards.txt
  






-----

.. admonition:: More to Explore

   TBD

