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
#include "wire.h"


// START

struct _Neuron {
	// The incoming signals (dendrites)
	Wire** dendrites;
	int num_dendrites;

	// The weight vector
	double* weights;

	// The outgoing connections
	Wire** synapses;
	int num_synapses;

	// The activation function
	double (*act)(double);
};

Neuron* alloc_neuron() {
	Neuron* n = malloc(sizeof(Neuron));

	n->dendrites = NULL;
	n->num_dendrites = 0;

	n->weights = NULL;

	n->synapses = NULL;
	n->num_synapses = 0;

	n->act = NULL;

	return n;
}

void free_neuron(Neuron* n) {
	free(n);
}
