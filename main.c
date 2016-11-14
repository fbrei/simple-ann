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

int main(int argc, char** argv) {

	// Preparation
	time_t t;
	srand((unsigned) time(&t));
	init_activation_functions();

	// Configuration variables
	const int NUM_HIDDEN_LAYERS = 6;
	const int NUM_NEURONS_PER_HIDDEN_LAYER = 256;
	ActFunction* ACT_FUNCTION = ID;

	const int NUM_INPUTS = 2;
	const int NUM_OUTPUTS = 3;
	
	const int MAX_NUM_TRAINING_ROUNDS = 50;
	double BACKPROP_STEP_SIZE = 0.0000000001;
	double MAX_ERROR = 0.01;

	const int MAP_HEIGHT = 50;
	const int MAP_WIDTH = 50;

	// Suppose we want to learn the RGB components of a pixel of an image
	double* target = malloc( 3 * sizeof(double));
	target[0] = 20.0;
	target[1] = 10.0;
	target[2] = 200.0;

	double* pixel = malloc( 2 * sizeof(double) );
	pixel[0] =  25;
	pixel[1] =  25;

	BACKPROP_STEP_SIZE /= (pixel[0] * pixel[1]);


	// Allocate and connect everything ... and I mean, everything ;)
	NeuronLayer* in = create_input(NUM_INPUTS,1, ACT_FUNCTION);
	NeuronLayer* out = create_output(NUM_OUTPUTS, ACT_FUNCTION);

	NeuronLayer** hidden = malloc( NUM_HIDDEN_LAYERS * sizeof(NeuronLayer*) );
	
	hidden[0] = alloc_neuron_layer(NUM_NEURONS_PER_HIDDEN_LAYER, ACT_FUNCTION);
	connect_layers(in, hidden[0]);

	for(int i = 1; i < NUM_HIDDEN_LAYERS; i++) {
		hidden[i] = alloc_neuron_layer(NUM_NEURONS_PER_HIDDEN_LAYER, ACT_FUNCTION);
		for(int j = 0; j < i; j++) {
			connect_layers(hidden[j], hidden[i]);
		}
	}

	connect_layers(hidden[NUM_HIDDEN_LAYERS-1], out);


	// ===========================================================================
	// Insert magic here

	set_input(in, pixel);

	fire_all(in);
	for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
		fire_all(hidden[i]);
	}
	fire_all(out);

	double* res = get_output(out);

	printf("The network fired: %f | %f | %f \n", res[0], res[1], res[2]);
	free(res);

	double* error_vector = malloc(NUM_OUTPUTS * sizeof(double));

//	for(int i = 0; i < NUM_TRAINING_ROUNDS; i++) {

	double total_error = 9999.9;
	int round = 1;

	while(total_error > MAX_ERROR && round < MAX_NUM_TRAINING_ROUNDS) {
			
		res = get_output(out);
		error_vector[0] = target[0] - res[0];
		error_vector[1] = target[1] - res[1];
		error_vector[2] = target[2] - res[2];

		total_error = fabs(error_vector[0]) + fabs(error_vector[1]) + fabs(error_vector[2]);

		printf("%d | %d : ERROR:  %f \t %f \t %f\n", round, MAX_NUM_TRAINING_ROUNDS, fabs(error_vector[0]), fabs(error_vector[1]), fabs(error_vector[2]));
		free(res);

		set_initial_gradient(out, error_vector);
		backprop_all(out, BACKPROP_STEP_SIZE);
		for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
			backprop_all(hidden[i], BACKPROP_STEP_SIZE);
		}
		backprop_all(in, BACKPROP_STEP_SIZE);
	
		fire_all(in);
		for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
			fire_all(hidden[i]);
		}
		fire_all(out);
	
		round++;
	}


	res = get_output(out);

	printf("The network fired: %f | %f | %f \n", res[0], res[1], res[2]);




	// Write the perceptive map to a file
	/*
	
	FILE *fp;
	fp = fopen("perceptive_map.ppm", "w");

	fprintf(fp, "P3\n%d %d\n255\n", MAP_HEIGHT, MAP_WIDTH);
	for(int i = 1; i <= MAP_WIDTH; i++) {
		for(int j = 0; j <= MAP_HEIGHT; j++) {
			pixel[0] = i;
			pixel[1] = j;
			set_input(in, pixel);
			fire_all(in);
			for(int i = 0; i < NUM_HIDDEN_LAYERS; i++) {
				fire_all(hidden[i]);
			}
			fire_all(out);
		
			res = get_output(out);

			printf("Calculating (%d,%d)\n",i,j);
			fprintf(fp, "%d %d %d ", min((int)res[0],255), min((int)res[1],255), min((int)res[2],255) );
		}
		fprintf(fp,"\n");
	}


	fclose(fp);
	*/

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
	free(pixel);
	free(res);
	free(target);

	free_activation_functions();

	return EXIT_SUCCESS;
}
