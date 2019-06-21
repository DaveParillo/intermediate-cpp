..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   triple: introductory topics; vim; text editors

Introducing the vim editor
==========================

Vim is a highly configurable text editor built to make creating 
and changing any kind of text very efficient. 
It is included as ``vi`` with most \*nix systems and with Apple OS X.
Among its features are:

- persistent, multi-level undo tree
- extensive plugin system
- support for hundreds of programming languages and file formats
- powerful search and replace
- integrates with many tools

If you plan to program in C++, 
you should have at least a minimal familiarity with ``vi``.
``vi`` is a very old, but very capable text editor with many features
specifically designed for writing software.
Technically, ``vi`` came first, and ``vim`` is a separate program (Vi IMproved),
but often typing either 'vi' or 'vim' invokes the same program, 
and the distinction is unimportant until you begin
exploring some of the features ``vim`` has added.  
This text uses the two terms interchangeably.

Vi has thousands of features.
No one knows them all, that is not the point.
Vi is a very efficient editor that has intuitive commands.
Because ``vi`` was created by programmers, for programmers,
most ``vi`` commands 'reward' you, if you know how to touch type.
The idea is to spend less time messing with menu commands and to spend
more time writing code.


**Benefits of learning Vim**

Once the basics of the ``vi`` editor have been mastered,
you'll find the skills learned to master vi translate to other 
tasks you'll perform as a programmer as well.

#. It is well integrated into Unix and Linux.
   Many Linux tools use the same key bindings as vim to perform similar actions,
   so while learning vim, you are also learning these commands without even knowing it.
#. The command shell history can be edited using vi commands.
#. Files can be edited directly over a network connection.
#. Vim can edit zip files directly with no need to extract their contents first.
#. Vim can easily compile programs and has rules for building many kinds of programs

**Vim help**

Vim is delivered with an extensive set of searchable, hyperlinked documentation.
Access vim help using ``:help`` (or just ``:h``.
By default a help window open with basic vim navigation and how to jump to hyperlinked topics within 
the documentation.

.. index:: 
   pair: vim; modes

Modes
-----

One of the first things to get used to with vi is that it is a **modal** editor.
Anyone who has used a computer to edit the contents of a text file has
most likely used a "mode-less" editor; 
for example, programs like Microsoft Word, Notepad or Notepad++. 
In a "mode-less" editor there is mode: text input mode. 
For composing an essay this is more-than-likely all that is needed.

On the other hand modal editors have more modes than just "insert text". 
Modes allow vi to do two basic things:

- accept a command, such as deleting a line
- accept text, written by you

Some commands tell vim to enter a new *mode* which affects what your next keystrokes will do.
In vi, type ``:help vim-modes`` to get help on modes and how to use them.

In the vi editor, each of these tasks is achieved by putting the editor 
into a particular *mode of operation* (normally just called a *mode*). 
When you wish to give vi a command,
you enter command mode, and when you want to enter text, 
you enter insert mode. 

It is important to set the correct mode before you begin writing, 
but this is simple to do. 
When you first start vi, it is automatically in normal mode.


+--------------+--------------------------------------------------------+-----------------------------+
|  Name        |  Description                                           | help page                   |
+==============+========================================================+=============================+
| normal       | For navigation and manipulation of text.               | ``:help Normal-mode``       |
|              | This is the mode that vim will usually start in,       |                             |
|              | which you can usually get back to with ESC.            |                             |
+--------------+--------------------------------------------------------+-----------------------------+
| insert       | For inserting new text.                                | ``:help Insert-mode``       |
|              | The main difference from vi is that many important     |                             |
|              | "normal" commands are also available in insert mode -  |                             |
|              | provided you have a keyboard with enough meta keys     |                             |
|              | (such as Ctrl, Alt, Windows-key, etc.).                |                             |
+--------------+--------------------------------------------------------+-----------------------------+
| visual       | For navigation and manipulation of text selections,    | ``:help Visual-mode``       |
|              | this mode allows you to perform most normal commands,  |                             |
|              | and a few extra commands, on selected text.            |                             |
+--------------+--------------------------------------------------------+-----------------------------+
| select       | Similar to visual, but with a more MS Windows-like     | ``:help Select-mode``       |
|              | behavior.                                              |                             |
+--------------+--------------------------------------------------------+-----------------------------+
| command-line | For entering editor commands -                         | ``:help Command-line-mode`` |
|              | like the help commands in the 3rd column.              |                             |
+--------------+--------------------------------------------------------+-----------------------------+
| Ex-mode      | Similar to the command-line mode but optimized         |  ``:help Ex-mode``          |
|              | for batch processing.                                  |                             |
+--------------+--------------------------------------------------------+-----------------------------+


There are many sources of vim tutorials and resources for learning about vim.
The best place to start is at your terminal, if you have one.
At the command prompt, type ``vimtutor``:

.. code-block:: text

    host@user: vimtutor

Will launch a short tutorial designed to get you started with the basics.

The site http://www.openvim.com hosts a web-based vim tutor that is easy to use.

`Linux.com <https://www.linux.com/learn/vim-101-beginners-guide-vim>`_ also has
a decent introduction to vim.

.. index:: 
   pair: vim; motions

Motions
-------

A motion is simply a command that moves the cursor. There's plenty of them, with
``h``, ``j``, ``k``, and ``l`` being the most
easily understood: move left, move up, move right, move down; all by only a
single character.

Word motions
............

``w`` To the beginning of the next word.

``e`` To the end of the current word.

``W`` To the beginning of the next WORD.

``E`` To the end of the current WORD.

``b`` Go backward a word.

``B`` Go backward a WORD.

Other motions
.............

``gg`` Go to the first line.

``G`` Go to the very last line.

``0`` Go to the very first character of the line.

``^`` Go to the very first non-whitespace character of the line.

``$`` Go to the very last character of the line.

Selections
----------

Selections are slightly different than motions in that they don't move the
cursor but they do alter the way in which commands work. They will apply a
command or operation to something like a word, or a sentence, or a block of text
inside paired parenthesis, etc. A single selection can do a lot to make life in
Vim easy.

``aw`` A word

``aW`` A WORD

``iw`` An inner word

``iW`` An inner WORD

Command & motion examples
-------------------------

- Re-indent everything ``gg=G``
- Re-indent a block of code, including braces ``=aB`` or ``=a{``

  - If the cursor is on a brace, ``=%`` is the same as ``=aB``

- Re-indent 'inner block', excluding braces ``=iB`` or ``=i{``
- Delete to the next word: ``daw``
- Delete to the next ``x`` character (replace 'x' with your character): ``dtx``
- Change a sentence: ``cas``
- Change 3 letters: ``3cl``
- Delete everything inside parenthesis: ``di)``
- Visually select a paragraph: ``vap``

.. index:: 
   pair: vim; hello world


Creating 'Hello World' using vim
--------------------------------

It is best to review this section after completing the *vimtutor*.
The *vimtutor* does a good job of explaining the basics of vim,
but doesn't provide information specific to compiling and running programs.

#. Before jumping into the editor, first let's plan to 
   save our project in a directory of its own:

   .. code-block:: text

      host@user: mkdir work
      host@user: cd work

   I chose to work in the directory, ``work``, but you could have named it
   ``hello``, ``project1``, or anything else.
   Just pick something that works for you, preferably related to the task at hand.
   Recommendation: avoid spaces in directory names.

#. At the command prompt, open a new cpp source file:

   .. code-block:: text

      host@user: vi hello.cpp

   You'll now be in ``vi``, which initially, will show a blank canvas.
   Use the commands you learned in *vimtutor* to enter insert mode and
   begin typing your program:

   .. code-block:: cpp

      #include <iostream>

      int main() {
        std::cout << "Hello, World!\n";
      }

#. When done typing, press ``ESC`` to leave insert mode.
#. Save your work by typing ``:w``.
#. Still within vim, run the *make command*: type ``:make hello``.
   You should see something similar to:

   .. code-block:: text

      c++ hello.cpp   -o hello

      Press ENTER or type command to continue

#. If you type ``:make hello`` a second time 
   (when hello already exists and you haven't yet modified hello.cpp),
   then you should see:

   .. code-block:: text

      make: `hello' is up to date.

#. At this point, you can run your program,
   also without leaving ``vi``,
   by typing ``:!./hello``.
   The ``:!`` command (bang command) executes shell commands from vim.
   If you typed the above source code, you should see:

   .. code-block:: text

      Hello, World!

      Press ENTER or type command to continue

Navigating to *make* errors
---------------------------

It is inevitable that sometimes you will create a program that does not compile.
Vim provides tools that make navigating the error list and jumping to source code easy.
The idea is to save the error messages from the compiler in a file and use Vim
to jump to the errors one by one.  You can examine each problem and fix it,
without having to remember all the error messages.

Given the following, almost correct version of our *hello, world* program:

.. code-block:: cpp

   #include <iostream>

   int main() {
     cout << "Hello, World!\n";
   }

Typing ``make foo`` results in:

   .. code-block:: text

      c++ -std=c++11 -Wall -Wextra -pedantic    foo.cpp   -o foo
      foo.cpp:4:5: error: use of undeclared identifier 'cout'; did you mean 'std::cout'?
          cout << "Hello, World!\n";
          ^~~~
          std::cout
      /usr/include/c++/v1/iostream:50:33: note: 'std::cout' declared here
      extern _LIBCPP_FUNC_VIS ostream cout;
                                        ^
      1 error generated.
      make: *** [foo] Error 1

      Press ENTER or type command to continue

When you press ENTER, the ``make`` output is hidden, but stored in a special vim buffer: 
the quickfix window.
Open the quickfix window with the command ``:copen``.
This will open the output from the last ``make`` command in a new pane.
You can move through the errors with the commands ``:cnext`` (or just ``:cn``)
and ``:cprevious`` (or just ``:cp``).
When done, close the quickfix window with ``:close`` (or just ``:ccl``)

There are many more quickfix commands, see ``:help quickfix`` for more information.

The ``make`` utility is described in more detail in the :doc:`make` section.

-----

.. admonition:: More to Explore


   - `Learning the vi Editor <https://en.wikibooks.org/wiki/Learning_the_vi_Editor>`_
   - `vi Reference <https://en.wikibooks.org/wiki/Learning_the_vi_Editor/vi_Reference>`_
   - `Vim Tips wiki <http://vim.wikia.com/wiki/Vim_Tips_Wiki>`_
   - `vim.org <http://www.vim.org/>`_
   - `vi reference cards <http://tnerual.eriogerg.free.fr/vim.html>`_ - available in several languages 
   - `vi lovers home page <http://www.thomer.com/vi/vi.html>`_
   - Swarthmore Dept. of Compter Science `vim tips and tricks page <https://www.cs.swarthmore.edu/help/vim/home.html>`_
   - `UNIX Text Processing <http://home.windstream.net/kollar/utp/>`__ - hasa chapter dedicated to vi.


   **Text editor downloads**

   - `Notepad++ <https://notepad-plus-plus.org/>`_ (Windows only) - also available on campus
   - `Atom <https://atom.io/>`_ (Win, OSX, or Linux)
   - `Vim <https://vim.sourceforge.io/>`_ 
   - `Emacs <http://www.gnu.org/software/emacs/>`_

   Both vim and emacs are included on the Mesa server.
   If you have already downloaded ``git``, then you also have vim.
   Git provides a subset of the Gnu/linux utilities, 
   including vim and ssh, but not make or g++.


