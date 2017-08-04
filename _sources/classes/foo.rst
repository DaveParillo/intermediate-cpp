..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   single: classes

Classes
=======

Normal paragraph text.

.. graphviz::

   digraph G {
     fontname = "Bitstream Vera Sans"
     fontsize = 10

     node [
        fontname = "Bitstream Vera Sans"
        fontsize = 10
        shape = "record"
        style=filled
        fillcolor=lightblue
     ]

     edge [
        fontname = "Bitstream Vera Sans"
        fontsize = 10
     ]

     Animal [
        label = "{Animal|+ name : string\l+ age : int\l|+ die() : void\l}"
     ]

     subgraph clusterAnimalImpl {
        label = "Package animal.impl"
        style=filled
        fillcolor=wheat

        Dog [
          label = "{Dog||+ bark() : void\l}"
        ]

        Cat [
          label = "{Cat||+ meow() : void\l}"
        ]
     }

     edge [
        arrowhead = "empty"
     ]

     Dog -> Animal
     Cat -> Animal

     edge [
        headlabel = "0..*"
        taillabel = "0..*"
     ]

     Dog -> Cat
   }


Another:

.. graphviz::

   digraph hierarchy {
     //size="5,5"
     label="Simple class hierarchy"

     node[shape=record,style=filled,fillcolor=gray95,
          fontname = "Bitstream Vera Sans", fontsize = 10
          style=filled
        fillcolor=lightblue]
     edge[dir=back, arrowtail=empty,
          fontname = "Bitstream Vera Sans", fontsize = 10]


     2[label = "{AbstractSuffixTree|+ text\n+ root|...}"]
     3[label = "{SimpleSuffixTree|...| + constructTree()\l...}"]
     4[label = "{CompactSuffixTree|...| + compactNodes()\l...}"]
     5[label = "{SuffixTreeNode|...|+ addSuffix(...)\l...}"]
     6[label = "{SuffixTreeEdge|...|+ compactLabel(...)\l...}"]

     {rank=same; 4 6} -> {rank=same; 3 5} [style=invis]

     2->3
     2->4
     5->5[constraint=false, arrowtail=diamond]
     4->3[constraint=false, arrowtail=odiamond]
     2->5[constraint=false, arrowtail=odiamond]
     5->6[arrowtail=diamond]
   }



Constructors
============

Enumerated Types
================


Operator Overloads
==================


Class Design
============

Memory Management
=================

Deep Copy
=========


.. index:: 
   single: class templates
   pair: templates; class


Class Templates
===============

File I/O
========

Serialization
=============


Subsection
..........

TBD

-----

.. admonition:: More to Explore

   TBD

