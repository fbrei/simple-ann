// Author .......... Felix Brei
// Creation Date ... 2016/11/01
// Last changed .... 2016/11/13

// Description
// -----------
// This file contains the main function and serves as the entry point to the program

// System includes
#include <stdlib.h>				// Contains useful constants
#include <stdio.h>				// printf
#include <math.h>
#include <time.h>

// Local includes
#include "neuron.h"
#include "wire.h"
#include "activation_function.h"
#include "neuron_layer.h"

// START

int main(int argc, char** argv) {

	// Preparation
	time_t t;
	srand((unsigned) time(&t));
	init_activation_functions();

	// Configuration variables
	const int NUM_HIDDEN_LAYERS = 3;
	const int NUM_NEURONS_PER_HIDDEN_LAYER = 64;
	ActFunction* ACT_FUNCTION = ID;

	const int NUM_INPUTS = 2;
	const int NUM_OUTPUTS = 3;
	

	// Allocate and connect everything
	NeuronLayer* in = create_input(NUM_INPUTS,1, ACT_FUNCTION);
	NeuronLayer* out = create_output(NUM_OUTPUTS, ACT_FUNCTION);

	NeuronLayer** hidden = malloc( NUM_HIDDEN_LAYERS * sizeof(NeuronLayer*) );
	
	hidden[0] = alloc_neuron_layer(NUM_NEURONS_PER_HIDDEN_LAYER, ACT_FUNCTION);
	connect_layers(in, hidden[0]);

	for(int i = 1; i < NUM_HIDDEN_LAYERS; i++) {
		hidden[i] = alloc_neuron_layer(NUM_NEURONS_PER_HIDDEN_LAYER, ACT_FUNCTION);
		connect_layers(hidden[i-1], hidden[i]);
	}

	connect_layers(hidden[NUM_HIDDEN_LAYERS-1], out);


	// ===========================================================================
	// Insert magic here

	double* test = malloc(2 * sizeof(double));
	test[0] = 1.0;
	test[1] = 0.0;

	set_input(in, test);

	fire_all(in);
	for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
		fire_all(hidden[i]);
	}
	fire_all(out);

	double* res = get_output(out);

	printf("The network fired: %f | %f | %f \n", res[0], res[1], res[2]);
	free(res);

	backprop_all(out,-0.0001);
	for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
		backprop_all(hidden[i], -0.0001);
	}
	backprop_all(in, -0.0001);

	set_input(in, test);

	fire_all(in);
	for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
		fire_all(hidden[i]);
	}
	fire_all(out);

	res = get_output(out);

	printf("The network fired: %f | %f | %f \n", res[0], res[1], res[2]);


	free(test);
	free(res);

	// End of magic
	// ===========================================================================


	// Freeing stuff

	for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
		free_neuron_layer(hidden[i]);
	}
	free(hidden);
	free_neuron_layer(in);
	free_neuron_layer(out);

	free_activation_functions();

	return EXIT_SUCCESS;
}
