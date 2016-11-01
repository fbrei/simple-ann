// Author .......... Felix Brei
// Creation Date ... 2016/11/01
// Last changed .... 2016/11/01

// Description
// -----------
// This file contains the functionality of the neuron

// System includes
#include <stdlib.h>				// Contains useful constants
#include <stdio.h>				// printf

// Local includes
#include "neuron.h"


// START

struct _Neuron {
	// Input values
	double x;
	double y;

	// Weights
	double a;
	double b;

	// Constant
	double c;
};

Neuron* alloc_neuron() {
	Neuron* n = malloc(sizeof(Neuron));
	n->x = 0;
	n->y = 0;
	n->a = 0;
	n->b = 0;
	n->c = 0;
	return n;
}

void free_neuron(Neuron* n) {
	free(n);
}
