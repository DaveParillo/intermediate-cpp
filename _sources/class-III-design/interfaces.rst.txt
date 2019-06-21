..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: abstract base class; interface
   pair: keyword; virtual

Abstract base classes
=====================
Often the functions declared in a base class cannot be defined
in the base class, but instead can only be implemented in the derived
classes.  
Consider the shape example from the section :doc:`inheritance`.
How might we add ``draw`` and ``erase`` functions?

.. graphviz:: 
   :alt: Shape inheritance

   digraph "shape"
   {
     edge [fontname="BitstreamVeraSans",
           fontsize="10",
           labelfontname="BitstreamVeraSans",
           labelfontsize="10",
           dir="back",
           arrowtail="onormal",
           style="solid",
           color="midnightblue"];
     node [fontname="BitstreamVeraSans",
           fontsize="10",
           height=0.2,
           width=0.4,
           color="black",
           fillcolor="white",
           shape=record,
           style="filled"];
     shape [
       label="{shape\n||+ ~shape()\l+ draw()\l+ erase()\l+ move()\l}",
       fillcolor="lightblue"];
     shape -> circle;
     circle [
       label="{circle\n||+ draw()\l+ erase()\l}"];
     shape -> rect;
     rect [label="{rectangle\n||+ draw()\l+ erase()\l}"];
     shape -> tri;
     tri [label="{triangle\n||+ draw()\l+ erase()\l}"];
   }

There is no situation where drawing a 'generic shape' makes sense.
A shape might define general behaviors like ``draw()``,
but there is no all-purpose draw function.
The shape class *can't* know the implementation ahead of time.
There is a way to code this in C++: by creating an 
:term:`abstract base class`.
In C++, an abstract class is any class with at least
one unimplemented function:

.. code-block:: cpp

   class enum Color {RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET};

   class shape {
       Color color_ = Color::BLUE;
     public:
       virtual ~shape() = default;
       void   color (Color new_color) { color_ = new_color; }
       Color  color ()  const         { return color_; }
       virtual void   move();      // implemented in shape.cpp
       virtual void   draw() = 0;
       virtual void   erase() = 0;
   };

The functions ``draw`` and ``erase`` are marked :cref:`virtual`.
Note the ``= 0;`` at the end of the declaration.
Referred to as the *pure specifier*,
this marks these functions as *pure virtual*.
It is the presence of at least 1 pure virtual function that
make a class *abstract*.
In this case, a ``shape`` does not know how to draw itself.
Code that can only properly be implemented in the class that
properly 'owns' the behavior (``draw`` and ``erase``)
should be implemented in the *derived* classes.

Because a class the defines a pure virtual function cannot implement it,
that means any class containing a pure virtual function can never be
instantiated.
Given the shape class defined here, this code:

.. code-block:: cpp

   shape s;

will not compile.

A class containing at least one pure virtual function can **only**
be used as a base class.

.. code-block:: cpp

   class circle: public shape {
      double radius = 1;
     public:
       void   draw()  const override;
       void   erase() override;
   };

   class rectangle: public shape {
      double ht = 1;
      double wd = 1;
     public:
       void   draw()  const override;
       void   erase() override;
   };

There is no requirement that pure virtual functions be implemented
in the first derived class that inherits from a base.
A derived class *could* implement it,
but can itself remain abstract.
A non-abstract derived class can make itself abstract
by declaring a new pure virtual function,
or by declaring an existing virtual function as pure virtual.

.. code-block:: cpp

   struct Base {
       virtual void f() = 0; // pure virtual
   };
    
   struct X : Base {
       void f() override {} // non-pure virtual
       virtual void g();     // non-pure virtual
   };
    
   struct Y : X {
       void g() override = 0; // pure virtual overrider
   };
    
   struct Z : Y {
       void g() override {}; // non-pure virtual
   };
    
   int main()
   {
       Base b;      // Error: abstract class
       X x;         // OK

       Base& b = x; // OK to reference abstract base
       b.f();       // virtual dispatch to X::f()
       Y y;         // Error: abstract class (final overrider of g() is pure)
       Z z;         // OK: final overrider of g() is non-pure
   }

Interfaces
----------
When an abstract base class declares no member variables and
declares **only** pure virtual functions,
then the class is referred to as an *interface*.
Technically, *every* class with at least 1 member function defines
an interface, however, some languages give interface classes special treatment,
so the term has fallen into use in C++ also.

We can rewrite the abstract class ``shape`` and convert it
to behave like an interface:

.. code-block:: cpp

   class shape {
     public:
       virtual ~shape() = default;
       virtual void   move() = 0;      // implemented in shape.cpp
       virtual void   draw() = 0;
       virtual void   erase() = 0;
   };

Notice we still have a default implementation for move,
even though we declared it to be pure virtual.

Some experts (for example Herb Sutter in his article *Virtuality*,
advocate it as a best practice to always define virtual methods private, 
unless there is a good reason to make them protected. 
Virtual methods, in their view, should never be public, 
because they define the class interface, 
which must remain consistent in all derived classes.
Protected and private virtuals define the class customizable behavior,
and there is no need to make them public.
A public virtual method would define both interface and a customization point,
a duality that could reflect weak design.

The primary problem with this type of public interface is that it doesn't
hold up well to changing requirements.
If ``draw`` or ``erase`` need to return values,
or if we need to add more pure virtual functions,
every derived class is affected.

We can protect ourselves from future changes using the *Template Method*
design pattern.
The Template Method defines the steps of an algorithm and allows
derived classes to provide implementations for one or more steps:

.. code-block:: cpp

   class hot_drink {
      public:
        ~hot_drink() = default;
        void prepare();       // the template method

      private:
        // ALL implementation steps are private
        virtual void brew() = 0;
        virtual void add_extras();

        // non-virtual mandatory parts of the recipe
        void heat();
        void pour();
   };

   void hot_drink::prepare()
   {
     heat();
     brew();        // call to the derived class
     pour();
     add_extras();  // optionally call derived class
   }
   void hot_drink::add_extras()
   {
     // this default implementation could just be a stub
     // it can optionally be customized by a derived class
   }

We now have a generic framework for making all kinds of drinks,
assuming they follow this basic recipe: coffee, tea, etc.

It may be surprising that private virtuals can be overridden, 
let alone are valid.
You have likely been taught that private members in a base class 
are not accessible in classes derived from it, which is correct.
However this inaccessibility **by** the derived class 
does not have anything to do with the virtual call mechanism,
which is **to** the derived class.

What good is a method that the derived class can’t call?
Even though the derived class can’t call it in the base class, 
the base class can call it --- down to the appropriate derived class.
And that’s what the Template Method pattern is all about.

In our coffee shop, we want to write the base class once,
but still want the flexibility to think of new drink recipes today.
The base class code we wrote a year ago will call
the private virtual methods in its recipe.
This might result in the base class calling code that did not exist
when the base class was originally written.

Once our base class is done, we can implement derived classes:

.. code-block:: cpp

   class coffee : public hot_drink {
      public:
        ~coffee() = default;
      private:
        virtual void brew() = 0;
        virtual void add_extras();
   };

   void coffee::brew()
   {
     // drip water through grinds
   }
   void coffee::add_extras()
   {
     // add milk and sugar
   }

   class tea : public hot_drink {
      public:
        ~tea() = default;
      private:
        virtual void brew() = 0;
        virtual void add_extras();
   };

   void tea::brew()
   {
     // steep tea in water
   }
   void tea::add_extras()
   {
     // add lemon
   }

And use it:

.. code-block:: cpp

   int main() {
     coffee c;
     c.prepare();

     tea t;
     t.prepare();
   }


The final specifier
-------------------
Added in C++11,
this keyword specifies that a virtual function cannot be overridden 
in a derived class or that a class cannot be inherited from.

When used in a virtual function declaration or definition, 
:cref:`final` ensures that the function is virtual and specifies
that it may not be overridden by derived classes.
Attempting to override a final function is a compile error.

.. code-block:: cpp

   struct Base
   {
       virtual void foo();
   };
    
   struct A : Base
   {
       void foo() final; // A::foo is overridden and it is the final override
       void bar() final; // Error: non-virtual function cannot be overridden or be final
   };
    
   struct B final : A // struct B is final
   {
       void foo() override; // Error: foo cannot be overridden as it's final in A
   };
    
   struct C : B // Error: B is final
   {
   };


-----

.. admonition:: More to Explore

   - From cppreference.com:
     - `virtual function specifier <https://en.cppreference.com/w/cpp/language/virtual>`__
     - `Abstract classes <https://en.cppreference.com/w/cpp/language/abstract_class>`__
     - `final specifier <https://en.cppreference.com/w/cpp/language/final>`__
   - `Virtuality <http://www.gotw.ca/publications/mill18.htm>`__ by Herb Sutter

