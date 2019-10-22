..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: function; overloads
   single: overloading functions


Function overloads
==================

Unlike C, in C++, 
two different functions can have the same name as long as their parameter lists are different.
When two functions have the same name, but different parameters,
the functions are said to be **overloaded**.

In order to count as a valid overload, 
either the number of parameters must be different, 
or the parameter types must be different, or a combination of both. 
For example:

.. activecode:: ac-overload-1
   :language: cpp

   #include <iostream>
   using std::cout;

   // add two ints
   int add (int a, int b) {
     return a+b;
   }
   // add two doubles
   double add (double a, double b) {
     return a+b;
   }

   int main () {
     int x=5, y=2;
     double p=3.14, e=2.718;
     cout << add (x,y) << '\n';
     cout << add (p,e) << '\n';

     // error: call to overloaded function add (double, int) ambiguous
     // cout << add (31.4, 10) << '\n';

     // explicit conversion is OK
     cout << add (31.4, double(10)) << '\n';
   }


Function overloads are a huge advantage over C
where (nearly) every function is global
and every function name must be unique.
For example:

- C defines 7 different functions just for absolute value 

  - ``abs``, ``llabs``, ``fabs``, ``fabsf``, etc.
    see :cref:`abs`

- and 13 different functions for different types of division operations

This just adds to the amount of stuff programmers have to commit to memory.
In C++, you only have to remember a single function to compute
the absolute value: ``abs``.

.. index::
   pair: video; function overloads

.. youtube:: IAMzWp3kS_k
   :http: https

Another example: a family of functions to compute volume.

.. activecode:: ac-volume
   :language: cpp

   #include <iostream>
   #include <cmath>  // not all compilers define M_PI

   // volume of a cube
   double volume (const double a) {
     return a * a * a;
   }

   // volume of a cylinder
   double volume (const double r, const double h) {
     return M_PI * r * r * h;
   }

   // volume of a cuboid
   double volume (const double a, const double b, const double c) {
     return a * b * c;
   }

   int main() {
     std::cout << "volume of a 2 x 2 x 2 cube: " 
               << volume(2) << '\n'

               << "volume of a cylinder, radius 2, height 3: " 
               << volume(2, 3) << '\n'

               << "volume of a 2 x 3 x 4 cuboid: " 
               << volume(2, 3, 4) << '\n';
     return 0;
   }



.. note:: 

   The return type is **not** part of the overload.

   Two functions in the same namespace that differ only in return type will not compile.


Overloading anti-patterns
.........................

How many parameters are too many?

This is an often asked question, with no clear cut answer.
It is primarily a question of *clarity* and *design*.


For example, given:

.. code-block:: cpp

   int operate (float a, int b, long c, double d);

In this case, the parameters and function name provide no guidance on
how to call this function.
So four is probably too many parameters, 
simply because future usage errors are likely.

Keep in mind that more parameters equal more complexity.
Limit the number of parameters you need in a given method, 
or use a ``struct`` to combine parameters.
Also, be wary of overloads with the same number of parameters and different types.
For example:

.. code-block:: cpp

   int operate (double a, int b);
   int operate (int a, double b);

Depending on what ``operate`` does with it's parameters, 
reversing the order of the parameters could have drastic consequences.
We just don't know without looking at the source code.
In this case even two parameters is too many.
It is almost certain someone will invoke the wrong version occasionally.


-----

.. admonition:: More to Explore

  - From: cppreference.com: 
    `overload resolution <http://en.cppreference.com/w/cpp/language/overload_resolution>`_ 


