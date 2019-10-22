..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: error-handling

Error handling
==============

Error handling involves:

- Detecting an error
- Transmitting information about an error to some handler code
- Preserving the valid state of a program
- Avoiding resource leaks

Returning values
----------------

TBD.


.. index:: exceptions

Exceptions
----------

An alternative to returning values from functions is to use **exceptions**.

A C++ exception is a response to an exceptional circumstance that occurs while a program is running, 
such as an attempt to open a file that does not exist.

Exceptions provide a way to transfer control from one part of a program 
(where the error occurs) to another (where the error is 'handled'). 
C++ exception handling is built upon three keywords: ``try``, ``catch``, and ``throw``.

throw 
    A program **throws** an exception when a problem shows up.

catch
    A program **catches** an exception with an exception handler at the place 
    in a program where you want to handle the problem.

try
    A ``try`` block identifies a block of code for which particular exceptions will be activated. 
    It's followed by one or more ``catch`` blocks.

Basic anatomy of an exception

#. Surround potentially error throwing code in a ``try`` block 
#. After the ``try`` block, include 1 or more ``catch`` blocks

   a. The parameter in the catch identifies the type of exception the catch block will handle

 .. code-block:: cpp

   try {
     // execute potentially dangerous statements
   } 

   // catch a specific class of exceptions
   catch (const std::exception& e) {  
     std::cout << "Exception occurred.\n";
     std::cout << "Details: " << e.what() << std::endl;
   }


If you specify a ``try``, you must include at least 1 ``catch``.

Passing catch parameters by *const reference* is considered a best practice

- std::exception.what()

  - Returns a description of what caused the error

- More than one ``catch`` block is acceptable

- The special catch

  .. code-block:: cpp

     catch (...)

will catch any exception.
If you use this, then you should be prepared to really handle *anything*.


.. index:: 
   pair: exceptions; standard exceptions

Standard exceptions
...................

The standard exceptions in C++ are organized in a class hierarchy.

- :cref:`std::exception` is the base class for all exceptions
- Classes derived from :cref:`std::exception` 

  - :cref:`std::bad_alloc`: thrown by ``new`` and other memory allocation errors 
  - :cref:`std::bad_cast`: thrown by ``dynamic_cast`` and similar
  - :cref:`std::bad_typeid`: thrown by ``typeid``  
  - :cref:`std::bad_exception`: runtime unexpected or pointer exceptions
  - :cref:`std::logic_error`: exceptions that *should* be detected by reading the code 
  - :cref:`std::runtime_error`: exceptions that theoretically can't be detected by reading the code
  - :cref:`std::logic_error`, and ``std::runtime_error`` are also exception bases

- Classes derived from :cref:`std::logic_error`

  - :cref:`std::domain_error`: invalid mathematical domain
  - :cref:`std::invalid_argument`: bad parameters or arguments used
  - :cref:`std::length_error`: Thrown when a std::string is too large
  - :cref:`std::out_of_range`: Used for range checked access, vector.at(x)

- Classes derived from :cref:`std::runtime_error`

  - :cref:`std::overflow_error`: mathematical overflow
  - :cref:`std::range_error`: Thrown when storing an out of range value
  - :cref:`std::underflow_error`: mathematical underflow

Using exceptions
................

C++ exceptions are designed to support *error handling*.

Use ``throw`` only to signal an error.
Use ``catch`` only to specify error handling actions when 
you know you can handle it.
Possibly by translating it to another type and re-throwing an exception of that type.
For example, catching a ``bad_alloc`` and re-throwing a ``no_space_for_file_buffers`` exception.

**Do not** use ``throw`` to catch a coding error in usage of a function. 
Instead, use assert or other mechanism to either stop the program or log the error.

**Do not** use ``throw`` if you discover an unexpected violation of an invariant of your component.
Instead, use ``assert`` or other mechanism to terminate the program. 
Throwing an exception will not cure memory corruption and may lead to further corruption of important user data.

Use ``try`` and ``catch`` blocks
if the logic is more clear than checking a condition and returning a value.
For example,
if you need to propagate errors several levels up the stack:

.. code-block:: cpp

   void f1() {
     try {
       f2();
     } catch (const some_exception& e) {
       // ... handle error
     }
   }
   void f2() { ...; f3(); ...; }
   void f3() { ...; f4(); ...; }
   void f4() { ...; f5(); ...; }
   void f5()
   {
     if ( /*...some error condition...*/ )
       throw some_exception();
   }


Only the code that detects the error, ``f5()``, 
and the code that handles the error, ``f1()``, have any clutter.
None of the other functions have to worry about passing error codes either in return values
or in extra parameters that would have to be mutable.

Do not use ``try`` blocks to reclaim resources.
This is a Java technique, 
which is great for Java, but is not needed in C++.
In C++, use Resource Acquisition Is Initialization (:term:`RAII`).

Use constructors to allocate resources
and use destructors to clean up resources,

Do not use ``try`` blocks as a proxy for error return codes.
This results in too many ``try`` blocks cluttering up functions,
which harms readability if nothing else.

.. index:: 
   pair: exceptions; I/O streams

Exceptions and I/O streams
..........................

I/O streams can be configured to throw exceptions with ``std::basic_ios::exceptions``.
This object gets and sets the exception mask of the stream. 
The exception mask set in the program determines which error states
in the stream will throw an exception if an error is encountered.
If no exception bits are set, then the I/O streams in C++ will not throw any exceptions.

For example:

.. code-block:: cpp

   std::ifstream ifs("in.txt");
   ifs.exceptions(std::ifstream::failbit);

At this point, only the ``failbit`` will trigger an exception.

I/O Streams may throw ``ios_base::failure``
But since C++11 this class inheritance changed.

``ios_base::failure`` inherits from ``std::system_error``

The end result is that ``ios_base::failure`` now has 
an ``error_code`` member to the exception object it didn't used to have.

.. code-block:: cpp

   catch (const ios_base::failure& e) {  
     std::cout << "I/O exception occurred.\n";
     std::cout << "Details: " << e.what() << std::endl;
     std::cout << "Code: " << e.code() << std::endl;
   }


-----

.. admonition:: More to Explore

   - `CPP Core Guidelines: Error Handling <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#S-errors>`_
   - `ISO C++ FAQ Exceptions <https://isocpp.org/wiki/faq/exceptions>`_
   - `Top 15 exception handling mistakes to avoid <http://www.acodersjourney.com/2016/08/top-15-c-exception-handling-mistakes-avoid/>`_
   - Overview of the `error handling <http://en.cppreference.com/w/cpp/error>`_ library and 
     `exceptions <http://en.cppreference.com/w/cpp/language/exceptions>`_
   - `try-catch <http://en.cppreference.com/w/cpp/language/try_catch>`_ and 
     `throw <http://en.cppreference.com/w/cpp/language/throw>`_
   - Post from Eric Lippert on 
     `vexing exceptions <https://blogs.msdn.microsoft.com/ericlippert/2008/09/10/vexing-exceptions/>`_


