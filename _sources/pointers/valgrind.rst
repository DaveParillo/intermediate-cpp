..  Copyright (C)  Dave Parillo.
    Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, Prefaces, and
    Contributor List, no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".


.. index:: 
   pair: debugging; pointers

Pointer debugging
=================

All the techniques described in section :doc:`../back-matter/app-a/debugging` applies
when debugging pointers.
What can make debugging pointer errors more difficult is that 
when things go wrong with a pointer, often memory is corrupted
as well, 
which limits what you can get done with ``cout``.

Tools are your friends.

#. Learn how to use a debugger.

   The debugging section has a brief overview of the gdb debugger
   and links to more information.

#. Consider a dynamic memory checker such as ``valgrind``.

.. index::
   pair: debugging; valgrind

Valgrind
--------

The ``valgrind`` program can be used to detect some (but not all) common errors in C and C++ programs 
that use pointers and dynamic storage allocation. 
In addition to basic memory checking, ``valgrind`` can find many bugs related to
uninitialized variables and undefinded behavior.
You can run ``valgrind`` on your program by putting ``valgrind`` at the start of the command line::

  valgrind ./my-program 

You may pass in arguments to your program or redirect input from the shell::

  valgrind ./my-program arg1 arg2 < test-input

This will run your program and produce a report of any memory allocations and de-allocations it did. 
Valgrind will also warn you about common errors like using uninitialized memory, 
dereferencing pointers to strange places, 
writing off the end of memory blocks allocated using ``malloc`` or ``new``, 
or failing to free blocks.

You can suppress all of the output except errors using the -q option, like this::

  valgrind -q ./my-program 

You can also turn on more tests, e.g.::

  valgrind -q --tool=memcheck --leak-check=yes ./my-program

See ``valgrind --help`` or ``man valgrind`` for more information about the (many) options, 
or look at the documentation at http://valgrind.org/ for detailed information about what the output means. 
If you want to run ``valgrind`` on your own machine, 
you may be able to find a version that works at http://valgrind.org. 
Unfortunately, this is only likely to work if you are running a Unix-like 
operating system (which includes Linux and MacOS X, but not Windows).

A simple walk-through.
Let's say we have the following code in ``foo.cpp`` with a simple error:

.. code-block:: cpp

   #include <iostream>
   int main () {
     int x;
     int y = 3;

     std::cout << "sum: " << (x + y) << '\n';
   }


Just as with gdb, compile it with debugging symbols.

.. code-block:: none

   g++ foo.cpp -g3 -o foo

Valgrind provides a lot of debugging information very quickly,
although on some systems, even with debug symbols compiled in,
your output looks like this::

    ==1229== Conditional jump or move depends on uninitialised value(s)
    ==1229==    at 0x40DDBA3: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/libstdc++.so.6.0.18)
    ==1229==    by 0x40DE168: std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::do_put(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/libstdc++.so.6.0.18)
    ==1229==    by 0x40E9F1D: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/libstdc++.so.6.0.18)
    ==1229==    by 0x40EA112: std::ostream::operator<<(int) (in /usr/lib/libstdc++.so.6.0.18)
    ==1229==    by 0x41CB9D2: (below main) (in /lib/libc-2.18.so)


In order to get ``valgrind`` to report line numbers related to errors 
in calls to library functions, you need to add the command line argument
``--track-origins=yes``, like this:

.. code-block:: none

    $ valgrind --track-origins=yes ./foo

    ==1302== Conditional jump or move depends on uninitialised value(s)
    ==1302==    at 0x40DDB47: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/libstdc++.so.6.0.18)
    ==1302==    by 0x40DE168: std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::do_put(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/libstdc++.so.6.0.18)
    ==1302==    by 0x40E9F1D: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/libstdc++.so.6.0.18)
    ==1302==    by 0x40EA112: std::ostream::operator<<(int) (in /usr/lib/libstdc++.so.6.0.18)
    ==1302==    by 0x41CB9D2: (below main) (in /lib/libc-2.18.so)
    ==1302==  Uninitialised value was created by a stack allocation
    ==1302==    at 0x8048717: main (foo.cpp:3)
    ==1302== 
    ==1302== Use of uninitialised value of size 4

.. reveal:: reveal-valgrind-details
   :showtitle: Show All valgrind output
   :hidetitle: Hide valgrind details

   .. code-block:: none

      ==1302==    at 0x40DDA53: ??? (in /usr/lib/libstdc++.so.6.0.18)
      ==1302==    by 0x40DDB7B: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/libstdc++.so.6.0.18)
      ==1302==    by 0x40DE168: std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::do_put(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/libstdc++.so.6.0.18)
      ==1302==    by 0x40E9F1D: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/libstdc++.so.6.0.18)
      ==1302==    by 0x40EA112: std::ostream::operator<<(int) (in /usr/lib/libstdc++.so.6.0.18)
      ==1302==    by 0x41CB9D2: (below main) (in /lib/libc-2.18.so)
      ==1302==  Uninitialised value was created by a stack allocation
      ==1302==    at 0x8048717: main (foo.cpp:3)
      ==1302== 
      ==1302== Conditional jump or move depends on uninitialised value(s)
      ==1302==    at 0x40DDA5C: ??? (in /usr/lib/libstdc++.so.6.0.18)
      ==1302==    by 0x40DDB7B: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/libstdc++.so.6.0.18)
      ==1302==    by 0x40DE168: std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::do_put(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/libstdc++.so.6.0.18)
      ==1302==    by 0x40E9F1D: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/libstdc++.so.6.0.18)
      ==1302==    by 0x40EA112: std::ostream::operator<<(int) (in /usr/lib/libstdc++.so.6.0.18)
      ==1302==    by 0x41CB9D2: (below main) (in /lib/libc-2.18.so)
      ==1302==  Uninitialised value was created by a stack allocation
      ==1302==    at 0x8048717: main (foo.cpp:3)
      ==1302== 
      ==1302== Conditional jump or move depends on uninitialised value(s)
      ==1302==    at 0x40DDBA3: std::ostreambuf_iterator<char, std::char_traits<char> > std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::_M_insert_int<long>(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/libstdc++.so.6.0.18)
      ==1302==    by 0x40DE168: std::num_put<char, std::ostreambuf_iterator<char, std::char_traits<char> > >::do_put(std::ostreambuf_iterator<char, std::char_traits<char> >, std::ios_base&, char, long) const (in /usr/lib/libstdc++.so.6.0.18)
      ==1302==    by 0x40E9F1D: std::ostream& std::ostream::_M_insert<long>(long) (in /usr/lib/libstdc++.so.6.0.18)
      ==1302==    by 0x40EA112: std::ostream::operator<<(int) (in /usr/lib/libstdc++.so.6.0.18)
      ==1302==    by 0x41CB9D2: (below main) (in /lib/libc-2.18.so)
      ==1302==  Uninitialised value was created by a stack allocation
      ==1302==    at 0x8048717: main (foo.cpp:3)
      ==1302== 
      sum: 134514654
      ==1302== 
      ==1302== HEAP SUMMARY:
      ==1302==     in use at exit: 0 bytes in 0 blocks
      ==1302==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
      ==1302== 
      ==1302== All heap blocks were freed -- no leaks are possible
      ==1302== 
      ==1302== For counts of detected and suppressed errors, rerun with: -v
      ==1302== ERROR SUMMARY: 20 errors from 4 contexts (suppressed: 0 from 0)

There can be a lot of noise in the output,
especially when templates are involved. 
If you look at the last line in each group, ``foo.cpp, line 3`` is called out each time.
And that is exactly where the error lies.


-----

.. admonition:: More to Explore

  - `The Valgrind Quick Start Guide <http://valgrind.org/docs/manual/QuickStart.html>`_
  - `Valgrind tutorial <http://pages.cs.wisc.edu/~bart/537/valgrind.html>`_ - from Barton P. Miller
  - `Valgrind video tutorial <https://www.youtube.com/watch?v=bb1bTJtgXrI>`_
  - `Valgrind is not a leak checker blogpost <http://maintainablecode.logdown.com/posts/245425-valgrind-is-not-a-leak-checker>`_



