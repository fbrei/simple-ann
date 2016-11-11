// Author .......... Felix Brei
// Creation Date ... 2016/11/01
// Last changed .... 2016/11/03

// Description
// -----------
// This file contains the main function and serves as the entry point to the program

// System includes
#include <stdlib.h>				// Contains useful constants
#include <stdio.h>				// printf
#include <math.h>

// Local includes
#include "neuron.h"
#include "wire.h"
#include "activation_function.h"

// START

int main(int argc, char** argv) {

	init_activation_functions();

	Neuron* n = alloc_neuron();
	set_activation_function(n, SIGMOID);

	Wire *x = alloc_wire();
	add_dendrite(n,x);

	Wire* y = alloc_wire();
	add_dendrite(n,y);

	Wire* z = alloc_wire();
	add_synapse(n,z);

	set_signal_strength(x,2.0);
	set_signal_strength(y,-1.0);

	fire(n);

	double res = get_signal_strength(z);

	printf("sigmoid(%f) = %f\n", 1.0, res);

	free_neuron(n);

	free_activation_functions();

	return EXIT_SUCCESS;
}
