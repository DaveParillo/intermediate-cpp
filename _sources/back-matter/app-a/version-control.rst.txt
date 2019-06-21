..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   triple: introductory topics; version control; git

Version control
===============

When you are programming, you will make mistakes. 
If you program long enough, 
these will eventually include shenanigans like accidentally deleting all of your source files. 
You are also likely to spend some of your time trying out things that don’t work, 
at the end of which you’d like to go back to the last version of your program that did work. 
All these problems can be solved by using a **version control system**.


If you have never used version control software before, I recommend ``git``.
If you have used it before, feel free to continue using what you are familiar with.
A brief summary of git is given below. 
For more details, see the tutorials available at http://git-scm.com.

Whatever version control software you use, they all follow the same basic pattern:

#. Initialize repository

   You only need to do this step once.

#. Work with repository

  a. Create new files
  b. Add files to repository
  c. Edit existing files
  d. Commit changes
  
  Repeat the above as often as needed.


Setting up git
--------------

Typically you run git inside a directory that holds some project you are working 
on (for example, homework). 
Before you can do anything with git, 
you need to create the repository, 
which is a hidden directory .git that records changes to your files:

.. code-block:: none

    $ mkdir git-demo
    $ cd git-demo/
    $ git init
    Initialized empty Git repository in /var2/home/dparillo/git-demo/.git/

Now let’s create a file and use ``git add`` to add it to the repository:

.. code-block:: none

    $ echo 'int main(int argc, char** argv) { return 0; }' > tiny.cpp
    $ git add tiny.cpp

The ``git status`` command will tell us that Git knows about tiny.c, 
but hasn't committed the changes to the repository yet:

.. code-block:: none

    $ git status
    On branch master

    Initial commit

    Changes to be committed:
      (use "git rm --cached <file>..." to unstage)

      new file:   tiny.cpp


The ``git commit`` command will save the actual changes, 
along with a message saying what you did. 
But before we commit our changes, 
we should configure git with our actual name and email address.
This step is not required in a standalone repository like the one
we are using here, but in a shared repository,
it's considered best practice to use a real name and email
in case someone needs to contact you:

.. code-block:: none

   $ git config --global user.email you@example.com

.. index::
   pair: vim; git editor

Now we are ready to save our changes in the git database.
For short messages, 
the easiest way to do this is to include the message on the command line:

.. code-block:: none

    $ git commit -m 'a very short c++ program'
    [master (root-commit) 3a6fd19] a very short c++ program
     1 file changed, 1 insertion(+)
     create mode 100644 tiny.cpp

Without the ``-m`` argument, git runs the default editor (vim) to let you edit your commit message. 
If you don’t like vim, you can change the default using ``git config``:

.. code-block:: none

    $ git config --global core.editor "emacs -nw"

You can see what commits made so far using ``git log``:

.. code-block:: none

    $ git log
    commit 3a6fd19e8ef4662744bd41a20cde9924aad918ed
    Author: DaveParillo <DaveParillo@noreply.github.com>
    Date:   Sat Jun 10 12:07:51 2017 -0700

        a very short c++ program

Editing files
.............

Suppose I edit tiny.cpp using my favorite editor to turn it into the classic hello-world program:

.. code-block:: cpp

   #include <iostream>

   int main() { 
     std::cout << "Hello, world!\n";
     return 0;
   }

I can see what files have changed using git status:

.. code-block:: none

    $ git status
    On branch master
    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

      modified:   tiny.cpp

    no changes added to commit (use "git add" and/or "git commit -a")


Notice how Git reminds me to use ``git commit -a`` to include these changes in my next commit. 
I can also do ``git add tiny.cpp`` to only include the changes to tiny.cpp 
(maybe I made changes to a different file that I want to commit separately), 
but usually that’s too much work.

If I want to know the details of the changes since my last commit, I can do git diff:

.. code-block:: none

    $ git diff
    diff --git a/tiny.cpp b/tiny.cpp
    index a9b8738..a6501a7 100644
    --- a/tiny.cpp
    +++ b/tiny.cpp
    @@ -1 +1,6 @@
    -int main(int argc, char** argv) { return 0; }
    +#include <iostream>
    +
    +int main() { 
    +  std::cout << "Hello, world!\n";
    +  return 0; 
    +}
    

Since I like these changes, I do a commit:

.. code-block:: none

    $ git commit -a -m 'turn tiny into a basic hello world'
    [master 170eaf0] turn tiny into a basic hello world
     1 file changed, 6 insertions(+), 1 deletion(-)

The repository now contains two commits:

.. code-block:: none

    $ git log | more
    commit 170eaf0461a7f0f865328b73bee6d313c3dbad42
    Author: DaveParillo <DaveParillo@noreply.github.com>
    Date:   Sat Jun 10 12:23:55 2017 -0700

        turn tiny into a basic hello world

    commit 3a6fd19e8ef4662744bd41a20cde9924aad918ed
    Author: DaveParillo <DaveParillo@noreply.github.com>
    Date:   Sat Jun 10 12:07:51 2017 -0700

        a very short c++ program

Renaming files
..............

You can rename a file with ``git mv``. 
This is just like regular ``mv``, 
except that it tells Git what you are doing.
If you for get to use ``git mv`` it's not normally a problem.
Unless your changes are massive, git is usually good about
figuring out when files have been moved.:

.. code-block:: none

    $ git mv tiny.cpp hello.cpp
    buffy:~/git-demo 
    $ git status
    On branch master
    Changes to be committed:
      (use "git reset HEAD <file>..." to unstage)

      renamed:    tiny.cpp -> hello.cpp


Moving a file counts as a change.
These changes don’t get written to the repository unless you do another git commit:

.. code-block:: none

    $ git commit -m 'give better name to hello program'
    [master 7a603f4] give better name to hello program
     1 file changed, 0 insertions(+), 0 deletions(-)
     rename tiny.cpp => hello.cpp (100%)

Adding and removing files
.........................

To add a file, create it and call ``git add``:

.. code-block:: none

  $ cp hello.cpp goodbye.cpp
  $ git status
  On branch master
  Untracked files:
    (use "git add <file>..." to include in what will be committed)

    goodbye.cpp

  nothing added to commit but untracked files present (use "git add" to track)
  $ git add goodbye.cpp 
  $ git commit -m 'started to make a second program to say goodbye'
  [master f41cb3a] started to make a second program to say goodbye
   1 file changed, 6 insertions(+)
   create mode 100644 goodbye.cpp

If you add many files at once, you can refer to the directory they are in.
If that directory is the current directory, ``.`` is acceptable.
When you specify a directory, then all of the files new or modified are
added recursively from that point downward.

To remove a file, use ``git rm``:

.. code-block:: bash

    $ git rm goodbye.cpp 
    rm 'goodbye.cpp'
    $ git status
    On branch master
    Changes to be committed:
      (use "git reset HEAD <file>..." to unstage)

      deleted:    goodbye.cpp

    $ git commit -m 'on second thought, goodbye.cpp was a bad idea'
    [master cbcf75f] on second thought, goodbye.cpp was a bad idea
     1 file changed, 6 deletions(-)
     delete mode 100644 goodbye.cpp

Recovering files from the repository
....................................

Nothing is ever truly deleted from the repository once checked in.
If you accidentally delete something, you can recover it from the repository.:

.. code-block:: bash

    $ ls -a
    ./  ../  .git/	hello.cpp

    $ rm hello.cpp 
    $ ls -a
    ./  ../  .git/

    # gone, but not forgotten

    $ git checkout -- hello.cpp
    $ ls -a
    ./  ../  .git/	hello.cpp

Using ``git checkout --`` gets the most recent version out of the repository, 
but using the commit id, we can operate on any version:

.. code-block:: bash

    $ git checkout 3a6f -- tiny.cpp
    $ ls -a
    ./  ../  .git/	hello.cpp  tiny.cpp

Because tiny.cpp is not part of the current HEAD (most recent version), 
it is considered a new file, 
but the checkout did add tiny.cpp and stage it for commit:

.. code-block:: bash

    $ git status
    On branch master
    Changes to be committed:
      (use "git reset HEAD <file>..." to unstage)

      new file:   tiny.cpp

    

-----

.. admonition:: More to Explore

   - `CISC187 git repository <https://github.com/DaveParillo/cisc187>`_
   - `Git Home <http://git-scm.com>`_

     All Git commands take a ``--help`` argument that brings up their manual page. 
     There is also extensive documentation at http://git-scm.com.

.. topic:: Endnotes

   1.  Content in this section is adapted from
       http://www.cs.yale.edu/homes/aspnes/classes/223/notes.html

   

