// Author .......... Felix Brei
// Creation Date ... 2016/11/01
// Last changed .... 2016/11/11

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
#include "neuron_layer.h"

// START

int main(int argc, char** argv) {

	init_activation_functions();
	
	NeuronLayer* first = alloc_neuron_layer(64, SIGMOID);
	NeuronLayer* second = alloc_neuron_layer(64, SIGMOID);
	NeuronLayer* third = alloc_neuron_layer(64, SIGMOID);

	connect_layers(first,second);
	connect_layers(first,third);
	connect_layers(second,third);

	free_neuron_layer(first);
	free_neuron_layer(second);
	free_neuron_layer(third);

	free_activation_functions();

	return EXIT_SUCCESS;
}
