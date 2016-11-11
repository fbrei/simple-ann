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
#include "activation_functions.h"

double delta(double x, double y) {
	return (x > y) ? x - y : y - x;
}

// START

void run_sample() {

	double BACKPROP_STEP_SIZE = 1.0;

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

	printf("We startoff with a 2-1 network, 1,2,3,4 as inputs\n");
	printf("=================================================\n");
	printf("The network calculated: %f\n\n", result); // 10

	// We want higher results, so ...
	set_gradient(res, 1.0);
	backprop(out, BACKPROP_STEP_SIZE);
	backprop(in1, BACKPROP_STEP_SIZE);
	backprop(in2, BACKPROP_STEP_SIZE);

	fire(in1);
	fire(in2);
	fire(out);
	result = get_signal_strength(res);
	
	printf("After pulling upwards with a strength of 1 the network now calculates (with still the same inputs)...\n");
	printf("=====================================================================================================\n");
	printf("The network calculated: %f\n\n", result); // 10

	// Now let's train the network to produce a goal value as output (just for fun)
	double goal = 15.0;

	// The force that pulls the network in a specific direction, depending on the correctness of the output
	double force = 0.0;

	printf("We now train the network to produce %f as goal output.\n",goal);
	printf("======================================================\n");
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

		if(delta(result,goal) < 0.00001) {
			printf("Done after %d rounds: %f\n\n", i, result);
			break;
		}
	}


	// Cleanup
	free_neuron(out);
	free_neuron(in1);
	free_neuron(in2);

	// Yay!

	printf("Now that was fun! Let's create another neuron, but this time it shall classify some data.\n");
	printf("=========================================================================================\n");
	Neuron* classifier = alloc_neuron();

	double** feature_vectors = malloc( 6 * sizeof(double*));
	for(int i = 0; i < 6; i++) {
		feature_vectors[i] = malloc(3 * sizeof(double));
	}

	// x and y input plus label
	feature_vectors[0][0] = 1.2;
	feature_vectors[0][1] = 0.7;
	feature_vectors[0][2] = 1.0;

	feature_vectors[1][0] = -0.3;
	feature_vectors[1][1] = 0.5;
	feature_vectors[1][2] = -1.0;

	feature_vectors[2][0] = -3.0;
	feature_vectors[2][1] = -1.0;
	feature_vectors[2][2] = 1.0;

	feature_vectors[3][0] = 0.1;
	feature_vectors[3][1] = 1.0;
	feature_vectors[3][2] = -1.0;

	feature_vectors[4][0] = 3.0;
	feature_vectors[4][1] = 1.1;
	feature_vectors[4][2] = -1.0;

	feature_vectors[5][0] = 2.1;
	feature_vectors[5][1] = -3.0;
	feature_vectors[5][2] = 1.0;

	Wire* class_x = alloc_wire();
	Wire* class_y = alloc_wire();

	add_dendrite(classifier, class_x);
	add_dendrite(classifier, class_y);

	Wire* class_out = alloc_wire();
	add_synapse(classifier, class_out);

	set_activation_function(classifier, ID);


	printf("Initial classification: prediction | real value\n");
	for(int i = 0; i < 6; i++) {
		set_signal_strength(class_x, feature_vectors[i][0]);
		set_signal_strength(class_y, feature_vectors[i][1]);
		fire(classifier);
		printf("\t\t%f | %f\n", get_signal_strength(class_out), feature_vectors[i][2]);
	}

	int correct = 0;
	int runs = 0;
	while(correct != 6) {
		runs++;

		// Some tests
		correct = 0;
		for(int j = 0; j < 6; j++) {
			set_signal_strength(class_x, feature_vectors[j][0]);
			set_signal_strength(class_y, feature_vectors[j][1]);
			fire(classifier);

			result = get_signal_strength(class_out);
			goal = feature_vectors[j][2];

			force = 0.0;
			correct++;
			if( result > -1.0 && goal == -1.0 ) {
				force = -1.0;
				correct--;
			}

			if( result < 1.0 && goal == 1.0 ) {
				force = 1.0;
				correct--;
			}

			set_gradient(class_out, force);
			backprop(classifier, BACKPROP_STEP_SIZE);

		}
	}


	printf("Classification after %d rounds of training: prediction | real value\n", runs);
	for(int i = 0; i < 6; i++) {
		set_signal_strength(class_x, feature_vectors[i][0]);
		set_signal_strength(class_y, feature_vectors[i][1]);
		fire(classifier);
		printf("\t\t%f | %f\n", get_signal_strength(class_out), feature_vectors[i][2]);
	}


	free_neuron(classifier);
	for(int i = 0; i < 6; i++) {
		free(feature_vectors[i]);
	}
	free(feature_vectors);

}
