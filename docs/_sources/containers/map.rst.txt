..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   pair: associative containers; map

The map class
=============

A :term:`map` refers to any data structure that 'maps' :term:`keys <key>` to values.
The ``map`` class is arguably the most useful container in the STL
after ``vector``.

All the containers discussed so far focused on storing 1 thing.
That is, each stores values of a single type.
Maps add a new wrinkle.
A ``map`` stores **pairs** of things.
Traditionally, the pair stored is referred to as a :term:`key-value pair`.\ [1]_

Nearly every programming language provides some kind of ``map`` implementation.
Some languages use the terms *associative array* or *dictionary List*,
but structurally, they are very similar.

**Values** are retrieved from a ``map`` using the **key**.
Each :term:`key` must be unique.
In other words, keys are members of a ``set``.
Like a :cref:`std::set`,
adding a second node with the same key replaces the old value.
Unlike a :cref:`std::set`,
a :cref:`std::map` provides the :cref:`map::operator[]`.

.. code-block:: cpp

   #include <iostream>
   #include <map>
   #include <string>

   int main() {
     std::map<std::string, int> name_counts {{"Alice", 27}, 
                                             {"Bob", 3}, 
                                             {"Clara", 1}};

     for (const auto& kvp : name_counts) {
       std::cout << kvp.first << ": " 
                 << kvp.second << '\n';
     }
     name_counts["Bob"]   = 42;      // update existing value
     name_counts["Darla"] = 9;       // insert a new value

     // get map values
     std::cout << "Alice is " << name_counts.find("Alice")->second << '\n';
     // or get the key iterator, then print
     auto it = name_counts.find("Alice");
     std::cout << "Alice is " << it->second << '\n';

     std::cout << "Bob is " << name_counts.at("Bob") << '\n';
     std::cout << "Darla is " << name_counts["Darla"] << '\n';
   }

Selected map functions
----------------------
Access and assignment
    :cref:`map::operator=`, :cref:`map::at`, and :cref:`map::operator[]`
Capacity
    :cref:`map::empty`, :cref:`map::size`, and :cref:`map::max_size`
Modifiers
    :cref:`map::clear`, :cref:`map::emplace`, :cref:`map::insert`, :cref:`map::erase`, :cref:`map::swap`
Lookup
    :cref:`map::count`, :cref:`map::find`, :cref:`map::equal_range`, 
    :cref:`map::upper_bound` and :cref:`map::lower_bound`

For large data sets, the lookup functions in a ``map`` are faster than their
counterparts in a sequential container such as ``vector``.

.. note::

   There is no ``push_back()`` for a map.

   The ``map`` decides where elements go, not you.
   All access requires either knowing the key or having an iterator.

Map structure
-------------
Internally, a ``map`` is a sorted :term:`complete binary tree`.
Each node in the tree is a :cref:`std::pair`.


.. digraph:: larger
   :alt: A complete binary tree

   graph [
          nodesep=0.25, ranksep=0.3, splines=line;
          labelloc=b;
          label="A complete binary tree";
       ];
   node [fontname = "Bitstream Vera Sans", fontsize=14,
         style=filled, fillcolor=lightblue,
         shape=circle, fixedsize=true, width=0.3];
   edge [weight=1, arrowsize=0.5, dir=none];

   a, b, am, c, d, bm, e, f, cm, g, h, dm, i, j, em, k, l, fm, m;
   am, bm, cm, dm, em, fm [style=invis, label=""];

   a->b,c;
   b->d [weight=2]; // nudge b: trees b & c are not balanced
   b->e;
   c->f,g;
   d->h,i;
   e->j,k;
   f->l,m;

   edge [style=invis, weight=100];
   d->dm; 
   e->em;
   b->bm;
   f->fm;
   c->cm;
   a->am;

All :term:`nodes <node>` are sorted by their :term:`keys <key>`.
Sorting is managed using ``operator<`` by default, 
but this can be configured in the map constructor
using a custom compare function or class, just as with a ``set``.

.. code-block:: cpp

   #include <iostream>
   #include <map>
   #include <set>
   #include <string>

   using std::string;

   void print (std::set<string> keys) {
     for (const auto& key: keys) {
       std::cout << key << ' ';
     }
   }

   int main() {
     std::map<string, int> inventory {
       {"apple", 12},
       {"kiwi", 4},
       {"lemon", 1},
       {"pear", 4},
       {"peach", 4},
       {"grape", 100},
       {"cocoa", 3},
     };

     std::set<string> inventory_keys;

     // extract keys from the inventory map
     for (const auto& i: inventory) {
       auto result = inventory_keys.insert(i.first);
       if (!result.second) std::cout << "no insertion\n";
     }

     std::cout << "All fruit keys:\n";
     print (inventory_keys);

     std::set<string> keys;
     auto it = inventory.upper_bound("kiwi");
     while(it != inventory.end()) {
       auto result = keys.insert(it->first);
       if (!result.second) std::cout << "no insertion\n";
       ++it;
     }
     std::cout << "\n\nAll fruit keys greater than 'kiwi':\n";
     print (keys);

   }

and produces:

.. code-block:: none

   All fruit keys:
   apple cocoa grape kiwi lemon peach pear

   All fruit keys greater than 'kiwi':
   lemon peach pear


Using a customer comparator, we can store map items in reverse order:

.. code-block:: cpp

   // custom comparator

   #include <functional>  // std::greater
   #include <iostream>
   #include <map>
   #include <string>

   
   // print inventories with different custom comparators
   template <class Comparator>
   void print (const string title, const std::map<string, int, Comparator>& x) {
      std::cout << title;
      for (const auto& kvp: x) {
        std::cout << kvp.first << ", " << kvp.second << '\n';
      }
   }

   int main() {
     std::map<string, int> inventory {
        {"apple", 12},
        {"kiwi", 4},
        {"lemon", 1},
        {"pear", 4},
        {"peach", 4},
        {"grape", 100},
        {"cocoa", 3},
     };

     print ("Initial inventory:\n", inventory);

        
     // define a reverse ordered map
     // a lambda is not the best choice here
     const auto greater_than = [] (string lhs, string rhs) { return lhs > rhs;};
     std::map<string, int, decltype(greater_than)> reverse_inventory1 (greater_than);

     // but it works
     for (auto& i: inventory) {
       reverse_inventory1.insert(i);
     }
     print ("\n\nReverse inventory using lambda:\n", reverse_inventory1);


     // STL provides many basic operations wrapped in a std::function
     std::map<string, int, std::greater<string>> reverse_inventory2;
     for (auto& i: inventory) {
       reverse_inventory2.insert(i);
     }
     print ("\nReverse inventory using std::greater:\n", reverse_inventory2);

     return 0;
   }

which produces:

.. code-block:: text

   Initial inventory:
   apple, 12
   cocoa, 3
   grape, 100
   kiwi, 4
   lemon, 1
   peach, 4
   pear, 4

   Reverse inventory using lambda:
   pear, 4
   peach, 4
   lemon, 1
   kiwi, 4
   grape, 100
   cocoa, 3
   apple, 12

   Reverse inventory using std::greater:
   pear, 4
   peach, 4
   lemon, 1
   kiwi, 4
   grape, 100
   cocoa, 3
   apple, 12    

Variations on std::map
----------------------
The STL provides 3 alternate forms of :cref:`std::map` class:

multimap
   A ``map`` in which duplicate keys are allowed.

unordered_map
   A ``map`` of unique :term:`key-value pairs <key-value pair>` 
   stored based on the :term:`key` object :term:`hash function`.
   Added in C++11.
  
unordered_multimap
   An ``unordered_map`` in which duplicate keys are allowed.
 


-----

.. admonition:: More to Explore

 - `STL containers library <http://en.cppreference.com/w/cpp/container>`_

.. topic:: Footnotes

 .. [1]  Sometimes this is abbreviated as 'KVP'.  
         On cppreference.com you'll see it shortened even further to just ``P``
