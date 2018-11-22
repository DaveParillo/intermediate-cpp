..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index::
   single: lambda
   single: lambda expressions
   single: lambda functions

Lambda expressions
==================

A *lambda expression*, or simply *lambda*, 
provides a means to define an anonymous function right at the location
where it is invoked or passed as an argument to a function.

Often, it is more convenient to write a very short function
'in line' where the function is used rather than:

#. Write a separate function with a name
#. Store the function in a specific compilation unit
#. ``#include`` the compilation unit definitions where it will be used
#. Call or pass the function as an argument

While using STL facilities with lambdas is not required,
it turns out that many facilities in the STL take function pointers as arguments.
This fact makes lambdas particularly useful since
any place a function pointer can be used, a lambda expression can be used instead.

Suppose we want to count the number of short strings in a vector.
There is a 'count if' function in the STL we can use to get the job done.
The :cref:`std::count_if` function expects 3 parameters:

- A pointer to the first element to examine in the ``vector``
- A pointer to one past the last element to examine in the ``vector``
- A pointer to a function that will determine if the element should be counted

The last parameter is commonly called a :term:`predicate function`.
A predicate function is a fancy name for a function that returns a ``bool``.

We could implement this using the techniques we have already learned:

.. code-block:: cpp

   bool less_than_5(const string& str) {
     return str.size() < 5;
   }

   size_t num_short_strings(const vector<string>& v) {
     const string* begin = v.data();            // must be const
     const auto end = begin + v.size();
     return count_if(begin, end, less_than_5);
   }

While it is easy to write as many functions like this as we need:
``less_than_10``, ``greater_than_15``, etc.,
it's clear this would get tedious quickly.
Nor it is very flexible.
Each time we want to compare a different value, or use a different comparator,
we need to add a new function and recompile the program!

In addition,
if ``less_than_5`` is never used anywhere else, it seems like a bad idea to have
this special-case function elevated to the status equivalent to all other functions. 
Conceptually, it doesn't deserve
to have the status of a full-fledged function with its own name, 
callable from anywhere. 

Our goal is to avoid writing a new function for every little comparison we want to make.
One obvious solution is to add a parameter to our ``less_than_5`` function:

.. code-block:: cpp

   bool less_than(const string& str, size_t size) {
     return str.size() < size;
   }

Unfortunately, we can't use this function in :cref:`std::count_if`.
The new version of the function is arguably more generic,
but we can't use our 'improved' ``less_than`` in ``count_if``.
A predicate must be a :term:`unary function`.
In other words, it can take only 1 parameter, no more.
The 'improved' function is less useful than the old,
even though we made it 'generic'.
We need a way to pass more than one parameter
to a function that can only take 1 parameter.

Starting in C++11, a new language feature was added just for this kind of problem:
lambda expressions.
Depending on where you go, you'll also see these referred to as
closures, lambda functions, function literals, or just lambdas.

A lambda allows us to omit the separate function definition entirely and use it
within the ``num_short_strings`` function as an inline parameter to ``count_if``:

.. code-block:: cpp
   :emphasize-lines: 6
   :linenos:

   size_t num_short_strings(const vector<string>& v) {
     const string* begin = v.data();
     const auto end = begin + v.size();

     return count_if(begin, end, 
                     [](string x) { return (x.size() < 5); });
   }

The lambda on line 6 completely replaces the old function ``less_than_5``.

The general syntax for a lambda is:

.. code-block:: text

  [ captures ] (parameters) -> returnType { lambda_body; }

The capture block ``[]`` is required, even if empty.
This informs the compiler that a lambda expression is beginning.

The capture block allows the lambda to **capture** variables from outside the scope
of the lambda body and use them within the lambda.
Without a capture, no variables outside the lambda scope are visible
within the lambda.

In our previous example, it would allow us to extend num_short_strings by 
being able to pass in a value, rather than hard code the value ``5``:

.. code-block:: cpp

   size_t num_short_strings(const vector<string>& v, size_t sz) {
     const string* begin = v.data();
     const auto end = begin + v.size();

     return count_if(begin, end, 
                     [&sz](string x) { return (x.size() < sz); });
   }

The parameter is optional, but many useful standard algorithms that operate
on containers expect to be able to pass each container element one at a time
to a function that will use it.
This is exactly what ``count_if`` does.

The return type is also optional.
A lambda will ordinarily be able to deduce the correct type from the return
statement, so an explicit return is not needed.

.. code-block:: cpp

   #include <algorithm>
   #include <iostream>
   #include <string>
   #include <vector>

   using std::string;
   using std::vector;

   // Show the number of strings in the vector whose length 
   // is between min and max.
   //
   // perhaps a better name for this function is 'show_lengths_between'
   void show_lengths (const vector<string>& v, size_t min, size_t max) {
     const string* begin = v.data();
     const auto end = begin + v.size();

     std::cout << "Number of names of length \n";
     for (std::size_t i = min; i < max; ++i) {
       std::cout << i << ": \t";
       std::cout << std::count_if(begin, end,
                  [&i](string x) { return (x.size() == i); });
       std::cout << '\n';
     }

   }

   int main () {
     vector<string> names = {
       "alice", "bob", "clarissa", "dario", "elizabeth",
       "abbi", "barnabas", "clarabelle", "daniel", "ethan"
       "farouk", "gabby", "hanh phuc", "lakshay",
       "fabrice", "gail", "habeeb", "jabir", "liza",
       "muhammad", "nora", "oscar", "pauline", "roberto",
       "scarlett", "thomas", "ubelia", "victorio",
       "wahkisha", "xan", "yacov", "zabrina"
     };

     show_lengths (names, 2, 13);
   }

.. admonition:: Try this!
    
    Rewrite the rot13/rot47 program to use lambdas to perform the rotation instead of traditional function calls


Assigning a lambda to a variable
--------------------------------
A lambda does not always need to be defined within another function or
within a function parameter list.
You can define a lambda any place a normal function can be defined,
but if you do this, you must assign the lambda to a variable so that it has a name:

.. code-block:: cpp

    #include <iostream>
    int main() {
      auto lambda = [] { 
        std::cout << "Hello, lambda!\n"; 
      };
      lambda();
    }

Once a lambda has a name, it is called like a function,
using ``operator()``.
The previous example was about as simple as a lambda can get.
No return type and no parameter.

Note the use of ``auto`` when defining the type of a lambda.
In the case of a lambda, auto is not an option.
If auto was not used, what type would we supply in its place?

.. code-block:: cpp
   :emphasize-lines: 7-8, 11
   :linenos:

   int main () {
     vector<int> numbers { 1, 2, 3, 4, 5, 10, 15, 20, 25,
                          35, 45, 50 };
     const int* begin = numbers.data();
     const auto end = begin + numbers.size();

     auto gt_5 = count_if(begin, end, 
                   [](int x) { return (x > 5); });

     cout << "The # of elements > 5 is: "
          << gt_5 << ".\n";
   }

Actually, there is no way to know.
Each lambda defines a new type.
Only the compiler knows exactly what the type is, so as a programmer, 
you must use auto and allow the compiler to deduce it.

Even two identical lambdas will become two different types when compiled.

It is possible to convert between lambda expressions and function pointers,
as this video demonstrates:

.. index::
   pair: video; lambda - function pointer conversion

.. youtube:: Cmk0Tlo1eCA
   :http: https


.. index::
   pair: lambda; trailing return type

Trailing return types in lambda expressions
-------------------------------------------
When the compiler cannot deduce the correct type, 
or does not deduce the desired type,
then the return type must be specified.

Since the capture clause must be first,
we have a problem: where to specify the return type.
It can't come before the capture clause,
which is where return types are defined for normal functions.

In a lambda, the only option is to specify a :term:`trailing return type`.
It can be used with ordinary functions also, but
they are most commonly seen in lambda expressions and function templates.

A trailing return type is ``operator->``, followed by the return type.
The trailing return type must occur after the parameter list 
and before the function body.
This is true for both lambdas and normal functions.

In the following function, we want to return a type
other than what would normally be returned by the operations.

.. code-block:: cpp

   int main () {
     cout << "The return value of this odd function is: "
             [](double x, double y) -> int { 
               if (x > 5) {
                 return x + y; 
               } else if (y < 2) {
                 return x - y; 
               } else {
                 return x * y;
               }
             } (3.14159, 2.71828) << ".\n";
   }
   
Note in the previous example we defined a lambda taking two parameters and then
immediately called it using ``operator()``.

-----

.. admonition:: More to Explore

   - From: cppreference.com: 

     - C++ `lambda expressions <http://en.cppreference.com/w/cpp/language/lambda>`_ . 
     - `std::count and std::count_if <http://en.cppreference.com/w/cpp/algorithm/count>`_.

   - `Descriptions of lambda expressions` <https://msdn.microsoft.com/en-us/library/dd293608.aspx>`_ from Microsoft's MSDN


