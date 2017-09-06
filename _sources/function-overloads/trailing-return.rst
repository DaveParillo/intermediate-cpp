..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index::
   pair: auto; trailing return type

Trailing Return Types
=====================

You can use ``auto``, together with the ``decltype`` type specifier, 
to delay the evaluation of a function return value until after the function parameters have been declared.

Use ``auto`` and ``decltype`` to declare a function whose return type depends on the types of its arguments. 

The ``decltype`` type specifier yields the **type** of a specified expression. 
The ``decltype`` type specifier, together with the auto keyword, 
is useful primarily to developers who write generic functions using templates.

Or, use auto and decltype to declare a template function that wraps a call to another function, and then returns whatever is the return type of that other function. For more information, see decltype.





-----

.. admonition:: More to Explore

   TBD


