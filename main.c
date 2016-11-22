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
	const int NUM_NEURONS_PER_HIDDEN_LAYER = 4;
	ActFunction* ACT_FUNCTION = SIGMOID;

	const int NUM_INPUTS = 2;
	const int NUM_OUTPUTS = 3;
	
	const int MAX_NUM_TRAINING_ROUNDS = 100000000;
	double BACKPROP_STEP_SIZE = 0.10;
	double MAX_BACKPROP_SCALING = 10.0;
	double MAX_ERROR = 1.0;
	double MIN_ERROR_DELTA = 0.000001;

	const int MAP_WIDTH = 1600;
	const int MAP_HEIGHT = 900;

	// Suppose we want to learn the RGB components of a pixel of an image
	double* first_target = malloc( 3 * sizeof(double));
	first_target[0] = 220.0;
	first_target[1] = 10.0;
	first_target[2] = 1.0;

	double* first_pixel = malloc( 2 * sizeof(double) );
	first_pixel[0] =  1;
	first_pixel[1] =  1;

	double* second_target = malloc( 3 * sizeof(double));
	second_target[0] = 15.0;
	second_target[1] = 1.0;
	second_target[2] = 221.0;

	double* second_pixel = malloc( 2 * sizeof(double) );
	second_pixel[0] =  1600;
	second_pixel[1] =  900;

	BACKPROP_STEP_SIZE /= (MAP_WIDTH * MAP_HEIGHT * NUM_NEURONS_PER_HIDDEN_LAYER * NUM_HIDDEN_LAYERS);


	// Allocate and connect everything ... and I mean, everything ;)
	NeuronLayer* in = create_input(NUM_INPUTS,1, ID);
	NeuronLayer* out = create_output(NUM_OUTPUTS, ID);

	NeuronLayer** hidden = malloc( NUM_HIDDEN_LAYERS * sizeof(NeuronLayer*) );
	
	hidden[0] = alloc_neuron_layer(NUM_NEURONS_PER_HIDDEN_LAYER, ACT_FUNCTION);
	connect_layers(in, hidden[0]);
	connect_layers(hidden[0],out);
	connect_layers(in, out);

	for(int i = 1; i < NUM_HIDDEN_LAYERS; i++) {
		hidden[i] = alloc_neuron_layer(NUM_NEURONS_PER_HIDDEN_LAYER, ACT_FUNCTION);
		connect_layers(in, hidden[i]);
		connect_layers(hidden[i], out);
		for(int j = 0; j < i; j++) {
			connect_layers(hidden[j], hidden[i]);
		}
	}

	connect_layers(hidden[NUM_HIDDEN_LAYERS-1], out);


	// ===========================================================================
	// Insert magic here

	double* error_vector = malloc(NUM_OUTPUTS * sizeof(double));

	double total_error = 9999.9;
	double old_error = 0.0;
	int round = 1;

	double* res;
	double local_backprop_stepsize = 0.0;
	double scaling = 0.0;
	while(total_error > MAX_ERROR && round < MAX_NUM_TRAINING_ROUNDS) {

		scaling = 1.0 / fabs(delta(total_error, old_error)),10.0;
		scaling = (scaling > MAX_BACKPROP_SCALING) ? MAX_BACKPROP_SCALING : scaling;
		local_backprop_stepsize = BACKPROP_STEP_SIZE * scaling;
		old_error = total_error;

		// Train first pixel
		set_input(in, first_pixel);

		fire_all(in);
		for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
			fire_all(hidden[i]);
		}
		fire_all(out);
			
		res = get_output(out);
		error_vector[0] = first_target[0] - res[0];
		error_vector[1] = first_target[1] - res[1];
		error_vector[2] = first_target[2] - res[2];

		total_error = fabs(error_vector[0]) + fabs(error_vector[1]) + fabs(error_vector[2]);
		
		free(res);
		set_initial_gradient(out, error_vector);
		backprop_all(out, local_backprop_stepsize);
		for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
			backprop_all(hidden[i], local_backprop_stepsize);
		}
		backprop_all(in, local_backprop_stepsize);

		// Train second pixel
		set_input(in, second_pixel);

		fire_all(in);
		for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
			fire_all(hidden[i]);
		}
		fire_all(out);
			
		res = get_output(out);
		error_vector[0] = second_target[0] - res[0];
		error_vector[1] = second_target[1] - res[1];
		error_vector[2] = second_target[2] - res[2];

		total_error += fabs(second_target[0] - res[0]) + fabs(second_target[1] - res[1]) + fabs(second_target[2] - res[2]);

		set_initial_gradient(out, error_vector);
		backprop_all(out, local_backprop_stepsize);
		for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
			backprop_all(hidden[i], local_backprop_stepsize);
		}
		backprop_all(in, local_backprop_stepsize);


		if(round % 10000 == 0) {
			printf("%d | %d : ERROR:  %03.5f \t %03.5f \t %03.5f \t Total: %05.5f \t Backprop scaling %05.5f \n", round, MAX_NUM_TRAINING_ROUNDS, fabs(error_vector[0]), fabs(error_vector[1]), fabs(error_vector[2]), total_error, scaling);
		}
		free(res);

		//if(delta(old_error, total_error) < MIN_ERROR_DELTA) { break; }
		round++;
	}


	set_input(in, first_pixel);

	fire_all(in);
	for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
		fire_all(hidden[i]);
	}
	fire_all(out);
		
	res = get_output(out);
	printf("The network fired: %f | %f \t %f | %f \t %f | %f \n", first_target[0], res[0], first_target[1], res[1], first_target[2], res[2]);
	free(res);

	set_input(in, second_pixel);

	fire_all(in);
	for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
		fire_all(hidden[i]);
	}
	fire_all(out);
		
	res = get_output(out);
	printf("The network fired: %f | %f \t %f | %f \t %f | %f \n", second_target[0], res[0], second_target[1], res[1], second_target[2], res[2]);
	free(res);

	// Write the perceptive map to a file
	
	/*
	FILE *fp;
	fp = fopen("perceptive_map.ppm", "w");

	fprintf(fp, "P3\n%d %d\n255\n", MAP_WIDTH, MAP_HEIGHT);
	for(int i = 1; i <= MAP_WIDTH; i++) {
		if(i % 20 == 0 ) printf("Calculating (%d,x)\n",i);
		for(int j = 0; j <= MAP_HEIGHT; j++) {
			first_pixel[0] = i;
			first_pixel[1] = j;
			set_input(in, first_pixel);
			fire_all(in);
			for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
				fire_all(hidden[i]);
			}
			fire_all(out);
		
			res = get_output(out);

			fprintf(fp, "%d %d %d ", min(max((int)res[0],0),255), min(max((int)res[1],0),255), min(max((int)res[2],0),255) );
		}
		fprintf(fp,"\n");
	}

	fclose(fp);
	*/

	printf("Done!\n");

	// End of magic
	// ===========================================================================


	// Freeing stuff

	for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
		free_neuron_layer(hidden[i]);
	}
	free(error_vector);
	free(hidden);
	free_neuron_layer(in);
	free_neuron_layer(out);
	free(first_pixel);
	free(second_pixel);
	free(first_target);
	free(second_target);

	free_activation_functions();

	return EXIT_SUCCESS;
}
