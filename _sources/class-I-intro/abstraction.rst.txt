..  Copyright (C)  Dave Parillo.  Permission is granted to copy, distribute
    and/or modify this document under the terms of the GNU Free Documentation
    License, Version 1.3 or any later version published by the Free Software
    Foundation; with Invariant Sections being Forward, and Preface,
    no Front-Cover Texts, and no Back-Cover Texts.  A copy of
    the license is included in the section entitled "GNU Free Documentation
    License".

.. index:: 
   single: abstraction

Abstraction
===========
Most programming constructs are *abstractions*.
For example, even the idea of **number** on a computer is an abstraction.

Programmers need to define, manipulate, and store numbers.
Each language and compiler implements specific properties and operations.
C++ defines Integral types and Floating point types.
However, these numbers are **not** the numbers you learned in your math classes.
In math, you learned that:

- The set of integers is infinite
-  There is only 1 value for 0
- :math:`0.1 * 10` exactly equals 1

None of these things are guaranteed true on a computer.

It depends on the abstractions used in your language.
In C++, no numbers are infinite.
Some numbers can only store positive values.
The floating point numbers have two different representations for the value :math:`0`.
Decimal numbers that have exact values in mathematics can only be approximated in C++.

Even with all these limitations,
numeric types in C++ are quite useful.
They achieve the goal of allowing programmers to work with numbers easily
without having to worry much about how they are actually represented in hardware.

Abstraction is all about hiding implementation details.

Consider a car as an example of abstraction in design.
Starting a car in 1915 [#f1]_ :

#. On front of car, pull chock near right fender and engage crank lever under radiator.

   - Turn slowly to prime carburetor.

#. Get into car, insert key in ignition.

   - Turn start setting to either magneto or battery
   - Adjust timing stalk and throttle stalk
   - Pull back on handbrake to place car in neutral

#. Return to front of car.

   - Use left hand to crank lever
   - If the engine back-fires, using left hand results in fewer broken arms

#. If car starts, jump in!

The Model-T was one of the most popular cars ever made.
It had no frills and few abstractions.
You had to understand how it was *made* even to get it started.

This is not true with most cars today.
Compare the previous steps with starting a car today:

#. Push button

Over the last 100 years
manufacturers have hidden most implementation details
even though cars today are far more complex than a Model T.

Class abstractions
------------------
The design principles that apply to *everyday objects* also apply to *software objects*.

- Hide as many details as possible
- Don't hide too many

You, as the designer of a class are responsible for getting the abstractions
correct in the classes you design.
Keep in mind that every class defines a new *type*.
In general we want to create classes that are easy to use
and easy to modify.

A poorly abstracted car class:

.. code-block:: cpp

   class Car {
     private:
       double speed_;
       double heading_;
       int    x_;
       int    y_;
     public:
       double speed ();
       double heading ();
       int    x ();
       int    y ();
       void speed (double speed);
       void heading (double direction);
       void x (int new_x);
       void y (int new_y);
   };

What is wrong with this design?

We have created a class and dutifully made all of the class variables private.
We then (also dutifully) created functions to set and get each of the class member variables.
Isn't this is what object-oriented programming is all about?

No, it is not.

What is wrong with this design?
This list is long, but here are the major problems:

#. By default, no class members are initialized. 
   A default constructed car is invalid.
#. It is still functionally a ``struct``, even though this class has invariants.

   - The x and y values can be modified independently of speed and heading.
   - The speed could be set :math:`< 0`.
   - The heading could be anything. It's not even clear what values are valid 
     (:math:`0 - 360`?  :math:`0 - \pi`?)

#. The car position is maintained in two separate ``int`` members, not a location object. 
#. If users try to use this ``Car``, 
   then **they** are responsible for calculating correct x and y
   from the current heading and speed.
#. Fundamentally, this is not how cars are operated.

   - A car has a steering wheel and at least 1 pedal to accelerate
   - Cars only change position when moving
   - Cars only change direction when moving AND when the steering wheel is turned
   - The steering wheel has limits to keep the tires aligned with the forward momentum.


How can we improve the abstractions in our car class?

First, group the x and y coordinates into a single type.
We could do just this:

.. code-block:: cpp

   // a location on a Cartesian grid
   struct Point {
     double x = 0.0;   
     double y = 0.0;
   };

This works, but it's not much fun to use.
When using ``Point`` objects, we will often want to initialize both the x and y values at once:

.. code-block:: cpp

   Point r {3.0,3.0};

The default constructors won't do this automatically.
We need a 2 argument constructor:

.. code-block:: cpp

     Point (double x_value, double y_value)
         : x{x_value}, y{y_value}
     {}

Once a non-default constructor is added to a class,
the compiler will **not** automatically generate the default constructor for us,
so we need to be explicit:

.. code-block:: cpp

     Point () = default;

And putting them together we have very minimal class:

.. code-block:: cpp

   // a location on a Cartesian grid
   struct Point {
     double x = 0.0;   
     double y = 0.0;
     Point (double x_value, double y_value)
         : x{x_value}, y{y_value}
     {}
     Point () = default;
   };

We can't consider this class complete, but we will stop with Point for now and move onto the Car class.
When we use Point, we should prevent ``Car`` users from changing it directly:

.. code-block:: cpp

   class Car {
     private:
       Point  location_;
       double speed_    = 0.0;
       double heading_  = 0.0;

     public:
       Point  location() const;
       double speed()    const;
       double heading()  const;
   };

It is OK to keep the access functions for speed and heading.
``Car`` users are likely to need this information,
but they should never set them directly.
We should also promise that these functions will never change the state
of a ``car`` by making all of the access functions ``const``.

In order to make our car more 'real',
we should add two more private member variables,
one for the current steer angle and one for the current change in speed.
Users are never given access to these, but internally a Car can use them to
compute a new location:

.. code-block:: cpp

   class Car {
     private:
       Point  location_;
       double speed_    = 0;
       double heading_  = 0;
       double angle_    = 0;  // current steering angle
       double rate_     = 0;  // current change in speed

     public:
       Point  location() const;
       double speed()    const;
       double heading()  const;
   };


Since users can't change steer angle directly, there needs to be come way to influence that value.
One way is to define an enumerated type to set the angle on the steering wheel:

.. code-block:: cpp

   enum class Direction { CENTER, LEFT, RIGHT };


With these parts added,
we can add public functions that use them:

.. code-block:: cpp

   //
   // Users steer the car by choosing a steer direction.
   // As long as a direction is applied, the steer angle will increase (or decrease)
   // towards the indicated direction until the max steering angle
   // for the car is reached.
   //
   // The max steer angle might be Car make/model dependent.
   //
   double steer (Direction dir);

   //
   // Change the car speed by (de)accelerating.
   // Positive values will increase car speed.
   // Negative values will reduce car speed.
   // Zero values leave the car speed unchanged.
   double accelerate (double rate);

And finally, an ``update`` function a car simulator might call to 
modify the state of the car every time step.
Putting it all together:

.. code-block:: cpp

   // a location on a Cartesian grid
   struct Point {
     double x = 0.0;   
     double y = 0.0;
     Point (double x_value, double y_value)
         : x{x_value}, y{y_value}
     {}
     Point () = default;
   };

   enum class Direction { CENTER, LEFT, RIGHT };

   class Car {
     private:
       Point  location_;
       double speed_    = 0;
       double heading_  = 0;
       double angle_    = 0;
       double rate_     = 0;

     public:
       Point  location() const;
       double speed()    const;
       double heading()  const;

       double steer (Direction dir);
       double accelerate (double rate);
       void   update();
   };

Actually implementing these functions is a lab assignment.

While this class is far from complete,
at least now we have a design that we can extend without needing to completely
change it later once we realize it did not control any of its invariants.


-----

.. admonition:: More to Explore

   - TBD

.. topic:: Footnotes

   .. [#f1] From https://www.caranddriver.com/features/how-to-drive-a-ford-model-t


