..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".



Using string and vector
=======================

Working primitive types: char, int double.



Working with batches of data.
The simplest 'batch of data' is a 'batch of characters'


Both string and vector are *container classes*.
That is, their primary job is to make it easy to work with the data stored inside the container.

A string is simpler than vector.
A string can store data of a single type: ``char``.

A vector can store data of **any** type: even types that you make up.
We will see how that is possible in a bit, 
but first let's focus on how to use these two important types.

