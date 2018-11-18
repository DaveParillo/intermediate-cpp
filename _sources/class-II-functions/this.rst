..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: this pointer
   pair: keyword; class
   pair: keyword; ``*this``


'this' pointer
================
The :cref:`this pointer` is a value that stores the address of the current object.
Every non-static class member function is passed the ``this`` pointer.
Whenever a member function or variable is used in a function,
``this->`` is automatically added before the name, 
resulting in a member access expression.

.. code-block:: cpp

   class example
   {
       int x;
       int y;

       public:
    
          void foo()
          {
              x = 6;       // same as this->x = 6;
              this->x = 5; // explicit use of this->
          }
       
          void foo() const
          {
            // x = 7; // Error: *this is constant
          }
       
          void foo(int x) // parameter x shadows the member with the same name
          {
              // x = x;       makes no sense in this function
              this->x = x; // unqualified x refers to the parameter
                           // 'this->' required for disambiguation
          }
    
          // No ambiguity in C++11 initializer syntax
          example (int x) 
            : x(x),      // use parameter x to initialize member x
              y(this->x) // use member x to initialize member y
          {}
    
   };

The this pointer can only be used in a member function.
It is a compile error to use ``this`` outside of a member function.

Although ``this`` is a pointer, 
it is *immutable*.
You can't change it and have it point to some other object.
It *always* points to the current object.

That is why the this pointer can't be used in a static member function.
Static members are members of the **class**.
There is only a single copy that all objects of a class share.
A static member has no way to determine which object instance
the this pointer refers to.


-----

.. admonition:: More to Explore

   - :cref:`this pointer`

