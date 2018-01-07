..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, Prefaces, and
    Contributor List, no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".


.. index::
   pair: FAQ; integrated development environment

Why not use an IDE?
===================

You can use an Integrated Development Environment (IDE) if you feel strongly about it.
An IDE can make you more productive in some environments.
But I don't recommend an IDE *ever* when learning a language.

Why?

Lots of reasons.

#. When learning, 
   you are still trying to commit the syntax and grammar of the new
   language to memory.
   If every other keystroke is <CTRL>-space and you let the tool
   autocomplete everything, you will never really master the language.

#. An IDE is not a 'free lunch'.
   They are typically complex applications with loads of options that require 
   as much learning as the modes and keyboard commands in vim.
   Unless you put in the time and effort to learn the IDE, 
   you won't realize most of the productivity gains anyways.

#. IDE's typically only support one, or a few language really well.
   Microsoft Visual Studio is an exception.
   I would rate it as very good for Visual Basic, C#, and Web Development (including JavaScript).

   There are no 'great' C or C++ IDE's.

   But even if you find a great IDE, 
   if you work in a different language,
   then you need to potentially learn a completely different tool
   to work with the other language.

#. IDE's are great if you are working on a single, medium sized project
   for an extended period of time.
   Think more than 1,000 lines of code.
 
   On a project, the time it takes to setup a new project is worth the
   investment, because you'll be working on it for potentially a long time.

   This is not mostly what we do in a classroom situation.

   We create lots of very small programs,
   because we are trying to distill new concepts down to the smallest
   program that will demonstrate the idea.

   In this environment, IDE's get in the way, 
   because it takes more time to make a new project in the IDE,
   than it does to just time ``make my_program`` on the command line or in vim.


-----

.. admonition:: More to Explore

   - Textbook: :doc:`../beginnings/make`


