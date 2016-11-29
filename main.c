// Author .......... Felix Brei
// Creation Date ... 2016/11/01

// Description
// -----------
// This file contains the main function and serves as the entry point to the program

// System includes
#include <stdlib.h>				// Contains useful constants
#include <stdio.h>				// printf
#include <math.h>
#include <time.h>

// Local includes
#include "activation_function.h"
#include "neural_net.h"
#include "net_config.h"

// START

int min(int x, int y) { return (x < y) ? x : y; }
int max(int x, int y) { return (x < y) ? y : x; }
double delta(double x, double y) { return fabs(x-y); }

int main(int argc, char** argv) {

	// Preparation
	time_t t;
	srand((unsigned) time(&t));
	init_activation_functions();

	// Configuration variables
	const int NUM_HIDDEN_LAYERS = 3;
	const int NUM_NEURONS_PER_HIDDEN_LAYER = 8;
	ActFunction* ACT_FUNCTION = SIGMOID;

	const int NUM_INPUTS = 2;
	const int NUM_OUTPUTS = 3;
	
	const int MAX_NUM_TRAINING_ROUNDS = 10000000;
	double BACKPROP_STEP_SIZE = 1.0;

	const double STEPSIZE_REDUCTION_FACTOR = 0.1;

	// Creating the config and setting up the neural net
	NetConfig* conf = alloc_net_config();
	
	set_num_inputs(conf, NUM_INPUTS);
	set_num_outputs(conf, NUM_OUTPUTS);

	set_num_hidden_layers(conf, NUM_HIDDEN_LAYERS);
	set_num_neurons_per_layer(conf, NUM_NEURONS_PER_HIDDEN_LAYER);

	set_act_function(conf, ACT_FUNCTION);
	set_output_function(conf, ID);

	set_backprop_step_size(conf, BACKPROP_STEP_SIZE);

	set_step_size_reduction(conf, STEPSIZE_REDUCTION_FACTOR);

	NeuralNet* nn = alloc_neural_net(conf);


	// Testing area, to be deleted
	double* trainings_input = malloc( 2*sizeof(double));
	trainings_input[0] = 60;
	trainings_input[1] = 90;

	double* trainings_output = malloc(3*sizeof(double));
	trainings_output[0] = 255;
	trainings_output[1] = 0;
	trainings_output[2] = 255;

	set_input_vector(nn, trainings_input);
	fire(nn);

	double* out = get_output_vector(nn);
	printf("Initial output: %lf | %lf | %lf\n", out[0], out[1], out[2]);
	free(out);

	for(int i = 0; i < 20; i++) {
		train(nn, trainings_input, trainings_output);
		out = get_output_vector(nn);
		printf("Round %d: %lf | %lf | %lf\n", i+1, out[0], out[1], out[2]);
		free(out);
	}


	free(trainings_input);
	free(trainings_output);
	// End of testing area


	free_neural_net(nn);
	free_activation_functions();
	return EXIT_SUCCESS;
}
