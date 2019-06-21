..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: class; operator overloads

Operator overloads
==================
There are many reasons to want to overload the builtin operator
functions for user defined types.

**Case 1**

Operator overloads are *required* for some containers in the STL.
Notably :cref:`std::set`,
which requires any type used in a set overloads ``operator<``,
or the operator defined for the set if a custom comparison
function is defined.
Similarly, :cref:`std::map` requires ``operator<``
and :cref:`std::unordered_map` requires both that and ``operator==``.

Classes that do not overload these comparison operators
can't be used in these containers.

Overloading these operators is useful in any conditional expression,
but only makes sense when creating a class
with data members that are *comparable*.

**Case 2**

C++ provides many builtin types and operators to manipulate them.
We want new user defined types to be as simple and intuitive to use as
the builtin types.

For example, finding the roots of a quadratic equation:

.. code-block:: cpp

   double root1 = (-b + sqrt(b*b - (4 * a * c))) / (2 * a);

When all the variables are builtin types, 
this looks familiar.
But without operator overloads, a rational number class
would be a pain to read and use.

.. code-block:: cpp

   Complex  root = Complex(0,0);
   Rational a    = Rational(2,3);
   Rational b    = Rational(6,1);
   Rational c    = Rational(5,3);
   Complex tmp   = sqrt(b.multiply(b)
                         .minus(c.multiply(a.multiply(4))));
   root.setComplex(b.invSign().plus(tmp.divide(a.multiply(2))));

When *everything* has to be a named function,
and the standard operators can only be used on builtin types,
the result is not as clean as we would like.

What we want here is the ability to use familiar semantics
on user defined types.

.. code-block:: cpp

   Rational a {2,3}, b{6,1}, c{5,3};
   Complex root1 = (-b + sqrt(b*b - (4 * a * c))) / (2 * a);

Overloading the standard operator functions
make this possible.

In C++, operators are overloaded in the form of functions with special names. 
For example, ``a+b`` and ``operator+(a,b)`` both call
the same function.

As with other functions, 
overloaded operators can generally be implemented either as a member 
function of their left operand's type or as non-member functions. 

Most of the work in overloading operators is boiler-plate code. 
Not surprising, 
since most operators defer their actual work to plain functions. 
The programming community has already thought long and hard on
techniques to make overloads efficient and easy to maintain.


.. index:: overloading guidelines

Basic overloading guidelines
----------------------------

Most C++ operators can be overloaded.
You cannot change the meaning of operators for built-in types in C++. 
Operators can only be overloaded when at least 1 operand is a user-defined type. 
Other rules of overloads still apply:
overloads for a specific function signature can only be used once.

Not all operators can be overloaded in C++. 
Those that cannot be overloaded are: 
``operator .``, ``operator ::``, 
``operator sizeof``, ``operator typeid``,
``operator .*``, and ``operator ? :``.

When it comes to operator overloading in C++, 
there are basic guidelines you should follow. 
As with all such guidelines, there are exceptions. 
The goal of operator overloading is to make classes *easier*
to use and to make them behave more like builtin types.
Keep that in mind when overloading.

#. Whenever the meaning of an operator is not obviously clear and undisputed, 
   it should not be overloaded. 

   Instead, provide a function with a well-chosen name.
   It is hard to understand the semantics behind the
   operator unless the use of the operator in the application 
   domain is well known and undisputed.
   Contrary to popular belief, this is hardly ever the case.

#. Always stick to the well-known semantics for the operator.

   C++ poses no limitations on the semantics of overloaded operators. 
   Your compiler will happily accept code that implements the binary + operator to 
   subtract from its right operand.
   However, the users of such an operator would never suspect the expression a + b 
   to subtract a from b.
   Of course, this supposes that the semantics of the operator in the application 
   domain is undisputed.

#. Always provide all out of a set of related operations.

   Operators are related to each other and to other operations. 

   - If your type supports ``a + b``, 
     then users will expect to be able to call ``a += b``, too. 
   - If it supports prefix increment ``++a``,
     then ``a++`` is likely expected also.
   - If they can check whether ``a < b``, 
     then most users expect to also to be able to check ``a > b``. 
   - If copy-construction is allowed, then assignment is expected.


The remaining sections describe the specific techniques and
function signatures for some of the most common operator overloads.

Assignment operator
-------------------
The copy assignment operator is called when an object appears 
on the left side of an assignment expression.

The canonical copy-assignment operator is expected to perform 
no action on self-assignment, and to return the ``lhs`` by reference:

.. code-block:: cpp

  T& T::operator=(const T& other)
  {
    // copy data from other to
    // current instance
    return *this;
  }


In those situations where copy assignment cannot benefit from resource reuse 
(it does not manage a heap-allocated array and does not have a 
member that does, such as a member std::vector or std::string), 
there is a popular convenient shorthand: 
the copy-and-swap assignment operator,
which takes its parameter by value 
swaps with the parameter, and lets the destructor clean it up.

.. code-block:: cpp

   // copy/move constructor is called to construct other
   T& T::operator=(T other) noexcept 
   {
       using std::swap;
       swap(*this, other); // exchange resources between *this and other
       return *this;
   } 

When the function ends,
the destructor of ``other`` is called to release the resources 
formerly held by ``*this``.
A custom swap function for the user defined type ``T``
is required for this technique to work:

.. code-block:: cpp

   friend void swap(T& first, T& second)
   {
     using std::swap;

     // by swapping the members of two objects,
     // the two objects are effectively swapped
     swap(first.size_, second.size_);
     swap(first.value_, second.value_);
     // repeat for each member
   }




Insertion and extraction operators
----------------------------------

The bitshift operators ``<<`` and ``>>``, 
although still used in hardware interfacing for the bit-manipulation functions 
they inherit from C, 
have become more prevalent as formatted stream operators in C++.

The overloads of ``operator >>`` and ``operator <<`` that take a 
:cref:`std::istream` & or :cref:`std::ostream` & as the left hand argument
are known as insertion and extraction operators. 

Since these operators change their left argument (they alter the stream), 
they should, according to the rules of thumb, 
be implemented as members of their left operand’s type. 
However, their left operands are streams from the standard library, 
and while most of the stream output and input operators defined by the 
standard library are indeed defined as members of the stream classes, 
when you implement output and input operations for your own types, 
you cannot change the standard library’s stream types. 
So clearly, these overloads cannot be stream member functions.

It is common, however, to see C++ examples posted on the internet that
define these overloads as friends.
The advantage of making these functions friends is they have access
to the private data of the class, if needed.
The disadvantage of making these functions friends is that
you may decide to stream data out of a class that is otherwise 
not accessible.

Why is that bad?

Josh Bloch in *Effective Java*, dedicates an entire section to this topic.
Effective Java discusses the ``toString()`` overload,
but it serves a similar purpose to ``operator <<`` in the Java language.

When you create
an output function that streams data out of your class
that is not available through any other function,
then some users will use your stream function just
to get their hands on your private data.

- If your data needs to be part of the output stream,
  then make a function to access it.
- If you have functions that provide access to every
  private member that is part of the stream,
  then you don't need it to be a member function
  or a ``friend``.

That’s why you need to implement these operators for your own types as 
non-member non-friend functions. The canonical forms are:

.. code-block:: cpp

   std::ostream& operator<<(std::ostream& os, const T& rhs)
   {
     // write rhs to stream

     return os;
   }

   std::istream& operator>>(std::istream& is, T& rhs)
   {
     // read rhs from stream

     if( /* could not construct T from stream */ ) {
       is.setstate(std::ios::failbit);
     }

     return is;
   }


Function call operator
----------------------
When a user-defined class overloads the function call operator, 
``operator()``, it becomes a FunctionObject type.
A function object is a class that can be called as if it was a function.
Many standard algorithms, from :cref:`std::sort`` to :cref:`std::accumulate`
accept objects of such types to customize behavior. 
Prior to C++11 with :cref:`std::function` and lambda expressions,
function objects were an important way to pass functions to algorithms.

There are no particularly notable canonical forms of ``operator()``,
but to illustrate the usage:

.. code-block:: cpp

   struct Sum {
       int sum;
       Sum() : sum(0) { }
       void operator()(int n) { sum += n; }
   };
   Sum s = std::for_each(v.begin(), v.end(), Sum());

.. note::

   Unlike lambda expressions and function pointers,
   when passing a function object to an algorithm,
   the function call operator **must** be included.

A function call overload can be overloaded 
to take any number of additional arguments, including zero.
A single class can contain more than 1 function call operator overload,
subject to the other rules of function overloading.


Relational operators
--------------------
Standard algorithms such as std::sort and containers such as 
:cref:`std::set` expect ``operator <`` to be defined, by default, 
for the user-provided types, and expect it to implement strict 
:cref:`std::weak_ordering`.
Strict weak ordering defines members of a set as *comparable* to each other.
The general signature for these non-member functions is:

.. code-block:: cpp

   inline bool operator<(const T& lhs, const T& rhs)
   {
      // compare the data in left-hand side and right-hand side objects
      // for less than
   }
   
   inline bool operator==(const T& lhs, const T& rhs)
   {
      // compare the data in left-hand side and right-hand side objects
      // for equality
   }


An idiomatic way to implement strict weak ordering for a structure is to use 
lexicographical comparison provided by :cref:`std::tie`:

.. code-block:: cpp

   struct Record
   {
       std::string name;
       unsigned int floor;
       double weight;
   };

   inline bool operator<(const Record& lhs, const Record& rhs)
   {
      // parameters passed to each tie must be in the same order
      // or this will always return false
      return std::tie(lhs.name, lhs.floor, lhs.weight)
           < std::tie(rhs.name, rhs.floor, rhs.weight);
   }

If some of the data required for the comparison is private
and has no function to access the data members,
then you may need to make your relational operators friends.

If you do need to define ``operator<`` as a member function,
then the left-hand side of the operator will be the this pointer.
The signature of the operator overload changes:

.. code-block:: cpp

   bool operator<(const T& rhs) const 
   { 
      /* do actual comparison with *this */
   }

Note that this form of the overload must be ``const``
in order to compile as a member function.

Once you have defined ``operator<`` and ``operator==``,
there is no need to rewrite the comparison logic again.
It is much better to implement the remaining comparison functions
in terms of ``<`` and ``==``.

.. code-block:: cpp

   // note the operands swapped inside the function body
   inline bool operator> (const T& lhs, const T& rhs){ return   rhs < lhs; }

   inline bool operator<=(const T& lhs, const T& rhs){ return !(lhs > rhs); }
   inline bool operator>=(const T& lhs, const T& rhs){ return !(lhs < rhs); }

   inline bool operator!=(const T& lhs, const T& rhs){ return !(lhs == rhs); }

.. note::

   Since C++20, all 6 comparison operators are defined if the 
   three-way comparison operator ``operator<=>`` is defined, 
   and *that* operator, in turn, is generated by the compiler if it is 
   defined as defaulted:

   .. code-block:: cpp

      struct Record
      {
          std::string name;
          unsigned int floor;
          double weight;
          auto operator<=>(const Record&) = default;
      };
      // records can now be compared with ==, !=, <, <=, >, and >=


Binary arithmetic operators
---------------------------
Binary operators are typically implemented as non-members to maintain symmetry.
For example, when adding a complex number and an integer, 
if ``operator+`` is a member function of the complex type, 
then addition doesn't behave in a way most people expect:

.. code-block:: cpp

   complex a = {1,1};
   int b = 3;
   complex c = a+b;  // compiles
   complex d = b+a;  // error


As a member function, only complex+integer would compile, not integer+complex.
Since for every binary arithmetic operator there exists a corresponding 
compound assignment operator, 
canonical forms of binary operators are implemented in terms of their 
compound assignments:

.. code-block:: cpp

   class T
   {
    public:
     T& operator+=(const T& rhs) // compound assignment (does not need to be a member,
     {                           // but often is, to modify the private members)
       // add rhs to *this
       return *this;             // return the result by reference
     }
   };

The normal addition is often implemented as a non-friend non-member:

.. code-block:: cpp

     T operator+(      T lhs,    // passing lhs by value helps optimize chained a+b+c
                 const T& rhs)   // otherwise, both parameters may be const references
     {
       lhs += rhs; // reuse compound assignment
       return lhs; // return the result by value (uses move constructor)
     }

The remaining binary arithmetic operators are implemented using the same pattern.

Increment and decrement operators
---------------------------------
When the postfix increment and decrement appear in an expression, 
the corresponding user-defined function (``operator++`` or ``operator--``) 
is called with an integer argument 0. 
Typically, it is implemented as ``T operator++(int)``, 
where the argument is ignored. 
The postfix increment and decrement operator is usually implemented 
in terms of the prefix version:

.. code-block:: cpp

   struct T
   {
       // prefix increment
       T& operator++()
       {
           // actual increment takes place here
           return *this;
       }

       // postfix increment
       T operator++(int)
       {
           T tmp(*this); // copy
           operator++(); // pre-increment
           return tmp;   // return old value
       }
   };

Conversion operators
--------------------
C++ allows you to create operators to convert between your type and other ADT's.
A conversion function is declared like a non-static member function or 
member function template with 

- no parameters, 
- no explicit return type, and 
- with the name of the form:

  .. code-block:: cpp

     // implcit conversion
     operator int() const { /* return int version of type */ }

     // explicit conversion
     explicit operator int() const { /* return int version of type */ }

Suppose we want to concatenate a Rational to a string?

.. code-block:: cpp
 
   Rational a {2,3};
   std::string s = {"A = "};
   s += a;                   // will not compile

Your compiler may present something like:

.. code-block:: none

   error: no viable overloaded '+='
   candidate function not viable: 
   no known conversion from 'Rational' to
   'const std::__1::basic_string<char>' for 1st argument
   _LIBCPP_INLINE_VISIBILITY basic_string& operator+=(const basic_string...


Defining a conversion operator for ``std::string`` allows this conversion 
to happen:

.. code-block:: cpp
 
   Rational::operator std::string() const {
      std::stringstream ss;
      ss << numerator << '/' << denominator;
      return ss.str();
   }
    
A class constructor taking a single argument can also be seen as
converting its argument into the type:

.. code-block:: cpp
 
   Rational (int x) {
      numerator = x;
      denominator = 1;
   }

And an expression like this works:

.. code-block:: cpp

   Rational r = 3;

The conversion both of these previous cases,
for the ``string`` and the ``int`` happened implicitly.
Often, we don't want types to **always** implicitly
convert to a user-defined type:

.. code-block:: cpp

   void func (Rational r);

   int main () {
      func(3);   // this works
   }

The call to ``func()`` works because Rational has a conversion
constructor that converts int values to Rational ones.
C++ provides a keyword ``explicit`` that requires
a cast - it inhibits the implicit conversion of a user defined type.

.. code-block:: cpp
 
   explicit Rational (int x) { . . .

   explicit operator std::string() const { . . . 

And the previous expressions need casts
or an explicit constructor call:

.. code-block:: cpp

   Rational r = Rational(3);       // constructor
   func(Rational(3));              // constructor
   func(static_cast<Rational>(3)); // cast
   func((Rational)3);              // c-style cast

   // explicitly convert a Rational to string
   // using functional conversion syntax
   std::string s = string(Rational(3));





-----

.. admonition:: More to Explore

   - `Operator overloading in C++ <https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading>`__ from stackoverflow.  
     Much of the content in this section was taken from there.
   - `Comparison operators <https://en.cppreference.com/w/cpp/language/operator_comparison>`__
     from cppreference.com.
   - `Named requirements: Compare <https://en.cppreference.com/w/cpp/named_req/Compare>`__.
     This page also includes a list of the parts of the STL that expect types
     that satisfy this requirement.
   - Effective Java, 3rd edition, Joshua Bloch. Addison-Wesley Professional, Jan 2018.
     
     The section regarding overloading toString is in section 12 of the 
     third edition and section 10 of the second.
 
