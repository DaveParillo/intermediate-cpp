..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   single: sequence containers

Sequence Containers
===================

If a program needs to manage a collection of closely related things,
numbers, bank accounts, students, fruit, 
then the simplest approach is to put them in a container.
You should already be familiar with arrays,
which are part of the language.
In an :doc:`earlier section <../string+vector/vector>`, 
we briefly introduced vector.
This chapter takes a closer look.

Like a raw array and ``vector``, all of the containers in this chapter
store a sequence of elements of a given type.
All the STL containers provide similar advantages over arrays:

- Add and remove data dynamically
- Bounds checking
- Work with data at a higher level of abstraction
- Manage subsets of data as a unit

Although all of the 'sequence containers' in the STL
share some core characteristics,
the different containers have different designs,
and have different trade-offs (costs).
This allows them to excel is specific niches,
where an 'all-purpose' might fall short.

All containers support the same basic operations:

- Add objects to the container

  - And remove objects from it

- Find out if an object is in the container (or a group of objects)
- Retrieve an object without removing it
- Walk through the container, looking at each object in turn

The container manages the storage space that is allocated for its elements and 
provides member functions to access them,
either directly or through iterators (objects with properties similar to pointers).

We normally do not think of the sequence containers as having an order.
For example, a vector may contain the values ``{3, 1, 4, 1, 5, 9}``,
which clearly are not in the :term:`natural order` for integers.
A ``vector`` *is* ordered, however: by its index position.


.. index:: 
   pair: sequence containers; vector

std::vector
-----------
The :cref:`std::vector` is a sequence container that simulates a dynamically sized array.
If you have taken a class in linear algebra, vector has nothing to do with mathematics,
but is just about a sequential data structure.

Like an array, elements are stored continuously.
This means that elements can be accessed not only through iterators, 
but also using offsets to regular pointers to elements.
The benefit of this is that a pointer to an element of a vector may be passed 
to any function that expects a pointer to an element of an array.

Unlike an array,
vector storage is handled automatically, being expanded and contracted as needed. 
Vectors usually occupy more space than static arrays, 
because more memory is allocated to handle future growth. 
This way a vector does not need to reallocate each time an element is inserted, 
but only when the additional memory is exhausted. 
The total amount of allocated memory can be queried using :cref:`vector::capacity()` function. 
Starting in C++11, extra memory can be returned to the system via a call to :cref:`vector::shrink_to_fit()`. 

Given a vector declared as:

.. code-block:: cpp

   std::vector<int> v(4) = {3, 1, 4};

This creates a vector of type ``int``, with size 4 and the first 3 values initialized.



.. graphviz:: 

   digraph {
     node [shape=plaintext, fontsize=14];
     "Pointers:" -> "Values:" -> "Indices:" [color=white];

     node [shape=record, fontcolor=black, fontsize=14, width=4.75, fixedsize=true];
     pointers [label="<f0> v | <f1> v+1 | <f2> v+2 | <f3> v+3 | <f4> v+4 | <f5> v+5", color=white];
     values [label="<f0> v[0] | <f1> v[1] | <f2> v[2] | <f3> v[3] | <f4> v[4] | <f5> v[5]", 
             color=black, fillcolor=lightblue, style=filled];
     indices [label="0 | 1 | 2 | 3| 4 | 5", color=white];

     { rank=same; "Pointers:"; pointers }
     { rank=same; "Values:"; values }
     { rank=same; "Indices:"; indices }

     edge [color=black];
     pointers:f0 -> values:f0;
     pointers:f1 -> values:f1;
     pointers:f2 -> values:f2;
     pointers:f3 -> values:f3;
     pointers:f4 -> values:f4;
     pointers:f5 -> values:f5;
   }



.. index:: 
   pair: sequence containers; array

std::array
----------
The :cref:`std::array` is a container that encapsulates fixed size arrays.





.. index:: 
   pair: sequence containers; list

std::list
---------
The :cref:`std::list` is a sequence container that stores data in *nodes*.
Each node in a list points to the next (and previous) node in the list.
Each node is a separate object that exists to encapsulate a piece of data
and to allow navigation to adjacent nodes.

.. graphviz::

    digraph list {
       graph [
          rankdir=LR;
          //splines=ortho;
          compound=true;
          labelloc=b;
          label="Linked list nodes";
          ranksep = 1;
       ]
       node [fontname = "Bitstream Vera Sans", fontsize=14,
                 style=filled, fillcolor=lightblue,
                 shape=record, width=0.5, height=.25, label=""];

      
      subgraph cluster_h {
        labelloc=t
        label="head"
        head [label=" |next()| "]
      }

      subgraph cluster_a {
        labelloc=t
        label="Node A" 
        a [label="data|next()|prev()"]
      }

        subgraph cluster_b {
        labelloc=t
        label="Node B" 
         b [label="data|next()|prev()"]
      }

      subgraph cluster_t {
        labelloc=t
        label="tail"
         tail [label=" | | prev()"]
      }

      head:m-> a [lhead=cluster_a];

      a -> b [lhead=cluster_b];
      a:s -> head:s [lhead=cluster_h];

      b -> tail [lhead=cluster_t];
      b:s -> a:s [lhead=cluster_a];

      tail:s -> b:s [lhead=cluster_b];
    }

A more compact way to graphically represent our doubly-linked list is like this:

.. graphviz::

   // doubly linked list
   digraph g {
       node [fontname = "Bitstream Vera Sans", fontsize=14,
             style=filled, fillcolor=lightblue,
             shape=box, width=0.5, height=.25];


       head [style=dotted, fillcolor=white];
       tail [style=dotted, fillcolor=white];

       head -> a -> b -> tail [ arrowhead=vee, arrowsize=0.5];
       tail -> b -> a -> head [ arrowhead=vee, arrowsize=0.5];

      {rank=same; head a b tail}
   }
   
A linked list that stores a sequence of ``int``s can be trivially implemented using a ``struct``:

.. code-block:: cpp

   struct node {
      int value;
      node *next;
      node *prev;
   };

Creating a linked list from such a 'home grown' struct is not complicated,
but it isn't pretty either:

.. code-block:: cpp

   // create an empty list
   node* head = new node;
   node* tail = new node;
   head->next = tail;
   tail->prev = head;

   // insert node a into the list
   node* a = new node;
   a->value = 61;
   a->next = tail;
   a->prev = head;
   head->next = a;
   tail->prev = a;

   // insert node b after node a
   node* b = new node;
   b->value = 62;
   b->next = tail;
   b->prev = a;
   a->next = b;
   tail->prev = b;


At this point, we have created the basic structure shown in the previous diagram.
Once we have such a list, we can access all of the elements,
if we have a pointer to any one of them.
For example, to print all of the elements, we could:

.. code-block:: cpp

   node* p = head->next;
   while (p->next != nullptr) {
     std::cout << p->value << ' ';
     p = p->next;
   }


Which, given the list we created, will print ``61 62\0``.

Obviously, no one would want to use such a list.
Every trivial detail needs to be managed, and any program using it
would be more likely to leak memory or fail suddenly due to some programming error.

The :cref:`std::list` class hides all the implementation details and
provides a list with many convenient features:

.. code-block:: cpp

   #include <iostream>
   #include <list>
   using std::cout;

   void print_list(const list<int>&);

   int main () {
     std::list<int> list = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
     cout << "size: "  << list.size() << '\n';
     cout << "front: " << list.front() << '\n';
     cout << "back: "  << list.back() << "\n\n";

     cout << "push_back 13: " << '\n';
     list.push_back(13);
     cout << "size: "  << list.size() << '\n';
     cout << "back() " << list.back() << '\n';

     print_list(list);

     return 0;
   }

   void print_list(const std::list<int>& list) {
     cout << "list contains: " << '\n';
     for(const int i: list) {
       cout << i << " ";
     }
     cout << "\n\n";
   }

The defining operations of a ``std::list`` are:

push_back
   Add a new element to the end of the list

pop_back
   Remove an element from the end of the list.

back
   Get the value of the element at the end of the list

push_front
   Add a new element to the beginning of the list

pop_front
   Remove an element from the beginning of the list.

front
   Get the value of the element at the beginning of the list

Underneath, the standard library list is not very different from the ``struct node`` above.
The primary characteristics are:

- All data is stored on the heap
- Each node in the list is a separate object
- Node traversal is accomplished by following pointers from one node to the next
- Access based on an index is not allowed.
  This kind of access, called *random  access* describes
  the ability to compute a location in memory using a starting address and an offset.
  Arrays and vectors support random access.
  Linked lists do not.


std::forward_list
.................
Like :cref:`std::list`, 
the :cref:`std::forward_list` is a container that stores elements in *nodes*.
A forward list only defines pointers to the next node in the list.
This means that a forward list can only be traversed in the direction of the tail.

.. digraph:: list

   rankdir=LR;
   node [fontname = "Bitstream Vera Sans", fontsize=14,
             style=filled, fillcolor=lightblue,
             shape=record];

   head [shape=box];
   a [label="{ <data> 8 | <ref>  }", width=1.2]
   b [label="{ <data> 13 | <ref>  }"];
   c [label="{ <data> 21 | <ref>  }"];
   tail [shape=box];
   head:e -> a:w     [arrowhead=vee];
   a:ref:c -> b:data [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false, arrowsize=1.2];
   b:ref:c -> c:data [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false];
   c:ref:c -> tail:w [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false];


The defining operations of a ``std::forward_list`` are:

push_front
   Add a new element to the beginning of the list

pop_front
   Remove an element from the beginning of the list.

front
   Get the value of the element at the beginning of the list

Compared to :cref:`std::list` this container provides more space efficient storage 
when bidirectional iteration is not needed.
A very light-weight container, 
it does not have any overhead compared to its implementation in C. 


.. index:: 
   pair: sequence containers; stack

std::stack
----------
The :cref:`std::stack` is a container adapter that gives the programmer the 
functionality of a stack - specifically, a Last-In-First-Out (LIFO) data structure.

The class template acts as a wrapper to the underlying container - only 
a specific set of functions is provided. 
The stack pushes and pops the element from the back of the underlying container, 
known as the top of the stack.

The defining operations of a ``std::stack`` are:

push
   Add a new element to the top of the stack.

pop
   Remove an element from the top of the stack.
   In some languages, but not ``std::stack``, pop returns 
   the element that is removed.

top
   Get the value of the element at the top of the stack.
   
.. graphviz::

   // shows push and pop
   digraph g {
       node [fontname = "Bitstream Vera Sans", fontsize=14,
             style=filled, fillcolor=lightblue,
             shape=box, width=0.5, height=.25, label=""];


       a,b,d,e;
       node [style=none];
       c [label=". . .", color=white];

       top [shape=none, label="top()"];
       push [shape=none, label="push()"];
       pop [shape=none, label="pop()"];

       a -> b -> c -> d -> e [dir=none, arrowhead=vee];
       push -> a:w [style=dotted];
       pop -> a:e [dir=back,style=dotted];

       pop:e -> top:w [style=invis]   
       top -> a [style=invis, constraint=false];
   }

.. code-block:: cpp

   #include <iostream>
   #include <stack>
   #include <string>
   using std::cout;
   using std::stack;

   #define StackContainer typename

   // remove all elements from a stack and print them out
   template <StackContainer C>
   void pop_all(C& s) {
     while(!s.empty()) {
       cout << s.top() << " ";
       s.pop();
     }
     cout << "\npopped all from stack\n";
   }

   int main () {
     stack<std::string> strings;
     cout << "push strings onto stack...\n";
     strings.push("one");
     strings.push("two");
     strings.push("three");
     strings.push("four");
     strings.push("five");

     cout << "size of stack before: " << strings.size() << '\n';
     pop_all (strings);
     cout << "size of stack after: " << strings.size() << '\n';
     if (strings.empty()) {
       cout << "stack is empty.\n";
     }


     return 0;
   }

which returns:

   push strings onto stack...
   size of stack before: 5
   five four three two one
   popped all from stack
   size of stack after: 0
   stack is empty.
       
It is also possible to initialize a stack from a vector, list or array:

.. code-block:: cpp

   #include <iostream>
   #include <stack>
   #include <list>
   using std::cout;
   using std::stack;

   #define StackContainer typename

   template <StackContainer C>
   void pop_all(C& s) {
     while(!s.empty()) {
       cout << s.top() << " ";
       s.pop();
     }
     cout << "\npopped all from stack\n";
   }

   int main () {
     cout << "initialize stack from list:\n";
     std::list<int> tmp = { 1, 2, 3, 4, 5 };
     stack<int, std::list<int>> numbers(tmp);

     cout << "list has " << tmp.size() << " entries\n";
     pop_all (numbers);
     if (numbers.empty()) {
       cout << "stack is empty.\n";
     }

     return 0;
   }

which returns:

   initialize stack from list:
   list has 5 entries
   5 4 3 2 1
   popped all from stack
   stack is empty.

Note that the elements from the list are pushed onto the stack in the order
they are retrieved from the list.
The number ``1`` is pushed first, so when iniitialization is complete,
it is on the bottom of the stack.
   
Stack elements **cannot** be accessed directly in the way
you are used to with other sequential containers like
arrays, vectors, and lists.
To 'visit' each element in a ``stack``, the items need to be popped off.

If you think you need to visit all the elements in a ``stack``, 
then you probably should not be using a ``stack``.

The STL containers ``std::vector``, ``std::list``, 
and ``std::deque`` can be adapted to create a stack.


.. index:: 
   pair: sequence containers; queue

std::queue
----------
The :cref:`std::queue` is a container adapter that gives the programmer the 
functionality of a queue - specifically, a FIFO (first-in, first-out) data structure.

The class template acts as a wrapper to the underlying container - only 
a specific set of functions is provided. 
The queue pushes elements on the back of the underlying container, 
and pops them from the front.

.. graphviz::

   digraph g {
       node [fontname = "Bitstream Vera Sans", fontsize=14,
             style=filled, fillcolor=lightblue,
             shape=box, width=0.5, height=.25, label=""];

       a,b,d,e;
       node [style=none];
       c [label=". . .", color=white];

       back [shape=none, label="back()"];
       front [shape=none, label="front()"];

       a -> b -> c -> d -> e [ arrowhead=vee];
       back -> a:w [dir=back];
       e:e -> front;

       node [style=invis] x,y;
       x -> a [style=invis];
       y -> e [style=invis];
       {rank=sink; a b c d e}
   }


The defining operations of a ``std::queue`` are:

push
   Add a new element to the back (end) of the queue.

pop
   Remove an element from the front (beginning) of the queue.

front
   Get the value of the element at the beginning of the queue.

back
   Get the value of the element at the end of the queue.

.. graphviz::

   // shows push and pop, enqueue / dequeue
   digraph g {
       node [fontname = "Bitstream Vera Sans", fontsize=14,
             style=filled, fillcolor=lightblue,
             shape=box, width=0.5, height=.25, label=""];


       o,z [style=dotted];
       a,b,d,e;
       node [style=none];
       c [label=". . .", color=white];

       back [shape=none, label="push()"];
       front [shape=none, label="pop()"];

       o -> a -> b -> c -> d -> e [ arrowhead=vee];
       e -> z [ arrowhead=none];
       back -> o [style=dotted];
       front -> z [style=dotted, dir=back];

       {rank=sink; o a b c d e z}
   }

The STL containers ``std::list`` and ``std::deque`` can be adapted to create a queue.

.. index:: 
   pair: sequence containers; deque

std::deque
----------
The :cref:`std::deque` (double-ended queue) is an indexed sequence container that 
allows fast insertion and deletion at both its beginning and its end. 
In addition, 
insertion and deletion at either end of a deque never invalidates pointers 
or references to the rest of the elements.

It's primary role in the standard library is to function as
the default container underlying ``std::stack`` and ``std::queue``.


-----

.. admonition:: More to Explore

   - `Sequence containers <http://en.cppreference.com/w/cpp/container>`_

