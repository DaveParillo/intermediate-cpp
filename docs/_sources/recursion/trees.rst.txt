..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: binary trees; trees; recursion

The Binary Tree ADT
===================
Unlike the linear sequences covered so far,
a :term:`tree` is a *hierarchical* abstract data type.
Conceptually, it can be thought of as a collection of
*nodes* defined by parent-child relationships.

Refer to :doc:`../containers/trees` to review the basic vocabulary and structure of binary trees.

So far, we have discussed trees only at a conceptual level.
In this section we will program one.

In a binary tree, one node is the :term:`root`.
It serves as the 'trunk' of the tree and serves the same
function as the :term:`head` of a :term:`list`
The root node is the *only* node in a tree without a parent.
All other nodes in a :term:`tree` refer to exactly 1 parent.
In a :term:`binary tree`,
the children are commonly referred to as the **left** and **right** children.

A simple binary tree can be implemented as a recursive data structure:

.. code-block:: cpp
   
   template <class T>
    struct tree {
       T value;
       tree<T>* left = nullptr;
       tree<T>* right = nullptr;
   };

This tree stores a single value of type ``T``
and has two pointers to potential children.
It is important to remember when working with a recursive tree such as this
that a child might be a ``nullptr``.

.. index:: traverval

Binary tree traversal
---------------------
Traversal of a data structure means visit elements of the structure.
It might mean visiting a subset, but can also involve visiting each element
from the first to last.

For sequential containers, identifying the start and end of the container is simple.
But where are the *first* and *last* elements of a tree?

The short answer is that there is no single answer.
Since a tree is not a sequential data structure,
a tree allows for different sequences (or traversals).
There are several different types of traversals.
The most common tree traversals are:

- Preorder
- Postorder
- Inorder
- Level order

Given the following binary tree,
let's implement functions that traverse the tree using each of the four methods.

.. digraph:: btree
   :alt: Subject of the next 4 traversals

   graph [
          nodesep=0.1, ranksep=0.25, splines=line;
          labelloc=b;
          label="Subject of the next 4 traversals";
       ];
   node [fontname = "Bitstream Vera Sans", fontsize=12,
         style=filled, fillcolor=lightblue,
         shape=circle, fixedsize=true, width=0.3];
   edge [weight=1, arrowsize=0.5, dir=none];

   a, b, am, c, bm, d, e, cm, f, g, em, h, fm, i;
   am, bm, cm, em, fm [style=invis, label=""];

   a->b,c;
   b->d [weight=2]; // nudge b: trees b & c are not balanced
   c->e,f;
   e->g;
   f->h,i;

   edge [style=invis, weight=100];
   f->fm;
   e->em;
   c->cm;
   b->bm;
   a->am;


Preorder traversal
..................
A depth first traversal.

Visit all nodes **before** visiting children:

.. tabbed:: preorder

   .. tab:: Preorder

      In this generic code block,
      the function ``visit`` represents the action to take on the current
      node.

      .. code-block:: cpp

         void preorder(tree<T>* node) {
           if (node == nullptr) {
             return;
           }
           visit(node);
           preorder(node->left);
           preorder(node->right);
         }

   .. tab:: Run It

      .. activecode:: ac-trees-preorder
         :language: cpp
         :compileargs: ['-Wall', '-Wextra', '-pedantic', '-std=c++11']

         #include <iostream>

         template <class T>
         struct tree {
           T value;
           tree<T>* left = nullptr;
           tree<T>* right = nullptr;
         };

         template <class T>
         void print(tree<T>* node) {
           if (node == nullptr) {
             return;
           }
           std::cout << node->value << ' ';
           print(node->left);
           print(node->right);
         }

         ====

         int main() {
           tree<char> a;
           tree<char> b;
           tree<char> c;
           tree<char> d;
           tree<char> e;
           tree<char> f;
           tree<char> g;
           tree<char> h;
           tree<char> i;
           a.value = 'a';
           b.value = 'b';
           c.value = 'c';
           d.value = 'd';
           e.value = 'e';
           f.value = 'f';
           g.value = 'g';
           h.value = 'h';
           i.value = 'i';
           a.left  = &b;
           a.right = &c;
           b.right = &d;
           c.left  = &e;
           c.right = &f;
           e.left  = &g;
           f.left  = &h;
           f.right = &i;

           std::cout << "Preorder: ";
           print (&a);

           return 0;
         }





Postorder traversal
...................
A depth first traversal.

Visit all nodes **after** visiting children:

.. tabbed:: postorder

   .. tab:: Postorder

      .. code-block:: cpp

         void postorder(tree<T>* node) {
           if (node == nullptr) {
             return;
           }
           postorder(node->left);
           postorder(node->right);
           visit(node);
         }

   .. tab:: Run It

      The only difference between the preorder example and this
      is the order of the function calls in the ``print`` function.

      .. activecode:: ac-trees-postorder
         :language: cpp
         :compileargs: ['-Wall', '-Wextra', '-pedantic', '-std=c++11']

         #include <iostream>

         template <class T>
         struct tree {
           T value;
           tree<T>* left = nullptr;
           tree<T>* right = nullptr;
         };

         template <class T>
         void print(tree<T>* node) {
           if (node == nullptr) {
             return;
           }
           print(node->left);
           print(node->right);
           std::cout << node->value << ' ';
         }

         ====

         int main() {
           tree<char> a;
           tree<char> b;
           tree<char> c;
           tree<char> d;
           tree<char> e;
           tree<char> f;
           tree<char> g;
           tree<char> h;
           tree<char> i;
           a.value = 'a';
           b.value = 'b';
           c.value = 'c';
           d.value = 'd';
           e.value = 'e';
           f.value = 'f';
           g.value = 'g';
           h.value = 'h';
           i.value = 'i';
           a.left  = &b;
           a.right = &c;
           b.right = &d;
           c.left  = &e;
           c.right = &f;
           e.left  = &g;
           f.left  = &h;
           f.right = &i;

           std::cout << "Postorder: ";
           print (&a);

           return 0;
         }




Inorder traversal
.................
A depth first traversal.

Visit the left child (and the left child subtree),
then visit the current node,
then 
visit the right child (and the right child subtree),


.. tabbed:: inorder

   .. tab:: Inorder

      .. code-block:: cpp

         void inorder(tree<T>* node) {
           if (node == nullptr) {
             return;
           }
           inorder(node->left);
           visit(node);
           inorder(node->right);
         }

   .. tab:: Run It

      .. activecode:: ac-trees-inorder
         :language: cpp
         :compileargs: ['-Wall', '-Wextra', '-pedantic', '-std=c++11']

         #include <iostream>

         template <class T>
         struct tree {
           T value;
           tree<T>* left = nullptr;
           tree<T>* right = nullptr;
         };

         template <class T>
         void print(tree<T>* node) {
           if (node == nullptr) {
             return;
           }
           print(node->left);
           std::cout << node->value << ' ';
           print(node->right);
         }

         ====

         int main() {
           tree<char> a;
           tree<char> b;
           tree<char> c;
           tree<char> d;
           tree<char> e;
           tree<char> f;
           tree<char> g;
           tree<char> h;
           tree<char> i;
           a.value = 'a';
           b.value = 'b';
           c.value = 'c';
           d.value = 'd';
           e.value = 'e';
           f.value = 'f';
           g.value = 'g';
           h.value = 'h';
           i.value = 'i';
           a.left  = &b;
           a.right = &c;
           b.right = &d;
           c.left  = &e;
           c.right = &f;
           e.left  = &g;
           f.left  = &h;
           f.right = &i;

           std::cout << "Inorder: ";
           print (&a);

           return 0;
         }



Level order traversal
.....................
Differs from the previous traversals: it is a 'breadth first' traversal.
Also, this algorithm is easier to implement iteratively than recursively.

Visit each node on each level of the tree
then visit the children one level deeper.

.. tabbed:: levelorder

   .. tab:: Level order

      This is an iterative, not a recursive function.

      .. code-block:: cpp

         void levelorder(tree<T>* node) {
           if (node == nullptr) {
             return;
           }
           std::queue<tree<T>*> q;
           q.push(node);
           while (!q.empty()) {
             auto tmp = q.front();
             visit(tmp);
             q.pop();
             if(tmp->left)  q.push(tmp->left);
             if(tmp->right) q.push(tmp->right);
           }
         }


   .. tab:: Run It

      .. activecode:: ac-trees-levelorder
         :language: cpp
         :compileargs: ['-Wall', '-Wextra', '-pedantic', '-std=c++11']

         #include <iostream>
         #include <queue>

         template <class T>
         struct tree {
           T value;
           tree<T>* left = nullptr;
           tree<T>* right = nullptr;
         };

         template <class T>
         void print(tree<T>* node) {
           if (!node) return;
           
           std::queue<tree<char>*> q;
           q.push(node);
           while (!q.empty()) {
             auto tmp = q.front();
             std::cout << tmp->value << ' ';
             q.pop();
             if(tmp->left)  q.push(tmp->left);
             if(tmp->right) q.push(tmp->right);
           }
         }

         ====

         int main() {
           tree<char> a;
           tree<char> b;
           tree<char> c;
           tree<char> d;
           tree<char> e;
           tree<char> f;
           tree<char> g;
           tree<char> h;
           tree<char> i;
           a.value = 'a';
           b.value = 'b';
           c.value = 'c';
           d.value = 'd';
           e.value = 'e';
           f.value = 'f';
           g.value = 'g';
           h.value = 'h';
           i.value = 'i';
           a.left  = &b;
           a.right = &c;
           b.right = &d;
           c.left  = &e;
           c.right = &f;
           e.left  = &g;
           f.left  = &h;
           f.right = &i;

           std::cout << "Level order: ";
           print (&a);

           return 0;
         }





-----

.. admonition:: More to Explore

   - `STL containers library <http://en.cppreference.com/w/cpp/container>`_
   - `Visualgo: binary heap <https://visualgo.net/en/heap?slide=1>`_

