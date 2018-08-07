..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: algorithms; model
   pair: graph; STL model


Basic Model
===========

One of the primary goals of the STL is
avoiding repetition & using regular, compact syntax.
The STL achieves these goals using *separation of concerns*.

.. graphviz:: 
   :alt: STL basic model

   digraph {
     graph [fontname = "Bitstream Vera Sans", 
     ];
     node [fontname = "Bitstream Vera Sans", fontsize=14, shape=plaintext];
     c [label="Containers store data, but are ignorant about algorithms"];
     vector, list, map, set;
     swap, sort, find, copy;

     it [label="iterators", shape=box, width=2.0
         fillcolor=lightblue, style=filled];
     edge [dir=both, arrowsize=.75];

     vector -> it:nw;
     list -> it;
     map -> it;
     set -> it:ne;
     it:sw -> swap;
     it -> sort;
     it -> find;
     it:se -> copy;
     a [label="Algorithms manipulate data, but remain ignorant about containers"];

     c -> map [style=invis];
     sort -> a [style=invis];
   }

Algorithms and containers interact through **iterators**.

.. index:: std::find

Basic Model in Action: find()
-----------------------------
Let's suppose we need to 
find the first element in a container that equals a value.
Specifically, we want to find a specific int in a vector.

This seems like a function we will need to use frequently,
so we decide right away that it should be written as a free function:


.. tabbed:: my_find

   .. tab:: Example

      We *could* choose to pass an entire container
      of a specific type to our find function.

      .. literalinclude:: my_find.txt
         :language: cpp
         :lines: 10,11
         :dedent: 3

      and loop over the entire container:

      .. literalinclude:: my_find.txt
         :language: cpp
         :lines: 12-14
         :dedent: 5

   .. tab:: Run It

      .. include:: my_find.txt

      See this example running `step-by-step
      <http://www.pythontutor.com/cpp.html#code=%23include%20%3Calgorithm%3E%0A%23include%20%3Ciostream%3E%0A%23include%20%3Cvector%3E%0A%0A//%20function%20to%20find%20'x'%20in%20v%0Astd%3A%3Avector%3Cint%3E%3A%3Aiterator%20%0Afind%28std%3A%3Avector%3Cint%3E%26%20v,%20int%20x%29%20%7B%0A%20%20for%28auto%20p%20%3D%20v.begin%28%29%3B%20p%20!%3D%20v.end%28%29%3B%20%2B%2Bp%29%20%7B%0A%20%20%20%20if%20%28x%20%3D%3D%20*p%29%20return%20p%3B%0A%20%20%7D%0A%20%20//%20did%20not%20find%20x%0A%20%20return%20v.end%28%29%3B%0A%7D%0A%20%20%20%20%20%20%20%20%20%20%20%20%0Aint%20main%20%28%29%20%7B%0A%20%20int%20value%20%3D%2031%3B%0A%20%20std%3A%3Avector%3Cint%3E%20nums%2899%29%3B%0A%20%20std%3A%3Aiota%28nums.begin%28%29,%20nums.end%28%29,%20-17%29%3B%0A%20%20auto%20it%20%3D%20find%28nums,%20value%29%3B%0A%20%20%20%20%20%0A%20%20if%20%28it%20%3D%3D%20nums.end%28%29%29%20%7B%0A%20%20%20%20std%3A%3Acout%20%3C%3C%20%22Did%20not%20find%20%22%20%3C%3C%20value%20%3C%3C%20%20'%5Cn'%3B%0A%20%20%7D%20else%20%7B%0A%20%20%20%20std%3A%3Acout%20%3C%3C%20%22Found%20%22%20%3C%3C%20value%20%3C%3C%20%22%20at%20position%20%22%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20%3C%3C%20%28std%3A%3Adistance%28nums.begin%28%29,%20it%29%29%20%3C%3C%20'%5Cn'%3B%0A%20%20%7D%0A%20%20return%200%3B%0A%7D%0A&curInstr=4&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D>`__


While this seems easier at first,
this version is not **nearly** as *generic*,
or *general purpose* as a version that defines
a generic type and uses iterators.


- No way to run this function over part of a container.
- Need a different function for every container type.

How do we refactor our find function to satisfy our goals?

- Replace ``vector<int> v`` with a pair of iterators
- Make the iterators generic types
- Make the value type generic
  

.. tabbed:: std_find

   .. tab:: Example

      .. literalinclude:: find.txt
         :language: cpp
         :lines: 9-20
         :dedent: 3

   .. tab:: Run It


      And we can prove to ourselves that we get the same results as
      :cref:`std::find`.

      .. include:: find.txt

      And since it is arguably the same function as ``std::find``,
      we now know we no longer need it.

.. admonition:: Try this!

   Change the name of the function ``my_find`` to ``find`` and change
   the matching name on line 24.

   Does this program still compile?  Explain.

   Rewrite the previous example to use :cref:`std::find`.


-----

.. admonition:: More to Explore

   - From cppreference.com

     - Overview of the `algorithms <http://en.cppreference.com/w/cpp/algorithm>`_ library.
     - `std::find <http://en.cppreference.com/w/cpp/algorithm/find>`_ (and find_if).

