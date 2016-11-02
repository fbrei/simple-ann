// Author .......... Felix Brei
// Creation Date ... 2016/11/02
// Last changed .... 2016/11/02

// Description
// -----------
// This file contains the implementation of the wire struct plus maintenance functions.
// Wires serve to connect neurons

// System includes
#include <stdlib.h>				// Contains useful constants
#include <stdio.h>				// printf

// Local includes
#include "wire.h"

// START

struct _Wire {

	// The strength of the signal that is being carried
	double signal_strength;

	// The gradient aka. force or tug on the signal strength
	double gradient;

	// Link to the predecessor neuron (where the signal is coming from)
	Neuron* pre;

	// Link to the successor (where the signal is transported to)
	Neuron* succ;
}

Wire* alloc_wire() {
	Wire* w = malloc(sizeof(Wire));
	w->signal_strength = 0.0;
	w->gradient = 0.0;
	w->pre = NULL;
	w->succ = NULL;
}
