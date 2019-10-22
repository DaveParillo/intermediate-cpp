..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. qnum::
   :prefix: beginnings-
   :start: 1

.. index:: 
   pair: introductory topics; header files
   pair: introductory topics; comments

What you should already know
============================

This book is intended for students exploring a second semester in C++ programming.
So, it's not unreasonable that you already have a solid understanding of the
material presented in the vast majority of first semester C and C++ courses.

The remaining sections list the things students should already have mastered
before proceeding with the material in this text.
There are some practice problems available which you can use to check your knowledge.


Source files and header files
-----------------------------

One of the primary goals of this course is to begin creating programs more
complex than those written previously.
One of the core skills required when writing large programs is to split 
different parts of the program source into separate files.

You may have only had to do this a few times previously, but you should know
by now:

* What are the differences between source and header files?

  * Why do they exist?
  * What are :term:`header guards <header guard>`?
  * What is ``#pragma once``?

* What happens during compilation?  Linking?
* How to use function *main()*, *argc*, and *argv*
* :io:`cout` and the meaning of statements like:

.. code-block:: cpp

   #include <iostream>
   #include <stdio.h>

   int main() {
     std::cout << "Hello C++!" << std::endl;
     puts("Hello C!");
     printf("Hello Alice!\n");
     printf("Hello %s!\n", "Bob");
   }

.. index:: 
   triple: introductory topics; comments; best practices
   triple: introductory topics; comments; anti-patterns

Code comments
-------------

You should have learned different formats for code :cpp:`comments`

.. code-block:: cpp

   // a one line comment
   std::cout << "Hello C++!" << std::endl;  // this is a comment
   puts("Hello C!");
   /*
   a block comment
   printf("Hello Alice!\n");
   printf("Hello %s!\n", "Bob");
   */

What you may not have have learned is **when** to use comments.
This is partly a stylistic discussion, and some people have very strong feelings
about the use of comments in software.
These opinions range from "never use them, ever", to enormous comment blocks
at the top of every source file and before each function.

The primary focus of this course is on **clarity**.
The goal of any program in any language is to express ideas in code
as *clearly as possible*.
If you can do that without writing any comments, great.
If you need to explain some piece of code, add a comment.
Although, a better solution might be to rewrite the confusing code
so that it doesn't need clarification with a comment.

Comments should always and only state things that cannot be captured well
in regular code.  For example:

* What are the boundary conditions or limitations of the code.
* What preconditions must exist before using the code?
* What postconditions are guaranteed to exist?  Is there a "minimum guarantee"?


In this course, I also need everyone to assert that their work is their own.
For that reason, the top of every source file should contain your name and student ID:

.. code-block:: cpp

   // file.cpp
   // Dave Parillo, 123456789


Commenting "anti-patterns"
..........................

An :term:`anti-pattern` is a common response to a recurring problem 
that is ineffective.
Anti-patterns represent examples that you **should not** emulate!
As bad as they are, they can still be instructive.

.. reveal:: reveal-1
    :showtitle: Show Comment Anti-Patterns
    :hidetitle: Hide Comment Anti-Patterns

    In case you are wondering,
    these anti-patterns are all actual code examples I have received in the past.

    One of my pet peeves is writing comments that say **exactly** what the code
    already says.

    .. code-block:: cpp

        help(argv[0]);   //passing the 1st arg. to func. help.
        
        for (int i=0; i<10; ++i)       // loop from 0 to 9
        {
          printf("counter: %d\n", i);  // print counter
        }

    Perhaps this is not obvious, but what is wrong here:

    .. code-block:: cpp

        int main( int argc, char* argv[] )  //or alternately char**arg[]

    .. reveal:: reveal-1-1
       :showtitle: What is Wrong?
       :hidetitle: Hide
      
       The comment is actually telling a lie: the alternative will not compile!

    .. code-block:: cpp

        // from a file named "average.cpp"

        int number;          // number of values in the set
        double value;        // value entered at keyboard
        double average;      // average value
        double total;        // sum of all values
        char again = 'y';    // repeat running the program
        char validElement;   // consider sentinel value -1 is valid

        // what is wrong with this code block??
        if (total != 0)
          average = total / number;  // calculate the average value

        fflush(stdin); // empty input buffer
        cin.get();     // read in a character


    The following series of code blocks are a combination of several commonly provided anti-patterns
    that have been combined into a single example.

    This first code block is composed of comments that add no value.
    There is only 'noise'.
    Every comment merely says basically the same thing as the code, just not as well.

    Also, we know we are in trouble in this program as the variable names provide little
    hint about anything this program might actually do.

    .. code-block:: cpp

       // The FooCalculator class calculates a Foo.
       // @author Dave Parillo
       struct FooCalculator {
         // The Integer maxFoo defines the maximum foo
         int maxFoo = 100;
         // The Integer foo defines the current foo.
         int foo = 0;
         // The member thing is an array of strings.
         std::string thing[100];
       };

       FooCalculator f;

    In this second block, which ``isFooSmallEnough`` appears to describe
    what this function is doing, the comments again, add nothing.

    The comments for ``rammer`` and ``rammerstat`` add no value and are actually misleading,
    since neither function appears to actually compute anything.

    .. code-block:: cpp

       // The isFooSmallEnough method determines if the foo is small enough
       // @return boolean {@code true} if foo is smaller than max
       // @return boolean {@code false} if foo is larger than max
       bool isFooSmallEnough() {
         return f.foo < f.maxFoo;
       }

       // Compute a rammer
       void rammer(std::string stat) {
         if (isFooSmallEnough()) {
           f.thing[f.foo++] = stat;
         }
         std::cout << stat << '\n';
       }

       // Calculate the ramerstat function.
       // @param rammer  A String that stores the rammer value
       void rammerstat(std::string x) {
           std::ifstream ram(x);   
           std::string stat;
           while (getline(ram,stat)) {
             rammer(stat);
           }
           ram.close();
       }

    The only comment here tells us what we already know.
    It would be nice to know what is expected of ``args`` that are passed into our
    nasty little program, but perhaps the author thought that was obvious?

    ::

       // Main is a global function.
       int main(int argc, char** argv) {
         if (argc > 1) {
           for (int i = 1;i < argc; ++i) {
             rammerstat(argv[i]);
           }
         } else {
           puts ("Usage: foo-comments args");
         }
       }

    What *does* this program do if compiled and run?

The preceding advice may conflict with what you have been told in the past 
about commenting your code.
Don't worry too much about that for now.
Remember the focus is on **clarity**, not how many comments you write.
Eventually some future employer will require you to (hopefully) adhere to 
some coding standard and you should follow that guidance when you encounter it.

Fundamental types and type conversions
--------------------------------------

You should already be familiar with declaring fundamental :cpp:`types`
(``int``, ``char``, ``double``, ``uint16_t``, etc.).
You should also be familiar with the basic operations and operators
(``+``, ``-``, ``=``, ``==``, etc.).
Including the shortcut operators (``++``, ``+=``, etc)

You should know the difference between *declaring*, *initializing*, and
*assigning a value* to a variable.
It is (sometimes) valid to assign variables of one type to those of a different
type, for example, `double x = 12;` assigns the integer `12` to the `double x`.
This is a **widening conversion** and is always safe.
The opposite of a widening conversion is a **narrowing conversion**.
A narrowing conversion frequently involves the loss of information.
Most compilers will warn about narrowing conversions even in cases where
they are allowed.

You should know how to explicitly cast fundamental types from one
type to another.
Most people should be familiar with the ``static_cast`` form:

::
    
   auto almost_pi = static_cast<int>(3.14159);

Some people may have also learned the C-style cast:

::
    
   auto almost_pi = (int)3.14159;

Know that these two forms are equivalent.
We will be learning other ways to explicitly cast that are a bit more consistent
with C++11's more uniform initialization syntax.

Finally, you should know the basic keywords of the language,
at least those common to both C and C++, and legal identifier names
for functions and variables.



User-defined types
------------------

Although you may not have done any object oriented programming yourself,
you probably have used objects, even if you weren't aware of it.
The C++ standard provides many classes.
Two of the oldest classes handle stream formatted input and output:
:io:`cin` and :io:`cout`.

You should have already encountered code like:

.. code-block:: cpp

   std::string  name;
   std::cout << "Enter your name: ";
   std::cin  >> name;
   std::cout << "Hello," << name << "!\n";

Hopefully, you have been taught the basics of :cpp:`string` and :container:`vector`
as it is hard to imagine doing much (non-embedded) C++ programming without ever using either.
A bit like writing a paragraph in English without using the letter 'e'.
Try that sometime!

We will be working with ``std::string`` and ``std::vector``
often in this course, so if you haven't used them yet,
don't worry - you will.

File input and output
.....................

I expect you to know how to use some form of file input and output,
whether it is the C-style :cstdio:`printf` and :cstdio:`scanf`, or the
C++-style input and output file streams: :io:`ofstream` and :io:`ifstream <basic_ifstream>`.
Both are serviceable, have their own advantages and disadvantages.
This course emphasizes *contemporary* C++ and encourages the use of
C++ generally, but sometimes ``printf`` is a perfectly acceptable
alternative to ``cout``. 

Don't panic.

While file I/O is not a primary focus of this course, you will be expected to employ
basic I/O in labs and projects.

Statements and branching
------------------------

Writing basic statements and conditionally executing code,
or executing blocks of code repeatedly, are fundamental skills
common to all programming languages.

Everyone should be **extremely familiar** with writing
``if``, ``switch``, ``for``, and ``while`` blocks.

You should have used combinations of statements and branching 
to perform tasks perhaps as complex as:

* Computing an amortization table
* Computing population growth
* Parsing text


Fixing errors in code
---------------------

You should know the difference between basic types of errors:

* :term:`Compile-time errors <compile-time error>`
* Link-time (linker) errors 
* :term:`Runtime errors <runtime error>`
* :term:`Semantic errors <semantic error>`

I expect some basic experience using a debugger in whatever 
programming environment you may have used previously.

If not, refer to the section :doc:`../back-matter/app-a/debugging`.

.. note::

   If **any** of the material in the preceding sections sounds unfamiliar, then

   * Consider working through the `week 1 example source code <https://github.com/DaveParillo/cisc187/tree/master/examples/week01>`_

   * Review the material from your first semester text

Skill Check
-----------
The questions in this hidden section provide a chance to demonstrate
your understanding of the concepts discussed so far.

These are all concepts you should already know.

.. reveal:: cpp-review-skill-check

   .. fillintheblank:: begin_fitb1

      Given the following plain english statements:

      - Create a variable x with value 8
      - Create a variable y with value 5
      - Add x and y, storing the result in y

      If they were implemented as a program,
      then what value is ``y`` when finished? 

      - :13: Correct.
        :5: No, because the variable y is modified.
        :8: No. ``y`` is the sum of x and y, not simply ``x``.
        :x: Try again.

   .. parsonsprob:: begin_parson1
      :adaptive:
      :noindent:
      :language: c

      Place these statements in their proper order
      so that the program prompts for input, computes the area,
      and displays the results.
      -----
      double h = 0;
      double w = 0;
      =====
      std::cout << "Enter height:\t";
      =====
      std::cin >> h;
      =====
      std::cout << "Enter width:\t";
      =====
      std::cin >> w;
      =====
      double area = h*w;
      =====
      std::cout << area << '\n';


   .. activecode:: begin_ac1
      :language: cpp
      :compileargs: ['-Wall', '-std=c++11']

      Fix this program so that it compiles.

      ~~~~
      int main() {
        21 = value;
        double value;

        std::cout << value << '\n';
      }

   .. fillintheblank:: begin_fitb2

      Given the following program:

      .. code-block:: cpp
         :linenos:

         int main() {
           int a = 7;
           int b = 4;

           if (a<=b) { 
             a = 99;
           } else {    
             int t = a;
             a = b;
             b = t;
           }
           return a;                                     
         }

      What value is returned? 

      - :4: Correct.
        :7: No, because the variable a is always modified in this program.
        :99: No. Since a is greater than b, the code on line 6 is never executed.
        :.*: Sorry, no. What is happening in the else block?

   
   .. activecode:: begin_ac2
      :language: cpp
      :compileargs: ['-Wall', '-std=c++11']

      Write a program that accumulates the sum of the 
      numbers 1 - 10 and prints the result.

      ~~~~
      int main() {

      }
   
   .. parsonsprob:: begin_parson2
      :adaptive:
      :language: c

      When assembled in its proper order, the following program segment 
      prints 'Odd numbers:' followed by all the odd numbers from 1 - 100, one per line.
      -----
      int main () {
      =====
        std::cout << "Odd numbers:\n";
      =====
        for(int num=1; num<=100; ++num) {
      =====
          if(num * 2 == 0) {  #distractor
      =====
          if(num % 2 != 0) {
      =====
            std::cout << '\t' << num << '\n';
      =====
          }
      =====
        }
      }


   .. mchoice:: begin_mc_initializing_1
      :multiple_answers:
      :correct: b,d
      :answer_a: int a;
      :answer_b: a = b;
      :answer_c: size_t sz = 10;
      :answer_d: cin >> a;
      :answer_e: int if = a;
      :feedback_a: This is a declaration
      :feedback_b: Correct.
      :feedback_c: This is a declaration with initialization
      :feedback_d: This may not look like an assignment, but it is.
      :feedback_e: Does not compile. The word 'if' is a reserved word and can't be used.

      Which of the following statements represent **assignment to** a variable?  Check all that apply.


   .. activecode:: begin_type_check
      :language: cpp
      :compileargs: ['-Wall', '-std=c++11']
      :caption: Write a program that prints your name

      Write a program that stores your name in a local variable and then prints it.

      ~~~~
      #include <iostream>

      int main() {

      }

   .. mchoice:: begin_mc_initializing_2
      :multiple_answers:
      :correct: a,b,e
      :answer_a: int inner_product_of_a_and_b;
      :answer_b: double* p2;
      :answer_c: char 1st_letter;
      :answer_d: long large num;
      :answer_e: long double _d;
      :feedback_a: A ridiculously long, but valid name.
      :feedback_b: Correct.
      :feedback_c: A variable may not start with a number
      :feedback_d: A variable can't contain spaces or most special characters
      :feedback_e: Correct. 'long double' is a single type. 

      Which of the following are legal variable names? Check all that apply.

   .. mchoice:: mc_shorcut_op_1
      :answer_a: x = -1, y = 1, z = 4
      :answer_b: x = -1, y = 2, z = 3
      :answer_c: x = -1, y = 2, z = 2
      :answer_d: x = -1, y = 2, z = 2
      :answer_e: x = -1, y = 2, z = 4
      :correct: e
      :feedback_a: This code subtracts one from x, adds one to y, and then sets z to to the value in z plus the current value of y.
      :feedback_b: This code subtracts one from x, adds one to y, and then sets z to to the value in z plus the current value of y.
      :feedback_c: This code subtracts one from x, adds one to y, and then sets z to to the value in z plus the current value of y.
      :feedback_d: This code subtracts one from x, adds one to y, and then sets z to to the value in z plus the current value of y.
      :feedback_e: This code subtracts one from x, adds one to y, and then sets z to to the value in z plus the current value of y.

      What are the values of x, y, and z after the following code executes?
   
      .. code-block:: cpp 

         int x = 0;
         int y = 1;
         int z = 2;
         --x;
         ++y;
         z+=y;

   .. mchoice:: begin_mc_mod_1
      :answer_a: 15
      :answer_b: 16
      :answer_c: 8
      :correct: c
      :feedback_a: This would be the result of 158 divided by 10.  Modulus gives you the remainder.
      :feedback_b: Modulus gives you the remainder after the division.
      :feedback_c: When you divide 158 by 10 you get a remainder of 8.  

      What is the result of 158 % 10?
   
   .. mchoice:: begin_mc_mod_2
      :answer_a: 3
      :answer_b: 2
      :answer_c: 8
      :correct: a
      :feedback_a: 8 goes into 3 no times so the remainder is 3.  The remainder of a smaller number divided by a larger number is always the smaller number!
      :feedback_b: This would be the remainder if the question was 8 % 3 but here we are asking for the reminder after we divide 3 by 8.
      :feedback_c: What is the remainder after you divide 3 by 8?  

      What is the result of 3 % 8?

   .. mchoice:: begin_mc_op_2
      :answer_a: x = 6, y = 2.5, z = 2
      :answer_b: x = 4, y = 2.5, z = 2
      :answer_c: x = 4, y = 2, z = 3
      :answer_d: x = 4, y = 2.5, z = 3
      :answer_e: x = 6, y = 2, z = 3
      :correct: e
      :feedback_a: This code sets x to z * 2 (6), y to y divided by 2 (5 / 2 = 2) and z = to z + 1 (2 + 1 = 3).
      :feedback_b: This code sets x to z * 2 (6), y must be an int, z is incremented
      :feedback_c: This code sets x to z * 2 (6),
      :feedback_d: This code sets x to z * 2 (6), y must be an int
      :feedback_e: Correct

      What are the values of x, y, and z after the following code executes?
   
      .. code-block:: java 

         int x = 3;
         int y = 5;
         int z = 2;
         x = z * 2;
         y /= 2;
         ++z;

   .. fillintheblank:: begin_fitb3

      Given the following statement:

      .. code-block:: cpp

         double x = 2 + 2^3

      What is value stored in ``x``? 

      - :7: Correct.
        :10: No. ``^`` is not the exponent operator.
             There is no such operator in C++.
             It is the *exclusive or* operator.
        :64: No. ``^`` is not the exponent operator.
             There is no such operator in C++.
             It is the *exclusive or* operator.
        :3: No. The spaces here are misleading.
            Addition has higher precedence than exclusive or.
        :x: Try again.

   

-----

.. admonition:: More to Explore

   - Jeff Atwood's blog: `Code smells <https://blog.codinghorror.com/code-smells/>`_
   - From cppreference.com: :lang:`statements` and :cref:`loops`


