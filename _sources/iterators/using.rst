..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. |---| unicode:: U+2014 

.. index:: 
   pair: iterator; using

Using iterators
===============

Assigning an iterator explicitly to a variable works much like any other type:

.. code-block:: cpp

   vector<int> nums = {1, 2, 3, 4, 5};
   vector<int>::iterator it = nums.begin();

The variable ``it`` now points to the beginning of the container ``nums``
and can used much like a pointer:

.. code-block:: cpp

   vector<int> nums = {1, 2, 3, 4, 5};
   vector<int>::iterator it = nums.begin();

   cout << *it;  // prints: 1

The iterator type always matches the value type of the enclosing container.
Just as with pointers, an iterator to a ``vector<int>``
is a different type from an iterator to a ``vector<string>``.

It is possible to declare an iterator and use it in a traditional for loop:

.. code-block:: cpp

   vector<int> nums = {1, 2, 3, 4, 5};
   cout << "nums contains:";

   for (vector<int>::iterator it = nums.begin(); 
        it != nums.end(); ++it) {
       std::cout << ' ' << *it;
   }

Which produces:

.. code-block:: none

   nums contains: 1 2 3 4 5

A while loop can produce equivalent results:

.. code-block:: cpp

   vector<int> nums = {1, 2, 3, 4, 5};
   cout << "nums contains:";

   vector<int>::iterator it = nums.begin(); 
   while (it != nums.end())
       std::cout << ' ' << *it;
       ++it;
   }

We can shorten either example with ``auto``, 
since the compiler can easily determine what type is returned from ``begin()``:

.. code-block:: cpp

   for (auto it = nums.begin(); it != nums.end(); ++it) {
       std::cout << ' ' << *it;
   }

Example code like one of the two previous examples is commonly found on the web,
even when the point of the example has nothing to do with iterators.
When you don't need an iterator, don't use it:

.. code-block:: cpp

   for (const auto& n: nums) {
       std::cout << ' ' << n;
   }

A common source of error for new programmers is confusion about the types used in these two loops:

``begin()``
    **Always** returns an iterator that must be dereferenced in order to access the element value.

The range for declaration
    **Always** is assigned a value from the container.
    Unless the container is a container of pointers, no dereferencing is needed.


Limits of Range-based for loops
-------------------------------
The :cref:`Range-for loop`, while convenient, has limitations.

Any situation in which you do not need or want to visit every element
requires a traditional loop:

.. code-block:: cpp

   for (int i=n; i>0; i/=2) {
     // do something with i . . .
   }

Similarly, if you need to iterate through multiple containers in a single loop,
possibly at different rates, then you need a traditional for loop:

.. code-block:: cpp

   for (int i=n, j=0; i>0; i/=2, j++) {
     // do something with i and j . . .
   }

If you need to :term:`traverse` a container and remove items,
then you need an explicit iterator so that you can call the container ``erase`` method.

See the erase example in the following section.

Container functions that require iterators
------------------------------------------
Most container functions that use position information do not 
accept an integral position or an index like ``operator[]``.
Position information is expressed using iterators.

insert
   Inserts elements at the specified location in the container.

.. tabbed:: tab_iterator_using_insert

   .. tab:: Example

      Create a ``vector<int>`` and initialize it with 3 values:

      .. code-block:: cpp

         std::vector<int> nums(3,100);

      Insert a value at the beginning of the vector:

      .. code-block:: cpp

         auto it = nums.begin();
         it = nums.insert(it, 200);

      Insert 2 values at the beginning of the vector:

      .. code-block:: cpp

         it = nums.insert(it, 2, 200);

      Insert one vector into another vector:

      .. code-block:: cpp

         auto it = nums.begin();
         std::vector<int> fib {1, 1, 2, 3, 5, 8, 13, 21};
         nums.insert(it+2, fib.begin(), fib.end());

   .. tab:: Run it

      .. activecode:: ac_iterator_insert
         :language: cpp
         :compileargs: ['-Wall', '-Wextra', '-pedantic', '-std=c++11']

         #include <iostream>
         #include <vector>
            
         void print(const std::vector<int>& v) {
           for (auto x: v) {
             std::cout << ' ' << x;
           }
           std::cout << '\n';
         }
            
         int main () {
           std::vector<int> nums(3,100);
           print(nums);
            
           auto it = nums.begin();
           it = nums.insert(it, 200);
           print(nums);
            
           nums.insert(it,2,300);
           print(nums);
            
           // 'it' no longer valid, get a new one:
           it = nums.begin();
            
           std::vector<int> fib {1, 1, 2, 3, 5, 8, 13, 21};
           nums.insert(it+2, fib.begin(), fib.end());
           print(nums);
            
           int arr[] = { 501,502,503 };
           nums.insert(nums.begin(), arr, arr+3);
           print(nums);
         }


erase
   Removes specified elements from the container.
   ``erase`` may remove a single element or a contiguous range of elements.

.. tabbed:: tab_iterator_using_erase

   .. tab:: Example

      Given a ``vector<int>``:

      .. code-block:: cpp

         std::vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

      We can erase the first element:

      .. code-block:: cpp

         nums.erase(nums.begin());

      or erase a range of adjacent elements:

      .. literalinclude:: using_erase.txt
         :language: cpp
         :dedent: 5
         :lines: 23

      or erase other elements:

      .. literalinclude:: using_erase.txt
         :language: cpp
         :dedent: 5
         :lines: 28-35

      Things to note about the last erase example:

      - ``it`` is not incremented in the for loop iteration expression
      - If an element is erased, the current iterator is *invalidated*.
        Any further use would be an error in a ``vector``.

        The :cref:`vector::erase` function returns the iterator to the next element
        in the container.
      - If an element is **not** erased, *then* increment the iterator.


   .. tab:: Run it

      .. include:: using_erase.txt


-----

.. admonition:: More to Explore

   - `Iterator Library <http://en.cppreference.com/w/cpp/iterator>`_ at cppreference.com
   - C++ Concepts: `Iterator <http://en.cppreference.com/w/cpp/concept/Iterator>`_
