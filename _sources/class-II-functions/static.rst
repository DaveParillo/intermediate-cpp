..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: static member functions; class

Static members
==============
It is possible to define classes that have 
static member functions and variables.
Static members are **not** stored in any instance of a class.
In fact, you don't need to ever create a class instance
in order to access static members.

Like global variables, static member lifetime is the same as the entire
program lifetime.

The static keyword is only used with the declaration of a static member, 
inside the class definition, but not with the definition of that static member:

.. code-block:: cpp

   class X { static int n; }; // declaration (uses 'static')
   int X::n = 1;              // definition (does not use 'static')

An example of a static member:

.. code-block:: cpp

   #include <iostream>

   // a class that counts how many live objects
   // currently exist
   class counter {
      static int instance_count;   // declaration, but no definition
      public:
         counter() {
            ++instance_count;
         }
         ~counter() {
            --instance_count;
         }

         int count() const {
            return instance_count;
         }
   };

   // must be defined before use
   int counter::instance_count = 0;    // definition. Now the type is complete

   void print(const counter& c) {
      std::cout << "There are " << c.count()
                << " counter objects in memory\n";
   }

   int main() {
      counter a;
      print(a);
      {
         counter a;
         counter b;
         counter c;
         print(a);
         print(b);
         print(c);
      }
      print(a);
      return 0;
   }

We could have written our counter so that we did not need an instance
member to determine the count.

.. code-block:: cpp

   #include <iostream>

   // a class that counts how many live objects
   // currently exist
   class counter {
      static int instance_count;   // declaration, but no definition
      public:
         counter() {
            ++instance_count;
         }
         ~counter() {
            --instance_count;
         }

         // can only access static member data
         static int count();
   };

   // both variable and function must be defined before use
   int counter::instance_count = 0;

   int counter::count() {
     return instance_count;
   }

   void print() {
      std::cout << "There are " << counter::count()
                << " counter objects in memory\n";
   }

   int main() {
      print();
      {
         counter a;
         print();
         {
            counter a;
            counter b;
            counter c;
            print();
         }
      }
      print();
      return 0;
   }

A static member function allows us to get the count
even if no instances of a counter class have ever been created.


-----

.. admonition:: More to Explore

   - :cref:`static members` from cppreference.com.
      Compare to :cref:`static storage duration`, which is different.

