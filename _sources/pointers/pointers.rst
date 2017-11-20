..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: pointers

Pointers
========

People make a big deal out of pointers.
They really aren't that hard to understand.
We already know that a variable stores some value:

.. code-block:: cpp
   
   double euler = 2.718281828459;

We use the name ``euler`` to retrieve the value.

A pointer is simply a variable that stores an *address*:

.. code-block:: cpp
   
   double* e_pointer = &euler;

The value assigned to ``e_pointer`` is the *address of* the variable ``euler``.


Declaring pointers
------------------

While some of the memory in a running program is stored in
a small number of **registers**, 
these live on the CPU chip and perform specialized functions like keeping track of the 
location of the next machine code instruction to execute.
Most of the memory of interest to programmers is **main memory**, 
which (mostly) lives outside the CPU chip and which stores the code and data of a running program. 
Main memory is partitioned within a program into the following areas, 
which we have seen in the section :doc:`../function-intro/functions`.

.. graphviz::

   digraph memory {
     fontname = "Bitstream Vera Sans"
     label="Typical program memory layout"
     node [
        fontname = "Bitstream Vera Sans"
        fontsize = 11
        shape = "record"
        style=filled
        fillcolor=lightblue
     ]
     mem [
        label = "{stack\n (grows down)|\n\n\nunused memory\n\n|\nfree store\n(grows up)|\nstatic data\n|\ncode\n(text area)}"
     ]

   }

Each part of a program: functions, variables, and objects are stored in main memory and
each is assigned a unique address.
When the CPU wants to fetch a value from a particular location in main memory, 
it must supply the address.
Frequently, we don't need to concern ourselves with the address of a value.
Instead, we use a variable or function name and the 
CPU resolves the address for us.
Sometimes we need more control, and then we use **pointers** to store memory addresses
and manipulate them like any other variable.
In C++, 
they are defined as a family of types that can be passed as arguments, 
stored in variables, returned from functions, etc.

A pointer is defined by the operator ``*`` *and* a **type**.
Both are required because a pointer can be thought of as a compound type.
The ``*`` declares that the system should store an initial memory address, not a value.
The type instructs the system how many bytes after the initial location
need to be allocated for storage of the value pointed to.
``int* int_pointer;`` defines a new, uninitialized pointer to an ``int``.

Both 
``int * int_pointer;`` and ``int *int_pointer;`` 
declare the exact same variable.
White space does not matter and the last variation is common.
Personally, I prefer ``int* p``, 
because it emphasizes (for me) that the *type*
is *integer pointer*.
Declarations of pointers to other fundamental types follow a similar pattern:

``double* dbl_pointer;`` is an uninitialized pointer to a ``double``.
 
``char* char_ptr;`` is an uninitialized pointer to a ``char``.

Each of these declarations creates a variable of either 4 or 8 bytes, depending on the architecture.
On any given CPU all pointers are the same size, regardless of what they point to - 
because the **only** thing a pointer ever stores is an address.
The pointer variable stores a specific memory location (the address) and the *value*
associated with the pointer is stored in one or more bytes starting at the pointer
address.

Like any other variable in C++, 
an uninitialized pointer will initially contain garbage --- in this case, 
the address of a location that might or might not contain something important. 
To initialize a pointer, 
you assign it the address of something that already exists.
If you already have an object, you can use the **address of operator** ``&``:

.. code-block:: cpp

   int main() {
     int n = 5; // a stack int
     int* p;    // a pointer to an int
     p = &n;    // p now points to n
   }

As you might expect, you do not need to declare pointers uninitialized.
You can declare and initialize in a single step.
Once you have an initialized pointer, use the **dereference operator** ``*``
to get the value stored in the pointer, or to assign a new value.


.. code-block:: cpp

   int main() {
      int x  = 10;
      int* p = &x;    // assign the address of x to p
      *p     = 7;     // x is now 7, p is unchanged

      int x2  = *p;   // assign the value of x to new int x2
      int* p2 = &x2;  // get a pointer to another int

      p2 = p;         // p2 and p both point to x
      p  = &x2;       // make p point to another object
   }


The equivalent example for references is:

.. code-block:: cpp

   int main() {
      int y  = 10;
      int& r = y;    // the & is in the type, not in the initializer
      r      = 7;    // assign to y through reference r

      int  y2 = r;   // read y through r (no * needed)
      int& r2 = y2;  // get a reference to another int

      r2  = r;       // the value of y is assigned to y2 
      //r = &y2;     // error: you can't change the value of a reference
                     //   (no assignment from int* to an int&)
   }

Using pointers
--------------

The simplest way to use a pointer is to get their value as with any other variable. 
This value will be an address, 
which can be stored in another pointer variable of the same type.

.. code-block:: cpp

   int n = 2;
   int* p = &n;  // points to n
   int* q = p;   // points to n also


Once a pointer has been dereferenced, it is treated exactly like any other variable of that type.

.. code-block:: cpp

   int n = 2;
   int* p = &n;
   *p = *p + *p; // n = 4

The ``*`` operator binds very tightly, that is it has high precedence.
You can usually use ``*p`` anywhere you could use the variable it points to 
without worrying about parentheses. 
However, a few operators, 
such as the unary decrement and increment (``--`` and ``++``) operators, 
and the member of (``.``) operator used to unpack structs and classes, bind tighter. 
These require parentheses if you want the ``*`` to take precedence.

.. code-block:: cpp

   int n = 2;
   int* p = &n;
   (*p)++; // increments n, n = 3
   *p++;   // increments p 
           // p now points to next address in memory
           // Almost always an error

`See what p points to when the last line is reached. <http://pythontutor.com/cpp.html#code=%23include%20%3Ciostream%3E%0Aint%20main%28%29%20%7B%0A%20%20int%20n%20%3D%202%3B%0A%20%20int*%20p%20%3D%20%26n%3B%20%20//%20points%20to%20n%0A%20%20int*%20q%20%3D%20p%3B%20%20%20//%20points%20to%20n%20also%0A%20%20*p%20%3D%20*p%20%2B%20*p%3B%20//%20n%20%3D%204%0A%20%20std%3A%3Acout%20%3C%3C%20%22n%20%3D%20%22%20%3C%3C%20n%20%3C%3C%20'%5Cn'%3B%0A%20%20%0A%20%20int*%20p2n%20%3D%20%26n%3B%20%20//%20another%20pointer%20to%20n%0A%20%20%28*p%29%2B%2B%3B%20//%20increments%20n%0A%20%20*p%2B%2B%3B%20%20%20//%20increments%20p%0A%0A%20%20return%200%3B%0A%7D&curInstr=0&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D>`_

A pointer can point to any memory address within the scope of the program,
which includes pointers themselves.
Each new pointer justs ands another to the chain of pointers.
The language does not impose a strict limit.
The only limit is your sanity...

.. code-block:: cpp

   int x = 8;

   // all of these variables point to x
   int* p2x     = &x;
   int** p2p    = &p2x;
   int*** p2pp  = &p2p;

`See it for yourself. <http://pythontutor.com/cpp.html#code=%23include%20%3Ciostream%3E%0Aint%20main%28%29%20%7B%0A%20%20int%20x%20%3D%208%3B%0A%0A%20%20//%20all%20of%20these%20variables%20point%20to%20x%0A%20%20int*%20p2x%20%20%20%20%20%3D%20%26x%3B%0A%20%20int**%20p2p%20%20%20%20%3D%20%26p2x%3B%0A%20%20int***%20p2pp%20%20%3D%20%26p2p%3B%0A%0A%20%20return%200%3B%0A%7D&curInstr=3&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D>`_

.. index:: 
   pair: pointers; references

Comparison with references
--------------------------

Recall from our earlier discussions of pass by reference
that the ``address of`` operator ``&`` allows us to pass by reference:

.. code-block:: cpp
   :linenos:

   #include <iostream>

   void by_value(int x) {
     x = 99;
     std::cout << "in by_value the address of x is " 
               << &x << '\n';
   }

   void by_reference (int& x) {
     std::cout << "in by_ref the address of x is   " 
               << &x << '\n';
     x = -1;
   } 

In function ``by_value`` the statement ``x = 99;`` changes the copy provided.
The value of ``x`` is printed, but is destroyed when ``x`` goes out of scope on line 6.

And no special character is needed of you want to use a function that takes a reference:

.. code-block:: cpp

   #include <iostream>

   int main () {
     int beta = 11;
     std::cout << "the address of beta is " 
               << &beta << '\n';
 
     by_value(beta);

     std::cout << "beta = " << beta << '\n';

     by_reference(beta);

     std::cout << "beta is now " 
               << beta << '\n';
   }

Using references does create some definite advantages:

- A reference must always be initialized using an existing object.
  In other words, a reference can **never** be ``null``.
- A reference can't be reassigned to a different object
- A ``const`` reference means you can't modify the thing the reference refers to
- References are simpler, more limited, and inherently safer than pointers

However, there are important things you can't do with references:

- You can't assign an address to a reference

  - This would have the effect of having a reference refer to a different object
  - The technical term for this is that references are not **assignable**

- You can't operate on a reference

  - In other words, you can't increment the referred to memory address,
    which, by definition, would involve having the reference refer to a different object

- You can't use a single reference to refer to more than one object
- You can't use references in containers such as ``vector``

  - Containers can only hold *assignable* entities

We still need to be able to do all these kinds of memory manipulations.
In C++, we achieve these goals using *pointers*.

Function passing semantics
..........................

We can pass pointers to a function that expects a reference: 

.. code-block:: cpp

   #include <iostream>

   void by_reference (int& x) {
     std::cout << "in by_ref the address of x is   " 
               << &x << '\n';
     x = -1;
   }

   int main() {
     int* p = new int{5};
     by_reference(*p);
     delete p;
   }


If we pass in only ``p``, what happens?

.. reveal:: reveal-skill-check
   :showtitle: Show Answer

   The program fails to compile.

   We can't pass an ``int*`` to a function expecting an ``int&``.


.. admonition:: Non-const references vs. pointers

   Some programmers consider passing by non-const reference bad style,
   because the call syntax is the same as pass by value.
   When a variable is passed into a function by non-const reference
   there is no visual indication to the programmer on what to expect.
   Without reading additional documentation or
   actually reading the source code, if available,
   there is no way to know if the function will change its parameter or not.

   .. code-block:: cpp

      void func (int& x);

      int main() {
        int x = 5;
        func(x);       // will x change?
      }


   For this reason, a function that takes a *non-owning pointer* is preferred:

   .. code-block:: cpp

      void func (int* x);
    
      int main() {
        int x = 5;
        func(&x);       // Caller expects x to change
      }

   A function signature is a *contract* between the function author and
   the function caller.
   A function that takes non-const references represents a poorly written contract.
   Callers don't know what to expect when the function is called.
   Even if the parameter isn't changed today, it might tomorrow.
   A non-owning pointer makes the intent clear.
   There is still no *requirement* to change the parameter,
   but since the caller is explicitly passing in an address, 
   they can expect it to change.



.. index:: 
   pair: pointers; arrays

Pointers and arrays
-------------------

Pointers are not arrays and arrays are not pointers.
However, much confusion arises between them because
*arrays in expressions* often behave like pointers.
The term you'll often see is that *arrays decay into pointers*.

Any array type will implicitly convert to a pointer of the type stored in the array.
The pointer is constructed to point to the first element of the array.
This conversion happens whenever arrays are used in an expression where
arrays are not expected, but pointers are:

.. code-block:: cpp

   #include <iostream>
     
   int main() {
     int a[3] = {13, 21, 35};
     int* p = a;
 
     std::cout << sizeof a << '\n'  // prints size of array
               << sizeof p << '\n'; // prints size of a pointer

    for(int n: a) {          // okay: arrays can be used in range-for loops
      std::cout << n << ' '; // prints elements of the array
    }
    // for(int n: p) {       // error: no range for looping on a pointer


    // arrays and pointers share the same semantics
    std::cout << '\n'
              << *a << '\n' // prints the first element
              << *p << '\n' // same
              << *(a + 1) << ' ' << a[1] << '\n'  // prints the second element twice
              << *(p + 1) << ' ' << p[1] << '\n'; // same
   }

This behavior applies to function calling as well:

.. code-block:: cpp

   #include <iostream>
     
   // print first element of array using pointer dereference
   void g(int (&a)[3]) {
     std::cout << *a << '\n'; 
   }
     
   // print first element of array using array semantics through pointer
   void f(int* p) {
     std::cout << p[0] << '\n';
   }

   int main() {
     int a[3] = {13, 21, 35};
     int* p = a;
 
    // where arrays are acceptable, but pointers aren't, only arrays may be used
    g(a); // okay: function takes an array by reference
    // g(p); // error: pointers do not implicitly convert to arrays

    // where pointers are acceptable, but arrays aren't, both may be used:
    f(a); // okay: function takes a pointer
    f(p); // okay: function takes a pointer
   }

**Array indexing pitfalls**

From the standard:

  The definition of the subscript ``operator[]`` is that ``E1[E2]`` is identical to ``(*((E1)+(E2)))``. 
  Because of the conversion rules that apply to the binary ``operator+``, 
  if ``E1`` is an array object (equivalently, a pointer to the initial element of an array object) 
  and ``E2`` is an integer, ``E1[E2]`` designates the ``E2``\-th element of ``E1`` (counting from zero).

.. note::

   What the standard doesn't repeat here is that addition commutes, that is 
   :math:`a+b = b+a`.
   A side-effect of this fact is that for any array and index pair ``a[i]``,
   then  ``a[i]`` must be equivalent to ``i[a]``.

   .. activecode:: ac-array-index-1
      :language: cpp

      #include <iostream>
      using std::cout;

      int main() {
        int a[4] = {3, 5, 8, 13};
        cout << "Print each array element 4 times:\n";
        for (int i=0; i<4; ++i) {
          cout << a[i]   << ' ' 
               << *(a+i) << ' ' 
               << *(i+a) << ' ' 
               << i[a]   << '\n';
        }
      }

   Although the standard does not strictly *prohibit* this syntax,
   doesn't mean you should.

.. index:: character arrays

Arrays of type ``char``
.......................

In the C language, 
the abstract idea of a string is implemented with an array of characters. 

For example,

.. code-block:: c

   char[] howdy = "Hello, world!";

In memory, this is automatically transformed into 

.. graphviz::

   digraph char_array {
     rankdir=LR
     fontname = "Bitstream Vera Sans"
     label="Character array in memory"
     node [
        fontname = "Bitstream Vera Sans"
        fontsize = 11
        shape = "record"
        style=filled
        fillcolor=lightblue
     ]
     arr [
        label = "{H|e|l|l|o|,| |w|o|r|l|d|!|\\0}"
     ]

   }

The last character in the array, ``\0`` is the *null character*,
and is used to indicate the end of the string.

.. note::

    Remember that the array must be large enough to hold 
    all of the characters AND the char '\0'.
    Forgetting to account for null, 
    or having a 'off by one error' is one of the most 
    common mistakes when working with C strings.

Whenever a char array is encountered it is normally referred to as
a *C string*.
The C++ standard uses this terminology and the standard library
contains functions to convert a ``std::string`` into a C string:

.. code-block:: cpp

   std::string hello = "Hello, world!";
   char[] howdy = hello.c_str();


A C string may allocate more memory that the characters currently stored in it.
An array declaration like this:

.. code-block:: c

   char hi[10] = "Hello";

results in an in-memory representation like this:

.. graphviz::

   digraph c {
     rankdir=LR
     fontname = "Bitstream Vera Sans"
     label="Character array with reserve memory"
     node [
        fontname = "Bitstream Vera Sans"
        fontsize = 11
        shape = "record"
        style=filled
        fillcolor=lightblue
     ]
     arr [
        label = "{H|e|l|l|o|\\0| | | | }"
     ]

   }

The array elements after the null are unused, but could be.
So, an array of size 10 has space for 4 more characters, 9 total.

A key limitation of C strings is that because thay are arrays,
you must declare in advance how many characters the string will hold.
The compiler will always statically determine the size, 
even if an explicit size is not provided.

.. code-block:: c

   char[] hi     = "Hello";  // size 6
   char   hi[10] = "Hello";  // size 10


One last word about the null terminator.

In older C and C++ code using C strings,
it's common to see code that uses the null terminator in 
the string as a loop exit condition:

.. activecode:: ac-c-copy-idiom
   :language: c

   #include <stdio.h>

   // an old C idiom to copy a 'string'
   int main (int argc, char** argv) {
     char a[] = "Hello World!";
     char b[13];

     // painfully print each char, 1 at a time.
     int i;
     for (i=0; i<12;++i) putchar(a[i]);
     printf("\n");


     char* p1 = a; 
     char* p2 = b;
     while ((*p2++ = *p1++)); // copy *p1 to *p2

     printf("copy:\n");
     printf("%s\n", p2);  // print chars until '\0' detected
     return 0;
   }

.. 
   **

Code like this can fail if the source string contains any embedded null characters.
The risk is that this code works fine 99% of the time, but fails
when working with character data from an uncontrolled source 
(a network or socket interface, for example).

.. admonition:: Try This!

   Run the previous example, but modify it,
   replacing the 'Hello World' with 'Hello\\0World'.
   What happens?

   What warnings does the compiler display?



Pointers to pointers
--------------------
We have already said that pointers can point to any address
in the program memory.
So it should be no surprise that pointers can point to pointers.
Like ``int`` or ``char``, a pointer type is still a type.
When you declare a variable of type pointer, 
storage still must be allocated somewhere,
and this storage must have an address too.

When dealing with pointers, we have to manage the added complexity
of keeping clear in our minds the difference between
*the pointer variable* and *what the pointer points to*.
When dealing with pointers to pointers, we have to manage
the pointer, what it points to, and *what the pointer that it points to points to*.

.. code-block:: cpp

   #include <iostream>
   #include <string>

   using std::string;
   using std::cout;

    int main() {
      string message[] = {"Alice","Bob here!","Carol checking in."};

      string *sp;   // a pointer to at least 1 string

      sp = message;
      cout << "sp:\n";
      cout << sp << '\n';
      cout << *sp << '\n';
      cout << *(sp + 1) << '\n';
      cout << *(sp + 2) << "\n\n";


      cout << "sp2:\n";
      string *sp2 = new string [3];          //create string pointer on the heap
      *sp2 = "\nAlice has left the building";
      *(sp2 + 1) = "Bob who?";
      *(sp2 + 2) = "Carol checked out.";

      cout << sp2 << '\n';
      cout << *sp2 << '\n';
      cout << *(sp2 + 1) << '\n';
      cout << *(sp2 + 2) << '\n' << '\n';

      string **sp3;                 // a pointer to a string pointer

      cout << "sp3:\n";
      sp3 = &sp2;
      cout << sp3 << '\n';
      cout << **sp3 << '\n';
    }

Now we have enough tools in our tool kit to understand command line arguments.

.. code-block:: cpp

    int main (int argc, char* argv[]) {
      return 0;
    }

or equivalently:

.. code-block:: cpp

    int main (int argc, char** argv) {
      return 0;
    }

The name of the variable ``argc`` stands for 'argument count'. 
``argc`` contains the number of arguments passed to the program. 
The name of the variable ``argv`` stands for "argument vector``". 
A vector is a one-dimensional array, and ``argv`` is a one-dimensional array of strings. 
Each string is one of the arguments that was passed to the program.
These names are used by convention, although technically,
any valid identifiers can be used.

Dereferencing ``argv`` returns the thing ``argv`` points to:
the first string in ``argv``.
By convention, essentially all compilers place the name of the 
program executed in ``argv[0]``.

We know that C strings are arrays of ``char``,
so ``argv`` is a pointer to a ``char`` array.
Or we can say ``argv`` is a pointer to a pointer to a ``char``.

When we compile a program like this:

   /usr/bin/gcc -o myprog myprog.cpp

The following is passed to gcc:

.. graphviz::

   digraph argv {
     rankdir=LR
     fontname = "Bitstream Vera Sans"
     label="The two dimensional argv array"
     node [
        fontname = "Bitstream Vera Sans"
        fontsize = 11
        shape = "record"
        style=filled
        fillcolor=lightblue
     ]
     argc [shape="plain", label="argc == 4"];
     argv [shape="plain", label="argv"];
     argv0 [shape="plain", label="argv[0]"];
     arr0 [
        label = "{/|u|s|r|/|b|i|n|/|g|c|c|\\0}"
     ]
     argv -- argv0 ->  arr0;
     argv1 [shape="plain", label="argv[1]"];
     arr1 [
        label = "{-|o|\\0}"
     ]
     argv2 [shape="plain", label="argv[2]"];
     arr2 [
        label = "{m|y|p|r|o|g|\\0}"
     ]
     argv3 [shape="plain", label="argv[3]"];
     arr3 [
        label = "{m|y|p|r|o|g|.|c|\\0}"
     ]

   }

We can access any character in ``argv`` using pointer arithmetic,
array index operators, or a combination.

.. code-block:: c

    #include <stdio.h>

    // Print arguments using c functions
    int main (int argc, char *argv[]) {
      printf ("The program '%s' was called with: \n", argv[0]);

      if (argc > 1) {
        for (int count = 1; count < argc; count++) {
          printf("argv[%d] = %s\n", count, argv[count]);
        }
      } else {
        puts("\tno other arguments.");
      }
      return 0;
    }

How this is typically used is to provide an ability
to change the behavior of programs using command line 'switches'
specified by the user when the program is run.
The following example takes 3 arguments:

-h
   Display help

-n
   Attempt to interpret the next word as a number and print it

anything else
   Interpret the next word as a string and print it

There is nothing special about the character ``-``.
It is a convention used to distinguish command line arguments
with special meaning (the switches) with other content.

.. code-block:: cpp

    #include <cstring>
    #include <iostream>
    #include <string>

    // Display a usage statement for this program.
    // name is the program name
    static void usage(const char* name) {
      std::cerr << "Usage: " << name << " [-h] [-n number] [any_word]\n";
    }

    int main(int argc, char** argv) {
      int number = 1;
      std::string word = "Hello";

      // Start at 1 to skip over program name
      for (int i=1; i < argc; ++i) {
        if (!std::strncmp(argv[i], "-h", 2)) {
          // print help if the current string is '-h'
          usage(*argv);
        } else if (!std::strncmp(argv[i], "-n", 2)) {
          // attempt to parse the string after '-n' as an int
          ++i;
          if (i < argc) {
            number = std::atoi(argv[i]);
            std::cout << "The number is: " << number << '\n';
          } else {
            std::cerr << "Error using '-n' argument: no number specified\n";
            usage(argv[0]);
          }

        } else {
            // print any other string provided
            word = argv[i];
            std::cout << "The word is: " << word << '\n';
        }
      }
      std::cout << "The last number is: " << number << '\n'
                << "The last word is: " << word << '\n';
      return 0;
    }

Keep in mind that everything received on the command line is
character data.
It is the responsibility of the programmer to transform the characters
in the array ``argv`` into whatever type is appropriate for the program.


.. index:: const pointers
   pair: pointers; const

Constant pointers
-----------------

Pointers can be declared ``const``, just like any other type.
Where ``const`` appears controls what is held constant:

.. code-block:: cpp
  
    // odd whitespace to help see where const is used
          int x;
          int*       p1 = &x;  // non-const pointer to non-const int
    const int*       p2 = &x;  // non-const pointer to const int
          int* const p3 = &x;  // const pointer to non-const int
    const int* const p4 = &x;  // const pointer to const int

- In ``p1``, nothing is constant.  Either the pointer or the value pointed to can change.
- In ``p2``, The pointer can change,  but the value pointed to is constant.
- In ``p3``, The pointer is constant,  but the value pointed to can change.
- In ``p4``, both are held constant.


-----

.. admonition:: More to Explore

   * Array declarations in `C <http://en.cppreference.com/w/c/language/array>`_ and `C++ <http://en.cppreference.com/w/cpp/language/array>`_

