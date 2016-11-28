// Author .......... Felix Brei
// Creation Date ... 2016/11/02

// Description
// -----------
// This file contains the implementation of the wire struct plus maintenance functions.
// Wires serve to connect neurons

// System includes
#include <stdlib.h>				// Contains useful constants
#include <stdio.h>				// printf

// Local includes
#include "neuron.h"
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
};

// Allocates an empty wire
Wire* alloc_wire() {
	Wire* w = malloc(sizeof(Wire));
	w->signal_strength = 0.0;
	w->gradient = 0.0;
	w->pre = NULL;
	w->succ = NULL;

	return w;
}

// Frees a given wire
void free_wire(Wire* w) {
	free(w);
}

// Updates the signal strength of a wire to a given real value
void set_signal_strength(Wire* w, double s) {
	w->signal_strength = s;
}

// Returns the signal strength of a wire
double get_signal_strength(Wire* w) {
	return w->signal_strength;
}

// Stores a link to a neuron inside a wire as its successor
void set_successor(Wire* w, Neuron* n) {
	w->succ = n;
}

// Returns a link to a wire's successor
Neuron* get_successor(Wire* w) {
	return w->succ;
}

// Stores a link to a neuron inside a wire as its predecessor
void set_predecessor(Wire* w, Neuron* n) {
	w->pre = n;
}

// Returns a link to a wire's predecessor
Neuron* get_predecessor(Wire* w) {
	return w->pre;
}

void set_gradient(Wire* w, double x) {
	w->gradient = x;
}

double get_gradient(Wire* w) {
	return w->gradient;
}
