// Author .......... Felix Brei
// Creation Date ... 2016/11/01
// Last changed .... 2016/11/03

// Description
// -----------
// This file contains the main function and serves as the entry point to the program

// System includes
#include <stdlib.h>				// Contains useful constants
#include <stdio.h>				// printf

// Local includes
#include "neuron.h"
#include "wire.h"
#include "activation_functions.h"


// START

int main(int argc, char** argv) {

	// Create an empty neuron
	Neuron* n = alloc_neuron();

	// Set the activation function from a predefined selection
	set_activation_function(n, SIGMOID);

	// Allocate two dendrites as input ...
	Wire* x = alloc_wire();
	Wire* y = alloc_wire();

	// ... and one synapse as output
	Wire* out = alloc_wire();

	// Connect the dendrites and synapses to the neuron
	add_dendrite(n,x);
	add_dendrite(n,y);

	add_synapse(n,out);

	// Set an arbitrary signal strength (just for testing)
	// At some (hopefully not so distant) point of time in the future this will be the output of another neuron
	set_signal_strength(x, 3.0);
	set_signal_strength(y, -1.0);

	// 'Run' the neuron
	fire(n);

	// Collect the output
	double z = get_signal_strength(out);
	printf("Neuron fired: %f\n",z);

	// Destroy the neuron
	free_neuron(n);

	// Yay!
	return EXIT_SUCCESS;
}
