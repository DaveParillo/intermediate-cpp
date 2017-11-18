..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: free store
   pair: pointers; free store

Free store pointers
===================

So far, all of our variables have been created on the :term:`stack`.
Another way to say this is our variables have *automatic storage duration*.
Variables exist only as long as the scope in which they were created.
Sometimes, we need to create objects with dynamic storage duration, 
that is, objects whose lifetime is not limited by the scope in which they were created.

One way to do this is to use the ``new`` keyword to create objects on the :term:`free store`.
The free store is a system-provided memory pool for variables whose lifetime is 
directly managed by the programmer.
Compare to our experiences so far where variables were *automatically*
managed by the system, not by the programmer.

The new operator takes a type and (optionally) a set of initializers for that type as its arguments.
It returns a pointer to an (optionally) initialized object of its type:

.. code-block:: cpp

   struct Point {
        double x = 0;  // member values is a C++11 feature
        double y = 0;
   };

   int main() {
     int* p1 = new int;     // allocate 1 uninitialized int
     int* p2 = new int[3];  // allocate 3 uninitialized ints
     int* p3 = new int(5);  // allocate 1 int initialized to 5
     int* p4 = new int{5};  // allocate 1 int initialized to 5, C++11 or later
     int* p5 = new int();   // allocate 1 int initialized to 0

     Point* pt1 = new Point;          // allocate a default constructed Point 
     Point* pt2 = new Point();        // allocate a default constructed Point 
     Point* pt3 = new Point[3];       // allocate 8 default constructed Points
   }

Step though
   `example 1 here <http://pythontutor.com/cpp.html#code=struct%20Point%20%7B%0A%20%20double%20x%20%3D%200%3B%20%20//%20member%20values%20is%20a%20C%2B%2B11%20feature%0A%20%20double%20y%20%3D%200%3B%0A%7D%3B%0A%0Aint%20main%28%29%20%7B%0A%20int*%20p1%20%3D%20new%20int%3B%20%20%20%20%20//%20allocate%201%20uninitialized%20int%0A%20int*%20p2%20%3D%20new%20int%5B3%5D%3B%20%20//%20allocate%203%20uninitialized%20ints%0A%20int*%20p3%20%3D%20new%20int%285%29%3B%20%20//%20allocate%201%20int%20initialized%20to%205%0A%20int*%20p4%20%3D%20new%20int%7B5%7D%3B%20%20//%20allocate%201%20int%20initialized%20to%205,%20C%2B%2B11%20or%20later%0A%20int*%20p5%20%3D%20new%20int%28%29%3B%20%20%20//%20allocate%201%20int%20initialized%20to%200%0A%0A%20Point*%20pt1%20%3D%20new%20Point%3B%20%20%20%20%20%20%20%20%20%20//%20allocate%20a%20default%20constructed%20Point%20%0A%20Point*%20pt2%20%3D%20new%20Point%28%29%3B%20%20%20%20%20%20%20%20//%20allocate%20a%20default%20constructed%20Point%20%0A%20Point*%20pt3%20%3D%20new%20Point%5B3%5D%3B%20%20%20%20%20%20%20//%20allocate%208%20default%20constructed%20Points%0A%7D&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D>`_

In all of the above cases,
since the ``new`` operator returns a pointer to an object of its type,
the initialization could use ``auto``.

.. code-block:: cpp

   auto pt1 = new Point;

Use the ``delete`` operator to free memory allocated using ``new``:

.. code-block:: cpp

   delete   p1;  // free memory allocated for p1
   delete[] p4;  // free array memory

   delete   pt2;  // same syntax is used for user defined types also
   delete[] pt3;





STL memory management
---------------------


TBD

-----

.. admonition:: More to Explore

   - `Free-store managment FAQ <https://isocpp.org/wiki/faq/freestore-mgmt>`_
   - From: cppreference.com: 
     `Operator new <http://en.cppreference.com/w/cpp/language/new>`_ and 
     `delete <http://en.cppreference.com/w/cpp/language/delete>`_. 
   - `Descriptions of lambda expressions` <https://msdn.microsoft.com/en-us/library/dd293608.aspx>`_ from Microsoft's MSDN




