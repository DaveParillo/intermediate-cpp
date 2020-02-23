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
Like a raw array and ``vector``, all of the containers in this section
store a sequence of elements of a given type.
Although all sequence containers store data sequentially,
it does not mean that the data is stored in a contiguous memory block.
Nor do all containers allow elements to be accessed by index using ``operator[]``.


.. index:: 
   pair: sequence containers; vector

The vector class
----------------
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


.. index:: 
   pair: graph; std::vector

Given a vector declared as:

.. code-block:: cpp

   std::vector<int> v(6) = {2, 7, 1, 8};

This creates a vector of type ``int``, with size 6 and the first 4 values initialized:

.. graphviz:: 
   :alt: A vector of type int

   digraph {
     graph [fontname = "Bitstream Vera Sans", 
            labelloc=b,
            label="A vector of type int"
     ];
     node [fontname = "Bitstream Vera Sans", fontsize=14, shape=plaintext];
     "Indices:" -> "Values:" [color=white];
     "uninitialized values";

     node [shape=record, width=4.75, fixedsize=true];
     indices [label="v[0] | v[1] | v[2] | v[3]| v[4] | v[5]", color=white];
     values [label="<f0> 2 | <f1> 7 | <f2> 1 | <f3> 8 | <f4> ? | <f5> ? ", 
             color=black, fillcolor=lightblue, style=filled];

     values:f4,values:f5 -> "uninitialized values" [dir=back];
     { rank=same; "Values:"; values }
     { rank=same; "Indices:"; indices }
   }

The data layout of a vector makes it easy to pass a vector to a legacy C
function that expects a raw array.
This is something that comes up more often than you might expect.
The book *Effective STL* has a good discussion of 
passing string and vector objects to legacy C functions\ [1]_\ .

Given a legacy C function that expects a raw array:

.. code-block:: cpp

  void print_sum (const int* values, size_t array_size) {
    int sum = 0;
    for (size_t i = 0; i < array_size; ++i) {
      sum += values[i];
    }
    printf("Sum of ints in the array is %d\n", sum);
  }

We expect to be able to pass in an array and print the sum:

.. code-block:: cpp

   int main() {

     int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
     const int numValues = sizeof data / sizeof(int);

     print_sum (data, num_values);

     return 0;
   }

We can pass a ``vector`` to this same legacy function:

.. code-block:: cpp

   int main() {
     int data[] = { -30, 102, 55, -19, 0, 222, -3000, 4000, 8, -2 };
     const int num_values = sizeof data / sizeof(int);

     print_sum (data, num_values);

     std::vector<int> v;
     v.insert (v.begin(), data, data + num_values);	// insert the ints in data
                                                    // into v at the front

     print_sum (&v[0], v.size());   // ok, unless v is empty

     if (!v.empty()) {              // safer
       print_sum (&v[0], v.size()); //&v[0] is better than v.begin()
     }

     return 0;
   }


.. index:: 
   pair: sequence containers; array

The array class
---------------
The :cref:`std::array` is a container that encapsulates fixed size arrays.
Since it is literally a wrapper around a raw array,
the size of the ``std::array`` must be defined when declared.

.. code-block:: cpp

   std::array <int, 12> days_per_month;

The ``std::array`` class is very lightweight and has effectively no
costs over a raw array.
Additionally, ``std::array`` provides convenience functions such as:

:cref:`array::at()`
   range checked access

:cref:`array::front()` and :cref:`array::back()`
   access to the first and last elements

:cref:`array::size()`
   return the number of elements

:cref:`array::empty()`
   check if the container is empty

Unlike a raw array, ``std::array`` cannot infer its size if
declared with an initializer list:

.. code-block:: cpp

   #include <array>
   #include <iostream>
   using std::cout;

   int main() {
     // compile error: array template parameter missing:
     //std::array<char> letters = {{'h', 'o', 'w', 'd', 'y', '!'}};

     std::array<char, 6> letters = {{'h', 'o', 'w', 'd', 'y', '!'}};

     if (!letters.empty()) {
       cout << "The first character is: " << letters.front() << '\n';
       cout << "The last character is: " << letters.back() << '\n';

       for (const auto& c: letters) {
         cout << c;
       }
       cout << std::endl;
     }
   }

.. index:: 
   pair: sequence containers; list
   pair: graph; std::list

The list class
--------------
The :cref:`std::list` is a sequence container that stores data in :term:`nodes <node>`.
Each :term:`node` in a :term:`list` points to the next (and previous) node in the :term:`list`.
Each node is a separate object that exists to encapsulate a piece of data
and to allow navigation to adjacent nodes.

.. graphviz::
   :alt: Linked list nodes

    digraph list {
       graph [
          rankdir=LR;
          //splines=ortho;
          compound=true;
          labelloc=b;
          label="Linked list nodes";
          ranksep = 1;
       ];
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

.. index:: 
   pair: graph; compact list

A more compact way to graphically represent our :term:`doubly linked list` is like this:

.. graphviz::
   :alt: A compact linked list diagram

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
   
A :term:`linked list` that stores a sequence of ``int``\s can be trivially implemented using a ``struct``:

.. code-block:: cpp

   struct node {
      int value;
      node* next;
      node* prev;
   };

The ``struct node`` contains a single value it 'owns',
plus pointers to adjacent nodes.


.. index:: 
   pair: graph; std::list

Creating a :term:`linked list` from such a 'home grown' ``struct`` is not complicated,
but it isn't pretty either:

.. sidebar:: An empty list

    .. digraph:: empty
       
       graph [
          nodesep=1,
       ];
       node [fontname = "Bitstream Vera Sans", fontsize=14,
             style=dotted, 
             shape=box, width=0.5, height=.25];

       head -> tail [constraint=false];
       tail-> head [constraint=false];

.. code-block:: cpp

   // create an empty list
   node* head = new node;
   node* tail = new node;
   head->next = tail;
   tail->prev = head;


.. sidebar:: Insert node 'a' to our list

    .. digraph:: node_a

        graph [
           rankdir=LR,
           nodesep=1
        ];
        node [fontname = "Bitstream Vera Sans", fontsize=14,
              style=filled, fillcolor=lightblue, 
              shape=box, width=0.5, height=.25];

        head,tail [style=dotted, fillcolor=white];

        head,tail-> a
        a -> head, tail

.. code-block:: cpp

   // insert node a into the list
   node* a = new node;
   a->value = 61;
   a->next = tail;
   a->prev = head;
   head->next = a;
   tail->prev = a;

.. sidebar:: Insert node 'b' after a

    .. digraph:: node_b

       graph [
           rankdir=LR,
           nodesep=1
        ];
        node [fontname = "Bitstream Vera Sans", fontsize=14,
              style=filled, fillcolor=lightblue, 
              shape=box, width=0.5, height=.25];

        head,tail [style=dotted, fillcolor=white];

        head -> a -> b -> tail;
        tail -> b -> a -> head;

.. code-block:: cpp

   // insert node b after node a
   node* b = new node;
   b->value = 62;
   b->next = tail;
   b->prev = a;
   a->next = b;
   tail->prev = b;

At this point, we have created the basic structure shown in the first list diagram.
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
     cout << "size: "  << list.size();
     cout << "\nfront: " << list.front();
     cout << "\nback: "  << list.back();

     cout << "\n\npush_back 13: ";
     list.push_back(13);
     cout << "\nsize: "  << list.size();
     cout << "\nback() " << list.back();

     print_list(list);

     return 0;
   }

   void print_list(const std::list<int>& list) {
     if (list.empty()) {
       cout << "list is empty.\n";
     } else {
       cout << "list contains:\n";
     }
     for(const int i: list) {
       cout << i << " ";
     }
     cout << "\n\n";
   }

The defining operations of a :cref:`std::list` are:

push_back
   Add a new element to the end of the list.

pop_back
   Remove an element from the end of the list.

back
   Get the value of the element at the end of the list.

push_front
   Add a new element to the beginning of the list.

pop_front
   Remove an element from the beginning of the list.

front
   Get the value of the element at the beginning of the list.


.. note:: empty() vs. size() == 0

   In most containers, calling ``size()`` is constant time.

   That is it takes the same amount of time regardless of
   the number items in the container.

   Not so for lists.

   There are situations where a list cannot determine the size
   without traversing the range and counting them.

   In general, never assume ``size()`` is as efficient as ``empty()``.

   If you **really** want to know if a container is empty (or not),
   then call ``empty()``.

   If you **really** want to know the number of elements in a container,
   then call ``size()``.

   See *Effective STL*, for more details\ [2]_\ .

Underneath, the standard library ``list`` is not very different from the ``struct node`` above.
The primary characteristics are:

- All data is stored on the heap
- Node traversal is accomplished by following pointers from one node to the next
- Access based on an index is not allowed.
  This kind of access, called *random  access* describes
  the ability to compute a location in memory using a starting address and an offset.
  Arrays and vectors support random access.
  Linked lists do not.


.. index:: 
   pair: graph; std::forward_list

std::forward_list
.................
Like :cref:`std::list`, 
the :cref:`std::forward_list` is a container that stores elements in :term:`nodes <node>`
A :term:`forward list <singly linked list>` only defines pointers to the next node in the list.
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


The defining operations of a :cref:`std::forward_list` are:

push_front
   Add a new element to the beginning of the list.

pop_front
   Remove an element from the beginning of the list.

front
   Get the value of the element at the beginning of the list.

Compared to :cref:`std::list` this container provides more space efficient storage 
when bidirectional iteration is not needed.
A very light-weight container, 
it does not have any overhead compared to its implementation in C. 


.. index:: 
   pair: sequence containers; stack
   pair: graph; std::stack

The stack class
---------------
The :cref:`std::stack` is a container adapter that gives the programmer the 
functionality of a stack - specifically, a Last-In-First-Out (LIFO) data structure.

The class template acts as a wrapper to the underlying container - only 
a specific set of functions is provided. 
The stack pushes and pops the element from the back of the underlying container, 
known as the top of the stack.

The defining operations of a :cref:`std::stack` are:

push
   Add a new element to the top of the stack.

pop
   Remove an element from the top of the stack.

top
   Get the value of the element at the top of the stack.
   
.. graphviz::
   :alt: std::stack elements

   // shows push and pop
   digraph g {
       graph [
          rankdir=LR;
          labelloc=b;
          label="std::stack elements";
       ];
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
       push -> a [style=dotted];
       pop -> a [dir=back,style=dotted];

       pop:e -> top:w [style=invis]   
       top -> a [style=dotted, dir=back, constraint=false];
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

.. code-block:: none

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

.. code-block:: none

   initialize stack from list:
   list has 5 entries
   5 4 3 2 1
   popped all from stack
   stack is empty.

Notice the elements from the list are pushed onto the stack in the order
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
and ``std::deque`` can be adapted to create a ``stack``.


.. index:: 
   pair: sequence containers; queue
   pair: graph; std::queue

The queue class
---------------
The :cref:`std::queue` is a container adapter that gives the programmer the 
functionality of a queue - specifically, a FIFO (first-in, first-out) data structure.

The class template acts as a wrapper to the underlying container - only 
a specific set of functions is provided. 
The queue pushes elements on the back of the underlying container, 
and pops them from the front.

.. graphviz::
   :alt: std::queue elements

   digraph g {
       graph [
          labelloc=b;
          label="std::queue elements";
       ];
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


   
.. index:: 
   pair: graph; queue operations

The defining operations of a :cref:`std::queue` are:

push
   Add a new element to the back (end) of the queue.

pop
   Remove an element from the front (beginning) of the queue.

front
   Get the value of the element at the beginning of the queue.

back
   Get the value of the element at the end of the queue.

.. graphviz::
   :alt: std::queue operations

   // shows push and pop, enqueue / dequeue
   digraph g {
       graph [
          labelloc=b;
          label="std::queue operations";
       ];
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


Minor modifications change ``pop_all()`` from a function
performing ``stack`` operations into one
performing ``queue`` operations:

.. code-block:: cpp

   #include <iostream>
   #include <queue>

   #define QueueContainer typename

   template <QueueContainer C>
   void pop_all(C& q) {
     while(!q.empty()) {
       std::cout << q.front() << " ";
       q.pop();
     }
     std::cout << "\npopped all from queue\n";
   }

The STL containers ``std::list`` and ``std::deque`` can be adapted to create a queue.

.. index:: 
   pair: sequence containers; deque

The deque class
---------------
The :cref:`std::deque` (double-ended queue) is an indexed sequence container that 
allows fast insertion and deletion at both its beginning and its end. 
In addition, 
insertion and deletion at either end of a ``deque`` never invalidates pointers 
or references to the rest of the elements.

It's primary role in the standard library is to function as
the default container underlying ``std::stack`` and ``std::queue``.

.. tabbed:: deque

   .. tab:: std::deque

      .. literalinclude:: deque.txt
         :language: cpp
         :start-after: compileargs
         :dedent: 3
         :linenos:

   .. tab:: Run It

      .. include:: deque.txt

An interesting problem that can be easily solved using the deque 
data structure is the classic palindrome problem. 
A **palindrome** is a string that reads the same forward and backward, 
for example, *radar*, *toot*, and *madam*. 
We would like to construct an algorithm to input a string of characters and 
check whether it is a palindrome.

One solution to this problem uses a deque to store the characters of the string.
First store each character in the string into a new deque.
Using the properties of the deque, we can process the characters from both ends
and compare them to each other.

Since we can remove both of them directly, 
we can compare them and continue only if they match. 
If we can keep matching first and the last items, 
we will eventually either run out of characters or 
be left with a deque of size 1 depending on whether the length of the 
original string was even or odd. In either case, 
the string must be a palindrome.


.. tabbed:: check_palindrome

   .. tab:: Check Palindrome

      .. literalinclude:: palindrome.txt
         :language: cpp
         :start-after: #include <iostream>
         :end-before: int main
         :dedent: 3
         :linenos:

   .. tab:: Run It

      .. include:: palindrome.txt

.. index:: std::equal

A moment of full disclosure:
even though it is possible to use a deque to determine if a string is a
palindrome or not, it's far from the simplest or most efficient
solution tot he the problem.
Simply checking the string characters directly is better:

.. tabbed:: is_palindrome

   .. tab:: Is Palindrome

      .. literalinclude:: is_palindrome.txt
         :language: cpp
         :start-after: compileargs
         :end-before: int main
         :dedent: 3
         :linenos:

      The STL provides the :algorithm:`equal` template which allows
      comparing the values in a pair ranges.

      The first `begin` and `end` define a range of values to be compared.
      The second `begin` defines the start of the second range of values.
      The second `end` does not need to be specified, because the comparison
      stops once the first end is reached.

      Notice that in this example, the second begin is `rbegin`.
      This means the second iterator starts at the **reverse beginning**,
      which is the *end* of the string and each iteration moves one
      step closer to the begining.

   .. tab:: Run It

      .. include:: is_palindrome.txt

While this solution does require more familiarity with the standard library,
it avoids copying the string into the container, 
removing elements from the container, and is generally simpler.


-----

.. admonition:: More to Explore

   - `STL containers library <http://en.cppreference.com/w/cpp/container>`_
   - `STL iterator library <http://en.cppreference.com/w/cpp/iterator>`_
   - `Visualgo: lists <https://visualgo.net/en/list?slide=1>`_

.. topic:: Footnotes

   .. [1] Effective STL (Item #16) by Scott Meyers (Addison-Wesley Professional).  Copyright 2001 Scott Meyers, 978-0-201-74962-5.
   .. [2] Effective STL (Item #4).

