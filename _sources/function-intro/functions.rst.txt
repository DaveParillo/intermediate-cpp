..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".
..  Some of the content in this section is adapted from
    http://www.cs.yale.edu/homes/aspnes/classes/223/notes.html
   
.. index:: functions

Introduction to functions
=========================

A *function* is a group of statements that work together to perform a task.
A function is composed of:

- A *name*
- Zero or more *parameters*
- A return value

  - A function that returns no value must still declare that fact by
    specifying a return type ``void``.

.. code-block:: cpp

   return_type function_name (argument list)
   {
      // zero or more statements
   }

The part outside the braces is called the **function declaration**.
The braces and their contents is called the **function body**.
Once defined, a function may be called and
the task it defines can be executed as often as needed.
Some simple, specific examples:

.. code-block:: cpp

   int area (int height, int width) {
     return height*width;
   }

   void say_hello() {
     std::cout << "hello";
   }


Function declarations and compilation units
-------------------------------------------

By default, functions have global :term:`scope`: 
they can be used anywhere in your program, even in other files. 
If a file doesn't contain a :term:`declaration` for a function  before it is used, 
then the compiler will complain.

The solution is to either:

(a) Move the function definition before any functions that use it; or 
(b) Put in a declaration without a body before any functions that use it, 
    in addition to the declaration that appears in the function definition. 

Option (b) is generally preferred, 
and is the only option when the function is used in a different file.

To make sure that all declarations of a function are consistent, 
the usual practice is to put them in an :cref:`include` file. 
For example, if the ``area`` function is used in a lot of places, 
we might put it in its own file ``area.cpp``:

.. code-block:: cpp

   #include "area.h"

   int area (int height, int width) {
     return height*width;
   }

.. index:: 
   pair: #include search path; make

The file ``area.cpp`` above uses an  ``#include`` directive to include a copy 
of the following header file area.h:

.. code-block:: cpp

   #ifndef AREA_H
   #define AREA_H

   /* Returns the area of a rectangle */
   int area (int height, int width);

   #endif /* AREA_H */

Note that the declaration in ``area.h`` doesn't have a body. 
Instead, it's terminated by a semicolon, like a variable declaration. 
A *function declaration* serves the same purpose as a *variable declaration*:
they both introduce a new name and its type into a :term:`scope`.

The ``#ifndef``, ``#define``, and ``#endif`` together form a pattern called a
:term:`header guard` or *include guard*.
They ensure the functions in include files are defined only once.

By convention, the documentation for functions is primarily in the include file.
The idea is that ``area.h`` is the public interface of this module, 
and so the explanation of how to use the function should be there.
The reason ``area.cpp`` includes ``area.h`` is to get the compiler to 
verify that the declarations in the two files match.

- ``area.h`` contains the function declaration
- ``area.cpp`` contains the function definition (which includes a declaration)

.. admonition:: Best Practice

   Keep your declarations and definitions separate.

   The source file that *defines* a function should include the file that *declares*
   a function.

Every other file that needs to use the ``area`` function uses an include directive
``#include "area.h"`` at the top of the file that uses it:

.. code-block:: cpp
   :linenos:

   #include "area.h"

   bool too_small (int x, int y) {
     const int min_size = 10;
     return area(x, y) < min_size; 
   }

The ``#include`` on line 1 uses double quotes instead of angle brackets; 
this tells the compiler to look for ``area.h`` in the current directory 
instead of the system include directory (typically /usr/include).
Using ``make``, you can add directories to the include search path using ``-I``.

.. seealso:: 

   :doc:`../beginnings/scope`


.. index:: static functions

Static functions and variables
------------------------------

By default, all functions are global; 
they can be used in any file of your program whether or not a declaration appears in a header file. 
To limit access to the
current file, declare a function or variable ``static``, like this:

.. code-block:: cpp

   // assume all these definitions are in a single file "foo.cpp"

   // static variable used by non-static functions
   static bool verbose = false;

   bool is_verbose() {
     return verbose;
   }

   // vprint could reside in another file
   void vprint (std::string message) {
     if (is_verbose()) {
       std::cout << message << '\n';
     }
   }
   // this function only works if it is the same file
   // as the one where verbose is defined
   void verbose_print (std::string message) {
     if (verbose) {
       std::cout << message << '\n';
     }
   }

   // local static function can only be called in this compilation unit
   static void helloHelper(void) {
     puts("hi!");
   }

   // anyone can call `hello`
   void hello(int repetitions) {
     for(int i = 0; i < repetitions; ++i) {
       helloHelper();
     }
   }

Similar to file static functions and variables, 
the keyword ``static`` can also be used inside functions.
Static variables are initialized only the first time the function is called,
for example:

.. code-block:: cpp


   size_t counter() {
     static size_t count = 0;
     return ++count;
   }

The first time ``counter`` is called, 
the variable ``count`` is initialized to zero.
Each call thereafter, ``count`` is increased by 1 and the new value is returned.

Another appropriate use of static variable in functions:
when defining a constant that should only be initialized once.
For example, our earlier ``too_small`` function, could be:

.. code-block:: cpp

   #include "area.h"

   bool too_small (int x, int y) {
     static const int min_size = 10;
     return area(x, y) < min_size; 
   }



When to write a function
------------------------

As with any kind of abstraction, there are two goals to making a function:

- **Encapsulation**: 
  If you have some task to carry out that is simple to describe from the outside, 
  but messy to understand from the inside, 
  then wrapping it in a function lets the caller carry out this task without having to know the details. 

  This is also useful if you want to change the implementation later.
- **Code re-use**: 
  If you find yourself writing the same lines of code in several places 
  (or worse, are tempted to copy a block of code to several places), 
  you should probably put this code in a function 
  (or perhaps more than one function, 
  if there is no succinct way to describe what this block of code is doing).

Both of these goals may be trumped by the goal of making your code **clear**. 
If you can’t describe what a function is doing in a single, simple sentence, 
this is a sign that maybe you need to restructure your code. 
Having a function that does more than one thing (or does different things depending on its arguments) 
is likely to lead to confusion.

So, for example, this is not a good function definition:

.. code-block:: cpp

   // This code is an anti-pattern.
   // It's an example of how NOT to write a function.

   /** 
    * If getMax is true, return maximum of x and y,
    * else return minimum.
    */
   int computeMinOrMax(int x, int y, bool getMax) {
     if(x > y) {
       if(getMax) { 
         return x;
       } else {
         return y; 
       }
     } else { 
       if(getMax) { 
         return y;
       } else {
          return x; 
       }
     } 
   }

This function is clearly trying to do two things and not doing either one very well.
Two functions would be far simpler:

.. code-block:: cpp

   // return the maximum of x and y
   // if x == y, return y
   int maximum (int x, int y) {
     return (x < y) ? y : x;
   }

   // return the minimum of x and y
   // if x == y, return y
   int minimum (int x, int y) {
     return (y < x) ? y : x;
   }

   int computeMinOrMax(int x, int y, bool getMax) {
       if(getMax) {
         return maximum(x, y);
       }
       return minimum(x, y);
   }

   // or more compactly:
   int computeMinOrMax(int x, int y, bool getMax) {
     return getMax ? maximum(x,y) : minimum(x,y);
   }


Is this *slightly* more typing? Yes.
At the end of the day, you will be far happier testing and debugging the three simpler functions
than the first version.
Your future co-workers will thank you.

.. note::

   Also be aware the STL provides functions
   `std::min <http://en.cppreference.com/w/cpp/algorithm/min>`_ and
   `std::max <http://en.cppreference.com/w/cpp/algorithm/max>`_,
   which eliminate the need for our ``minimum`` and ``maximum`` entirely
   and have the advantage of working on any :term:`comparable` type.

   This would transform the previous example to:

   .. code-block:: cpp

      #include <algorithm>

      int computeMinOrMax(int x, int y, bool getMax) {
        return getMax ? std::max(x,y) : std::min(x,y);
      }



.. index:: call stack
   pair: pointer; stack pointer

The call stack
--------------


.. index:: 
   pair: graph; call stack


Functions are routinely called from many places
and more than one function can be 'active' at any one time.
The CPU needs a mechanism to keep track of every function call,
all function parameters, and local variables,
so that the CPU can execute each instruction in its proper order.

Some of this information will be stored in **registers**, 
memory locations built into the CPU itself, 
but most will go on the :term:`stack`, 
a region of memory that on typical machines grows downward, 
even though the most recent additions to the stack are called the “top” of the stack. 

.. graphviz::

   digraph memory {
     fontname = "Bitstream Vera Sans"
     label="Typical program memory layout"
     node [
        fontname = "Bitstream Vera Sans"
        fontsize = 11
        shape = "record"
        style=filled
        fillcolor=lightblue
     ]
     mem [
        label = "{stack\n (grows down)|\n\n\nunused memory\n\n|\nfree store\n(grows up)|\nstatic data\n|\ncode\n(text area)}"
     ]

   }

Typically, each called function and any local variables, return values, or
parameters passed in, is stored in a special data structure called a **stack frame**
or an **activation record**.
Each function call pushes another activation record onto the stack.

The location of the top of the stack is stored in the CPU in a special register called the **stack pointer**.
So a typical function call looks like this internally:

#. The current instruction pointer or program counter value, 
   which gives the address of the next line of machine code to be executed, 
   is pushed onto the stack.
#. Any arguments to the function are copied either into specially designated 
   registers or onto new locations on the stack. 
   The exact rules for how to do this vary from one CPU architecture to the next, 
   but a typical convention might be that the first few arguments are copied 
   into registers and the rest (if any) go on the stack.
#. The instruction pointer is set to the first instruction in the code for the function.
#. The code for the function allocates additional space on the stack to hold its 
   local variables (if any) and to save copies of the values of any registers 
   it wants to use (so that it can restore their contents before returning to its caller).
#. The function body is executed until it hits a return statement.
#. Returning from the function is the reverse of invoking it: 
   
   - Any saved registers are popped back from the stack, 
   - The return value is copied to a standard register, 
   - The values of the instruction pointer and stack pointer are restored 
     to what they were before the function call.

From the programmer’s perspective, 
the important point is that both the arguments and the local variables inside a 
function are stored in freshly allocated locations that are thrown away after the function exits. 
After a function call the state of the CPU is restored to its previous state, 
except for the return value. 
Any arguments passed to a function are passed as copies by default,
so changing the values of the function arguments inside the function has no effect on the caller. 
Any information stored in local variables is lost.

Under very rare circumstances,
it may be useful to have a variable local to a function that persists from one function call to the next.
You can do so by declaring the variable static.
For example, here is a function that counts how many times it has been called:

.. code-block:: cpp

   // return the number of times the function has been called
   int counter(void) {
     static count = 0;
     return ++count; 
   }

Static local variables are stored in the same memory space as global variables. 
But they are only visible inside the function that declares them. 
This makes them slightly less troublesome than global variables;
there is no fear that some unrelated code elsewhere will quietly change their value.
Static variables are rarely used in practice, however,
because they do not work well in multi-threaded applications.

.. admonition:: Try This!

   Read the code below and predict what the output should be.
   Then step though
   `the example code here <http://pythontutor.com/cpp.html#code=%23include%20%3Ciostream%3E%0A%0A//%20forward%20function%20declarations%0Avoid%20dig%28%29%3B%0Avoid%20deeper%28%29%3B%0A%0Aint%20main%28%29%20%7B%0A%20%20std%3A%3Acout%20%3C%3C%20%22Programs%20always%20start%20in%20function%20main.%5Cn%22%3B%0A%0A%20%20dig%28%29%3B%0A%0A%20%20std%3A%3Acout%20%3C%3C%20%22Returned%20to%20main.%5Cnexiting.%22%3B%0A%20%20return%200%3B%0A%7D%0A%0Avoid%20dig%28%29%20%7B%0A%20%20std%3A%3Acout%20%3C%3C%20%22Digging...%5Cn%22%3B%0A%20%20deeper%28%29%3B%0A%20%20std%3A%3Acout%20%3C%3C%20%22Still%20digging...%5Cn%22%3B%0A%7D%0A%0Avoid%20deeper%28%29%20%7B%0A%20%20std%3A%3Acout%20%3C%3C%20%22now%20even%20deeper....%5Cn%22%3B%0A%7D%0A&curInstr=6&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D>`_
   to see the call stack in action.

   Did your expectations match what actually happened?

   .. code-block:: cpp

      // call-stack.h

      // it's a better idea to physically separate 
      // definitions and declarations

      #ifndef CALL_STACK_H
      #define CALL_STACK_H

      // declare the interface here
      void dig();
      void deeper();

      #endif


   .. code-block:: cpp

      // implement the call-stack functions 
      // declared in call-stack.h

      #include "call-stack.h"
      #include <iostream>

      int main() {
        std::cout << "Programs always start in function main.\n";

        dig();

        std::cout << "Returned to main.\nexiting.";
        return 0;
      }

      void dig() {
        std::cout << "Digging...\n";
        deeper();
        std::cout << "Still digging...\n";
      }

      void deeper() {
        std::cout << "now even deeper....\n";
      }

.. index:: 
   pair: functions; passing parameters
   single: pass by value
   pair: parameter passing; by value

Passing parameters
------------------

In C and C++, parameter passing defaults to **pass by value**.
Unless you specify otherwise,
function parameters are initialized with *copies* of the actual arguments, 
and function callers get back a *copy* of the value returned by the function.
Pass by value is the simplest way to get data into and out of functions.

.. code-block:: cpp

   #include <iostream>

   // Declare a function that takes a parameter.
   void printFavorite(int x);

   int main() {
   int favorite = 72;
     printFavorite(favorite); // Call the function.
     return 0;
   }

   // define the function
   void printFavorite(int x) {
     std::cout << "my favorite number is " << x << '\n';
   }

You can also step through `example 2.1.5-1 here <http://pythontutor.com/cpp.html#code=%23include%20%3Ciostream%3E%0A%0A//%20Declare%20a%20function%20that%20takes%20a%20parameter.%0Avoid%20printFavorite%28int%20x%29%3B%0A%0Aint%20main%28%29%20%7B%0A%20%20int%20favorite%20%3D%2072%3B%0A%20%20printFavorite%28favorite%29%3B%20//%20Call%20the%20function.%0A%20%20return%200%3B%0A%7D%0A%0A//%20define%20the%20function%0Avoid%20printFavorite%28int%20x%29%20%7B%0A%20%20std%3A%3Acout%20%3C%3C%20%22my%20favorite%20number%20is%20%22%20%3C%3C%20x%20%3C%3C%20'%5Cn'%3B%0A%7D%0A&curInstr=0&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D>`_.  

The important point is that two copies of my favorite number are stored.
The one declared in main, ``favorite``, and
the one declared in printFavorite, ``x``.
The parameter ``x`` is initialized using the value of ``favorite`` in main.


More than one parameter can be passed.
For example, a function to add two numbers:

.. code-block:: cpp

   #include <iostream>

   // This function takes two parameters.
   int addNumbers(int x, int y);

   int main() {
     int a = 13;
     int b = 21;
     int sum = addNumbers(a, b);
     std::cout << sum << '\n';
     return 0;
   }

   int addNumbers(int x, int y){
     int answer = x + y;
     return answer;
   }

Step through `example 2.1.5-2 <http://pythontutor.com/cpp.html#code=%23include%20%3Ciostream%3E%0A%0A//%20This%20function%20takes%20two%20parameters.%0Aint%20addNumbers%28int%20x,%20int%20y%29%3B%0A%0Aint%20main%28%29%20%7B%0A%20%20int%20a%20%3D%2013%3B%0A%20%20int%20b%20%3D%2021%3B%0A%20%20int%20sum%20%3D%20addNumbers%28a,%20b%29%3B%0A%20%20std%3A%3Acout%20%3C%3C%20sum%20%3C%3C%20'%5Cn'%3B%0A%20%20return%200%3B%0A%7D%0A%0Aint%20addNumbers%28int%20x,%20int%20y%29%7B%0A%20%20int%20answer%20%3D%20x%20%2B%20y%3B%0A%20%20return%20answer%3B%0A%7D%0A&curInstr=0&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D>`_
and see how the copies of both local variables and return values are managed on the stack.

.. index:: 
   single: pass by reference
   pair: parameter passing; by reference

For large / complex data types, however, pass by value becomes expensive even in small programs.
An alternative to pass by value, is called **pass by reference**.
Rather than passing a *copy* of the object, 
instead only the *address* of the object (the object reference),
is passed instead.
We use the *address of operator* ``&`` to declare that only the address of the 
variable is passed, rather than a copy.
The primary advantage is that since all addresses are the same size,
the cost of passing is the same, 
regardless of how large the object is.


.. code-block:: cpp

   #include <iostream>

   /**
    * A copy of x is passed to this function.
    * Changes to x are not reflected in the caller.
    */
   void by_value(int x) {
     std::cout << "in by_val the address of x is   " << &x << '\n';
     x = 99;
   }

   /**
    * A reference to x is passed to this function.
    * Changes to x are not reflected in the caller.
    */
   void by_reference (int& x) {
     std::cout << "in by_ref the address of x is   " << &x << '\n';
     x = -1;
   }

   int main () {
     auto alpha = 11;
     auto beta = 11;

     std::cout << "in main the address of alpha is " << &alpha << '\n';
     std::cout << "in main the address of beta is  " << &beta << '\n';

     by_value(alpha);
     by_reference(beta);

     std::cout << "alpha is now " << alpha << '\n';
     std::cout << "beta is now " << beta << '\n';
     return 0;
   }

Step through `example 2.1.5-3 <http://pythontutor.com/cpp.html#code=%23include%20%3Ciostream%3E%0A%0A/**%0A%20*%20A%20copy%20of%20x%20is%20passed%20to%20this%20function.%0A%20*%20Changes%20to%20x%20are%20not%20reflected%20in%20the%20caller.%0A%20*/%0Avoid%20by_value%28int%20x%29%20%7B%0A%20%20std%3A%3Acout%20%3C%3C%20%22in%20by_val%20the%20address%20of%20x%20is%20%20%20%22%20%3C%3C%20%26x%20%3C%3C%20'%5Cn'%3B%0A%20%20x%20%3D%2099%3B%0A%7D%0A%0A/**%0A%20*%20A%20reference%20to%20x%20is%20passed%20to%20this%20function.%0A%20*%20Changes%20to%20x%20are%20not%20reflected%20in%20the%20caller.%0A%20*/%0Avoid%20by_reference%20%28int%26%20x%29%20%7B%0A%20%20std%3A%3Acout%20%3C%3C%20%22in%20by_ref%20the%20address%20of%20x%20is%20%20%20%22%20%3C%3C%20%26x%20%3C%3C%20'%5Cn'%3B%0A%20%20x%20%3D%20-1%3B%0A%7D%0A%0Aint%20main%20%28%29%20%7B%0A%20%20auto%20alpha%20%3D%2011%3B%0A%20%20auto%20beta%20%3D%2011%3B%0A%0A%20%20std%3A%3Acout%20%3C%3C%20%22in%20main%20the%20address%20of%20alpha%20is%20%22%20%3C%3C%20%26alpha%20%3C%3C%20'%5Cn'%3B%0A%20%20std%3A%3Acout%20%3C%3C%20%22in%20main%20the%20address%20of%20beta%20is%20%20%22%20%3C%3C%20%26beta%20%3C%3C%20'%5Cn'%3B%0A%0A%20%20by_value%28alpha%29%3B%0A%20%20by_reference%28beta%29%3B%0A%0A%20%20std%3A%3Acout%20%3C%3C%20%22alpha%20is%20now%20%22%20%3C%3C%20alpha%20%3C%3C%20'%5Cn'%3B%0A%20%20std%3A%3Acout%20%3C%3C%20%22beta%20is%20now%20%22%20%3C%3C%20beta%20%3C%3C%20'%5Cn'%3B%0A%20%20return%200%3B%0A%7D%0A&curInstr=0&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D>`_.

.. reveal:: reveal-skill-check-functions
   :showtitle: Show Skill Check
   :hidetitle: Hide Skill Check

   Given the following program:

   .. code-block:: cpp
      :linenos:

      #include <iostream>

      int change_and_add(int &a, int &b) {
        a = 3;
        b = 4;
        return a + b;
      }

      int main() {
        int a = 1;
        int b = 2;
        int c = change_and_add(a, a);
        std::cout << a << b << c;
      }

   .. fillintheblank:: fib_param_1

      What is the output from this program?

      - :428: Correct.
        :123: The variable a is modified in this program.
        :437: The variable b is never modified in this program.
        :427: Variable a is modified <em>twice</em> before the addition is performed.
        :.*: What is passed to the function change_and_add? What changes? What doesn't?



.. index:: function writing guidelines

General function writing guidelines
-----------------------------------

#. Write for clarity and correctness **first**
#. Avoid *premature optimization*
#. Avoid *premature "pessimization"*
   That is, prefer faster when **equally** clear
#. Minimize side-effects

   A function that modifies its parameters is said to have *side-effects*.
   Programs with too many side-effects are hard to predict and debug.

   Returning to our call-stack example.
   What if the function signatures were changed to accept a pass-by-reference parameter?

   .. code-block:: cpp

      #pragma once

      void dig(double& x);
      void deeper(double& x);

   Given that the names of these functions provide no insight to their purpose,
   there is no way to know without inspecting the source if
   the variable x is modified when passed to these functions.

   .. code-block:: cpp

      #include "call-stack.h"
      #include <iostream>

      int main() {
        double pi = 3.14159;
        std::cout << "in main.\npi = " << pi << '\n';
        dig(pi);

        std::cout << "Returned to main.\npi = " << pi << '\n';
        return 0;
      }

      void dig(double& val) {
        std::cout << "Digging...\n";
        val *= 2;
        deeper(val);
        std::cout << "Done digging...\n";
      }

      void deeper(double& val) {
        val -= 1;
        std::cout << "now even deeper....\n";
      }

   This is one of the reasons why some programmers **only** use pass-by-reference
   when the parameter is ``const``.
   Some programmers prefer passing pointers over non-``const`` parameters.
   This requires the caller to explicitly pass in an address and 
   clearly states that the function may modify the parameter.

#. Keep functions short

   - A function should do *one* thing well

     If you see a function doing more than one thing
     consider breaking it up into multiple functions

   - Is this (slightly) more work?

     In the short run, perhaps.

     In the long run, your total time spent
     debugging, testing, maintaining, and modifying
     will be far, far less than if you packed everything into one monster function


   - Note that :term:`unit testing <unit test>` is practically impossible 
     once functions reach a certain size.

#. Strive to write a function *once* and never modify it again.
#. Check function parameters for validity.
   Unless you *completely* trust the caller (and their caller...)

   - It should be obvious: do not trust ``argv[]``


.. index::
   pair: video; function returns

.. youtube:: 9mWWNYRHAIQ
   :http: https


-----

.. admonition:: More to Explore

  - `Basic intro to functions <https://www.youtube.com/watch?v=-87KQS-rZCA>`__
    from Buckys C++ Programming Tutorials.
  - From: cppreference.com: 
    `function declarations <http://en.cppreference.com/w/cpp/language/function>`_. 
  - `C++ Core Guidelines for functions 
    <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#S-functions>`_
    from GitHub
  - cppplusplus.com tutorial on `functions <http://www.cplusplus.com/doc/tutorial/functions/>`_
  - A very brief description of 
    "`extract method <http://refactoring.com/catalog/extractMethod.html>`_" from Martin Fowler's Refactoring site.
  - `ExtractMethod <http://c2.com/cgi/wiki?ExtractMethod>`_ discussion from the 
    `PortlandPatternRepository <http://c2.com/cgi/wiki?PortlandPatternRepository>`_ - the very first wiki

