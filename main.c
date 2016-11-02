// Author .......... Felix Brei
// Creation Date ... 2016/11/01
// Last changed .... 2016/11/01

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


// START

double id(double x) { return x; }
double sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); }


int main(int argc, char** argv) {

	Neuron* n = alloc_neuron();
	set_activation_function(n,&sigmoid);

	Wire* x = alloc_wire();
	Wire* y = alloc_wire();

	add_dendrite(n,x);
	add_dendrite(n,y);

	set_signal_strength(x,4.0);
	set_signal_strength(y,1.0);

	double out = fire(n);
	printf("Neuron fired: %f\n",out);

	free_neuron(n);

	return EXIT_SUCCESS;
}
