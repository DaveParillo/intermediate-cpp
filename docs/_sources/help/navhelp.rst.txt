:orphan:

.. qnum::
   :start: 1
   :prefix: sc-1-

.. index:: 
   single: help
   single: interactive tools
   single: search

.. _quick_help:

Getting Around The Book
=======================

This page will help you learn how to get around this interactive textbook and use the embedded tools.

Navigation Bar
--------------

Use the Search dropdown menu on the site toolbar to access several handy features:

.. image:: navbar_search_dropdown.png
    :class: search-dropdown-img

* The entire book table of contents
* An alphabetic index of of all the keywords in this book
* Scratch ActiveCode
  This will popup a window allowing you to test out an arbitrary chunk of C++ code
* Search performs basic (very basic) text search of the book

.. index:: 
   pair: help; ActiveCode

ActiveCode Windows
------------------

One of the most important things that you can do when you are learning a programming language is to write programs.  Unfortunately,
typical textbooks allow you to read about programming but don't allow you to practice.  We have created a unique tool called
**ActiveCode** that allows you to write, modify, and execute programs right
in the text itself (right from the web browser).  Although this is certainly not the way real programs are written, it provides an excellent
environment for learning a programming language since you can experiment with the language as you are reading.

Take a look at the ActiveCode interpreter in action.  If we take a simple program and make it active, 
you will see that it can be executed directly by pressing the *Run* button.
Try pressing the *Run* button below.

.. activecode:: codeexample1
    :language: javascript

    var x = 10;
    var y = 11;
    var z = x + y;
    console.log(z);
    writeln('hello world');

.. index:: 
   pair: help; CodeLens

The CodeLens Tool
-----------------

In addition to ActiveCode, you can also execute code with the assistance of a unique visualization tool.  
This tool, known as **CodeLens**, allows you to control the step by step execution of a program.  
It also lets you see the values of all variables as they are created and modified.  
The following example shows CodeLens in action on the same simple program as we saw above.  
Remember that in ActiveCode, the source code executes from beginning to end and you can see the final result.  
In Codelens you can see and control the step by step progress.  

Try clicking on the *Forward* button below.

.. raw:: html

   <div data-childcomponent="codelens1" class="explainer ac_section alert alert-warning">
   <iframe width="800" height="500" frameborder="0" src="http://pythontutor.com/iframe-embed.html#code=%23include%20%3Ciostream%3E%0A%0Aint%20main%20%28%29%20%7B%0A%20%20int%20test%5B%5D%20%3D%20%7B%201,%202,%203,%205,%208%20%7D%3B%20%20//%20can%20we%20use%20an%20initilaizer%20list%3F%0A%20%20for%20%28auto%20i%3A%20test%29%20%7B%20%20%20%20%20%20%20%20%20%20%20%20%20//%20can%20we%20use%20a%20range-for%20loop%3F%0A%20%20%20%20std%3A%3Acout%20%3C%3C%20%22i%20is%20%22%20%3C%3C%20i%20%3C%3C%20'%5Cn'%3B%0A%20%20%7D%0A%20%20return%200%3B%0A%7D&codeDivHeight=400&codeDivWidth=350&curInstr=1&mode=edit&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D"> </iframe>
   </div>

Many CodeLens examples will link to an external page, like `this <http://pythontutor.com/cpp.html#code=%23include%20%3Ciostream%3E%0A%0Aint%20main%20%28%29%20%7B%0A%20%20int%20test%5B%5D%20%3D%20%7B%201,%202,%203,%205,%208%20%7D%3B%20%20//%20can%20we%20use%20an%20initilaizer%20list%3F%0A%20%20for%20%28auto%20i%3A%20test%29%20%7B%20%20%20%20%20%20%20%20%20%20%20%20%20//%20can%20we%20use%20a%20range-for%20loop%3F%0A%20%20%20%20std%3A%3Acout%20%3C%3C%20%22i%20is%20%22%20%3C%3C%20i%20%3C%3C%20'%5Cn'%3B%0A%20%20%7D%0A%20%20return%200%3B%0A%7D&curInstr=0&mode=display&origin=opt-frontend.js&py=cpp&rawInputLstJSON=%5B%5D>`_
or `that <https://goo.gl/WGiilZ>`_. 

.. index:: 
   pair: help; answering self-check questions

Self-Check Questions
--------------------

Finally, it is also possible to embed simple questions into the text.  These
questions provide a way for you to check yourselves as you go along.  The questions also provide feedback so that you can
understand why an answer may or may not be correct.

**Check your understanding**

.. mchoice:: question1_1
   :answer_a: Python
   :answer_b: Java
   :answer_c: C++
   :answer_d: Haskell
   :correct: a
   :feedback_a: Python is a great language, but is not covered in this course.
   :feedback_b: Java is a good object oriented language but 
   :feedback_c: Yes, this couse will teach you C++.  Specifically, *Modern* C++
   :feedback_d: No, Haskell is a functional programming language.  You can use C++ to write functional programs as well.

   What programming language does this course help you to learn?


This next type of question allows more than one correct answer to be required.  The feedback will tell you whether you have the
correct number as well as the feedback for each.


.. mchoice:: question1_2
   :multiple_answers:
   :answer_a: red
   :answer_b: yellow
   :answer_c: black
   :answer_d: green
   :correct: a,b,d
   :feedback_a: Red is a definitely on of the colors.
   :feedback_b: Yes, yellow is correct.
   :feedback_c: Remember the acronym...ROY G BIV.  B stands for blue.
   :feedback_d: Yes, green is one of the colors.

   Which colors might be found in a rainbow? (choose all that apply)


.. raw:: html

    <link href='_static/guiders-1.3.0.css' rel='stylesheet' type='text/css'>
    <script src='_static/guiders-1.3.0.js' type='text/javascript'></script>
    <script src='_static/navhelp.js' type='text/javascript'></script>

