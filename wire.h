// Author .......... Felix Brei
// Creation Date ... 2016/11/02
// Last changed .... 2016/11/03

// Description
// -----------
// This file contains the wire api that is to be used in the main program and to connect neurons. Since dendrites and synapses basically fulfill the same functionality there will only be one generic type to represent both.

// The usual header guard

#ifndef WIRE_H_
#define WIRE_H_

// Local includes
#include "typedefs.h"

// START

// Allocate and free a wire struct
Wire* alloc_wire();
void free_wire(Wire* w);

// Write and read the signal strength of a wire
void set_signal_strength(Wire*, double);
double get_signal_strength(Wire*);

// Register successor and predecessor  of a connecting wire
void set_successor(Wire*, Neuron*);
void set_predecessor(Wire*, Neuron*);

#endif
