..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. include:: <isonum.txt>

.. index:: scope

Scope
=====

Each name that appears in a C++ program is only valid in some *possibly discontiguous*
portion of the source code called its :term:`scope`.

Within a scope, 
unqualified name lookup can be used to associate the name with its declaration.


.. code-block:: cpp

   #include <cassert>

   int n = 3;                  // global variable

   int main() {
     int n = 42;               // local variable 
     assert (n == 42);         // local scope definition replaces the global
   }

   void func () {
     assert (n == 3);          // only name 'n' in scope is the global one
   }

.. admonition:: Macro assert

   The ``assert`` macro from C is a simple way to validate
   something in your program that **must** be true before you
   proceed.
   To use the assert macro, ``#include <cassert>``,
   then call the function ``assert``.
   The assert function takes a boolean variable or
   an expression that evaluates to a ``bool``.

   Use the assert macro in your own code to validate function
   parameters or any other important checks.


In the following example, 
all of the assertions about ``n`` are ``true``:

.. code-block:: cpp

   #include <cassert>

   int n = 3;

   int main() {
     int n = 42;
     assert (n == 42);

     // a new block scope can be created anywhere
     {
       double n = -3.14159;
       assert (n - -3.1415 < 0.01);
     
     } // double n is no longer in scope 

     assert (n == 42);
   }

Errors related to scope are common,
especially for beginning programmers who tend to rely more on 
global variables, or variables with more scope than needed.
For example, what is the output of the following?

.. code-block:: cpp

   #include <iostream>

   int main() {
     int i1;
     for (i1 = 0; i1 < 10; i1++) {
       std::cout << i1 << ' ';
     }
     int i2;
     for (i2 = 0; i1 < 10; i2++) {
       std::cout << i2 << ' ';
     }

   }

.. reveal:: reveal-scope-1
   :showtitle: Show Answer
   :hidetitle: Hide

   If you guessed ``0 1 2 3 4 5 6 7 8 9`` , then you got it!

   Can you explain *why*?

   Hint:  What is the value of ``i2`` when the end of main is reached?

   What should be done to fix this program?

.. admonition:: Try This!

   Change the preceeding program and put the declarations for 
   ``i1`` and ``i2`` in their respective ``for`` loops.  
   Don't make any other changes.

   What happens?

   Why is this better than the unmodified program?

.. index:: local variables

Local variables
---------------

You may read somewhere that global variables are evil, harmful, or whatever.
There are no *harmful* language features.

There *are* some language features that can get you into trouble if you have not
carefully weighed the pros and cons of their use.
That is why in this book, we generally like to avoid absolutes and to use instead *prefer*.

We *prefer* keeping scope to the absolute minimum to get something done.
Because we prefer keeping scope to a minimum, we *prefer*: 

- Local variables over global variables.
- Declaring variables in the block where they are used.

  - Even a local variable can have too much scope, as in the preceding example.

There is no reason in modern languages to declare all your variables at the start of a function.
This is actually a requirement of alder languages like FORTRAN and old C.
In modern languages, it's an old habit some people have carried forward for no good reason.

One of the simplest things you can do as a programmer to improve the clarity and
maintainability of your code and reduce errors is to minimize the scope of local variables.
The most powerful technique for minimizing the scope of local variables
is to declare them where they are first used.

The more distance between the top of a function and the place
where a variable is actually used, the more important this advice is.
If a variable is initialized far from it's first use, the reader has
probably forgotten the initial value,
or even if the variable is local or global.

Long methods with dozens of local variable are part of the reason special
variable naming schemes became popular in some programming circles
in the 70's - 90's.
Some are still popular even today (Hungarian notation).
Generally, all of these systems attempt to compensate for confusion created by
poor design choices.

Declaring a variable too early creates the problems described earlier,
but also creates the problem of causing the scope to extend later than needed.
When a variable is declared before the block in which it is used,
it also exists after the block scope ends.
This is the fundamental problem with our two ``for`` loops in the previous example.

This is a classic :term:`semantic error`. 
The code compiles and runs, 
but does not produce the expected result.

One of the reasons we prefer ``for`` loops to ``while`` loops is that 
for loops allow us to initialize the loop variables within the for block.
While loops, in contrast, nearly always define a variable controlling the exit condition
outside the scope of the while block.

**Prefer initialized local variables to unitialized ones**.
Uninitialized variables are a common source of error.
If you code contains conditional logic or loops and the variable
is accessed in its uninitialized state only occasionally, 
the result can be bugs that are difficult to identify and fix.


.. index:: namespace

Keyword: ``namespace``
----------------------

A ``namespace`` is simply a named block that defines a scope.
Namespaces provide a method for preventing name conflicts in large projects.

Symbols declared inside a namespace block are placed in a named scope that prevents them from being mistaken for identically-named symbols in other scopes.

Multiple namespace blocks with the same name are allowed. 
All declarations within those blocks are declared in the named scope.

.. code-block:: cpp

   // declare some things in the mesa namespace
   namespace mesa {
     int i = 0;
     double pi = 3.1416;
     void details (char);
   }

   void mesa::details (char c) { // define the function declared earlier
     // do something
   }

   //void mesa::oops () {       // error: oops not yet declared in mesa namespace
   //}

   namespace mesa {  // a separate mesa namespace block
     void oops ();
     namespace cisc {
       double pi = 3.14159265358979;  // not the same variable as mesa::pi
     }
   }

   int main () {
     using mesa::cisc::pi;
     pi = 3.f;
     mesa::details('a');
   }

   

The larger your project, the more important it is to partition the global namespace.
By default, all symbols are declared in the *global namespace* (``::``).

What is the problem with the global namespace?

- There is only 1 of them
- Name conflicts can be common on large projects
- Complicates mixing third party libraries

Well-behaved third party libraries will not put much (if anything) in the global namespace.

You can put anything in a namespace, except ``main``.
The function main has a few special rules and one is that it must be in the global namespace.

The ``using`` directive allows all the names in a namespace to be used 
without the namespace-name as an explicit qualifier. 
Use a using directive in an implementation file (i.e. ``*.cpp``) 
if you are using several different identifiers in a namespace; 
if you are just using one or two identifiers, 
then consider a using declaration to only bring those identifiers into scope 
and not all the identifiers in the namespace. 
If a local variable has the same name as a namespace variable, 
the namespace variable is hidden. 
It is an error to have a namespace variable with the same name as a global variable.

.. index::
   pair: namespace; using directive

Using namespaces
................

What's wrong with ``using namespace std;``?

Nothing, technically.
It was a simplification in your first semester classes.
The intent was to avoid 'burdening' you with having to care about this technical detail.

**BUT**

The using-directive ``using namespace std;`` at any namespace scope introduces 
*every* name from the namespace std into the global namespace 
(since the global namespace is the nearest namespace that contains both std and any user-declared namespace), 
which may lead to undesirable name collisions. 
This, and other using directives are generally considered bad practice at file scope of a header file.
Additionally, shadowing names in the standard namespace can lead to unexpected behaviors.


.. tabbed:: namespace

   .. tab:: Example: namespace std

      It can be hard to remember every name that might be
      imported when ``using namespace std;``.
      Even when only 1 header is included.

      The following example seems innocent enough,
      until you learn that :io:`showpoint<manip/showpoint>` is a name
      in ``std::ios``

      Run the following example twice,
      first as is, then remove the line ``bool showpoint = true;``:

      .. activecode:: ac-namespace-1
         :language: cpp

         #include <iostream>

         using namespace std;

         int main () {
           bool showpoint = true; 

           cout << "1.0 with showpoint: " << showpoint << 1.0 << '\n'
                << "1.0 with noshowpoint: " << noshowpoint << 1.0 << '\n';

         }
   
Errors using namespace directives are seldom this obviously wrong.


.. tabbed:: so_question

   .. tab:: Stack Overflow

      Here is a simplification of a 
      `real question <https://stackoverflow.com/questions/2712076/how-to-use-an-iterator>`_
      asked on stack overflow:

      .. activecode:: ac-namespace-2
         :language: cpp
         :compileargs: ['-Wall', '-Wextra', '-std=c++11']

         #include <iostream>
         #include <vector>
         #include <cmath>
         using namespace std;

         struct point {
           float x;
           float y;
         };

         // calculate the distance between two points
         float distance(const point& p1, const point& p2) {
           return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
                       (p1.y - p2.y)*(p1.y - p2.y));
         }

         int main() {
           vector <point> po;
           point p1; p1.x = 0; p1.y = 0;
           point p2; p2.x = 100; p2.y = 100;
           po.push_back(p1);
           po.push_back(p2);

           for (auto ii = po.begin(); ii != po.end(); ii++) {
             for (auto jj = po.begin(); jj != po.end(); jj++) {
               cout << distance(ii,jj) << " ";
             }
           }
           return 0;
         }
             
            
      This code compiles and runs and says the answer is: ``0 1 -1 0``.
      I think we can all agree that is not the correct answer for two points ``(0,0)`` and ``(100,100)``.

.. admonition:: Try This!

   What is wrong with the program?

   Can you fix it?

The problem with each of the preceding programs was that the 
author did not realize the potential pitfalls with ``using namspace std;``.


.. index::
   pair: Herb Sutter; namespace using
   pair: Andrei Alexandrescu; namespace using

One final word from two experts:

  **Summary**

  Namespace usings are for your convenience, not for you to inflict on others: 
  Never write a ``using`` declaration or a ``using`` directive before an ``#include`` directive.

  Corollary: In header files, 
  don’t write namespace-level using directives or using declarations; 
  instead, explicitly namespace-qualify all names. 
  (The second rule follows from the first, 
  because headers can never know what other header ``#include`` might appear after them.)

  **Discussion**

  In short: 
  You can and should use namespace using declarations and directives liberally 
  in your implementation files after ``#include`` directives and feel good about it. 
  Despite repeated assertions to the contrary, 
  namespace ``using`` declarations and directives are not evil and they do not defeat the purpose of namespaces. 
  Rather, they are what make namespaces usable.

  -- Herb Sutter and Andrei Alexandrescu, C++ Coding Standards


-----

.. admonition:: More to Explore

  - From: cppreference.com: 
    `scope <http://en.cppreference.com/w/cpp/language/scope>`_
    `namespace declarations <http://en.cppreference.com/w/cpp/language/namespace>`_ and 
    `namespace alias <http://en.cppreference.com/w/cpp/language/namespace_alias>`_
  - From stack overflow: `Why is using namespace std considered bad practice? <https://stackoverflow.com/questions/1452721/why-is-using-namespace-std-considered-bad-practice>`_


