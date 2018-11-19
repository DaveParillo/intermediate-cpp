..  Copyright (C)  Dave Parillo, Brad Miller, David Ranum, Jeffrey Elkner, 
    Peter Wentworth, Allen B. Downey, Chris Meyers, and Dario Mitchell.  
    Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, Prefaces, and
    Contributor List, no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

..  Some content from the OpenDSA eTextbook project. See
    http://algoviz.org/OpenDSA for more details.
    Copyright (c) 2012-2013 by the OpenDSA Project Contributors, and
    distributed under an MIT open source license.

.. _glossary:

Glossary
--------

.. glossary::
   :sorted:

   abstraction
      A technique used to reduce the complexity of systems and data.
      An abstraction often involves a simplified model of the
      'real world' for the purposes of achieving goals
      within a specific problem domain. 

      Data abstraction enforces a clear separation between the 
      abstract properties of a :term:`data type` and the concrete details 
      of its implementation. 

   abstract base class
      A class in which some functions are not implemented.
      Abstract bases classes cannot be instantiated --- a derived class
      must override the abstract virtual function with an implementation.

   abstract data type
      Abbreviated :term:`ADT`. The realization of a :term:`data type`
      as a software component.

   activation record
      The entity that is stored on the :term:`runtime stack` during
      program execution.
      It stores any active :term:`local variable` and the return
      address from which a new subroutine is being called, so that
      this information can be recovered when the subroutine
      terminates.

   activecode
      A unique interpreter environment that allows code to be executed within a web browser.

   ADT
      Abbreviation for :term:`abstract data type`.

   aggregate type
      A :term:`data type` whose :term:`members <member>` have subparts.
      For example, a typical database record.
      Another term for this is :term:`composite type`. 

   algorithm
      A general step by step process for solving a :term:`problem`.

   ancestor
      In a tree, for a given node :math:`A`, any node on a
      path from :math:`A` up to the root is an ancestor of
      :math:`A`.

   anti-pattern
      A common response to a recurring problem that is generally ineffective.
      Anti-patterns represent examples that you **should not** emulate!
      As bad as they are, they can still be instructive.
      Compare to :term:`design pattern`.

   array-based list
      An implementation for the :term:`list` ADT that uses an array to
      store the list elements.

   array-based stack
      Analogous to an :term:`array-based list`, this uses an array to
      store the elements when implementing the :term:`stack` ADT.

   array-based queue
      Analogous to an :term:`array-based list`, this uses an array to
      store the elements when implementing the :term:`queue` ADT.

   ASCII character coding
      American Standard Code for Information Interchange.
      A commonly used method for encoding characters using a binary code.
      Standard ASCII uses an 8-bit code to represent upper and lower
      case letters, digits, some punctuation, and some number of
      non-printing characters (such as carrage return).
      Now largely replaced by UTF-8 encoding.

   assignable
      A :term:`type` is *assignable* if the type can be copy-assigned
      a new value as the left-hand side of the operation.

      References are not assignable because once initialized,
      they cannot be assigned a new value.


   associative container
      A set of sorted data structures that can be quickly searched.
      ``map`` and ``set`` are examples.

   attribute
      In :term:`object-oriented programming <object-oriented programming paradigm>`,
      a synonym for :term:`data member`.

   backing storage
      The underlying storage for an :term:`ADT`.

   bag
      In set notation, a bag is a collection of elements with no order
      (like a set), but which allows for duplicate-valued elements
      (unlike a set).
      A synonym for :term:`multilist`.

   balanced tree
      A :term:`tree` where the :term:`subtrees <subtree>` meet some
      criteria for being balanced.
      Two possibilities are that the tree is
      :term:`height balanced`, or that the tree has a roughly equal
      number of :term:`nodes <node>` in each subtree.

   base
      Synonym for :term:`radix`.

   base case
      In :term:`recursion`, the base case is the termination condition.
      This is a simple input or value that can be solved
      without resorting to a recursive call.

   base class
      In :term:`object-oriented programming <object-oriented programming paradigm>`,
      a class from which another class :term:`inherits <inherit>`.
      The class that inherits is called a :term:`subclass` or :term:`derived class`.
  
   big-Oh notation
      In algorithm analysis, a shorthand notation for describing the
      upper bound for an algorithm or problem.

   binary search
      A standard :term:`recursive <recursion>` algorithm for finding
      the :term:`record` with a given :term:`key` within
      a sorted list.
      It runs in :math:`O(\log n)` time.
      At each step, look at the middle of the current sublist, and throw
      away the half of the records whose keys are either too small or
      too large.
      
   binary tree
      A non-linear data structure with a set of nodes which is either empty, 
      or else has a root node together two binary trees, called the left and right
      :term:`subtrees <subtree>`, which are disjoint from each
      other and from the :term:`root`.

   binning
      In :term:`hashing`, binning is a type of :term:`hash function`.
      Say we are given keys in the range 0 to 999, and have a hash
      table of size 10.
      In this case, a possible hash function might simply divide the
      key value by 100.
      Thus, all keys in the range 0 to 99 would hash to slot 0, keys
      100 to 199 would hash to slot 1, and so on.
      In other words, this hash function "bins" the first 100 keys to
      the first slot, the next 100 keys to the second slot, and so
      on.
      This approach tends to make the hash function dependent on the
      distribution of the high-order bits of the keys.

   block
      Defines a :term:`scope` within a program.
      A synonym for :term:`code block`.

   boolean variable
      A variable that takes on one of the two values ``true`` and
      ``false``.

   bucket
      In :term:`bucket hashing`, a bucket is a sequence of
      :term:`slots <slot>` in the :term:`hash table` that are grouped
      together.

   bucket hashing
      A method of :term:`hashing` where multiple :term:`slots <slot>`
      of the :term:`hash table` are grouped together to form a
      :term:`bucket`.
      The :term:`hash function` then either hashes to some bucket, or
      else it hashes to a :term:`home slot` in the normal way, but
      this home slot is part of some bucket.
      :term:`Collision resolution <collision resolution>` is handled
      first by attempting to find a free position within the same
      bucket as the home slot.
      If the bucket if full, then the record is placed in an
      :term:`overflow bucket`.

   bug
      An error in a program.

   ceiling
      Written :math:`\lceil x \rceil`, for real value :math:`x` the
      ceiling is the least integer :math:`\geq x`.

   child
      In a tree, the set of :term:`nodes <node>` directly pointed to
      by a node :math:`R` are the :term:`children <child>` of :math:`R`.

   class
      In the :term:`object-oriented programming paradigm`
      an ADT and its implementation together make up a class.
      An instantiation of a class within a program is termed an
      :term:`object`.

   class hierarchy
      In :term:`object-oriented programming <object-oriented programming paradigm>`,
      a set of classes and their interrelationships.
      One of the classes is the :term:`base class`, and the others are
      :term:`derived classes <derived class>` that :term:`inherit` either
      directly or indirectly from the base class.

   class invariant
   type invariant
   invariants
      A class invariant is an assertion about conditions which must be true
      in order for a class to remain valid.

   client
      The user of a service.

   closed hash system
      A :term:`hash system` where all records are stored in slots of
      the :term:`hash table`.
      This is in contrast to an :term:`open hash system`.

   code block
      Defines a :term:`scope` within a program.
      A synonym for :term:`block`.


   codelens
      An interactive environment that allows the user to control the step by step execution of a program

   cohesion
      In :term:`object-oriented programming <object-oriented programming paradigm>`,
      a term that refers to the degree to which a class has a single 
      well-defined role or responsibility.

   collision
      In a :term:`hash system`, this refers to the case where two
      search :term:`keys <key>` are mapped by the
      :term:`hash function` to the same 
      slot in the :term:`hash table`.
      This can happen on insertion or search when another record has
      already been hashed to that slot.
      In this case, a :term:`closed hash system` will require a
      process known as :term:`collision resolution` to find the
      location of the desired record.

   collision resolution
      The outcome of a :term:`collision resolution policy`.

   collision resolution policy
      In :term:`hashing`, the process of resolving a
      :term:`collision`.
      Specifically in a :term:`closed hash system`, this is the
      process of finding the proper position in a :term:`hash table`
      that contains the
      desired record if the :term:`hash function` did not return the
      correct position for that record due to a :term:`collision` with
      another record.

   comment
      Information in a program that is meant for other programmers (or anyone
      reading the source code) and has no effect on the execution of the
      program.

   comparable
      The concept that two objects can be compared to determine if they
      are equal or not, or to determine which one is greater than the
      other. 
      In set notation, elements :math:`x` and :math:`y` of a set are
      comparable under a given relation :math:`R` if either
      :math:`xRy` or :math:`yRx`.
      To be reliably compared for a greater/lesser relationship,
      the values being compared must belong to a :term:`total order`.
      In programming, the property of a data type such that two
      elements of the type can be compared to determine if they the
      same (a weaker version), or which of the two is larger (a
      stronger version).

   comparator
      A function given as a parameter to a method of a library
      (or alternatively, a parameter for a C++ template or a Java
      generic).
      The comparator function concept provides a generic way
      encapulates the process of performing a comparison between two
      objects of a specific type.
      For example, if we want to write a generic sorting routine, that
      can handle any record type, we can require that the user of the
      sorting routine pass in a comparator function
      to define how records in the collection are to be compared.

   comparison
      The act of comparing two :term:`keys <key>` or
      :term:`records <record>`.
      For many :term:`data types <data type>`, a comparison has
      constant time cost.
      For others, such as :term:`linked list` the cost often increases
      as the number of elements increases.

   compile
      To translate a program written in a high-level language into a
      low-level language all at once, in preparation for later execution.

   compile-time error
      Errors detected by the compiler.
      Compare to :term:`runtime error`, :term:`link error`,
      and :term:`semantic error`.

   compile-time polymorphism
      A form of :term:`polymorphism` known as Overloading.
      Overloaded methods have the same names, but different signatures
      as a method available elsewhere in the class.
      Compare to :term:`runtime polymorphism`.

   complete binary tree
      A binary tree where the nodes are filled in row by row, with the
      bottom row filled in left to right.
      Due to this requirement, there is only one tree of :math:`n`
      nodes for any value of :math:`n`.
      Since storing the records in an array in row order leads to a
      simple mapping from a node's position in the array to its
      :term:`parent`, :term:`siblings <sibling>`, and
      :term:`children <child>`, the array representation is most 
      commonly used to implement the complete binary tree.
      The :term:`heap` data structure is a complete binary tree with
      partial ordering constraints on the node values.

   Composite design pattern
      Given a class hierarchy representing a set of objects, and a
      container for a collection of objects, the composite
      :term:`design pattern` addresses the relationship between the
      object hierarchy and a bunch of behaviors on the objects.
      In the composite design, each object is required to implement
      the collection of behaviors.
      This is in contrast to the procedural approach where a behavior
      (such as a tree :term:`traversal`) is implemented as a
      method on  the object collection (such as a :term:`tree`).
      Procedural tree traversal requires that the tree have a method
      that understands what to do when it encounters any of the object
      types (:term:`internal <internal node>` or
      :term:`leaf nodes <leaf node>`) that the tree might contain.
      The composite approach would have the tree call the "traversal"
      method on its root node, which then knows how to perform the
      "traversal" behavior.
      This might in turn require invoking the traversal method of
      other objects (in this case, the children of the root).

   composite type
      A type whose :term:`members <member>` have subparts.
      For example, a typical database record.
      Another term for this is :term:`aggregate type`.

   composition
      Relationships between classes based on usage rather than 
      :term:`inheritance <inherit>`, i.e. a **HAS-A** relationship.
      For example, some code in class 'A' has a reference to some
      other class 'B'.

   constant running time
      The cost of a function whose running time is not related to its
      input size.
      In Theta notation, this is traditionally written as
      :math:`\Theta(1)`.

   container
   container class
      A :term:`data structure` that stores a collection of
      :term:`records <record>`.
      Typical examples are arrays and
      :term:`hash tables <hash table>`.

   cost
      The amount of resources that the solution consumes.

   CPU
      Acronym for Central Processing Unit, the primary processing
      device for a computer.

   current position
      A property of some list ADTs, where there is maintained a
      "current position" state that can be referred to later.

   data field
      In :term:`object-oriented programming <object-oriented programming paradigm>`,
      a synonym for :term:`data member`.

   data item
      A piece of information or a record whose value is drawn from a type.

   data member
      The variables that together define the space required by a data
      item are referred to as data members.
      Some of the commonly used synonyms include :term:`data field`,
      :term:`attribute`, and :term:`instance variable`.

   data structure
      The implementation for an :term:`ADT`.

   data type
      A type together with a collection of operations to manipulate
      the type.

   debugging
      The process of finding and removing any of the three kinds of
      programming errors.

   declaration
     A declaration introduces a new :term:`name` 
     and :term:`type` into a :term:`scope`.

   depth
     The depth of a node :math:`M` in a tree is the length
     of the path from the root of the tree to :math:`M`.

   dequeue
      A specialized term used to indicate removing an element from a queue.

   derived class
      In :term:`object-oriented programming <object-oriented programming paradigm>`,
      any class within a :term:`class hierarchy` that
      :term:`inherits <inherit>` from some other class.
      A synonym for :term:`derived class`.

   descendant
      In a tree, the set of all nodes that have a node :math:`A` as an
      :term:`ancestor` are the descendants of :math:`A`.
      In other words, all of the nodes that can be reached from
      :math:`A` by progressing downwards in tree.
      Another way to say it is: The
      :term:`children <child>` of :math:`A`, their children, and so
      on.

   deserialization
      The process of returning a :term:`serialized <serialization>`
      representation for a data structure back to its original
      in-memory form.

   design pattern
      An abstraction for describing the design of programs,
      that is, the interactions of objects and classes.
      Experienced software designers learn and reuse patterns
      for combining software components, and design patterns allow
      this design knowledge to be passed on to new programmers more quickly.
      Examples are :term:`Composite design pattern`,
      :term:`flyweight`,
      :term:`iterator`,
      :term:`strategy`, and
      :term:`visitor`.

   dictionary
      An abstract data type or interface for a data structure or
      software subsystem that supports insertion, search, and deletion
      of records.

   double hashing
      A :term:`collision resolution` method. A second hash
      function is used to generate a value :math:`c` on the key.
      That value is then used by this key as the step size in
      :term:`linear probing by steps`.
      Since different keys use different step sizes (as generated by
      the second hash function), this process avoids the clustering
      caused by standard linear probing by steps.

   doubly linked list
      A :term:`linked list` implementation variant where each list
      node contains access pointers to both the previous element and
      the next element on the list.

   dynamic array
      Arrays, once allocated, are of fixed size. A dynamic array puts
      an interface around the array so as to appear to allow the array
      to grow and shrink in size as necessary. Typically this is done
      by allocating a new copy, copying the contents of the old array,
      and then returning the old array to :term:`free store`.
      In some programming languages, the term
      :term:`vector` is used as a synonym for dynamic array.

   dynamic memory allocation
      A programming technique where linked objects in a data structure
      are created from :term:`free store` as needed. When no longer
      needed, the object is either returned to :term:`free store` or
      left as :term:`garbage`, depending on the programming language.

   element
      One value or member in a set.

   empty
      For a :term:`container` class, the state of containing no
      :term:`elements <element>`.

   encapsulation
      In programming, the concept of hiding implementation details
      from the user of an ADT, and protecting
      :term:`data members <data member>` of an
      object from outside access.

   enqueue
      A specialized term used to indicate inserting an element onto a queue.

   enumeration
      The process by which a :term:`traversal` lists every object in
      the :term:`container` exactly once.
      Thus, a traversal that prints the :term:`nodes <node>` is said
      to enumerate the nodes.
      An enumeration can also refer to the actual listing that is
      produced by the traversal 
      (as well as the process that created that listing).

   equivalence class
      An :term:`equivalence relation` can be used to partition a set
      into equivalence classes.

   equivalence relation
      Relation :math:`R` is an equivalence relation on set
      :math:`\mathbf{S}` if it is :term:`reflexive`,
      :term:`symmetric`, and :term:`transitive`.

   exception
      Another name for a runtime error.

   exchange
      A swap of adjacent records in an array.

   executable
      Another name for object code that is ready to be executed.

   external fragmentation
      A condition that arises when a series of memory requests
      result in lots of small :term:`free blocks <free block>`, no one
      of which is useful for servicing typical requests.

   FIFO
      Abbreviation for "first-in, first-out".
      This is the access paradigm for a :term:`queue`,
      and an old terminolgy for the queue is "FIFO list".

   fixed-length coding
      Given a collection of objects, a fixed-length coding scheme
      assigns a code to each object in the collection using codes that
      are all of the same length.
      Standard ASCII and Unicode representations for characters are
      both examples of fixed-length coding schemes.
      This is in contrast to :term:`variable-length coding`.

   floor
      Written :math:`\lfloor x \rfloor`, for real value :math:`x` the
      floor is the greatest integer :math:`\leq x`.

   flyweight
      A :term:`design pattern` that is meant to solve the following
      problem:
      You have an application with many objects.
      Some of these objects are identical in the information that
      they contain, and the role that they play.
      But they must be reached from various places, and conceptually they
      really are distinct objects.
      Because there is so much duplication of the same information,
      we want to reduce memory cost by sharing that space. 
      For example, in document layout, 
      the letter "C" might be represented by an object that
      describes that character's strokes and bounding box.
      However, we do not want to create a separate "C" object everywhere
      in the document that a "C" appears.
      The solution is to allocate a single copy of the shared representation
      for "C" objects.
      Then, every place in the document that needs a "C" in a given font,
      size, and typeface will reference this single copy.
      The various instances of references to a specific form of "C" are
      called flyweights.

   folding method
      In :term:`hashing`, an approach to implementing a
      :term:`hash function`.
      Most typically used when the key is a string, the folding method
      breaks the string into pieces (perhaps each letter is a piece,
      or a small series of letters is a piece), converts the letter(s)
      to an integer value (typically by using its underlying encoding
      value), and summing up the pieces.

   free block
      A block of unused space in a memory pool.

   free block list
      In a memory manager, the list that stores the necessary
      information about the current :term:`free blocks <free block>`.
      Generally, this is done with some sort of :term:`linked list`,
      where each node of the linked list indicates the start position
      and length of the free block in the memory pool.

   free store
      Space available to a program during runtime to be used for
      :term:`dynamic memory allocation` of objects.
      The free store is distinct from the :term:`runtime stack`.
      The free store is sometimes referred to as the :term:`heap`,
      which can be confusing because :term:`heap` more often refers to
      a specific data structure. Most programming languages provide
      functions to allocate (and maybe to deallocate) objects from the
      free store, such as ``new`` in C++ and Java.

   full tree
      A :term:`binary tree` is full if every :term:`node` is either a
      :term:`leaf node` or else it is an :term:`internal node` with
      two non-empty :term:`children <child>`.

   function
      In programming, a subroutine that takes input parameters and
      uses them to compute and return a value.
      In this case, it is usually considered bad practice for a
      function to change any global variables
      (doing so is called a side effect).

   fundamental type
      One of the :term:`simple types <simple type>` 
      provided by the language.
      Examples are ``bool``, ``char``, ``int``, and ``double``.
      Types provided by the STL, such as ``std::string`` and ``std::vector``
      are not considered 'fundamental' types.

   garbage
      In memory management, any memory that was previously (dynamically)
      allocated by the program during runtime, but which is no longer
      accessible since all pointers to the memory have been deleted or
      overwritten.
      In some languages, garbage can be recovered by
      :term:`garbage collection`.
      In languages such as C and C++ that do not provide built-in garbage
      collection, so creating garbage is considered a
      :term:`memory leak`.

   garbage collection
      Languages with garbage collection such
      Java, JavaScript, Lisp, and Scheme will periodically reclaim
      :term:`garbage` and return it to :term:`free store`.

   general tree
      A tree in which any given node can have any number of
      :term:`children <child>`.
      This is in contrast to, for example, a :term:`binary tree` where
      each node has a fixed number of children (some of which might be
      ``null``).
      General tree nodes tend to be harder to implement for this reason.
   
   generic programming
      A computer programming style in which functions are written 
      using *placeholders for* types. In C++ this is accomplished
      using :term:templates<template>`.
      Templates are used to create actual functions for specific types
      as needed. 

   hash function
      In a :term:`hash system`, the function that converts a
      :term:`key` value to a position in the :term:`hash table`.
      The hope is that this position in the hash table contains the
      record that matches the key value.

   hash system
      The implementation for search based on hash lookup in a
      :term:`hash table`.
      The :term:`key` is processed by a
      :term:`hash function`, which returns a position in a
      :term:`hash table`, which hopefully is the correct position in
      which to find the record corresponding to the search key.

   hash table
      The data structure (usually an array) that stores data
      records for lookup using :term:`hashing`.

   hashing
      A search method that uses a :term:`hash function` to convert a
      :term:`key` into a position within a
      :term:`hash table`. 
      In a properly implemented :term:`hash system`, that position in
      the table will have high probability of containing the record
      that matches the key value.
      Sometimes, the hash function will return an position that does
      not store the desired key, due to a process called
      :term:`collision`.
      In that case, the desired record is found through a process
      known as :term:`collision resolution`.

   head
      The beginning of a :term:`list`.

   header guard
      In C and C++, used to prevent definitions copied into a file
      using the ``#include`` directive from beging defined
      more than once.

      .. code-block:: cpp

         #ifndef FOO_H_INCLUDED // any name uniquely mapped to file name
         #define FOO_H_INCLUDED
         // contents of the file are here
         #endif

   header node
      Commonly used in implementations for a :term:`linked list` or
      related structure, this :term:`node` preceeds the first element
      of the list.
      Its purpose is to simplify the code implementation by
      reducing the number of special cases that must be programmed
      for.

   heap
      This term has two different meanings.
      Sometimes, it is a synonym for :term:`free store`.
      A heap may also refer to a particular data structure.
      This data structure is a :term:`complete binary tree` with the
      requirement that every :term:`node` has a value greater than its
      :term:`children <child>` (called a :term:`max heap`), or else
      the requirement that every node has a value less than its
      children (called a :term:`min heap`).
      Since it is a complete binary tree, a heap is nearly always
      implemented using an array rather than an explicit tree
      structure.
      To add a new value to a heap, or to remove the extreme value
      (the max value in a max-heap or min value in a min-heap) and
      update the heap,
      takes :math:`\Theta(\log n)` time in the worst case.
      However, if given all of the values in an unordered array,
      the values can be re-arranged to form a heap in only
      :math:`\Theta(n)` time. 
      Due to its space and time efficiency, the heap is a
      popular choice for implementing a :term:`priority queue`.

   height
      The height of a tree is one more than the :term:`depth` of the
      deepest :term:`node` in the tree.

   height balanced
      The condition the :term:`depths <depth>` of each :term:`subtree`
      in a tree are roughly the same.

   high-level language
      A programming language that is designed to be easy for
      humans to read and write.

   home slot
      In :term:`hashing`, this is the :term:`slot` in the
      :term:`hash table` determined for a given key by the
      :term:`hash function`.

   identifier
      An identifier is used to name a type introduced into a program by a :term:`declaration`.

      An identifier is an arbitrarily long sequence of digits, underscores, 
      lowercase and uppercase Latin letters. 
      A valid identifier must begin with a non-digit character (Latin letter, underscore, 
      Identifiers are case-sensitive (lowercase and uppercase letters are distinct), 
      and every character is significant.

   inherit
      In :term:`object-oriented programming <object-oriented programming paradigm>`,
      the process by which a :term:`subclass` gains
      :term:`data members <data member>` and :term:`methods <method>`
      from a :term:`base class`.

   inorder traversal
      In a :term:`binary tree`, a :term:`traversal` that first
      :term:`recursively <recursion>` :term:`visits <visit>` the left
      :term:`child`, then visits the :term:`root`,
      an then recursively visits the right child.

   instance variable
      In :term:`object-oriented programming <object-oriented programming paradigm>`,
      a synonym for :term:`data member`.

   integrated development environment
      A software suite that consolidates many tools developers need to 
      write and test software.
      An IDE normally consists of a source code editor, version control,
      build automation tools, and a debugger. 
      Most also automatically complete partially typed keywords and
      create commonly used code from templates.


   internal fragmentation
      A condition that occurs when more than :math:`N` bytes
      are allocated to service a memory request for :math:`N`
      bytes, wasting free storage.
      This is often done to simplify memory management.

   internal node
      In a tree, any node that has at least one non-empty
      :term:`child` is an  internal node.

   iterable
      A :term:`container` in which each element
      can be visited using an :term:`iterator`.

   iterator
      In a :term:`container` such as a :cref:`std::vector`
      or :cref:`std::set`, a separate class that
      indicates position within the container, with support for
      :term:`traversing <traversal>` through all
      :term:`elements <element>` in the container.

   key
      A field or part of a larger record used to represent that record
      for the purpose of searching or comparing.

   key-value pair
      A standard solution for solving the problem of how to relate a
      :term:`key` value to a record (or how to find the key for a
      given record) within the context of a particular index.
      The idea is to simply store as records in the index pairs of
      keys and records.
      Specifically, the index will typically store a copy of the key
      along with a reference to the record.
      The other standard solution to this problem is to pass a
      :term:`comparator` function to the index.

   LIFO
      Abbreviation for "Last-In, First-Out".
      This is the access paradigm for a :term:`stack`,
      and an old terminolgy for the stack is "LIFO list".

   leaf node
      In a :term:`binary tree`, leaf node is any node that has two
      empty :term:`children <child>`.
      (Note that a binary tree is defined so that every
      node has two children, and that is why the leaf node has to have
      two empty children, rather than no children.)
      In a general tree, any node is a leaf node if it has no children.

   level
      In a tree, all nodes of :term:`depth` :math:`d` are at
      level :math:`d` in the tree.
      The root is the only node at level 0, and its depth is 0.

   linear probing
      In :term:`hashing`, this is the simplest
      :term:`collision resolution` method.
      Term :math:`i` of the :term:`probe sequence` is simply
      :math:`i`, meaning that collision resolution works by moving
      sequentially through the hash table from the :term:`home slot`.
      While simple, it is also inefficient, since it quickly leads to
      certain free :term:`slots <slot>` in the hash table having
      higher probability of being selected during insertion or
      search.

   linear probing by steps
      In :term:`hashing`, this :term:`collision resolution` method is
      a variation on simple :term:`linear probing`.
      Some constant :math:`c` is defined such that
      term :math:`i` of the :term:`probe sequence` is
      :math:`ci`.
      This  means that collision resolution works by moving
      sequentially through the hash table from the :term:`home slot`
      in steps of size :math:`c`.
      While not much improvement on linear probing, it forms the basis
      of another collision resolution method called
      :term:`double hashing`, where each key uses a value for
      :math:`c` defined by a second :term:`hash function`.

   link error
      After compiling, a link error occurs when each compilation unit compiles correctly, 
      but in the next stage, the linker is unable to combine all 
      the object code into a single valid executable file.
      Compare to :term:`compile-time error`, :term:`runtime error`, 
      and :term:`semantic error`.


   linked list
      An implementation for the list ADT that uses
      :term:`dynamic memory allocation`
      of link nodes to store the list elements. Common variants are the
      :term:`singly linked list` and :term:`doubly linked list`.

   list
      A finite, ordered sequence of data items known as
      :term:`elements <element>`.
      This is close to the mathematical concept of a :term:`sequence`.
      Note that "ordered" in this definition means that the list
      elements have position.
      It does not refer to the relationship
      between :term:`key` values for the list elements (that is,
      "ordered" does not mean "sorted").

   local variable
      A variable declared within a function or method.
      It exists only from the time when the function is called to when
      the function exits.
      When a function is suspended (due to calling another function),
      the function's local variables are stored in an
      :term:`activation record` on the :term:`runtime stack`.

   logical form
      The definition for a data type in terms of an ADT. Contrast to
      the :term:`physical form` for the data type.

   low-level language
      A programming language that is designed to be easy for a computer to
      execute; also called machine language or assembly language.

   map
      A :term:`data structure` that relates a :term:`key` to a
      :term:`record`.

   mapping
      A :term:`function` that maps every element of a given
      :term:`set` to a unique element of another set; a
      correspondence.

   max heap
      A :term:`heap` where every :term:`node` has a :term:`key` value
      greater than its :term:`children <child>`.
      As a consequence, the node with maximum key value is
      at the :term:`root`.

   member
      In set notation, this is a synonym for :term:`element`. 
      In abstract design, a :term:`data item` is a member of a :term:`type`.
      In an object-oriented language,
      :term:`data members <data member>` are data fields in an
      object.

   member function
      Each operation associated with the ADT is implemented by a
      member function or :term:`method`.

   memory leak
      In programming, the act of creating :term:`garbage`.
      In languages such as C and C++ that do not support
      :term:`garbage collection`, repeated memory leaks will evenually
      cause the program to terminate.

   method
      In the :term:`object-oriented programming paradigm`,
      a method is an operation on a :term:`class`.
      A synonym for :term:`member function`.

   min heap
      A :term:`heap` where every :term:`node` has a :term:`key` value
      less than its :term:`children <child>`.
      As a consequence, the node with minimum key value is
      at the :term:`root`.

   mod
      Abbreviation for the :term:`modulus` function.

   modulus
      The modulus function returns the
      remainder of an integer division.
      Sometimes written :math:`n \bmod m` in mathematical expressions,
      the syntax in many programming languages is ``n % m``.

   multilist
      A list that may contain sublists.
      This term is sometimes used as a synonym to the term
      :term:`bag`.

   name
      See :term:`identifier`.

   natural language
      Any one of the languages that people speak that evolved naturally.

   natural order
      An ordering of a sequence of objects that seems 'natural' to most people.
      The 'natural order' of whole numbers is the sequence used to count things:
      1,2,3,4,5,6...
      The natural order for words is sorted alphabetically.

   node
      The objects that make up a linked structure such as a linked
      list or binary tree.
      Typically, nodes are allocated using
      :term:`dynamic memory allocation`.

   object
      An instance of a class, that is, something that is created and
      takes up storage during the execution of a computer program.
      In the :term:`object-oriented programming paradigm`, objects
      are the basic units of operation.
      Objects have state in the form of :term:`data members <data member>`,
      and they know how to perform certain actions
      (:term:`functions <function>`).

   object code
      The output of the compiler after it translates the program.

   object-oriented programming
   object-oriented programming paradigm
      An approach to problem-solving where all computations are
      carried out using :term:`objects <object>`.

   open addressing
      A synonym for :term:`closed hashing <closed hash system>`.

   open hash system
      A :term:`hash system` where multiple records might be associated
      with the same slot of a :term:`hash table`.
      Typically this is done using a linked list to store the records.
      This is in contrast to a :term:`closed hash system`.

   operating system
      The control program for a computer.
      Its purpose is to control hardware, manage resources, and
      present a standard interface to these to other software
      components.

   overflow
      The condition where the amount of data stored in an entity has
      exceeded its capacity.
      For example, a node in a array can store a certain
      number of records.
      If a record is attempted to be inserted into a node that is
      full, then something has to be done to handle this case.

   overflow bucket
      In :term:`bucket hashing`, this is the :term:`bucket` into which
      a record is placed if the bucket containing the record's
      :term:`home slot` is full.
      The overflow bucket is logically considered to have infinite
      capacity, though in practice search and insert will become
      relatively expensive if many records are stored in the overflow
      bucket.

   parameters
      The values making up an input to a :term:`function`.

   parent
      In a tree, the :term:`node` :math:`P` that directly links to a
      node :math:`A` is the parent of :math:`A`. :math:`A` is the
      :term:`child` of :math:`P`.

   parse
      To examine a program and analyze the syntactic structure.

   permutation
      A permutation of a sequence :math:`\mathbf{S}`
      is the :term:`elements <element>` of :math:`\mathbf{S}` arranged
      in some order.

   physical form
      The implementation of a data type as a data structure.
      Contrast to the :term:`logical form` for the data type.

   Pigeonhole Principle
      A commonly used lemma in Mathematics. A typical variant states:
      When :math:`n+1` objects are stored in :math:`n` locations, at
      least one of the locations must store two or more of the objects.

   POD
      An abbreviation for 'plain old data'.
      Used to indicate a data structure containing no member functions
      and only publicly accessible data.

   pop
      A specialized term used to indicate removing an :term:`element`
      from a :term:`stack`. 

   pointer-based implementation for binary tree nodes
      A common way to implement :term:`binary tree` :term:`nodes
      <node>`.
      Each node stores a data value (or a reference to a data value),
      and pointers to the left and right children.
      If either or both of the children does not exist, then a null
      pointer is stored.

   polymorphism
      An :term:`object-oriented programming <object-oriented programming paradigm>`
      term meaning *one name, many forms*.
      It describes the ability of software to change its behavior
      dynamically.  Two basic forms exist:
      :term:`runtime polymorphism` and :term:`compile-time polymorphism`.

   portability
      A property of a program that can run on more than one kind of computer.

   position
      The defining property of the list ADT, this is the concept that
      list elements are in a position. Many list ADTs support access
      by position.

   postorder traversal
      In a :term:`binary tree`, a :term:`traversal` that first
      :term:`recursively <recursion>` :term:`visits <visit>` the left
      :term:`child`, 
      then recursively visits the right child, and then visits the
      :term:`root`.

   predicate
   predicate function
      A function that returns a boolean value.

   preorder traversal
      In a :term:`binary tree`, a :term:`traversal` that first
      :term:`visits <visit>` the :term:`root`, then
      :term:`recursively <recursion>` visits the left :term:`child`,
      then recursively visits the right child.

   primary clustering
      In :term:`hashing`, the tendency in certain
      :term:`collision resolution`
      methods to create clustering in sections of the hash table.
      The classic example is :term:`linear probing`.
      This tends to happen when a group of keys follow the same
      :term`probe sequence` during collision resolution.

   primitive type
      A :term:`data type` whose values contain no subparts.
      An example is the integers.
      A synonym for :term:`simple type` 
      and :term:`code block`.

   priority
      A quantity assigned to each of a collection of
      tasks that indicate importance for order of processing.
      For example, in an operating system, there could be a collection
      of processes (jobs) ready to run.
      The operating system must select the next task to execute, 
      based on their priorities.

   priority queue
      An ADT whose primary operations of insert of records, and
      deletion of the greatest (or, in an alternative implementation,
      the least) valued record.
      Most often implemented using the :term:`heap` data structure.
      The name comes from a common application where the records being
      stored represent tasks, with the ordering values based on the
      :term:`priorities <priority>` of the tasks.

   probe function
      In :term:`hashing`, the function used by a
      :term:`collision resolution` method to calculate where to look
      next in the :term:`hash table`.

   probe sequence
      In :term:`hashing`, the series of :term:`slots <slot>` visited
      by the :term:`probe function` during
      :term:`collision resolution`.

   problem
      A task to be performed.
      It is best thought of as a :term:`function` or a mapping of
      inputs to outputs.

   problem solving
      The process of formulating a problem, finding a solution, and
      expressing the solution.

   procedural
      Typically referring to the
      :term:`procedural programming paradigm`, in contrast to the
      :term:`object-oriented programming paradigm`.

   procedural programming paradigm
      Procedural programming uses a list of instructions (and
      procedure calls) that define a series of computational steps to
      be carried out.
      This is in contrast to the 
      :term:`object-oriented programming paradigm`.
     
   program
      An instance, or concrete representation, of an algorithm in some
      programming language.
      A sequence of instructions that specifies to a computer actions and
      computations to be performed.
      A program can refer to the :term:`compiled <compile>` system
      :term:`object code`, or to the original :term:`source code`.

   programming language
      A formal notation for representing solutions.

   pseudo-random probing
      In :term:`hashing`, this is a :term:`collision resolution`
      method that stores a random permutation of the values 1 through
      the size of the :term:`hash table`.
      Term :math:`i` of the :term:`probe sequence` is simply the value
      of position :math:`i` in the permuation.

   push
      A specialized term used to indicate inserting an :term:`element`
      onto a :term:`stack`.

   push_back
      A specialized term used to indicate appending an :term:`element`
      onto a :term:`vector`.

   quadratic probing
      In :term:`hashing`, this is a :term:`collision resolution`
      method that computes term :math:`i` of the
      :term:`probe sequence` using some quadratic equation
      :math:`ai^2 _ bi + c` for suitable constants :math:`a, b, c`.
      The simplest form is simply to use :math:`i^2` as term :math:`i`
      of the probe sequence.

   queue
      A list-like structure in which elements are inserted only at one
      end, and removed only from the other one end.

   radix
      Synonym for :term:`base`. The number of digits in a number
      representation. For example, we typically represent numbers in
      base (or radix) 10. Hexidecimal is base (or radix) 16.

   RAII
      Resource Acquisition Is Initialization
      is the C++ term for a programming style in which critical resources are
      tied to the object which owns them.
      Because they are typically allocated in class constructors and 
      destroyed in class destructors, in other languages, this is
      sometimes called *Constructor Acquires, Destructor Releases*

   record
      A collection of information, typically implemented as an
      :term:`object` in an
      :term:`object-oriented programming language <object-oriented programming paradigm>`.
      Many data structures are organized containers for a collection
      of records.

   recursion
      The process of using recursive calls.
      An algorithm is recursive if it calls itself to do part of
      its work.
      See :term:`recursion`.

   recursive call
      Within a :term:`recursive function`, it is a call that the
      function makes to itself.

   recursive data structure
      A data structure that is partially
      composed of smaller or simpler instances of the same data structure.
      For example, :term:`linked lists <linked list>` and
      :term:`binary trees <binary tree>` can be viewed as recursive
      data structures.

   recursive function
      A function that includes a :term:`recursive call`.

   reference
      A value that enables a program to directly access some
      particular data item.
      An example might be a byte position within a file where the
      record is stored, or a pointer to a record in memory.
      (Note that Java makes a distinction between a reference and the
      concept of a pointer, since it does not define a reference to
      necessarily be a byte position in memory.)

   reference count algorithm
      An algorithm for :term:`garbage collection`.
      Whenever a reference is made from a variable to some memory
      location, a counter associated with that memory location is
      incremented.
      Whenever the reference is changed or deleted, the reference
      count is decremented.
      If this count goes to zero, then the memory is considered free
      for reuse.
      This approach can fail if there is a cycle in the chain of
      references.

   reflexive
      In set notation, binary relation :math:`R` on set :math:`S` is
      reflexive if :math:`aRa` for all :math:`a \in \mathbf{S}`.

   regular type
      A user defined :term:`type` that behaves like a 'regular'
      built-in (fundamental) type.
      Regular types support the following operations:

      ========================= ====================
       Operation                 Definition
      ========================= ====================
       Default constructor        T a;
       Copy constructor           T a = b;
       Destructor                 ~T (a);
       Assignment                 a = b;
       Equality                   a == b;
       Inequality                 a != b;
       Ordering                   a < b;
      ========================= ====================

   relation
      In set notation, a relation :math:`R` over set
      :math:`\mathbf{S}` is a set of ordered pairs from
      :math:`\mathbf{S}`.

   root
      In a :term:`tree`, the topmost :term:`node` of the tree.
      All other nodes in the tree are :term:`descendants <descendant>`
      of the root.

   runtime environment
      The environment in which a program (of a particular programming
      language) executes.
      The runtime environment handles such activities as managing the
      :term:`runtime stack`, the :term:`free store`, and the
      :term:`garbage collector <garbage collection>`,
      and it conducts the execution of the program.

   runtime error
      Errors encountered during program execution.
      Compare to :term:`compile-time error`, :term:`link error`, 
      and :term:`semantic error`.

   runtime polymorphism
      A form of :term:`polymorphism` known as Overriding.
      Overridden methods are those which implement a new method
      with the same signature as a method inherited from its
      base class.
      Compare to :term:`compile-time polymorphism`.

   runtime error
      An error that does not occur until the program has started to execute
      but that prevents the program from continuing.

   runtime stack
      The place where an :term:`activation record` is stored when a
      subroutine is called during a program's runtime.

   scope
      A region of the program where a defined variable, definition, or function exists. 
      Beyond that point the variable can not be accessed. 

   secondary clustering
      In :term:`hashing`, the tendency in certain
      :term:`collision resolution`
      methods to create clustering in sections of the hash table.
      In :term:`primary clustering`, this is caused by a cluster of
      keys that don't necessarily hash to the same slot but which
      following significant portions of the same
      :term:`probe sequence` during collision resolution.
      Secondary clustering results from the keys hashing to the same
      slot of the table (and so a collision resolution method that is
      not affected by the key value must use the same probe sequence
      for all such keys).
      This problem can be resolved by :term:`double hashing` since its
      probe sequence is determined in part by a second hash function.

   semantic error
      An error in a program that makes it do something other than what the
      programmer intended.
      Compare to :term:`compile-time error`, :term:`link error`, 
      and :term:`runtime error`.

   semantics
      The meaning of a program.

   separate chaining
      In :term:`hashing`, a synonym for
      :term:`open hashing <open hash system>`

   sequence
      In set notation, a collection of elements with an order, and
      which may contain duplicate-valued elements.
      A sequence is also sometimes called a :term:`tuple` or a
      :term:`vector`.

   sequence container
      A container in which elements can be accessed sequentially.
      The underlying data may be a contiguous block of memory, as with ``vector`` and
      ``array``, or may be non-contiguous memory, as with ``list``.
      
   sequential tree representation
      A representation that stores a series of node values with the
      minimum information needed to reconstruct the tree structure.
      This is a technique for :term:`serializing <serialization>` a
      tree.

   serialization
      The process of taking a data structure in memory and
      representing it as a sequence of bytes.
      This is sometimes done in order to transmit the data structure
      across a network or store the data structure in a
      :term:`stream`, such as on disk.
      :term:`Deserialization <deserialization>` reconstructs the
      original data structure from the serialized representation.

   set
      A collection of distinguishable :term:`members <member>` or
      :term:`elements <element>`.

   sibling
      In a :term:`tree`, a sibling of :term:`node` :math:`A` is any
      other node with the same :term:`parent` as :math:`A`.

   signature
      In a programming language, the signature for a function is its
      return type and its list of parameters and their types.

   simple type
      A :term:`data type` whose values contain no subparts.
      An example is the integers.
      A synonym for :term:`primitive type`
      and :term"`fundamental type`.

   simulating recursion
      If a programming language does not support :term:`recursion`,
      or if you want to implement the effects of recursion more
      efficiently, you can use a :term:`stack` to maintain the
      collection of subproblems that 
      would be waiting for completion during the recursive process.
      Using a loop, whenever a recursive call would have been made,
      simply add the necessary program state to the stack.
      When a return would have been made from the recursive call, pop
      the previous program state off of the stack.

   singly linked list
      A :term:`linked list` implementation variant where each list
      node contains access an pointer only to the next element in the list.

   slot
      In :term:`hashing`, a position in a :term:`hash table`.

   software engineering
      The study and application of engineering to the design,
      development, and maintenance of software.

   software reuse
      In :term:`software engineering`, the concept of reusing a piece
      of software.
      In particular, using an existing piece of software (such as a
      function or library) when creating new software.

   source code
      A program, stored in a file, in a high-level language before being compiled or interpreted.

   stack
      A list-like structure in which elements may be inserted or
      removed from only one end.

   strategy
      An approach to accomplish a task, often encapsulated as an
      algorithm.
      Also the name for a :term:`design pattern` that separates the
      algorithm for performing a task from the control for applying
      that task to each member of a collection.
      A good example is a generic sorting function that takes a
      collection of records (such as an array) and a "strategy" in the
      form of an algorithm that knows how to extract the key from a
      record in the array.
      Only subtly different from the :term:`visitor` design pattern,
      where the difference is primarily one of intent rather than
      syntax.
      The strategy design pattern is focused on encapsulating an
      activity that is part of a larger process, so that different
      ways of performing that activity can be substituted.
      The visitor design pattern is focused on encapsulating an
      activity that will be performed on all members of a collection
      so that completely different activities can be substituted
      within a generic method that accesses all of the collection
      members.

   stream
      The process of delivering content in a
      :term:`serialized <serialization>` form.

   subclass
      In :term:`object-oriented programming <object-oriented programming paradigm>`,
      any class within a :term:`class hierarchy` that
      :term:`inherits <inherit>` from some other class.
      A synonym for :term:`derived class`.

   subtree
      A subtree is a subset of the nodes of a binary tree that
      includes some node :math:`R` of the tree as the subtree
      :term:`root` along with all the :term:`descendants <descendant>`
      of :math:`R`.


   symmetric
      In set notation, relation :math:`R` is symmetric if whenever
      :math:`aRb`, then :math:`bRa`, for all :math:`a, b \in \mathbf{S}`.

   syntax
      The structure of a program.

   syntax error
      An error in a program that makes it impossible to parse --- and
      therefore impossible to interpret.

   tail
      The end of a :term:`list`.

   template
      A template is a specific way in C++ to write 
      :term:`generic <generic programming>` functions and classes.

      A template by itself is not a class, type, function, or any other entity.
      It defines a **recipe** for generating a class or function.

   test-driven development
      Test-driven development (TDD) is a software development process 
      that relies on the repetition of a very short development cycle: 
      requirements are turned into very specific test cases, 
      then the software is improved to pass the new tests, only. 
      This is opposed to software development that allows software to be 
      added that is not proven to meet requirements.

      Kent Beck, who is credited with having developed the technique, 
      stated in 2003 that TDD encourages simple designs and inspires confidence.

   token
      One of the basic elements of the syntactic structure of a program,
      analogous to a word in a natural language.

   total order
      A binary relation on a set where every pair of distinct elements
      in the set are :term:`comparable` (that is, one can determine
      which of the pair is greater than the other).

   trailing return type
      A C++11 language feature that allows a function or lambda expression
      to defer evaluating the function return type.  Example:

      .. code-block:: cpp

         template<class T>
         auto mul(T a, T b) -> decltype(a*b){
           return a*b;
         }

      or

      .. code-block:: cpp

         [](double x, double y) -> int {return x*y;}

   transitive
      In set notation, relation :math:`R` is transitive if whenever
      :math:`aRb` and :math:`bRc`, then :math:`aRc`, for all
      :math:`a, b, c \in \mathbf{S}`.

   traversal
   traverse
      Any process for visiting all of the objects in a collection
      (such as a :term:`tree` or :term:`list`) in some order.

   tree
      A tree :math:`\mathbf{T}` is a finite set of one or more
      :term:`nodes <node>` such that there is one designated node
      :math:`R`, called the :term:`root` of :math:`\mathbf{T}`.
      If the set :math:`(\mathbf{T} -\{R\})` is not empty, these
      nodes are partitioned into :math:`n > 0`
      disjoint sets :math:`\mathbf{T}_0`,
      :math:`\mathbf{T}_1`, ..., :math:`\mathbf{T}_{n-1}`, 
      each of which is a tree, and whose :term:`roots <root>`
      :math:`R_1, R_2, ..., R_n`,
      respectively, are :term:`children <child>` of :math:`R`.

   tree traversal
      A :term:`traversal` performed on a tree.
      Traditional tree traversals include
      :term:`preorder <preorder traversal>` and
      :term:`postorder <postorder traversal>` traversals for both
      :term:`binary <binary tree>` and :term:`general <general tree>`
      trees, and :term`inorder traversal` for binary search trees.

   tuple
      In set notation, another term for a :term:`sequence`.

   two's complement
      A mathematical operation on binary numbers, 
      as well as a binary signed number representation based on this operation. 

   type
      A collection of values.

   unary function
      A function that accepts one parameter.

   unit test
      A software test method in which a single *unit* of source code, 
      for example, a single function is tested in isolation.
      Unit tests are short code fragments, typically created by programmers 
      as part of the development process.
      In a process like :term:`test-driven development` the unit tests
      are written before any other code.

   unsorted list
      A :term:`list` where the records stored in the list can appear
      in any order (as opposed to a sorted list).
      An unsorted list can support efficient (:math:`\Theta(1)`)
      insertion time (since you can put the record anywhere
      convenient), but requires :math:`\Theta(n)` time for both search
      and deletion.

   variable-length coding
      Given a collection of objects, a variable-length coding scheme
      assigns a code to each object in the collection using codes that
      can be of different lengths.
      Typically this is done in a way such that the objects that are
      most likely to be used have the shortest codes, with the goal of
      minimizing the total space needed to represent a sequence of
      objects, such as when representing the characters in a document.
      This is in contrast to :term:`fixed-length coding`.

   vector
      In set notation, another term for a :term:`sequence`.
      As a data structure, the term vector usually used as a snyonym
      for a :term:`dynamic array`.

   visit
      During the process of a :term:`traversal` on a :term:`list` or
      :term:`tree` the action that takes place on each :term:`node`.

   visitor
      A :term:`design pattern` where a :term:`traversal` process is
      given a function (known as the visitor) that is applied to every
      object in the collection being traversed.
      For example, a generic tree or graph traversal might be
      designed such that it takes a function parameter,
      where that function is applied to each node.

   volatile
      In the context of computer memory, this refers to a memory that
      loses all stored information when the power is turned off.

