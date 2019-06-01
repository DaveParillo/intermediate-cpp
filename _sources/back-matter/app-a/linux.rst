..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. include:: <isonum.txt>

.. index:: 
   pair: introductory topics; linux

Introducing Gnu/Linux
---------------------

Early in its evolution, 
the command-line environment of UNIX (its only user interface back then) 
became dominated by dozens of small utilities and tools which are still in common use today.
These tools are small and generally do one thing well. 
Most read from 'standard input' and write to 'standard output'.
The tools are commonly chained together in longer command pipelines, 
one program passing its output to the next as input, 
and controlled by a variety of command-line options and arguments.

This is one aspect of UNIX that makes it a powerful environment for processing 
text-based data, one of its first uses in a corporate environment. 
Dump some text in one end of a command pipeline and retrieve processed output from the other end.
As programmers, this is useful, because at its core, programming involves manipulating text:
transforming source code into executable machine code, 
converting database query results into readable reports, etc.

This section is not intended to make you an expert if you have never
used linux before.
It is intended to give you enough of a jump start to demystify things somewhat
and ease forward progress.

.. index::
   pair: git; ssh client

Getting access
..............

All projects and some of the lab assignments are required to be handed in on the
San Diego Mesa College server **buffy**.
Access is only available using a *secure shell* client program (ssh).
There are a few ways to access buffy using ``ssh``.
If you have a MacOS X or Linux computer available already, then you already have ssh installed.
If you have a Windows computer, 
then my first recommendation is to install ``git``.
Technically, ``git`` is a source code revision control program,
but it also provides a minimal GNU/Linux environment 
(not too surprising since the creator, Linus Torvalds, is also the creator of Linux).
Git provides just about everything you need, except for a compiler.

Another good choice for an SSH
client if you run Microsoft Windows is PuTTY:

.. code-block:: none

   http://www.chiark.greenend.org.uk/~sgtatham/putty/

In ``git`` you would type the following in the *GIT Bash* to connect to the buffy server:

.. code-block:: none

   host@user: ssh fireNN@209.129.16.61

where *fireNN** is the user name assigned to you by the instructor.


The command line
................

A command line, or terminal, is a text based interface to the system.
You enter commands by typing them on the keyboard and feedback is returned as text.

The command line typically presents you with a prompt. 
As you type, it will be displayed after the prompt.
Most of the time you will be issuing commands. Here is an example:

.. code-block:: none

   host@user: ls -l /home/user
   total 12
   -rw-rw---- 1 user student  419 May 29 06:49 main.cpp
   -rw-rw---- 1 user student 3320 May 29 06:50 util.h
   -rw-r--r-- 1 user student  725 May 29 06:49 vim_tips.md
   host@user:

What's happening?

* The first line is the **prompt** ( host\@user ). 
  On this first line, a command was also entered ``ls``.
  The ``ls`` command lists the contents of a directory.
  In this example, we also supplied some command line arguments (-l /home/user).
  It is conventional to start command line arguments (or 'switches') with a dash.
* The next 4 lines are output from the 'ls' command.
  Most commands produce output that is written to standard output,
  which in the case of running on the command line is the terminal itself.
* The last line displays the command prompt again.
  At this point, the system is waiting for the next command.

  If no prompt is displayed, this means the command is still running.

Absolute vs relative paths
..........................

Look at the argument passed to the ``ls`` command in the previous example:

.. code-block:: none

   /home/user

Specifically, this indicates the *absolute path* to the directory ``/home/user``.
There are 2 types of paths we can use, **absolute** and **relative**. 
All references to a file or directory use one of these forms. 

Absolute path 
    Specifies a location starting at the **root directory**. 
    An absolute path *must* start with the character '/'.

Relative path 
    Specifies a location in relation the current working directory. 
    A relative path will *never* start with the character '/'.

When navigating or specifying paths, there are two special files which
reside in every directory: ``.`` and ``..``.

\.
  The single dot ``.`` file contains information about the files in the current
  directory.  In many commands, it is synonymous with the current directory.

\..
  The two dots ``..`` file contains information about the files in the directory
  that is the parent of the current directory.
  The only directory that does not contain a ``..`` file is the root directory: ``/``.


In addition, the character ~ (tilde) is an abbreviation for the path to any user home directory.

.. code-block:: none

   ls ~alice/public_html

Displays the contents of the public_html folder in her home directory,
regardless of where her home directory actually is located.


.. reveal:: reveal-skill-check-paths
   :showtitle: Show Skill Check
   :hidetitle: Hide Skill Check


   .. mchoice:: mc_paths_1
      :multiple_answers:
      :correct: a,c,e
      :answer_a: ../usr/bin
      :answer_b: /usr/bin
      :answer_c: ./
      :answer_d: /
      :answer_e: user/files
      :feedback_a: Correct. ../usr/bin does not start with a '/'.
      :feedback_b: /usr/bin starts with a slash.
      :feedback_c: Correct. ./ does not start with a '/'.
      :feedback_d: / this is the 'root' directory.
      :feedback_e: Correct. user/files does not start with a '/'.

      Which of the following statements are **relative paths**?  Check all that apply.

   .. mchoice:: mc_paths_2
      :multiple_answers:
      :correct: a,b,d
      :answer_a: In directory <tt>/tmp</tt>, <tt>../home/user</tt> 
      :answer_b: In directory <tt>/home</tt>, <tt>../home/user</tt> 
      :answer_c: In directory <tt>/home/user</tt>, <tt>..</tt> 
      :answer_d: In directory <tt>/home/user/work</tt>, <tt>..</tt> 
      :answer_e: In directory <tt>/home/user/work</tt>, <tt>../../user</tt> 
      :feedback_a: Correct. 
      :feedback_b: Correct. 
      :feedback_c: This lists the contents of <tt>/home</tt>.
      :feedback_d: Correct. 
      :feedback_e: This attempts to list the contents is <tt>/user</tt>.

      Which of the following paths list the contents ``/home/user``?  Check all that apply.

Basic commands
..............

pwd
   Prints the working directory name.
   ``pwd`` prints the full path name of the directory you are currently in.

ls
   Print directory contents.
   With no arguments, :code:`ls` prints the current directory contents,
   that is the contents of the directory returned by :code:`pwd`.
   For each operand that names a file
   of type directory, ls displays the names of files contained within that directory, as
   well as any requested, associated information.

   The :code:`ls` command has a **lot** of options.

cd
   Change directory.
   With no arguments, (just ``cd``), this command will take you to **your**
   home directory.
   A file after the cd command ``cd ../lab/solutions`` changes the current working
   directory to the named path.

   The special name ``~`` is a shortcut for the users home directory.

mkdir
   Make a new directory. At least one argument is required. For example:

   .. code-block:: bash

      host@user: cd
      host@user: ls -l 
      total 4
      -rw-rw---- 1 user student  419 May 29 06:49 main.cpp
      host@user: mkdir labs
      host@user: ls -l 
      total 8
      drwx------ 1 user student  419 May 29 15:06 labs
      -rw-rw---- 1 user student  419 May 29 06:49 main.cpp

man
   Display manual pages for a command.

   There is an **enormous** amount of information available from the command line.
   Conceived of and written before the internet existed, it was intended
   to function as a comprehensive reference for everything a programmer
   would need to know to be productive in Unix.  For example:

   .. code-block:: man

      host@user: man ascii
   
      ASCII(7)               Linux Programmer's Manual              ASCII(7)
      NAME
         ascii - ASCII character set encoded in octal, decimal, and hexadecimal

      DESCRIPTION
         ASCII  is  the American Standard Code for Information Interchange.  
         It is a 7-bit code.  Many 8-bit codes (such as ISO 8859-1, the Linux 
         default character  set)  contain  ASCII  as  their lower half.  
         The international counterpart of ASCII is known as ISO 646.

         The following table contains the 128 ASCII characters.

         C program '\X' escapes are noted.

         Oct   Dec   Hex   Char                        Oct   Dec   Hex   Char
         ────────────────────────────────────────────────────────────────────────
         000   0     00    NUL '\0'                    100   64    40    @
         001   1     01    SOH (start of heading)      101   65    41    A
         002   2     02    STX (start of text)         102   66    42    B
         003   3     03    ETX (end of text)           103   67    43    C
         004   4     04    EOT (end of transmission)   104   68    44    D
         005   5     05    ENQ (enquiry)               105   69    45    E
         006   6     06    ACK (acknowledge)           106   70    46    F
         007   7     07    BEL '\a' (bell)             107   71    47    G
         010   8     08    BS  '\b' (backspace)        110   72    48    H
         011   9     09    HT  '\t' (horizontal tab)   111   73    49    I
         012   10    0A    LF  '\n' (new line)         112   74    4A    J
         013   11    0B    VT  '\v' (vertical tab)     113   75    4B    K
         014   12    0C    FF  '\f' (form feed)        114   76    4C    L
         015   13    0D    CR  '\r' (carriage ret)     115   77    4D    M
         016   14    0E    SO  (shift out)             116   78    4E    N
         017   15    0F    SI  (shift in)              117   79    4F    O
         020   16    10    DLE (data link escape)      120   80    50    P
         021   17    11    DC1 (device control 1)      121   81    51    Q
         022   18    12    DC2 (device control 2)      122   82    52    R
         023   19    13    DC3 (device control 3)      123   83    53    S
         024   20    14    DC4 (device control 4)      124   84    54    T
         025   21    15    NAK (negative ack.)         125   85    55    U
         026   22    16    SYN (synchronous idle)      126   86    56    V
         027   23    17    ETB (end of trans. blk)     127   87    57    W
         030   24    18    CAN (cancel)                130   88    58    X
         031   25    19    EM  (end of medium)         131   89    59    Y
         032   26    1A    SUB (substitute)            132   90    5A    Z

   (remainder ommitted)

For these last four 'core' commands, 
use the ``man`` command to learn detailed information about how they function, 
if you need it.

cp
  Copy files or directories

mv
  Move files or directories

rm
  Remove files or directories

passwd
  Change your login password


.. admonition:: Try This!

   Use this example terminal to try the commands described in this section.

   It's a sandbox, feel free to play for a bit.
   
   - The top window is a file where you can type and save commands.
   - The bottom window is a linux shell.
     Commands typed directly in the shell are not saved.


   .. raw:: html

      <div>
      <iframe height="400px" width="100%" src="https://repl.it/@DaveParillo/bashtutorial?lite=true" scrolling="no" frameborder="no" allowtransparency="true" allowfullscreen="true" sandbox="allow-forms allow-pointer-lock allow-popups allow-same-origin allow-scripts allow-modals"></iframe>
      </div>

    

-----

.. admonition:: More to Explore

   - `LinuxCommand.org <http://linuxcommand.org>`__
   - `UNIX Text Processing <http://home.windstream.net/kollar/utp/>`__ - one of the best general
     references for people new to Unix or GNU/Linux.
   - `GNU / Linux tutorial <https://www.debian.org/doc/manuals/debian-reference/>`_ - from debian.org
   - `UNIX Philosophy <https://en.wikipedia.org/wiki/Unix_philosophy>`_ - from Wikipedia
   - Learn Enough\ |trade| `Command-Line to be Dangerous tutorial <http://www.learnenough.com/command-line-tutorial>`_ by Michael Hartl.
   - `Ryans Tutorials: Linux <http://ryanstutorials.net/linuxtutorial/>`_ - a decent introduction to the linux command line 

