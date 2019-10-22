..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".


.. index:: vector

The vector class
================
A :container:`vector` is intended to behave like a dynamically sized array.
It is a :term:`template`, so unlike a string, 
which is a container for characters only,
a vector can serve as a container for any type.
More on templates later, for now,
we just need to know enough to know how declare a vector.

As with strings, in standard C, 
the typical way to work with a collection of data is with an array:

.. code-block:: c

   int a[] = {3, 1, 4, 1, 5, 9};


Some downsides to arrays are that they:

- Do not know their own size
- Need to have their size specified when declared
- Decay into pointers easily
- Provide no convenience functions 

The ``vector`` class solves these problems for us and a few others besides.
Declaring a ``vector`` is quite similar to the ``string`` declarations
from the previous section, with one minor addition:

.. code-block:: cpp

   #include <string>        // access std::string functions
   #include <vector>        // access std::vector functions
   
   using std::vector;       // just use 'vector' for type std::vector 

   int main() {
     vector<int> x;                          // empty vector of int

     vector<std::string> two_exes (2, "x");  // "x", "x"

     vector<int> pi_digits = {3,1,4,1,5,9};  // C++11 
     return 0;
   }

When a ``vector`` is created, you must declare what type
of data the vector can store.
The ``<int>`` and ``<std::string>`` represent the *template parameters*
passed to the ``vector``.
It is these template parameters that allow the vector class to serve
as a container for (almost) any type.
There are some limits we will cover later,
but for now, know that any normal type you already have learned about
can be stored in a vector.

Unlike a fundamental type, the declaration ``vector<int> x;`` does **not** create 
an uninitialized variable.
It creates a fully formed vector with no elements stored in it yet.
This is perfectly OK and normal.


.. index:: 
   pair: graph; vector

Given a vector declared as:

.. code-block:: cpp

   std::vector<int> v(4);

.. graphviz:: 

   digraph {
   node [
        fontname = "Courier"
        fontsize = 14
        shape = "record"
        style=filled
        fillcolor=lightblue
     ]
     names [ 
        color = white;
        fillcolor=white;
        label = "{size: | <f0> data: }";
     ]
     struct [
        label = "{4 | <f0> }";
     ]

     node [shape=record, color=black, fontcolor=black, fillcolor=white, width=3.75, fixedsize=true];
     labels [label="<f0> | <f4> size | <f5> spare\ncapacity ", color=white];
     values [label="<f0> v[0] | <f1> v[1] | <f2> v[2] | <f3> v[3] | | <f5> ", 
             color=black, fillcolor=lightblue, style=filled];

     edge [color=black];
     struct:f0:s -> values:f0;
     labels:f4 -> values:f3;
     labels:f5 -> values:f5;
     {rank=same; struct,labels};
   }

Although the ``vector`` object is initialized, its contents are not.
Many compilers will initialize the contents to zero, but don't rely on this behavior.
Explicitly initialize with a default value, if that is what you want:

.. code-block:: cpp

   std::vector<int> v(4, -1);

A vector comes with a rich assortment of convenience functions.
Like an array, the :cref:`vector::operator[]` can be used to access elements
without bounds checking.
Like a string, the :cref:`vector::at()` function provides bounds checking
and will throw an exception if an out of bounds index is used on the ``vector``.

.. code-block:: cpp

   #include <vector>
   #include <iostream>
     
   int main() {
     std::vector<int> numbers {2, 4, 6, 8};
     
     std::cout << "Size: " << numbers.size() << '\n';
     std::cout << "Second element: " << numbers[1] << '\n';
     
     numbers.at(0) = 5;
     numbers.at(4) = numbers[3] + 2;  // out of range error. 
                                      // index 4 is out of bounds
     
     std::cout << "All numbers:";
     for (auto i : numbers) {
       std::cout << ' ' << i;
     }
     std::cout << '\n';
     return 0;
   }

.. admonition:: Something to consider

   What is the difference between a ``std::string`` and 
   ``std::vector<char>``?

   Why did the developers of the STL decide it was important to include both?

Comparisons between vectors are also automatically handled by the class.
In the case of a vector, :cref:`vector::operator==`, 
or equality comparison between two vectors ``a`` and ``b``,
means the two vectors are equal if ``a.size() == b.size()``
and each element in ``a`` compares equal with each element in ``b``
in the same position in the vector.

.. code-block:: cpp

   #include <vector>
   #include <iostream>
     
   int main() {
     std::vector<int> x {2, 4, 6, 8};
     std::vector<int> y {2, 6, 4, 8};
     
     if (x == y) {
       std::cout << "x and y are equal\n";
     } else {
       std::cout << "x and y are equal\n";
     }
     return 0;
   }


.. admonition:: Try This!

   Create two int arrays containing ``{2, 4, 6, 8}`` and check them for equality.


Adding data to a vector
-----------------------
How do we solve the :cref:`std::out_of_range` exception from a few examples ago?
How do we dynamically add data to a ``vector``?
A simple way is to use the :cref:`vector::push_back()` function.

.. code-block:: cpp

   #include <vector>
   #include <iostream>
     
   int main() {
     std::vector<char> letters {'a', 'b', 'c'};
     
     letters.at(0) = 'z';
     letters.push_back('d');  // add 'd' to the end of the vector
     char ch = 'e';
     letters.push_back(ch);  // add 'e' to the end
     letters.pop_back();     // pop_back is the opposite:
                             //  - removes the end element from the vector

     std::cout << "All letters:";
     for (auto c : letters) {
       std::cout << ' ' << c;
     }
     std::cout << '\n';
     letters.clear();         // clear all contents from vector
     return 0;
   }


-----

.. admonition:: More to Explore

   - cppreference.com `std::vector <http://en.cppreference.com/w/cpp/container/vector>`_
   - WikiBooks.org C++ Programming `STL Containers <https://en.wikibooks.org/wiki/C%2B%2B_Programming/STL#Containers>`_


