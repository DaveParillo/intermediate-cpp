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

``std::vector``
---------------
The ``std::vector`` is a sequence container that simulates a dynamically sized array.
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
The total amount of allocated memory can be queried using ``capacity()`` function. 
Starting in C++11, extra memory can be returned to the system via a call to ``shrink_to_fit()``. 

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

``std::array``
--------------
The ``std::array`` is a container that encapsulates fixed size arrays.





.. index:: 
   pair: sequence containers; list

``std::list``
-------------
The ``std::list`` is a sequence container that supports constant time insertion 
and removal of elements from anywhere in the container. 
Fast random access is not supported. 
It is usually implemented as a doubly-linked list. 
Compared to ``std::forward_list`` this container provides bidirectional iteration capability while being less space efficient.

Addition, removal, and moving the elements within the list or across several lists 
does not invalidate the iterators or references. 
An iterator is invalidated only when the corresponding element is deleted.

.. graphviz::

   // doubly linked list
   digraph g {
        node [fontname = "Bitstream Vera Sans", fontsize=14,
             style=filled, fillcolor=lightblue,
             shape=box, width=0.5, height=.25, label=""];


       a,b,d,e;
       f [style=dotted];
       node [style=none];
       c [label=". . .", color=white];

       begin [shape=none, label="begin()"];
       end [shape=none, label="end()"];

       begin -> a;
       a -> b -> c -> d -> e -> f [ arrowhead=vee, arrowsize=0.5];
       e -> d -> c -> b -> a [ arrowhead=vee, arrowsize=0.5];
       f -> end [dir=back];

       node [style=invis] x,y;
       node [shape=point] p1, p2;
       edge [style=invis];
       x -> a;
       y -> f;
       begin -> p1;
       end -> p2;
       p1 -> a ->f -> p2;
       {rank=sink; p1 a b c d e f p2}
   }


``std::forward_list``
.....................
Like ``std::list``, 
the ``std::forward_list`` is a container that supports fast insertion and 
removal of elements from anywhere in the container. 
Fast random access is not supported. 
It is implemented as a singly-linked list and essentially does not have any overhead 
compared to its implementation in C. 
Compared to std::list this container provides more space efficient storage 
when bidirectional iteration is not needed.


.. index:: 
   pair: sequence containers; stack

``std::stack``
--------------
The ``std::stack`` is a container adapter that gives the programmer the 
functionality of a stack - specifically, a FILO (first-in, last-out) data structure.

The class template acts as a wrapper to the underlying container - only 
a specific set of functions is provided. 
The stack pushes and pops the element from the back of the underlying container, 
known as the top of the stack.

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




.. index:: 
   pair: sequence containers; queue

``std::queue``
--------------
The ``std::queue`` is a container adapter that gives the programmer the 
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

.. index:: 
   pair: sequence containers; deque

``std::deque``
--------------
The ``std::deque`` (double-ended queue) is an indexed sequence container that 
allows fast insertion and deletion at both its beginning and its end. 
In addition, 
insertion and deletion at either end of a deque never invalidates pointers 
or references to the rest of the elements.


-----

.. admonition:: More to Explore

   - `Sequence containers <http://en.cppreference.com/w/cpp/container>`_
   - `std::vector <http://en.cppreference.com/w/cpp/container/vector>`_ and 
     `std::array <http://en.cppreference.com/w/cpp/container/array>`_
   - `std::list <http://en.cppreference.com/w/cpp/container/list>`_ and
     `std::forward_list <http://en.cppreference.com/w/cpp/container/forward_list>`_
   - `std::stack <http://en.cppreference.com/w/cpp/container/stack>`_,
     `std::queue <http://en.cppreference.com/w/cpp/container/queue>`_, and
     `std::deque <http://en.cppreference.com/w/cpp/container/deque>`_

