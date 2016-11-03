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

	const int BACKPROP_STEP_SIZE = 0.001;

	// Create two input neurons
	Neuron* in1 = alloc_neuron();
	Neuron* in2 = alloc_neuron();

	// Create the output neuron
	Neuron* out = alloc_neuron();

	// Both input neurons get two inputs
	Wire* x1 = alloc_wire();
	Wire* y1 = alloc_wire();

	Wire* x2 = alloc_wire();
	Wire* y2 = alloc_wire();

	// Connect the inputs
	add_dendrite(in1,x1);
	add_dendrite(in1,y1);

	add_dendrite(in2,x2);
	add_dendrite(in2,y2);

	// Create the connections from input layer to output layer
	Wire* z1 = alloc_wire();
	Wire* z2 = alloc_wire();

	add_synapse(in1,z1);
	add_synapse(in2,z2);

	add_dendrite(out,z1);
	add_dendrite(out,z2);

	// Create an output synapse
	Wire* res = alloc_wire();
	add_synapse(out,res);

	// Set the activation functions (we use identity for easy debugging)
	set_activation_function(in1, ID);
	set_activation_function(in2, ID);
	set_activation_function(out, ID);

	// Set the input values, arbitrary
	set_signal_strength(x1, 1.0);
	set_signal_strength(y1, 2.0);

	set_signal_strength(x2, 3.0);
	set_signal_strength(y2, 4.0);

	// Launch the neurons!
	fire(in1);
	fire(in2);
	fire(out);

	// Read from the out synapse
	double result = get_signal_strength(res);

	printf("The network calculated: %f\n", result);

	// Cleanup
	free_neuron(out);
	free_neuron(in1);
	free_neuron(in2);

	// Yay!
	return EXIT_SUCCESS;
}
