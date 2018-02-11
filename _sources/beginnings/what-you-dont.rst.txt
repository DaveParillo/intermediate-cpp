..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

..  Much of the content in version control section is adapted from
    http://www.cs.yale.edu/homes/aspnes/classes/223/notes.html

.. index:: 
   pair: introductory topics; C++

What you don't need to know (yet)
=================================

C++ is a large, relatively complex, language.
Due to its size, there are many topics you may have 
not covered, covered incompletely, or covered incorrectly.
Luckily for all of us,
there is a relatively simple language buried inside C++.
One of the goals of this text is to concentrate
on the simpler parts while still solving more advanced
problems than found in a typical introductory text.

Pointers, for example.
Pointers are tricky for some people to get used to.
Very few languages outside of C and C++ give you
direct access to pointers and so many ways to manipulate them.
Depending on your point of view, you may consider this 
pure genius, or the most incredibly foolish design decision
ever made by a programmer.

Modern C++ adds a variety of tools that make working with pointers
easier and safer.

C++
---

This may sound odd, considering this is supposed to be a second semester course in C++.
But as I said, C++ is a very large language.
Most likely, you have learned mostly C (probably), 
with a very small amount of C++ thrown in:

* The classes ``cin`` and ``cout``
* A ``class`` with *setters* and *getters* - maybe even using ``private`` members

The version of C++ most likely taught to most is C++98.
Modern C++ doesn't look much like the C++ that was written in the 80's and 90's.
Primarily because programmers have learned a lot about how to write
programs in C++ over the years, but also because the
power of the *Standard Template Library* (STL).
The STL was not developed until C++ had been used for more than 10 years.
While it was incorporated into the first ISO version of the C++ standard (C++98),
it took some time for many programmers to recognize the power and flexibility
of :term:`generic programming`.

Unfortunately, some of you have "learned C++" mostly using an environment like
CHide. CHide is not C++.
It does not conform even to the C++98 version of the standard
because it don't include the STL.

C++ is actually a federation of several languages:

.. graphviz::

   digraph foo {
     fontname = "Bitstream Vera Sans"
     node [
        fontname = "Bitstream Vera Sans"
        fontsize = 11
        style=filled
        fillcolor=lightblue
     ]

     label="Evolution of C++, briefly";
     labelloc=bottom;
     rankdir=LR;
     c [label="C\n(with classes)", shape="box"];
     modern [label="Modern\nC++"];
     c -> "C++98" -> "C++03" -> modern;
   }

Where 'Modern' C++ is C++11 and later.
More specifically, the current version of the standard.

It is possible to write code in any of these languages
compile it with a C++ compiler and call it a "C++ program".
This course emphasizes 'modern' C++.
Although there is emphasis on newer language features, 
that does not mean that features released before 2011 should never be used.
Generally, C++ gives programmers many choices and it is true
that some choices are preferred over others.
We will try to make preferred programming choices clear.

A simple test for a modern C++ compiler:

.. activecode:: ac_begin_compiler_test
   :language: cpp
   :compileargs: ['-Wall', '-Wextra', '-pedantic', '-std=c++11']

   // A simple test for C++11 compiler
   // compiled with: -Wall -Wextra -pedantic -std=c++11
   
   #include <iostream>

   // test C++11 features
   int main () {
     int test[] = { 1, 2, 3, 5, 8 };  // can we use an initializer list?
     for (auto i: test) {             // can we use a range-for loop?
       std::cout << "i is " << i << '\n';
     }
     return 0;
   }

The current textbook compiler does not support C++14.
This valid code fails to compile:

.. activecode:: ac_begin_compiler_test_1y
   :language: cpp
   :compileargs: ['-Wall', '-Wextra', '-pedantic', '-std=c++1y']

   // A simple test for 'make_unique' support
   // compiled with: -Wall -Wextra -pedantic -std=c++1y
   
   #include <iostream>
   #include <memory>
    
   struct point
   {
       int x, y;
       point() : x(0), y(0) { }
       point(int x, int y) :x(x), y(y) { }
   };
   std::ostream& operator<<(std::ostream& os, const point& p) {
       return os << '{' << "x:" << p.x << " y:" << p.y << '}';
   }
    
   int main()
   {
       // Use the default constructor.
       std::unique_ptr<point> p1 = std::make_unique<point>();
       // Use the constructor that matches these arguments
       std::unique_ptr<point> p2 = std::make_unique<point>(1, 2);
       // Create a unique_ptr to an array of 5 elements
       std::unique_ptr<point[]> p3 = std::make_unique<point[]>(5);
    
       std::cout << "make_unique<point>():      " << *p1 << '\n'
                 << "make_unique<point>(1,2): " << *p2 << '\n'
                 << "make_unique<point[]>(5):   " << '\n';
       for (int i = 0; i < 5; i++) {
           std::cout << "     " << p3[i] << '\n';
       }
   }

.. **

If you run it on `cppreference.com <http://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique>`_
then you can see the output.

The textbook compiler does not know that ``-std=c++1z``, much less c++17 is an option:

.. activecode:: ac_begin_compiler_test_1z
   :language: cpp
   :compileargs: ['-Wall', '-Wextra', '-pedantic', '-std=c++1z']

   // A simple test for C++17 support
   // compiled with: -Wall -Wextra -pedantic -std=c++1z

    #include <iostream>
    #include <memory>

    template <typename T>
    auto get_value(T t) {                   // auto return type deduction: c++14
        if constexpr (std::is_pointer_v<T>) // constexpr-if: C++17
            return *t;
        else
            return t;
    }

    int main()
    {
         auto pi = std::make_unique<int>(9);
         int i = 9;
         
         std::cout << get_value(pi.get()) << "\n";
         std::cout << get_value(i) << "\n";
    }

.. **

And now we know what our capabilities are.

GNU/Linux (or Unix) in general
------------------------------

And **make** in particular.

This course does not assume any familiarity with any specific operating system.
That is, no assumptions regarding **any** command prompt or terminal environments,
or knowledge of hardware beyond broad generalities.

This course  **does**, however have a certain *linux flair*, and
all projects and any labs that require handing in source code
must be able to compile on the command line, preferably using **make**.

For all projects, a working **Makefile** will be provided.
You won't have to edit it.

Parsing command line arguments
------------------------------

This information is for the extra credit part of the lab,
but is required for all projects.

Why command line programs?

C++ is primarily used in *systems programming* and
is a fundamental part of all *\*nix* programs.
*\*nix* is short for *Unix & friends*, *MacOS X*, and *GNU/Linux*.

Parsing the command line is not complicated.
It is a matter of iterating through a 2 dimensional array of `char`.

Function ``main()`` traditionally takes two arguments that provide information
about the command line.

* ``int argc``: the total number of arguments, strings separated by whitespace
* ``char *argv[]``: an array of these strings

  ``char *argv[]`` can also be specified as ``char **argv``, 
  which is the same thing, if you remember pointers from your first semester.
  If not, we'll cover it soon.

The important thing to remember is that ``argc`` and ``argv`` are 
passed automatically to main and are available to use.
If you run a program named ``foo`` invoked as::

   /home/dave/foo -n 10 www.sdmesa.edu

Then ``argc`` would be set = ``4`` and array ``argv`` would contain::

   argv[0]:  "/home/dave/foo"
   argv[1]:  "-n"
   argv[2]:  "10"
   argv[3]:  "www.sdmesa.edu"



-----

.. admonition:: More to Explore

   - `Using the getopt function <https://www.gnu.org/software/libc/manual/html_node/Using-Getopt.html>`_ - from gnu.org
   - Textbook: :doc:`../pointers/pointers`
   - C++17: `constexpr if <http://en.cppreference.com/w/cpp/language/if>`_



