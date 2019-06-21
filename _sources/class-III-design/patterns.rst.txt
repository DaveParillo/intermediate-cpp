..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   single: design patterns
   pair: classes; patterns

Design patterns
===============
A software design pattern is a general, 
reusable solution to a common software problem.
It is not an actual implementation,
but rather an idea.

Design patterns gained popularity in computer science after the book 
*Design Patterns: Elements of Reusable Object-Oriented Software*
was published in 1994 by (Gamma et al.).
The book had 4 authors and together they became known as the
"Gang of Four", or even more briefly the "GoF". 

Design patterns are useful for several reasons:

- They provide useful solutions to common problems
- They provide a common vocabulary between programmers when discussing a design
- They exploit lessons learned by other developers


.. epigraph::

   ... with patterns you get *experience* reuse.

   -- Head First Design Patterns, Freeman and Robson, 2014, p. 1.

.. index:: 
   pair: inheritance; strategy pattern

Fixing an inheritance problem
-----------------------------
Recall our flying penguin problem from the section on :doc:`inheritance`:

.. graphviz:: 
   :alt: Bird inheritance

   digraph "bird"
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
           fillcolor="lightblue",
           shape=box,
           style="filled"];
     bird [shape=record,
       label="{bird\n|-wingspan: double|+fly(): void\l+eat(): void\l}"];

     bird -> hawk;
     bird -> owl;
     bird -> penguin;
     bird -> robin;
   }

This type of design error is actually common.

It's easy to overlook a design error, in this case flying penguins.
Part of what makes these errors problematic is that design errors
that actually get delivered in the final product are among the most
expensive software errors to fix.

So how do we fix our bird design?

We **could** just override the ``fly`` method for penguins
and have the override do nothing.
This might solve our immediate problem, but it's not a general
solution to this problem:

- It doesn't work as well for non-void functions.
  In this case, ``fly`` -- a void function -- really could do nothing
  A non-void function **must** return something.
  If the function returns something, but that 'something' actually means
  'nothing', then we have another design problem.
  This value now represents a marker that every caller of the function
  might need to handle and understand that no action was taken.
- What happens when we need behaviors other than ``fly``?
  If every time we have an exception case for a derived type
  and we create overrides that do nothing,
  then it can become difficult to understand the true capabilities
  of any object in the hierarchy just by looking that the interface.

  You have to examine the *code* to see how each (or if) an 
  interface was *implemented*.

  Any design that requires us to look at the source code before we can
  completely understand it is not a design we want to use.

Another problem with the existing design is that it encourages
duplication in derived classes.
For example, let's assume we need to model bird flying behavior.
Most birds don't just 'fly'.
They soar, flock, flit about, dive, or don't fly at all.
There are many thousands of different kinds of birds,
but relatively few ways of flying.

We *could* decide to solve this problem using an interface:

.. graphviz:: 
   :alt: Flying interfaces

   digraph "bird"
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
           fillcolor="lightblue",
           shape=record,
           style="filled"];
     flyable [
       label="{\<\<interface\>\>\nflyable\n||+fly() = 0: void\l}"];
     bird [
       label="{bird\n|-wingspan: double|+eat(): void\l}"];
    
     hawk [
       label="{hawk\n||+fly(): void\l}"];
     owl [
       label="{owl\n||+fly(): void\l}"];
     robin [
       label="{robin\n||+fly(): void\l}"];
     penguin [shape=box];
    
     bird -> hawk;
     bird -> owl;
     bird -> penguin;
     bird -> robin;
     flyable -> hawk [style=dotted];
     flyable -> owl [style=dotted];
     flyable -> robin [style=dotted];
   }

This does allow limiting the flying behavior to those birds that actually fly,
but at a high cost.
Now every bird that *does* fly needs to reimplement the code for ``fly()``.
Derived classes cannot inherit code from each other.
Future maintenance of all the duplicated code could be expensive.
Our current situation:

- Not all birds fly, so inheritance is not the right choice
- A simple interface solves the inheritance problem,
  but creates an unacceptable maintenance burden.

There must be a better option.

.. note::
  
   **Accommodating change**

   How can we isolate the parts of a system that change from the parts
   that do not change?
   By isolating the parts most likely to change frequently,
   we can later change or extend them without impacting other parts of the system.

   This simple idea is the motivation behind nearly every design pattern.

.. index:: 
   pair: design pattern; strategy

Strategy pattern
................
We can think of flying as a *strategy* different birds employ to move around.
Birds don't *inherit* a fly behavior, they *have it*.
The centerpiece of the solution is to isolate many different
types of flying behavior behind a single class that stores
a pointer to a function implementing the behavior.
Each implementation defines a different **strategy** for the interface.

.. graphviz:: 
   :alt: Flying strategy

   digraph "bird"
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
           fillcolor="lightblue",
           shape=record,
           style="filled"];
     fly_behavior [
       label="{fly_behavior\n|-strategy: std::function\<void()\>|+fly(): void\l}"];
   }

Any callable entity (function, function object, or lambda) is
a potential strategy that derived classes of a bird can now use.

.. code-block:: cpp

   #include <iostream>
   #include <functional>
   #include <utility>

   #define FunctionObject typename 

   // an alias to avoid copying std::function ... everywhere
   using fly_strategy = std::function<void()>;

   class fly_behavior {
     public:
       template<FunctionObject F>
       explicit fly_behavior(F strategy) 
         : strategy {strategy}
       { }

       void fly() { strategy(); }

     private:
       fly_strategy strategy;
   };

   // a function object that implements a strategy
   struct soar
   {
     void operator() () {
      std::cout << "fly by soaring.\n";
     }
   };

   // a free function can also implement a strategy
   void no_flying_allowed() {
     std::cout << "I don't fly.\n";
   }


The base class now *delgates* the fly behavior to the strategy
instead of either defining a single fixed behavior or forcing every
derived class to create one.
In languages without lambda expressions, each implemented strategy
is usually implemented as a separate class, each inheriting from the base
strategy class.
In C++, an inheritance based solution is possible, but not required.
There is no 'best' solution - your needs must drive the final
design decision.
In general, if the strategy also needs to store state information,
then implement as a class or function object.
If the strategy is stateless, then implement a functional solution.

.. code-block:: cpp

   class bird {
     fly_strategy strategy = soar();

     public:
     bird () = default;
     explicit bird(fly_strategy strategy)
      : strategy(strategy)
     {}
     ~bird () = default;

     // change strategy mid-stream
     void fly_behavior (fly_strategy new_strategy) {
      strategy = new_strategy;
     }

     void fly() {
      strategy();
     }
   };

In this example, a bird may

- default construct the default soaring strategy, or
- set a strategy when constructed, or
- change the strategy at some point after construction.

An example of birds using the strategy:

.. code-block:: cpp

   // a hawk can use the default soar behavior
   class hawk : public bird {
     public:
      hawk() = default;
   };

   // this penguin defines its fly behavior using a free function
   class penguin : public bird {
     public:
      penguin()
        : bird(no_flying_allowed)
      {}
   };

   int main() {
     hawk h;
     h.fly();

     penguin p;
     p.fly();

     // change the behavior for just this penguin
     p.fly_behavior(
        [](){ 
         std::cout << "With a rocket pack, now I can fly!!\n";
        }
     );
     p.fly();

     return 0;
   }

Notice that we fixed our inheritance problem by using :term:`composition`.
Not only did composition allow us to encapsulate a family of behaviors,
it also allowed a simple hook to enable changing the behavior at runtime.

.. index:: 
   pair: design pattern; chain of responsibility

Chain of Responsibility pattern
-------------------------------
Sometimes we need to give more than one object a chance to handle a request.
The Chain of Responsibility pattern is a 'behavioral' software design pattern. 
The goal of the pattern is to separate request senders and request handlers,
while giving more than one object a chance to handle the request.

The Chain of Responsibility design pattern allows an object to send a command 
without knowing what object will receive and handle it. 
The request is sent from one object to another making them parts of a chain and
each object in this chain can handle the command, pass it on or do both.
The most usual example of a machine using the Chain of Responsibility is the 
vending machine coin slot: rather than having a slot for each type of coin, 
the machine has only one slot for all of them. 
The dropped coin is routed to the appropriate storage place that is determined 
by the receiver of the command.

Instead of calling a single function to satisfy a request, 
multiple functions in the chain have a chance to satisfy the request.
Since the chain is effectively a list, 
it can be dynamically created,
so you could also think of it as a more general,
dynamically-built switch statement.

This fun example is adapted from Thinking in C++, Vol 2.

.. tabbed:: cor_pattern_tab

   .. tab:: Abstract class

      First we define an abstract class each handler
      in the chain of responsibility must implement. 

      .. code-block:: cpp

         #include <iostream>
         #include <memory>
         #include <vector>

         enum class Answer { NO, YES };
          
         struct GimmeStrategy {
           virtual Answer canIHave() = 0;
           virtual ~GimmeStrategy() = default;
         };
          

      Rather than a ``bool``, in this case, our early termination
      criteria is an enumerated type.


   .. tab:: Implementing classes

      For a chain to be a chain, at least two classes must implement the interface.
      (It's not much of a chain with only 1 link).

      .. code-block:: cpp

         struct AskMom : public GimmeStrategy {
           Answer canIHave() {
             std::cout << "Mommy? Can I have this?\n";
             return Answer::NO;
           }
         };
          
         struct AskDad : public GimmeStrategy {
           Answer canIHave() {
             std::cout << "Dad, I really need this!\n";
             return Answer::NO;
           }
         };
          
         struct AskGrandpa : public GimmeStrategy {
           Answer canIHave() {
             std::cout << "Grandpa, is it my birthday yet?\n";
             return Answer::NO;
           }
         };
          
         struct AskGrandma : public GimmeStrategy {
           Answer canIHave() {
             std::cout << "Grandma, I really love you!\n";
             return Answer::YES;
           }
         };

   .. tab:: Building the chain

      Much discussion related to this pattern is about how to create 
      the chain of responsibility as a linked list.
      However, when you look at the pattern it really shouldn't matter how 
      the chain is created: that's an implementation detail.
      The only important part is that *some* kind of
      :term:`iterable` type is used to visit each handler.
      How that is implemented should be invisible to users.

      While the ``Gimme`` class also is derived from the ``GimmeStrategy``
      it is used to construct the chain of all the other strategies
      used.

      .. code-block:: cpp

         class Gimme : public GimmeStrategy {
            private:
               std::vector<std::unique_ptr<GimmeStrategy>> chain;
            public:
              Gimme() {
                chain.push_back(std::unique_ptr<GimmeStrategy>(new AskMom));
                chain.push_back(std::unique_ptr<GimmeStrategy>(new AskDad));
                chain.push_back(std::unique_ptr<GimmeStrategy>(new AskGrandpa));
                chain.push_back(std::unique_ptr<GimmeStrategy>(new AskGrandma));
              }
              Answer canIHave() {
                for (const auto& it: chain) {
                  if (it->canIHave() == Answer::YES) {
                     return Answer::YES;
                  }
                }
                // Reached end without success...
                std::cout << "Waaaaaahh!!\n";
                return Answer::NO;
              }
         };

Once the abstract and implementing classes have been defined,
then calling the chain is easy:

.. code-block:: cpp

   int main() {
     Gimme chain;
     chain.canIHave();
   }

If you research the Chain of Responsibility in the GoF Patterns book
or on the web, you'll find that the structure differs significantly from 
the one above because most people focus on creating their own linked list. 
However, if you keep in mind that the essence of Chain of Responsibility is 
to try a number of solutions until you find one that works, 
you'll realize that the implementation of the sequencing mechanism is not 
an essential part of the pattern.

-----

.. admonition:: More to Explore

   - `Strategy Design Pattern <http://www.oodesign.com/strategy-pattern.html>`__ on oodesign.com
     and on `Wikipedia <https://en.wikipedia.org/wiki/Strategy_pattern>`__.
   - `Chain of Responsibility Design Pattern <http://www.oodesign.com/chain-of-responsibility-pattern.html>`__ on oodesign.com
     and on `Wikipedia <https://en.wikipedia.org/wiki/Chain-of-responsibility_pattern>`__.
   - Bruce Eckel. Thinking in C++, Vol 2.,  section 3.3.10.

   - `Design Patterns Are Missing Language Features <http://wiki.c2.com/?DesignPatternsAreMissingLanguageFeatures>`__ from the PortlandPatternRepository.
   - `Revenge of the Nerds <http://www.paulgraham.com/icad.html>`__
     an excellent article written by Paul Graham in 2002.
     About the evolution of language and how modern languages are becoming more
     like Lisp -- which was discovered in 1958.
     The end has a short criticism of patterns.

     Keep this date in mind when he uses phrases like 'recently invented':
     that's still over 20 years ago!


