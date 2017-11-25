..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, Prefaces, and
    Contributor List, no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

Preface
=======

There are many books available if you want to learn to program in C++.
Does the C++ community really need yet another textbook?
Apparently, I think the answer to that question is 'yes'. Why?

- Many excellent books are not appropriate for new language learners.
- Many books, although excellent when written,
  have not been updated as the language has changed.

  Significant language changes over the past 10 - 15 years 
  justifies teaching new features and retiring old ones.

- Many textbooks claiming to be 'for C++' are not much more than
  bare bones ports from other languages.

I take exception especially to this last group, as they claim to be
C++ textbooks (and charge good money for it), however,
they do not teach good **idiomatic** C++.

What do I mean by **idiomatic** C++?

In a nutshell, it means writing C++ code that follows the conventions of the language.
Because C++ is a language that has undergone significant change since
its inception, the C++ of 1998 is not the C++ of today.
Perhaps a short story would help make the point more clearly:

.. topic:: English As She is Spoke

   `English As She Is Spoke <https://en.wikipedia.org/wiki/English_As_She_Is_Spoke>`_ 
   is the common name of a 19th-century book written by Pedro Carolino.

   A well-meaning person, to be sure; his goal was to create a
   Portuguese-to-English phrase book.
   One minor obstacle stood in Pedro's way.
   He apparently spoke no English.

   Undaunted, and armed with both an earlier Portuguese-French phrase book
   and a French-English dictionary, he embarked on his quest.
   He managed to create a book that fails utterly in teaching
   common English language phrases and idioms to anyone.

   He did not intend to write a humor book, but that was the result.

   .. epigraph::

      Nobody can add to the absurdity of this book, 
      nobody can imitate it successfully, 
      nobody can hope to produce its fellow; 
      it is perfect.

      -- Mark Twain, 1883.\ [1]_

While most C++ textbooks that have been marginally ported from other
languages cannot hope to achieve the level of silliness reached by
English As She Is Spoke, they still fail their readers.
That is, they fail to teach C++ as C++.
C++ is not C, Python, Java, Visual Basic, or anything else.

Good, idiomatic C++ embodies the philosophy behind the C++ Core Guidelines\ [2]_\ ,
the first few of which are:

- Ideas are expressed in code
- Code in ISO Standard C++
- Express intent

The goal of this book is to describe the current version of the language
in a clear, concise style, supplemented by meaningful activities
where appropriate.

The goal of this book is **not** to describe every language feature in C++.
Why?
Primarily because C++ is a large language,
but also because you don't need to know *all* of C++ to be an effective C++ programmer.
If you really want to read about every language feature,
then read `cppreference.com <http://en.cppreference.com/w/>`_.

Programming is not a "spectator sport".  
It is something you do, something you participate in. 
It would make sense, then,
that the book you use to learn programming should allow you to be active.

This book is meant to provide you with an interactive experience as you learn to program.  
You can read the text, watch videos, and write and execute code.
In addition to simply executing code,
there are visualizations which allow you to control the flow of execution, 
and watch variables as they are created and destroyed,
in order to gain a better understanding of how the program works.

Different presentation techniques are used where appropriate.  
In other words, sometimes it might be best to read a
description of some aspect of a programming language.  
On a different occasion,
it might be best to execute a small example program.  
An important goal is to  provide multiple options for covering the material in each section.  
Hopefully, you will find
your understanding is enhanced because you are able to experience
content in more than just one way.

How to Contribute
-----------------

Readers are encouraged to fork the source repository for this book on GitHub.
Improve it and submit a pull request.
The document `GitHub-Forking <https://gist.github.com/Chaser324/ce0505fbed06b947d962>`_
is an excellent place to get started.
Read this first.

Every pull request will be evaluated for inclusion and if not included, 
I will let you know why.


----

.. topic:: Footnotes

   .. [1] Mark Twain, "Introduction to The New Guide of the Conversation in Portuguese and English" (1883) p. 239.
   .. [2] Bjarne Stroustrup and Herb Sutter, 
          `C++ Core Guidelines <http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines>`_

