..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: templates; class

Class templates
===============
C++ allows writing class templates using the same syntax used to write function templates.
We use templates in classes for the same reason we use templates in functions:
when we want to use variables without making a commitment to a fixed type.
A class template is **not** a class.
It defines instructions the compiler uses to create classes as needed.
No code is generated from a source file that contains only template definitions. 
In order for any code to appear, a template must be instantiated: 
the template arguments must be provided so that the compiler can generate an actual class.
Class template type cannot be deduced from the passed parameters
in the way that function templates may.

.. code-block:: cpp

   template <class T, class U>
   struct pair {
     T first;
     U second;
   };

   int main() {
     pair<char, int> symbol = {'A', 65};
     return symbol.second;
   }

A class template allows us to define a family of classes that performs the same
behaviors on many different types.
Container classes are the canonical examples of how templates
can make code maintenance easier.
The following class is a 'bag' - a general purpose container.

.. code-block:: cpp

   template <class T>
   class bag {
       std::vector<T> data;

     public:
       void add(T item);
       void erase(bag<T>::iterator item);
       void swap(bag<T> item);
   };

As this class demonstrates, a :cref:`std::vector` is a *bag*:
a general purpose container for (nearly) any type.

Recall the reason why we wanted to create a function template.
We were writing multiple copies of the same functions over and over.
The function bodies were identical except for the types used.
The same applies to class templates:
we want to avoid writing multiple classes that are the same
except for the data stored and types passed to functions.

Value class templates
---------------------
Using the information we have so far, we can create a complete
class template that supports most of the basic operations
we are generally interested in for any value type:

- Default construct
- Copy and assign values
- Use any relational operation

The following example uses some common conventions for user defined types:

- Constructors are defined in the class body if they are short
  (5 lines of code or less).
- The name *other* is used as the parameter name for another object
  of the same type when passed as the only parameter to a function.
- Binary operator overloads use *lhs* and *rhs* to denote the
  right-hand side and left-hand side operands of the binary operation.
- The `default keyword <https://en.cppreference.com/w/cpp/language/member_functions#Special_member_functions>`__ is used to instruct the compiler to create
  the default implementation for the marked special member function.

  Only special member functions may be marked ``default``.

.. code-block:: cpp

   #pragma once

   template <typename T> 
   struct item
   {
     T value;
     item() {}
     ~item() = default;

     // Copy construct and assignment
     item(const item& other) : value(other.value) {}
     item& operator=(const item& other) {
       value = other.value;
       return *this;
     }
     // Conversions from T and to T:
     explicit item(const T& x) : value(x) {}
     explicit operator T() const { return value; }
   };

   // Non-member functions

   // Relational operators
   template <typename T> 
     inline bool operator==(const item<T>& rhs, const item<T>& lhs) {
       return rhs.value == lhs.value;
     }
   template <typename T> 
     inline bool operator!=(const item<T>& rhs, const item<T>& lhs) {
       return !(rhs == lhs);
     }
   template <typename T> 
     inline bool operator<(const item<T>& rhs, const item<T>& lhs) { 
       return rhs.value < lhs.value;
     }
   template <typename T> 
     inline bool operator>(const item<T>& rhs, const item<T>& lhs) {
       return lhs < rhs;
     }
   template <typename T> 
     inline bool operator<=(const item<T>& rhs, const item<T>& lhs) {
       return !(y < rhs);
     }
   template <typename T> 
     inline bool operator>=(const item<T>& rhs, const item<T>& lhs) {
       return !(rhs < lhs);
     } 

   // stream extraction
     template <typename T> 
  inline std::ostream& operator<<(std::ostream& os, const item<T>& lhs) {
    return os << lhs.value;
  }


Friend or non-friend?
---------------------
Some operators must be implemented as member functions,
``operator=``, ``operator[]``, and member access - 
both ``operator.`` and ``operator->>``,
because the language requires it.
We have choices where we define the others.

Some are commonly implemented as non-member functions,
because their left operand cannot be modified by you. 
The most prominent of these are the stream insertion and extraction operators.
The left operands are stream classes from the standard library which you cannot change.

For operators where you have to choose to either implement them as a
member function or a non-member function, 
use the following guidelines: 

#. If it is a **unary operator**, 
   then implement it as a **member** function.
   For example, ``operator++``.

#. If a binary operator treats both operands equally
   then implement as a **non-member** function.

   Generally, neither operand is modified in this situation.
   The relational operators all fall into this category.

#. If a binary operator does not treat both of its operands equally 
   then consider making it a member function.

   If the left-hand side operator is modified in the operation,
   or the function returns the ``this`` pointer, then
   it should be a member function of the left hand operand type.

   Otherwise, it can be implemented as a non-member function.

In the previous section, the relational operators were all declared as
*non-friend non-member* functions.
This is considered best practice by many programmers.

.. epigraph::

   Prefer writing non-friend non-member functions

   -- Item 44 of *C++ Coding Standards*, by Herb Sutter and Andrei Alexandrescu


Compare to the functionally similar friend, member overload
for ``operator==``:

.. code-block:: cpp

   friend bool operator==(const item& x, const item& y) {
     return x.value == y.value;
   }

- A non-friend function does not automatically know that a function is
  part of a class template unless told.

  This is why the non-friend functions repeat the template declaration
  from the ``struct``.

- The friend functions declared in the class are implicitly *inlined*.
  The compiler *may* replace function calls to these functions with
  in-line copies of the function body.
  The compiler is not obligated to do so, but usually does.

  To get the same behavior from non-member functions, the :cref:`inline`
  keyword is used.

- The ``friend`` keyword is often used to provide private member access to
  non-member functions.
  In the case of the ``item`` struct, this wasn't needed.

  The use of friend here prevents the ``this`` pointer from being passed
  to functions declared (and in this case defined) in the data structure
  body.


-----

.. admonition:: More to Explore

   - :cref:`friend specifier`
   - Item 44 from `C++ Coding Standards, Sutter and Alexandrescu, 2004. <https://www.google.com/search?client=safari&rls=en&q=isbn+978-0321113580>`__

