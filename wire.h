// Author .......... Felix Brei
// Creation Date ... 2016/11/02
// Last changed .... 2016/11/02

// Description
// -----------
// This file contains the wire api that is to be used in the main program and to connect neurons.


// START

#ifndef WIRE_H_
#define WIRE_H_

typedef struct _Wire Wire;

Wire* alloc_wire();
void free_wire(Wire* w);

void set_signal_strength(Wire*, double);
double get_signal_strength(Wire*);

#endif
