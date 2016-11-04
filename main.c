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

double delta(double x, double y) {
	return (x > y) ? x - y : y - x;
}

// START

int main(int argc, char** argv) {

	const double BACKPROP_STEP_SIZE = 0.0001;

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
	connect(in1,out);
	connect(in2,out);

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

	printf("The network calculated: %f\n", result); // 10

	// We want higher results, so ...
	set_gradient(res, -1.0);
	backprop(out, BACKPROP_STEP_SIZE);
	backprop(in1, BACKPROP_STEP_SIZE);
	backprop(in2, BACKPROP_STEP_SIZE);

	fire(in1);
	fire(in2);
	fire(out);
	result = get_signal_strength(res);
	
	printf("The network calculated: %f\n", result); // 10

	// Now let's train the network to produce a goal value as output (just for fun)
	double goal = 25.0;

	double force = 0.0;
	for(int i = 0; i < 10000; i++) {
		result = get_signal_strength(res);
		force = (result > goal) ? -1.0 : 1.0;
		set_gradient(res, force);

		backprop(out, BACKPROP_STEP_SIZE);
		backprop(in1, BACKPROP_STEP_SIZE);
		backprop(in2, BACKPROP_STEP_SIZE);

		fire(in1);
		fire(in2);
		fire(out);

		if(delta(result,goal) < 0.01) {
			printf("Done after %d rounds: %f\n", i, result);
			break;
		}
	}


	// Cleanup
	free_neuron(out);
	free_neuron(in1);
	free_neuron(in2);

	// Yay!
	return EXIT_SUCCESS;
}
