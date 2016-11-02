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

	// The activation function and its threshold
	double (*act)(double);
	double theta;
};

Neuron* alloc_neuron() {
	Neuron* n = malloc(sizeof(Neuron));

	n->dendrites = NULL;
	n->num_dendrites = 0;

	n->weights = NULL;

	n->synapses = NULL;
	n->num_synapses = 0;

	n->act = NULL;
	n->theta = 0.0;

	return n;
}

void free_neuron(Neuron* n) {
	for(int i = 0; i < n->num_dendrites; i++) {
		free_wire(n->dendrites[i]);
	}
	free(n->dendrites);
	free(n->weights);
	free(n);
}

void set_activation_function(Neuron* n, double (*act)(double)) {
	n->act = act;
}

double fire(Neuron* n) {
	double x = n->theta;
	for(int i = 0; i < n->num_dendrites; i++) {
		x += get_signal_strength(n->dendrites[i]) * n->weights[i];
	}

	return (*(n->act))(x);
}

void add_dendrite(Neuron* n, Wire* w) {
	if(n->num_dendrites == 0) {
		n->dendrites = malloc(sizeof(Wire*));
		n->dendrites[0] = w;
		n->weights = malloc(sizeof(double));
		n->weights[0] = 1.0;
	} else {
		Wire** new_dendrites = malloc( (n->num_dendrites+1) * sizeof(Wire*));
		double* new_weights = malloc( (n->num_dendrites+1) * sizeof(double));
		for(int i = 0; i < n->num_dendrites; i++) {
			new_dendrites[i] = n->dendrites[i];
			new_weights[i] = n->weights[i];
		}
		new_dendrites[n->num_dendrites] = w;
		new_weights[n->num_dendrites] = 1.0;

		free(n->weights);
		free(n->dendrites);
		n->weights = new_weights;
		n->dendrites = new_dendrites;
	}
	n->num_dendrites++;
}
