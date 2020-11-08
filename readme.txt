

This is a prototype for a non blocking functor 
called in a strict sequence.

The statemachine name is wrongly chosen :(

The core of the prototype is the state_machine.h

It takes a class instance and pointers to it's methods
and calls each of them without blocking. 
In the same time preserves the order of the calls.
for the moment the supported method signature is
int some_method(void);

For usage see the file main.cpp, in this case
the test1, test2, test3 methods are called in this order.
Even if one of the above methods blocks the machine does not.
