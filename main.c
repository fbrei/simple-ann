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
	const int NUM_HIDDEN_LAYERS = 1;
	const int NUM_NEURONS_PER_HIDDEN_LAYER = 32;
	ActFunction* ACT_FUNCTION = SIGMOID;

	const int NUM_INPUTS = 2;
	const int NUM_OUTPUTS = 3;
	
	const int MAX_NUM_TRAINING_ROUNDS = 10000000;
	double BACKPROP_STEP_SIZE = 0.00001;
	double MAX_BACKPROP_SCALING = 10.0;
	double MAX_ERROR = 3.0;

	const double STEPSIZE_REDUCTION_FACTOR = 0.1;
	const int MAX_STEPSIZE_REDUCTION_ITERATIONS = 1000;

	const int MAP_WIDTH = 1600;
	const int MAP_HEIGHT = 900;


	// Creating the config and setting up the neural net
	NetConfig* conf = alloc_net_config();
	
	set_num_inputs(conf, NUM_INPUTS);
	set_num_outputs(conf, NUM_OUTPUTS);

	set_num_hidden_layers(conf, NUM_HIDDEN_LAYERS);
	set_num_neurons_per_layer(conf, NUM_NEURONS_PER_HIDDEN_LAYER);

	set_act_function(conf, ACT_FUNCTION);
	set_output_function(conf, ID);

	set_backprop_step_size(conf, BACKPROP_STEP_SIZE);

	NeuralNet* nn = alloc_neural_net(conf);


	// Testing area, to be deleted
	double* trainings_input = malloc( 2*sizeof(double));
	trainings_input[0] = 60;
	trainings_input[1] = 90;

	double* trainings_output = malloc(3*sizeof(double));
	trainings_output[0] = 66;
	trainings_output[1] = 166;
	trainings_output[2] = 255;

	set_input_vector(nn, trainings_input);
	fire(nn);

	double* out = get_output_vector(nn);
	printf("Initial output: %lf | %lf | %lf\n", out[0], out[1], out[2]);
	free(out);

	train(nn, trainings_output);

	set_input_vector(nn, trainings_input);
	fire(nn);
	out = get_output_vector(nn);
	printf("Initial output: %lf | %lf | %lf\n", out[0], out[1], out[2]);
	free(out);
	

	free(trainings_input);
	free(trainings_output);
	// End of testing area


	free_neural_net(nn);
	free_net_config(conf);
	free_activation_functions();
	return EXIT_SUCCESS;
}
