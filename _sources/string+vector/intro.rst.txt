..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index::
   pair: containers; string and vector

Using string and vector
=======================

Many useful things get done using the
standard fundamental types.
Often, however, we need to group a set of related types together.
In order to group them together, 
we need some sort of **container**.

Two of these containers you should learn first:
:cpp:`std::string<string>` and :container:`std::vector<vector>`.
They come with many useful functions that help solve many common problems.
While there is some cost in using them,
often the cost is worth the benefits in terms of
reduced development time, code clarity, and other advantages.

Both ``string`` and ``vector`` are *container classes*.
That is, 
their primary job is to make it easy to work with the 
data stored inside the container.

The simplest 'batch of data' is a 'batch of characters'
Another word for 'batch of characters' is 'string'.
A ``string`` is a container for data of a 
single type: :cpp:`char<keyword/char>`.

A ``vector`` can store data of **any** type: even types that you make up.
We will see how that is possible in a bit, 
but first let's focus on how to use these two important types.

