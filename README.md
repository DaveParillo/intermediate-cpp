# Intermediate Modern C++: Interactive Edition

A C++ textbook based on [runestone interactive](http://runestoneinteractive.org/build/html/index.html).

Does the world really need another programming textbook?

Apparently, the answer to that question is yes.

This project began with an effort to choose a suitable textbook specifically 
for students learning their second semester of C++.
The goals of this project are to produce a text book that:

* Covers C++ programming at the _intermediate_ level - not too basic, but not too advanced.
* Places an emphasis on Getting the most out of 'modern' C++ - that is C++11 and later.
  * There are plenty of places to learn standard C or C++98.
* Is highly interactive and supports active learning.
  * Programming is not a "spectator sport".  
    It is something you do, something you participate in. 
    It makes sense, then, that the book you use to learn programming allows you to be active.

This book is meant to provide you with an interactive experience as you learn C++.
You can read the text, watch videos, answer questions, and write and execute code.
In addition to simply executing code,
there is a unique feature called 'codelens' that allows you to control the
flow of execution in order to gain a better understanding of how the program
works.


# Getting Started

We have tried to make it as easy as possible for you to build and use this book.  

1. You can see and read this book [online](https://daveparillo.github.io/intermediate-cpp).

2.  You can build it and host it yourself in just a few simple steps:

## Install and make a Python virtualenv
 
* Documentation here:  https://virtualenv.pypa.io/en/stable/
* Video here:  https://www.youtube.com/watch?v=IX-v6yvGYFg
* For the impatient:

```
    $ sudo pip install virtualenv
    $ virtualenv /path/to/some/directory
    $ source /path/to/some/directory/bin/activate
```
     
* You will need to do the last command **every time** you want to work on the book in your virtual environment.
If you have not used Python virtual environments before I strongly recommend reading the docs or watching the video
 
With the virtual environment installed and configured you can continue.

```
    $ pip install runestone

    $ runestone build -- will build the html and put it in ``./build/intermediate-cpp``
    $ runestone serve   -- will start a webserver and serve the pages locally from ``./build/intermediate-cpp``

```

