..  Copyright (C)  Dave Parillo, Brad Miller, David Ranum, Jeffrey Elkner, 
    Peter Wentworth, Allen B. Downey, Chris Meyers, and Dario Mitchell.  
    Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, Prefaces, and
    Contributor List, no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. Much of the content in this section is adapted from
   http://www.cs.yale.edu/homes/aspnes/classes/223/notes.html

.. index:: 
   single: debugging
   single: errors

Debugging
=========

Different kinds of errors can occur in a program, and it is useful to
distinguish among them in order to track them down more quickly:

#. Syntax errors are produced when compilers or interpreters translate 
   source code into machine readable form. 
   A syntax error is the failure to follow the basic rules of the language.
   For example, mis-matched parentheses or braces, or misplaced keyword,
   or a variable used where a keyword is expected.
#. Link errors occur when each compilation unit compiles correctly,
   but the next stage, the linker is unable to combine all the object code
   into a single valid executable file.
#. Runtime errors are produced by the executable system if something goes wrong
   while the program is running. Runtime error messages may include
   information about where the error occurred and what functions were
   executing. Detailed runtime error output is typically only available in
   compiled languages such as C++ with debugging symbols explicitly compiled
   into the final program.
#. Semantic errors are problems with a program that compiles and runs but
   doesn't do the right thing. Example: An expression may not be evaluated in
   the order you expect, yielding an unexpected result.

The first step in debugging is to figure out which kind of error you are
dealing with. Although the following sections are organized by error type, some
techniques are applicable in more than one situation.

.. index:: 
   pair: debugging; syntax errors
   pair: debugging; compiler arguments

Syntax errors
-------------

Syntax errors are usually easy to fix once you figure out what they are.
Unfortunately, the error messages are often not helpful. 
The errors reported vary from compiler to compiler and can be long and cryptic.
This is especially true of errors involving templates.

Often syntax errors in one part of a program can cascade, generating
more downstream errors in other parts of the program.
This is common for simple errors such as typographical mistakes.
Therefore, it is a good idea to attack errors from the top of the 
error list first.
Commonly, fixing a few minor errors reported at the top of the error list
eliminates dozens of lines of reported errors.
Bottom line: don't let the size of an error output intimidate you,
the compiler is just trying to be thorough.

On the other hand, the messages from most syntax errors do tell you 
almost exactly where in the program the problem occurred. 
Actually, it tells you where the compiler noticed a problem, which is not
necessarily where the error is. Sometimes the error is prior to the location of
the error message, often on the preceding line.

If you are copying code from a book, start by comparing your code to the book's
code very carefully. Check every character. At the same time, remember that the
book might be wrong, so if you see something that looks like a syntax error, it
might be.

Here are some ways to avoid the most common syntax errors:

#. Make sure you are not using a keyword for a variable name.
#. Make sure you are compiling with the ``-std=c++11`` argument.
#. Check that indentation is consistent. You may indent with either spaces or
   tabs but it's best not to mix them. Each level should be nested the same
   amount. Neatness catches more errors than you might expect.
#. Make sure that any strings in the code have matching quotation marks.
#. If a function declares a return value, ensure your function returns a value.
#. An unclosed bracket -- (, {, or [ -- makes the compiler continue with the next
   line as part of the current statement. Generally, an error occurs almost
   immediately in the next line.
#. Check for the classic ``=`` instead of ``==`` inside a conditional.

A simple dropped semi-colon may generate 
slightly different results using different compilers.
For example, given the following:

.. code-block:: cpp
   :linenos:
   :lineno-start: 2

   int foo() {
     return 1;
   }

   int main() {
     foo()
   }

The ``gcc`` compiler, reports the error on line 8.
It notices an end brace reached ``}`` but a semi-colon was expected:

.. code-block:: none

   g++ -std=c++11 -Wall -Wextra -pedantic    foo.cpp   -o foo
   g++: warning: couldn’t understand kern.osversion ‘14.5.0
   foo.cpp: In function ‘int main()’:
   foo.cpp:8:1: error: expected ‘;’ before ‘}’ token
    }
    ^


The ``clang`` compiler knows where the semi-colon belongs and in this case, 
provides a slightly more specific error:

.. code-block:: none

   The ``clang`` compiler, reports the error on line 7.
   clang++ -std=c++11 -Wall -Wextra -pedantic    foo.cpp   -o foo
   foo.cpp:7:8: error: expected ';' after expression
     foo()
          ^
          ;
   1 error generated.

I can't get my program to compile no matter what I do.
......................................................

If the compiler says there is an error and you don't see it, that might be
because you and the compiler are not looking at the same code. Check your
programming environment to make sure that the program you are editing is the
one you are actually compiling. If you are not sure, try putting an obvious and
deliberate syntax error at the beginning of the program. Now compile it
again. If the compiler doesn't find the new error, there is probably something
wrong with the way your environment is set up.

If this happens, one approach is to start again with a new program like Hello,
World!, and make sure you can get a known program to run.  Then gradually add
the pieces of the new program to the working one.

.. index:: 
   pair: debugging; link errors

Link errors
-----------

If you encounter a link error, then the basic syntax of each compilation unit is correct.
The most common mistake new programmers make is to start changing code in
response to a link error.
This will only make matters worse, as the program syntax was OK to begin with.
The simplest kind of link error is when the linker can't find a ``main`` function
to start execution:
  
.. code-block:: none

   g++: warning: couldn’t understand kern.osversion ‘14.5.0
   Undefined symbols for architecture x86_64:
     "_main", referenced from:
         __start in crt1.o
   ld: symbol(s) not found for architecture x86_64
   collect2: error: ld returned 1 exit status

Although cryptic looking, there are several clues that we do not have a syntax problem:

#. The first line of output says "Undefined symbols ...".
   This is a clear indication that the linker could not find something it expected.
#. The next 4 lines expand on this to tell us that the linker program (``ld``)
   was unable to find the symbol ``_main``, which is the *mangled name* this particular compiler
   gives to the function ``main()``.
   Compilers are free to mangle function names as they see fit to generate an executable
   in which every function signature is unique.

Since link errors or other problems related to setting up your environment are not covered
in detail in this course, this is a perfectly fine time to ask your instructor for help.
Since the problem is either in your environment, your ``Makefile``, or both.

.. index:: 
   pair: debugging; runtime errors

Runtime errors
--------------

Once your program is syntactically correct, you can create an executable and
start running it. What could possibly go wrong?


My program does absolutely nothing.
...................................

This problem is most common when your file consists of functions and classes
but does not actually invoke anything to start execution. This may be
intentional if you only plan to import this module to supply classes and
functions.

If it is not intentional, make sure that your program has a ``main()`` function.

My program hangs.
.................

If a program stops and seems to be doing nothing, we say it is hanging. Often
that means that it is caught in an infinite loop or an infinite recursion.

#. If there is a particular loop that you suspect is the problem, add a
   ``cout`` or ``puts`` statement immediately before the loop that says entering the loop
   and another immediately after that says exiting the loop.
#. Run the program. If you get the first message and not the second, you've got
   an infinite loop. 
   Go to the Infinite Loop section below.
#. Most of the time, an infinite recursion will cause the program to run for a
   while and then produce a RuntimeError: StackOverflow error. 
   If that happens, go to the Infinite Recursion section below.
#. If you are not getting this error but you suspect there is a problem with a
   recursive method or function, you can still use the techniques in the
   Infinite Recursion section.
#. If neither of those steps works, start testing other loops and other
   recursive functions and methods.
#. If that doesn't work, then it is possible that you don't understand the flow
   of execution in your program. Go to the Flow of Execution section below.


One last possibility is that your program is simply waiting for input and
there is no visual indication that input is expected.
If you don't suspect an infinite loop, 
try typing something and pressing *Enter*.
If your program does **anything**, including crashing, 
then you don't have an infinite loop.
You have a logic error.
Go to the Semantic error section below.

.. index:: 
   pair: debugging; infinite loop

Infinite loops
..............

If you think you have an infinite loop and you think you know what loop is
causing the problem, add a ``print`` statement at the end of the loop that
prints the values of the variables in the condition and the value of the
condition.

For example:

.. code-block:: cpp
    
   while ( x > 0 && y < 0) {
     // do something to x
     // do something to y
   
     std::cout << "x: " << x << '\n';
     std::cout << "y: " << y << '\n';
     std::cout << "condition: " << (x > 0 && y < 0) << '\n';
   }

Now when you run the program, you will see three lines of output for each time
through the loop. The last time through the loop, the condition should be
``0``. If the loop keeps going, you will be able to see the values of ``x``
and ``y``, and you might figure out why they are not being updated correctly.

In a development environment like *CodeBlocks*, *Visual Studio*, or using
command line debuggers such as *gdb* one can also set a breakpoint
at the start of the loop, and single-step through the loop.  While you do
this, inspect the values of ``x`` and ``y`` by hovering your cursor over 
them. 

Of course, all programming and debugging require that you have a good mental 
model of what the algorithm ought to be doing: if you don't understand what 
ought to happen to ``x`` and ``y``, printing or inspecting its value is
of little use. Probably the best place to debug the code is away from 
your computer, working on your understanding of what should be happening. 

Infinite recursion
..................

Most of the time, an infinite recursion will cause the program to run for a
while and then produce a ``Stack overflow`` error.

If you suspect that a function or method is causing an infinite recursion,
start by checking to make sure that there is a base case.  In other words,
there should be some condition that will cause the function or method to return
without making a recursive invocation. If not, then you need to rethink the
algorithm and identify a base case.

If there is a base case but the program doesn't seem to be reaching it, add a
``print`` statement at the beginning of the function or method that prints the
parameters. Now when you run the program, you will see a few lines of output
every time the function or method is invoked, and you will see the parameters.
If the parameters are not moving toward the base case, you will get some ideas
about why not.

Once again, if you have an environment that supports easy single-stepping,
breakpoints, and inspection, learn to use them well. It is our opinion that
walking through code step-by-step builds the best and most accurate mental
model of how computation happens. Use it if you have it!

.. index:: 
   pair: debugging; semantic errors

Semantic errors
---------------

In some ways, semantic errors are the hardest to debug, because the
compiler and the runtime system provide no information about what is
wrong. 
If there is a semantic error in your program, 
it will run successfully in the sense that the computer will
not generate any error messages.  
However, your program will not do the right thing. 
It will do something else. 
Specifically, it will do what you told it to do.
Only you know what the program is supposed to do, and only you
know that it isn't doing it.

The problem is that the program you wrote is not the program you wanted to write. 
The meaning of the program (its semantics) is wrong.  
Identifying semantic errors can be tricky because it requires 
you to work backward by looking at the output of the program and 
trying to figure out what it is doing.

The first step is to make a connection between the program text and
the behavior you are seeing. You need a hypothesis about what the
program is actually doing. One of the things that makes that hard is
that computers run so fast.

You will often wish that you could slow the program down to human
speed, and with some debuggers you can. But the time it takes to
insert a few well-placed ``print`` statements is often short compared to
setting up the debugger, inserting and removing breakpoints, and
walking the program to where the error is occurring.

General debugging tips
----------------------

Before you can effectively use debugging tools, 
you need to know what your program is *supposed* to do.
The basic method of all debugging:

#. Know what your program is supposed to do. 
#. Detect when it doesn't.
#. Fix it.

A tempting mistake is to skip step 1, 
and just try randomly tweaking things until the program works. 
Better is to see what the program is doing internally,
so you can see exactly where and when it is going wrong. 
A second temptation is to attempt to intuit where things are going wrong 
by staring at the code or the program’s output. 
Avoid this temptation as well: 
let the computer tell you what it is really doing inside your program instead of guessing.


My program doesn't work
.......................

You should ask yourself these questions:

#. Is there something the program was supposed to do but which doesn't
   seem to be happening? Find the section of the code that performs that
   function and make sure it is executing when you think it should.
#. Is something happening that shouldn't? Find code in your program
   that performs that function and see if it is executing when it
   shouldn't.
#. Is a section of code producing an effect that is not what you
   expected? Make sure that you understand the code in question,
   especially if it involves invocations to functions or methods 
   in other compilation units. 
   `Read the documentation <https://www.cppreference.com/>`_
   for the functions you invoke.
   Try them out by writing simple test cases and checking the results.

In order to program, you need to have a mental model of how programs
work. If you write a program that doesn't do what you expect, very
often the problem is not in the program; it's in your mental model.

The best way to correct your mental model is to break the program into
its components (usually the functions) and test each
component independently. 
Ask yourself if each function is truly doing one thing in your program.
Small function that do one thing well makes solving semantic errors
much easier.
Once you find the discrepancy between your
model and reality, you can solve the problem.

Of course, you should be building and testing components as you
develop the program. If you encounter a problem, there should be only
a small amount of new code that is not known to be correct.


I've got a big hairy expression and it doesn't do what I expect
...............................................................

Having a "big hairy expression" is your first problem.
Ask your self if this is the simplest solution for the problem
you are trying to solve.

Writing complex expressions is fine as long as they are **clear**, 
but they can be hard to debug. 
Consider breaking a complex
expression into a series of assignments to temporary variables.

For example:

.. code-block:: cpp
    
    this.hands[i].add_card (this.hands[this.neighbor(i)].top())

This can be rewritten as:

.. code-block:: cpp

    auto neighbor = this.neighbor (i);
    auto picked = hands[neighbor].top();
    hands[i].add_card (picked);

The explicit version is easier to read because the variable names provide
additional documentation, and it is easier to debug because you can check the
types of the intermediate variables and display or inspect their values.

Another problem that can occur with big expressions is that the order of
evaluation may not be what you expect. For example, if you are translating the
expression ``x/2pi`` into code, you might write:

.. code-block:: cpp
    
    y = x / 2 * M_PI;

That is not correct because multiplication and division have the same
precedence and are evaluated from left to right. So this expression computes
``(x/2)pi``.

A good way to debug expressions is to add parentheses to make the order of
evaluation explicit:

.. sourcecode:: cpp
    
    y = x / (2 * M_PI);

Whenever you are not sure of the order of evaluation, use parentheses.  Not
only will the program be correct (in the sense of doing what you intended), it
will also be more readable for other people who haven't memorized the rules of
precedence.


I've got a function that doesn't return what I expect
.....................................................

If you have a ``return`` statement with a complex expression, you don't have a
chance to print the ``return`` value before returning. Again, you can use a
temporary variable. For example, instead of:

.. code-block:: cpp
    
    return this.hands[i].remove_matches();

you could write:

.. sourcecode:: cpp
    
    auto count = hands[i].remove_matches();
    return count;

Now you have the opportunity to display or inspect the value of ``count`` before
returning.

.. index:: assert

Assertions
..........

The include ``<assert.h>`` defines a very handy **assert** macro.
The assert macro tests if a condition is true and halts your program
with an error if it is false.

.. code-block:: cpp
   :linenos:

   #include <assert.h>

   int main() {
     assert (5 == 2+2);
   }

When compiled an run, the output is:

.. code-block:: none

   Assertion failed: (5 == 2+2), function main, file foo.cpp, line 4.

Line numbers and everything, 
even if you compile with the optimizer turned on. 
Much nicer than a mere segmentation fault, and if you run it under the debugger, 
the debugger will stop exactly on the line where the assert failed so you can poke around and see why.

.. index::
   pair: debugging; gdb

Debugging tools
---------------

There are many tools to help programmers find and fix errors.
The simplest thing you can do is add print statements or assertions
to your code.
This is the slowest way to debug your code as it requires a recompile
each time you want to look at something different.

It is better, generally to use a more sophisticated tool.
Every compiler and language provides some sort of debugging tool to assist developers
in writing software.

Nearly every :term:`IDE <integrated development environment>` comes with a graphical debugger.
Most of them are very good.
Linux provides a variety of debugging tools.
The program ``ddd`` is a graphical debugger for linux.
The program ``gdb`` is a text-based debugger for linux.


The GNU debugger (gdb)
......................

The standard debugger on GNU/Linux is called ``gdb``. This lets you run your program
under remote control, so that you can stop it and see what is going on inside.

Given the small, buggy program:

.. code-block:: cpp

   #include <iostream>

   int main() {
     int sum = 0;

     for (int i = 0; i -= 1000; ++i) {
       sum += i;
     }
     std::cout << "sum = " << sum << '\n';
   }


Note that we are going to add the flag -g3 to tell the compiler to include debugging information. 
Debug level 3 is the most detailed debug level.
Debug levels 2 and 3 allow gdb to translate machine addresses back into 
identifiers and line numbers in the original program for us.

Let’s compile and run it and see what happens:

.. code-block:: none

  $ g++ bogus.cpp -std=c++11 -Wall -Wextra -pedantic -g3 -o bogus
  $ ./bogus
  sum = -34394132
  $

That doesn't look like the sum of 1 to 1000. 
So what went wrong? 
If we were clever, we might notice that the test in the for loop is using the 
shortcut -= operator instead of the <= operator that we probably want. 
But let's suppose we're not so clever right now—it's four in the morning, 
we've been working on bogus.cpp for twenty-nine straight hours, 
and there's a -= up there because in our befuddled condition we know in our bones 
that it's the right operator to use. 
We need somebody else to tell us that we are deluding ourselves, 
but nobody is around this time of night. 
So we’ll have to see what we can get the computer to tell us.

The first thing to do is fire up ``gdb``, the debugger. 
This runs our program in stop-motion, 
letting us step through it a piece at a time and watch what it is actually doing. 
In the example below gdb is run from the command line:

.. code-block:: none

    $ gdb bogus
    GNU gdb (GDB; openSUSE 13.1) 7.6.50.20130731-cvs
    Copyright (C) 2013 Free Software Foundation, Inc.
    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
    This is free software: you are free to change and redistribute it.
    There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
    and "show warranty" for details.
    This GDB was configured as "i586-suse-linux".
    Type "show configuration" for configuration details.
    For bug reporting instructions, please see:
    <http://bugs.opensuse.org/>.
    Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.
    For help, type "help".
    Type "apropos word" to search for commands related to "word".
    ..
    Reading symbols from /var2/home/dparillo/bogus...done.
    (gdb) run
    Starting program: /var2/home/dparillo/bogus 
    sum = -34394132
    [Inferior 1 (process 32083) exited normally]


So far we haven't learned anything. 
To see our program in action, we need to slow it down a bit.
We'll stop it as soon as it enters main, 
and step through it one line at a time while having it print out the values of the variables.

.. code-block:: bash

    (gdb) break main
    Breakpoint 1 at 0x8048719: file bogus.cpp, line 4.
    (gdb) run
    Starting program: /var2/home/dparillo/bogus 

    Breakpoint 1, main () at bogus.cpp:4
    4	  int sum = 0;

    (gdb) display sum
    1: sum = -1209683968
    (gdb) next
    6	  for (int i = 0; i -= 1000; ++i) {
    1: sum = 0
    (gdb) next
    7	    sum += i;
    1: sum = 0
    (gdb) display i
    2: i = -1000
    (gdb) next
    6	  for (int i = 0; i -= 1000; ++i) {
    2: i = -1000
    1: sum = -1000
    (gdb) n                      # getting lazy and used 'n' instead of 'next'
    7	    sum += i;
    2: i = -1999
    1: sum = -1000
    (gdb) n
    6	  for (int i = 0; i -= 1000; ++i) {
    2: i = -1999
    1: sum = -2999
    (gdb) quit
    A debugging session is active.

      Inferior 1 [process 32187] will be killed.

    Quit anyway? (y or n) y


Here we are using 
**break main** to tell the program to stop as soon as it enters main, 
**display** to tell it to show us the value of the variables ``i`` and ``sum`` whenever it pauses, 
and **n** (or **next**) to execute the program one line at a time.

When stepping through a program, ``gdb`` displays the line it will execute next 
as well as any variables you've told it to display. 
This means that any changes you see in the variables are the result of the previous displayed line. 
Bearing this in mind, we see that ``i`` drops from 0 to -1000 the very first time 
we hit the top of the for loop and drops to -1999 the next time. 
So something bad is happening in the top of that for loop, 
and we might begin to suspect that ``i -= 1000`` is not doing what we intended.

.. index::
   pair: debugging; gdb commands

Useful gdb commands
~~~~~~~~~~~~~~~~~~~

help
  Get a description of gdb commands.

run
  Runs your program. 
  You can give it arguments that get passed in to your program just as if 
  you had typed them to the shell. 
  Also used to restart your program from the beginning if it is already running. 

quit
  Leave gdb, killing your program if necessary. 

break
  Set a breakpoint, which is a place where gdb will automatically stop your program. 
  Some examples: 
  
  - ``break function_name`` stops before executing the first line in ``function_name``. 
  - ``break 117`` stops before executing line number 117. 

list
  Show part of your source file with line numbers (handy for figuring out where to put breakpoints). 
  Examples: 
  
  - ``list function_name`` lists all lines of ``function_name``. 
  - ``list 117-123`` lists lines 117 through 123.

next
  Execute the next line of the program, including completing any function calls in that line.
  This command executes, but does not *step into* functions.

step
  Execute the next step of the program, 
  which is either the next line if it contains no function calls, 
  or the entry into the called function.


finish
  Continue until you get out of the current function (or hit a breakpoint). 
  Useful for getting out of something you stepped into that you didn't want to step into.

cont
  (Or continue). 
  Continue until 

  a) the end of the program, 
  b) a fatal error like a Segmentation Fault or Bus Error, or 
  c) a breakpoint. 

  If you give it a numeric argument (e.g., ``cont 1000``) it will skip 
  over that many breakpoints before stopping. 


print
  Print the current value of some expression once, e.g. ``print i``. 

display
  Like ``print``, but runs automatically every time the program stops. 
  Useful for watching values that change often. 


.. reveal:: reveal-skill-check-errors
   :showtitle: Show Skill Check
   :hidetitle: Hide Skill Check

   .. mchoice:: question1_5_1
      :answer_a: tracking down programming errors and correcting them.
      :answer_b: removing all the bugs from your house.
      :answer_c: finding all the bugs in the program.
      :answer_d: fixing the bugs in the program.
      :correct: a
      :feedback_a: Programming errors are called bugs and the process of finding and removing them from a program is called debugging.
      :feedback_b: Maybe, but that is not what we are talking about in this context.
      :feedback_c: This is partially correct.  But, debugging is more than just finding the bugs.  What do you need to do once you find them?
      :feedback_d: This is partially correct.  But, debugging is more than just fixing the bugs. What do you need to do before you can fix them?

      Debugging is:

   .. mchoice:: question1_8_1
      :answer_a: Attempting to divide by 0.
      :answer_b: Forgetting a semi-colon at the end of a statement where one is required.
      :answer_c: Forgetting to divide by 100 when printing a percentage amount.
      :correct: c
      :feedback_a: A semantic error is an error in logic. In this case the program does not produce the correct output because the problem is not solved correctly. This would be considered a run-time error.
      :feedback_b: A semantic error is an error in logic. In this case the program does not produce the correct output because the code can not be processed by the compiler or interpreter. This would be considered a syntax error.
      :feedback_c: This will produce the wrong answer because the programmer implemented the solution incorrectly.  This is a semantic error.

      Which of the following is a semantic error?

   .. mchoice:: question1_6_1
      :answer_a: Attempting to divide by 0.
      :answer_b: Forgetting a colon at the end of a statement where one is required.
      :answer_c: Forgetting to divide by 100 when printing a percentage amount.
      :correct: b
      :feedback_a: A syntax error is an error in the structure of the python code that can be detected before the program is executed.   The compiler cannot usually tell if you are trying to divide by 0 until it is executing your program (e.g., you might be asking the user for a value and then dividing by that value - you cannot know what value the user will enter before you run the program).
      :feedback_b: This is a problem with the formal structure of the program.  The compiler knows where colons are required and can detect when one is missing simply by looking at the code without running it.
      :feedback_c: This will produce the wrong answer, but wthe compiler ill not consider it an error at all.  The programmer is the one who understands that the answer produced is wrong.

      Which of the following is a syntax error?

   .. mchoice:: question1_7_1
      :answer_a: Attempting to divide by 0.
      :answer_b: Forgetting a colon at the end of a statement where one is required.
      :answer_c: Forgetting to divide by 100 when printing a percentage amount.
      :correct: a
      :feedback_a: The compiler cannot reliably tell if you are trying to divide by 0 until it is executing your program (e.g., you might be asking the user for a value and then dividing by that value - you cannot know what value the user will enter before you run the program).
      :feedback_b: This is a problem with the formal structure of the program.  The compiler knows where colons are required and can detect when one is missing simply by looking at the code without running it.
      :feedback_c: This will produce the wrong answer, but the compiler will not consider it an error at all.  The programmer is the one who understands that the answer produced is wrong.

      Which of the following is a run-time error?

   .. mchoice:: question1_6_2
      :answer_a: The programmer.
      :answer_b: The compiler / interpreter.
      :answer_c: The computer.
      :answer_d: The teacher / instructor.
      :correct: b
      :feedback_a: Programmers rarely find all the syntax errors, there is a computer program that will do it for us.
      :feedback_b: The compiler and / or interpreter is a computer program that determines if your program is written in a way that can be translated into machine language for execution.
      :feedback_c: Well, sort of.  But it is a special thing in the computer that does it.  The stand alone computer without this additional piece can not do it.
      :feedback_d: Your teacher and instructor may be able to find most of your syntax errors, but only because they have experience looking at code and possibly writing code.  With experience syntax errors are easier to find.  But we also have an automated way of finding these types of errors.

      Who or what typically finds syntax errors?



-----

.. admonition:: More to Explore

  - From: cppreference.com: 
    `assert <http://en.cppreference.com/w/cpp/error/assert>`_ and
    `static_assert <http://en.cppreference.com/w/cpp/language/static_assert>`_. 
  - `GDB tips <http://heather.cs.ucdavis.edu/~matloff/UnixAndC/CLanguage/Debug.html>`_
  - `GDB tutorial <https://www.cprogramming.com/gdb.html>`_
  - `DDD <http://www.gnu.org/software/ddd/>`_


