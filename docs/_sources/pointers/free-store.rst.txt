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

One way to do this is to use the :cref:`operator new` to create objects on the :term:`free store`.
The free store is a system-provided memory pool for variables whose lifetime is 
directly managed by the programmer.
Compare this to our experiences so far where variables were *automatically*
managed by the system, not by the programmer.

The ``new`` operator takes a type and (optionally) a set of initializers for that type as its arguments.
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
     Point* pt3 = new Point[3];       // allocate 3 default constructed Points
   }

Step through `example 1 here <http://pythontutor.com/cpp.html#code=struct%20Point%20%7B%0A%20%20double%20x%20%3D%200%3B%20%20//%20member%20values%20is%20a%20C%2B%2B11%20feature%0A%20%20double%20y%20%3D%200%3B%0A%7D%3B%0A%0Aint%20main%28%29%20%7B%0A%20int*%20p1%20%3D%20new%20int%3B%20%20%20%20%20//%20allocate%201%20uninitialized%20int%0A%20int*%20p2%20%3D%20new%20int%5B3%5D%3B%20%20//%20allocate%203%20uninitialized%20ints%0A%20int*%20p3%20%3D%20new%20int%285%29%3B%20%20//%20allocate%201%20int%20initialized%20to%205%0A%20int*%20p4%20%3D%20new%20int%7B5%7D%3B%20%20//%20allocate%201%20int%20initialized%20to%205,%20C%2B%2B11%20or%20later%0A%20int*%20p5%20%3D%20new%20int%28%29%3B%20%20%20//%20allocate%201%20int%20initialized%20to%200%0A%0A%20Point*%20pt1%20%3D%20new%20Point%3B%20%20%20%20%20%20%20%20%20%20//%20allocate%20a%20default%20constructed%20Point%20%0A%20Point*%20pt2%20%3D%20new%20Point%28%29%3B%20%20%20%20%20%20%20%20//%20allocate%20a%20default%20constructed%20Point%20%0A%20Point*%20pt3%20%3D%20new%20Point%5B3%5D%3B%20%20%20%20%20%20%20//%20allocate%203%20default%20constructed%20Points%0A%7D&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D>`_.

In all of the above cases,
since the ``new`` operator returns a pointer to an object of its type,
the initialization could use ``auto``.

.. code-block:: cpp

   auto pt1 = new Point;

The :cref:`operator new` allocates memory.
When finished with the free-store memory,
we return it to the pool of available memory using 
the :cref:`operator delete`:

.. code-block:: cpp

   struct Point {
        double x = 0;  // member values is a C++11 feature
        double y = 0;
   };

   int main() {
     int* p1 = new int;
     int* p2 = new int[5];

     Point* pt_x = new Point;
     Point* points = new Point[3];

     delete   p1;  // free memory allocated for a single object
     delete[] p2;  // free array memory

     delete   pt_x;  // same syntax is used for user defined types also
     delete[] points;
   }

There should always be exactly 1 ``delete`` for every pointer returned by ``new``.

.. note::

   There are two forms of ``delete``:

   - ``delete p`` frees the memory for a single object allocated using ``new``
   - ``delete[] p`` frees the memory for an array of objects allocated using ``new``

   Mistakes over which version of delete to use is a common source of error.

Other mistakes related to delete include deleting the same pointer twice, 
or not deleting the pointer at all.

Deleting the same pointer twice is a problem because it leads to undefined
or unpredictable behavior.
The problem rarely arises in very small or short programs.
However, in larger programs, strange or unpredictable events may happen
long after the statements that perform the double delete are executed.
Programs that free memory twice have created real-world
`security vulnerabilities <http://www.kb.cert.org/vuls/id/650937>`_.

Simply choosing to never delete a pointer on the theory that 
"well, at least my program won't crash" is not a good idea either.
All computers have a finite amount of memory.
Depending on how long your program needs to run, 
never returning unused memory back to the memory *pool* is
referred to as a :term:`memory leak`.
Also, remember that computers are *fast*.
Depending on what your program does, 
even a short program can run out of memory before accomplishing all of its goals.

.. index:: memory management
   single: smart pointer; auto_ptr; unique_ptr; shared_ptr

STL memory management
---------------------
When memory is allocated using :cref:`operator new`,
eventually it must be recovered using :cref:`operator delete`.
When only a few lines of code are requesting memory,
this is not a major problem.
However, real world programs often request hundreds or thousands
of blocks of memory.
Keeping track of all this memory and when it should be freed can be labor intensive.
Moreover, the consequences of an error are high: program crashes or corrupted data.

Many languages, such as Java, Python, Ruby, and JavaScript take this problem 
completely out of the hands of programmers.
In these languages, memory is never explicitly deleted by the program.
Rather it is managed by a :term:`garbage collector <garbage collection>`,
which is responsible for cleaning up after the program
(removing its :term:`garbage`).

C++ does not provide a garbage collection mechanism by default.
Given that memory management is such a problem, 
does the STL provide any resources to help solve it?

Yes.

The C++ Standard Template Library provides a family of classes to help solve these problems.
They are all contained in the header ``<memory>``
and are defined as templates so that they can point to objects of any type.

Smart pointers are classes that behave like *raw* pointers but also manage objects 
created with ``new``,
so that you don't have to worry about when and whether to delete them.
Smart pointers are declared on the :term:`stack` and
automatically delete the encapsulated object when the smart pointer goes out of scope.
The smart pointer is defined in such a way that it can be used
syntactically almost exactly like a raw pointer. 

One of the earliest so-called 'smart pointers' was ``auto_ptr``.
Much online documentation and many text books still refer to and recommend ``auto_ptr``.
The ``auto_ptr`` function was officially deprecated in C++11 and removed in C++17.
Generally, where old texts refer to ``auto_ptr``, use ``unique_ptr`` instead.


Class ``std::unique_ptr``
.........................
A :cref:`std::unique_ptr` is a so-called 'smart pointer' that owns and manages another object through a pointer 
and disposes of that object when the ``unique_ptr`` goes out of scope.
A ``unique_ptr`` is a very lightweight wrapper around a pointer.
The basic syntax is:

.. code-block:: cpp

   // older C++11 syntax
   // clunky and repetitive
   std::unique_ptr<int> p1 = std::unique_ptr<int>(new int);

   std::unique_ptr<int> p2 = std::make_unique<int>();       // C++14 adds make_unique

In each example, both ``p1`` and ``p2`` are unique pointers that 'own' an ``int*``.
Our earlier examples can be changed to:

.. code-block:: cpp

   #include <memory>
   struct Point {
     double x = 0;
     double y = 0;
   };

   int main() {
     std::unique_ptr<int> p2 = std::make_unique<int>();
     auto                 p3 = std::make_unique<int>();       // less redundant

     // array examples
     // unique pointers to arrays of 5 elements
     std::unique_ptr<int[]> p4 = std::unique_ptr<int[]>(new int[5]);
     auto                   p5 = std::make_unique<int[]>(5);

     // user define types are no different
     auto pt_x   = std::make_unique<Point>();    // one Point*
     auto points = std::make_unique<Point[]>(3); // array of 3 Point*
   }
   
Once declared, a unique pointer can be manipulated using the same syntax as a raw pointer.

.. code-block:: cpp

     auto p = std::make_unique<Point>(); 
     // modify Point coordinates and print
     p->x = 8;
     p->y = 13;
     std::cout << p->x << ' ' << p->y << '\n';

     // this is an error
     // std::cout << p.x << ' ' << p.y << '\n';
     

What makes a ``unique_ptr`` *unique*?

An object stored within a unique pointer **uniquely owns** its pointer.
In other words, an object is 'owned' by exactly one unique_ptr.
Unlike raw pointers, a unique pointer cannot be copied or assigned to another variable,
even another ``unique pointer``.

No two unique pointers can ever contain the same raw pointer value.
This solves the 'double delete' problem if both go out of scope.
The result is that some operations you **can** perform on raw pointers 
are not allowed on ``unique_ptr``:

.. code-block:: cpp

     auto x = std::make_unique<Point>(); 
     std::unique_ptr<Point> y = {x};     // error - copy construction not allowed

     std::unique_ptr<Point> z;           // new empty (nullptr) 
     if(!z) {                            // check if z != nullptr
       z = x;                            // error - copy assignment not allowed
     }

Although copying unique pointers is not allowed, 
you can :cref:`unique_ptr::release()` the pointer and assign it to a 
raw pointer,
or transfer ownership to a different ``unique_ptr``.

-----

.. admonition:: More to Explore

   - `Free-store managment FAQ <https://isocpp.org/wiki/faq/freestore-mgmt>`_
   - From: cppreference.com: 

     - `Operator new <http://en.cppreference.com/w/cpp/language/new>`_ and 
       `delete <http://en.cppreference.com/w/cpp/language/delete>`_. 
     - `unique_ptr <http://en.cppreference.com/w/cpp/memory/unique_ptr>`_ and 
       `make_unique <http://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique>`_.




