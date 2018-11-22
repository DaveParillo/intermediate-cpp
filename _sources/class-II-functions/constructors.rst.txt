..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   single: constructors

Constructors
============
All user defined types include a constructor.
Even if you do not write one explicitly,
the compiler will write one for you.
For most of the classes and structs seen so far, 
we let the compiler generate the default constructors for us.

==================== =======================
Operation            Function Signature
==================== =======================
default constructor  ``X()``
copy constructor     ``X(const X&)``
copy assignment      ``operator=(const X&)``
move constructor     ``X(X&&)``
move assignment      ``operator=(X&&)``
destructor           ``~X()``
==================== =======================

The default constructor can be overloaded like any other function.
When you design your types, you may create constructors with
one, two, or more arguments as appropriate.

The compiler will **not** generate a default
constructor if we write any non-default ones.
The compiler may still create other default operations.

So while this is fine:

.. code-block:: cpp

   struct point {
     int x = 0;
     int y = 0;
   };

   int main () {
     point p;        // implicitly defined constructor
     point q = p;    // implicitly defined copy constructor
   }

We can only initialize our point using the default constructor.

.. code-block:: cpp

     // this works, but it's tedious
     point p;
     p.x = 8;
     p.y = 13;
     

     // This syntax is preferred, but won't compile
     point e {3,5};

If we want to initialize class members at construction time,
then we need to add custom constructors.

.. code-block:: cpp

   struct point {
     int x;
     int y;
     point (int x, int y) : x(x), y(y) {}
   };

   int main () {
     point p {3,5};  // 2 arg constructor OK
     point q = p;    // default copy constructor
     point e;        // compile error
   }

Now we can use our 2 argument constructor,
but now our old default invocation is broken.
You'll see and error like this:

.. code-block:: none

   foo.cpp:11:11: error: no matching constructor for initialization of 'point'

This is fixed by either:

- Writing our own default implementation

  .. code-block:: cpp

     point () 
       : x(3), y(5) 
     {}

- Telling the compiler to write it

  .. code-block:: cpp

     point () = default;

- Telling the compiler to delete it

  .. code-block:: cpp

     point () = delete;

  In this case, attempting the use the default constructor is still a 
  compile error, but the error is more explicit: you can't use it because it was deleted.

.. note::

   If you write a non-default constructor,
   then you should *always* write your own default constructor,
   or explicitly instruct the compiler to make it for you,
   or delete it.

   In general, take care deleting the default constructor.
   Delete it only when you are sure objects of the class will **never** 
   need to be default constructed.



Initialization syntax
---------------------
Some programmers coming to C++ from other OO languages sometimes
feel as if they have to initialize objects like this:

.. code-block:: cpp

   point p();

Even though all semester, you been writing:

.. code-block:: cpp

   std::string s;
   std::vector<int> v;
   std::random_device r;

When it comes to user defined types, sometimes it feels 'incomplete' 
if you don't include the ``()``.
Usually, those parentheses create more problems than they resolve.
This is because of an inherent ambiguity in the C++ language.
Although it seems obvious to us the statement ``point p();`` 
is a call to the default constructor and the results should be a new variable ``p``,
the compiler interprets it differently.

The basic rule is:

.. code-block:: none

   If it looks like a function call, it's a function call.


This means that in the code above, the compiler instead looks for:

- a function named ``p`` 
- that takes no arguments
- and returns an object of type ``point``

Since in this case, there is no such function, it returns an error.
Some compilers, like *clang*, will try to tell you:

.. code-block:: none

   point.cpp:7:12: warning: empty parentheses interpreted as a function declaration [-Wvexing-parse]
       point p();
              ^~
   point.cpp:7:12: note: replace parentheses with an initializer to declare a variable
       point p();
              ^~

C++ resolves this ambiguity in C++11 using the *uniform initializer syntax*.
You can use curly braces: ``{}`` instead of parentheses to initialize objects.
Braces are an extension of the initializer list syntax for containers 
and can be used even for default constructed objects.

.. code-block:: cpp

   string s{};
   vector<int> v{};
   point p{};
   string s{"hello, world!"};
   vector<int> v{1,2,3,4,5};


While the above works every time, omitting the braces entirely when not needed is preferred:

.. code-block:: cpp

   string s;
   vector<int> v;
   point p;

Initializer syntax works within constructors as well.

.. code-block:: cpp

   vector<point> redundant {
      point {2,3},
      point {3,5},
      point {8,13},
      point {21,34}
   };

   // The compiler can deduce the type in the container,
   // so we don't have to repeat the type every time
   vector<point> points {
      {2,3}, {3,5}, {8,13}, {21,34}
   };

Recall that for containers, there is a difference between 
``vector<int>(5)``
and
``vector<int>{5}``.
What's the difference?

.. reveal:: reveal-whats-the-difference

   The first version creates a vector of size 5 with no initialized values.

   The second version creates a vector of size 1 with a single value equal to 5.

Overloaded constructors
-----------------------
The same guidelines that apply to writing good functions apply to writing good
overloaded constructors.
A good class is built around good functions.
Just as with regular functions,
avoid confusing parameter lists.
Consider the following:

.. code-block:: cpp

   Date (int, int, int);

It's seems likely that the three parameters represent the
year, month, and day, but without reading the code,
there is no way to know what order.

.. code-block:: cpp

   // is this correct?
   Date d = {1776, 7, 4};

   // or this?
   Date d = {4, 1776, 7};

Even if we read the code and learn the order,
it is still probable that we will forget the order and transpose
a month and day at some point.

Instead of resigning ourselves to hoping we remember or
having debugging problems at runtime, simply defining
appropriate types improves clarity and utility:

.. code-block:: cpp

   class year {
     int y;
     public:
       year() = default;
       year(int value) : y {value} {}

       int year() { return y;}
   };
   enum class month {
     jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
   };

   // now a new date can be constructed like:
   Date d = {year{1776}, month::jul, 4};

This version is easier for programmers to remember and any errors are 
compile errors instead of runtime errors.

Telescoping constructors
------------------------
The original ``date`` class suffered from a common design problem:
too many parameters of the same type.
A closely related problem is how to provide flexibility when constructing
new objects. A common solution is to provide constructors with
different numbers of arguments:

.. code-block:: cpp

   struct date {
      date();                          // make a default date
      date(year y);                    // use a default month and day
      date(year y, month m);           // use a default day
      date(year y, month m, int day);  // specify the entire date
   };

What about the possibility of specifying ``month`` and ``day``?
How many different constructors should be allowed?
The number of permutations get unmaintainable even for a relatively
few number of parameters.

This is called a *telescoping constructor*, and is generally
considered an :term:`anti-pattern`.
That is, there are better solutions to this problem.

The easiest solution in C++ is to use default values for function parameters.
This works best when the default values are different types
and there is no need to allow every possible combination of parameters.

.. code-block:: cpp

   struct date {
      date(year y = date::current_year(), 
           month m = date::current_month(), 
           int day = date::current_day());
   };


This solution is still limited by the fact that defaults are still evaluated
left to right.
A date declaration of the form

.. code-block:: cpp

   date d {15};

won't create a date for the 15th day of the current month and year.
In addition, the solution does not work well when all (or most) 
of the parameters are the same type.
Consider this example:

.. code-block:: cpp

   class NutritionFacts {
     private:
       // variables in need of initialization to make valid object
       const double serving_size_;  // mL
       const int servings_;         // per container
       const double calories_;      // Kcal
       const double fat_;           // g
       const double sodium_;        // mg
       const double carbs_;         // g
    
     public:
       // How about this as a solution?
      NutritionFacts(double, int, double, double, double, double); 
   };


Is the proper order ``calories``, ``fat``, ``carbs``, or
``fat``, ``calories``, ``carbs``, or
something else?
Even if we give these parameters meaningful names,
there is no runtime enforcement.
It's easy to make a mistake when too many parameters are the same type.

When confronted with many optional parameters, 
a builder is an effective alternative.
Basic ideas:

- Use constructor parameters to accept mandatory parameters.
- Use a helper class (Builder) to default initialize optional parameters.
- A ``Builder::build()`` function creates a NutritionFacts object from a builder.
- The builder makes the class it helps a friend.

  This is used only avoid creating builder accessor functions.

- A conversion constructor is used to copy builder state into the
  enclosing class.


.. code-block:: cpp

   #pragma once

   #include <iostream>

   class NutritionFacts {
     private:
       // variables in need of initialization to make valid object
       const double serving_size_;  // mL
       const int servings_;         // per container
       const double calories_;      // Kcal
       const double fat_;           // g
       const double sodium_;        // mg
       const double carbs_;         // g
    

     public:
       // Only one simple constructor for mandatory parameters
       // - rest is handled by Builder
       NutritionFacts( const double serving_size, const int servings) 
         : serving_size_{serving_size}, servings_{servings},
         calories_{0}, fat_{0}, sodium_{0}, carbs_{0}
       {}

       // use this class to construct Nutritionfacts
       class Builder {
         private:
           friend NutritionFacts;
           double serving_size_ = 15;  // mL
           int servings_ = 10;         // per container
           double calories_ = 0;       // Kcal
           double fat_ = 0;            // g
           double sodium_ = 0;         // mg
           double carbs_ = 0;          // g

         public:
           Builder() = default;

           // create a NutritionFacts object from a builder
           NutritionFacts build() {
             return NutritionFacts (*this);
           }

           Builder& serving_size(const double size) { 
             serving_size_ = size; 
             return *this;
           }
           Builder& servings(const int s) { 
             servings_ = s; 
             return *this;
           }
           Builder& calories(const double c) { 
             calories_ = c; 
             return *this;
           }
           Builder& fat(const double f) { 
             fat_ = f; 
             return *this;
           }
           Builder& sodium(const double s) { 
             sodium_ = s; 
             return *this;
           }
           Builder& carbohydrates(const double c) { 
             carbs_ = c; 
             return *this;
           }

       };

       explicit NutritionFacts(const Builder& builder)
         : serving_size_{builder.serving_size_}, 
         servings_{builder.servings_},
         calories_{builder.calories_}, 
         fat_{builder.fat_}, 
         sodium_{builder.sodium_}, 
         carbs_{builder.carbs_}
       {}

       double serving_size() const { return serving_size_; }
       int servings() const { return servings_; }
       double calories() const { return calories_; }
       double fat() const { return fat_; }
       double sodium() const { return sodium_; }
       double carbohydrates() const { return carbs_; }
   };


   std::ostream& operator<<(std::ostream& os, const NutritionFacts& rhs) {
     return os << "Serving size: " << rhs.serving_size()
               << "\tServings: " << rhs.servings()
               << "\tCal: " << rhs.calories()
               << "\tFat: " << rhs.fat()
               << "\tSodium: " << rhs.sodium()
               << "\tCarbs: " << rhs.carbohydrates();
   }


When complete, the classes can be used like this:

.. code-block:: cpp

   #include "NutritionFacts.h"

   #include <iostream>

   int main() {
     // make some facts without any optional parts
     NutritionFacts cake = {75, 8};

     // create a builder
     NutritionFacts::Builder b;

     // change the state
     b.serving_size(28.4).servings(1);
     b.fat(10).sodium(2).calories(150).carbohydrates(15);

     // create a set of nutrition facts using the builder
     auto chips = b.build();

     // create nutrition facts without creating a (named)
     // temporary builder object
     // 
     NutritionFacts soda = NutritionFacts::Builder()
                           .serving_size(368).servings(1)
                           .carbohydrates(40).calories(150).sodium(15);

     std::cout << "Cake:\t" << cake << "\n";
     std::cout << "Chips:\t" << chips << "\n";
     std::cout << "Soda:\t" << soda << "\n";

     return 0;
   }

While not the most idiomatic C++ solution, 
it is something we can create and use with only the knowledge 
of classes we have so far.
We will revisit the builder pattern later after we cover inheritance.

-----

.. admonition:: More to Explore

   - `Most vexing parse (wikipedia) <https://en.wikipedia.org/wiki/Most_vexing_parse>`__
   - Item #6 "Most Vexing Parse" from 'Effective STL' by Scott Meyers (Addison-Wesley Professional).  
     Copyright 2001 Scott Meyers, 978-0-201-74962-5.
   - Builder design pattern:

     - `Builder Design Pattern 
       <http://www.oodesign.com/builder-pattern.html>`__ on oodesign.com
     - `Builder Design Pattern
       <https://en.wikipedia.org/wiki/Builder_pattern>`__ on Wikipedia
     - `Example telescoping constructor <https://gist.github.com/DavidTPate/9041099>`__
     - Effective Java, by Joshua Bloch. 
       Item #2: Consider a builder when faced with many constructor parameters


