..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. include:: <isonum.txt>

.. index:: 
   pair: introductory topics; compiling

Command-line compiling
----------------------

Why in the 'modern' era, is there still such focus on command line and
text based tools for programming?
Several actually.

- Command line applications can easily be used in batch files or scripts, 
  which is essential for automated testing or builds. 
  On large software projects, even if your team uses an 
  Integrated Development Environment (IDE), you'll also need a command line
  tool-chain that a machine can execute.
- The input, output and error streams can easily be redirected, 
  allowing information to be sent or received from files or other applications. 
  This can mean test data can be easily supplied or output captured.
- Use over remote shell or similar connections makes it possible to
  efficiently perform tasks remotely, 
  such as when a developer is connecting from home or on the road. 
- There are defined standards for help 
  (such as the Unix **man** command or passing -? as an argument). 
  If someone does not know a feature, they can easily discover what the tool provides. 
- If you are writing such tools rather than using them, 
  the command line is easy to develop for. 

  Accepting arguments on the command line is trivial and 
  output to a text stream is similarly easy.

.. index:: g++ compiler
   single: c++ compiler
   single: compiler
   single: build steps
   pair: graph; build steps


The C++ compiler
................

There are many programs that will make executables from C++ source.
One popular choice is ``gcc``, the Gnu project C and C++ compiler.
``gcc`` is free and open-source, meaning that it can be made to run
on many different operating systems.
It also has the advantage of being able to compile more than just C and C++,
although it was developed initially for that.
One of the advantages of using a multi language tool like gcc is that
it potentially minimizes the number of new tools you have to learn
to begin working in a new language.

When you invoke ``gcc``, it normally does preprocessing, compilation, assembly and linking.

.. graphviz::
   :alt: Standard executable build steps

   digraph foo {
     fontname = "Bitstream Vera Sans"
     label="Standard executable build steps";
     labelloc=bottom;
     rankdir=LR;
     node [
        fontname = "Bitstream Vera Sans"
        fontsize = 14
        style=filled
        fillcolor=lightblue
     ];

     cpp [label="C preprocessor"];
     gcc [label="compiler"];
     as  [label="assembler"];
     ld [label="linker (ld)\nlink in libstdc++ object code"];

     node [
        shape=box,
        fillcolor=wheat
     ];
     hello [label="hello.cpp\n(source code)"];
     cpp2 [label="preprocessed\nhello.cpp"];
     asm [label="hello.s\n(assembly code)"];
     obj [label="hello.o\n(object code)"];
     exe [label="hello\n(executable)"];

     hello -> cpp -> cpp2 ->gcc -> asm -> as ->obj -> ld -> exe; 

     {rank=same hello cpp cpp2} -> {rank=same gcc asm as} -> {rank=same obj ld exe} [style=invis]

   }

``gcc`` is a complex program with **many** options.
You can execute only one of these steps, some of them, 
all of them, or change the behavior of one or more steps.

Generally, we are interested in building our programs as simply as possible.
Given a single source file ``main.cpp``, that contains all the code
needed to describe a working program, it is enough to type::

    g++ main.cpp

This command will perform all of the steps to make an executable 
and write the executable to a file named ``a.out``.
Normally, however, we want to give our programs meaningful names::

    g++ main.cpp -o main

The ``-o`` switch tells g++ to write the executable to a file named ``main``.
We could have added a file extension, like ``.exe``, but that is ordinarily
only done on the Windows |copy| operating system.
On most other systems, the extension is used for people to sort out different
types of files, but the operating system doesn't need them to figure things out.

If our ``main.cpp`` contained syntax from the C++11 standard,
or included any headers that did, then in order for it to compile,
the following switch must also be added::

    g++ main.cpp -std=c++11 -o main

The default C++ version for most compilers, gcc included is c++98.

A summary of useful command line arguments:

o
  Specify the output executable filename.

g
  Include debugging symbols in the executable output.
  Debug level #2 is the default.

  You must include this if you want to debug your program using a debugger.

Wall
   Print all warnings

Werror
   Treat warnings as errors and do not write an executable output file.

Wextra
   Print extra warnings above and beyond 'all'.

pedantic
   Warn about code not compliant with the ISO standard.

std=c++11
   Instruct the compiler the program contains C++11 syntax.

O3
   Compile with optimization level #3 enabled.

The order of command line arguments (generally) does not matter.


.. index:: 
   pair: introductory topics; make

The make utility
................

The ``make`` program automatically determines which pieces of a large
program need to be recompiled, and issues commands to recompile them.
Note how this is different from the previous sections.
The ``make`` program doesn't actually compile anything.
It doesn't know how.
What ``make`` *does know* is

* What source files are normally associated with C++ programs
* What commands are used to compile and link C++ source files

``make`` actually 'knows' some other things as well,
and can be given more information to make it even more useful,
but these first two things are the most important.

To prepare to use 'make', you must write a file called the "makefile"
that describes the relationships among files in your program and
provides commands for updating each file.  
By default, ``make`` searches for a file named **Makefile**.

Once a file named Makefile exists, each time you change some source
files, this simple shell command::

   make

is enough to perform all necessary recompilations.  The ``make`` program
uses the makefile data and the last-modification times of the files
to decide which of the files need to be updated.  For each of those
files, it issues the recipes recorded in the makefile.


A simple makefile consists of "rules" with the following shape::

    TARGET ... : PREREQUISITES ...
       RECIPE
       ...
       ...

A "target" is usually the name of a file that is generated by a
program; examples of targets are executable or object files.  A target
can also be the name of an action to carry out, such as 'clean'.
Since these don't result in object files or executables, they are called
*phony targets*.

A "prerequisite" is a file that is used as input to create the
target.  A target often depends on several files.

A "recipe" is an action that 'make' carries out.  A recipe may have
more than one command, either on the same line or each on its own line.

.. note:: 

   You need to put a tab character at the beginning of every
   recipe line!  This is an obscurity that catches the unwary.

A *very* simple Unix C++ makefile:

.. code-block:: make

   CXX = c++
   CXXFLAGS=-Wall -Wextra -pedantic -std=c++11 -O3

   my_prog : clean
      ${CXX} ${CXXFLAGS} -o my_prog *.cpp

   clean:
      rm -f my_prog

This makefile always deletes the executable file 'my_prog'
whether any source files have changed or not and recompiles 
every cpp file in the current directory to regenerate the executable.
Not particularly efficient, but for small programs
it gets the job done and requires no maintenance if new files are added.

Assuming you keep your work separated into directories so that
all the source code in a directory applies only to a single executable,
then this simple makefile is sufficient for everything you'll
need to worry about over course duration.

Suffice it to say that make provides many tools and techniques to define
'smarter' recipes that do not suffer the constraints listed above.

The make program defines a large number of built-in variables to control
how programs get built.
While there are many, 
the two to focus on for now are those used in the previous makefile.

  CXX
     Specify which C++ compiler to use

  CXXFLAGS
     Specify command line arguments to pass to the C++ compiler

A slight variation on this theme creates several executables from a list.
The primary assumption in this makefile is that each program in the list ``PROGS``
contains a main and is a single file.
The makefile makes use of the fact that ``make`` can make a simple program
without a makefile, if the program is contained within a single file.

.. code-block:: make

   CXX = c++
   CXXFLAGS=-Wall -Wextra -pedantic -std=c++11 -O3

   PROGS = asciitable \
           hello \
           phrase-o-matic \
           printodds \
           std11-test \

   all: $(PROGS)

   clean:
       rm -f $(PROGS)

Even without a Makefile, ``make`` is smart enough to produce sensible
defaults for simple programs.
For example, given our ``main.cpp`` example from the previous section,
we can make it using make::

    make main

The make program will actually invoke::

    g++ main.cpp -o main

If you have exported an environment variable that make uses,
such as ``CXXFLAGS``, then those will be used by make::

    export CXXFLAGS=-Wall -Wextra -pedantic -std=c++11

Now the make program will invoke::

    make main
    g++ main.cpp -Wall -Wextra -pedantic -std=c++11 -o main

Which is exactly what the previous makefile is doing, but on all of the 
programs listed.

Running your programs
.....................

If you compile your own program, you will need to prefix it with ./ 
on the command line to tell the shell that you want to run a program 
in the current directory (called ‘.’) instead of one of the standard system directories. 
So for example, if I've just built a program called *hello*, I can run it by typing::

  ./hello

-----

.. admonition:: More to Explore

   - Textbook FAQ: :doc:`../q101-why-not-an-ide`

   - `GNU Make Manual <https://www.gnu.org/software/make/manual/>`_
   - Prefer compile-time and link-time errors to runtime errors

     - Effective C++ item #46

   - Pay attention to compiler warnings
     
     - Effective C++ item #48
