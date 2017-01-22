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
	ActFunction* ACT_FUNCTION = ID;

	const int NUM_INPUTS = 2;
	const int NUM_OUTPUTS = 3;
	
	const int MAX_NUM_TRAINING_ROUNDS = 1000000;
	double BACKPROP_STEP_SIZE = 0.0000000001;

	const double STEPSIZE_REDUCTION_FACTOR = 0.1;

	//const int OUTPUT_IMAGE_REFRESH_INTERVAL = width * height * 0.1;
	const int OUTPUT_IMAGE_REFRESH_INTERVAL = 100;

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
	FILE* image_file = fopen("square.ppm", "r");
	char format[2];
	fscanf(image_file, "%s\n", format);

	char width_text[3], height_text[3];
	fscanf(image_file, "%s\n", width_text);
	fscanf(image_file, "%s\n", height_text);

	int width = atoi(width_text);
	int height = atoi(height_text);

	printf("Bildformat: %s\n", format);
	printf("Breite: %d\n", width);
	printf("Hoehe:  %d\n", height);
	fscanf(image_file, "%s\n", width_text);


	char tmp[3];
	printf("Reading image \n");

	int ***image = malloc(height * sizeof(int**));
	double*** inputs = malloc(height * sizeof(double**));

	for(int row = 0; row < height; row++) {
		image[row] = malloc(width * sizeof(int*));
		inputs[row] = malloc(width * sizeof(double*));

		for(int col = 0; col < width; col++) {
			image[row][col] = malloc(NUM_OUTPUTS * sizeof(int));
			inputs[row][col] = malloc(NUM_INPUTS * sizeof(double));
			for(int k = 0; k < NUM_OUTPUTS; k++) {
				fscanf(image_file, "%s\n", tmp);
				image[row][col][k] = (atoi(tmp) - 120) / 2;
			}
			inputs[row][col][0] =  20 * ((row / (0.5 * height)) - 1.0);
			inputs[row][col][1] =  20 * ((col / (0.5 * width)) - 1.0);
		}

		printf(".");
		//printf("%d\%\n", (int) ((100.0 * i) / width));
	}
	printf("100\%\n");
	fclose(image_file);


	double* trainings_input = malloc(NUM_INPUTS * sizeof(double));
	double* trainings_output = malloc(NUM_OUTPUTS * sizeof(double));

	for(int runs = 1; runs <= MAX_NUM_TRAINING_ROUNDS; runs++) {
		int lucky_row = rand() % height;
		int lucky_col = rand() % width;

		
		/*
		int n = rand() % 2;
		int n = runs % 2;
		if(n == 0) {
			lucky_row = 0;
			lucky_col = 0;
		} else {
			lucky_col = width-1;
			lucky_row = height-1;
		}
		*/

		/*
		printf("Training pixel : %d | %d\n", lucky_x, lucky_y);
		printf("Input vector   : %lf | %lf\n", inputs[lucky_x][lucky_y][0], inputs[lucky_x][lucky_y][1]);
		printf("Target vector  : %d | %d | %d\n", image[lucky_x][lucky_y][0], image[lucky_x][lucky_y][1], image[lucky_x][lucky_y][2]);
		*/


		trainings_input[0] = inputs[lucky_row][lucky_col][0];
		trainings_input[1] = inputs[lucky_row][lucky_col][1];
				
		trainings_output[0] = image[lucky_row][lucky_col][0];
		trainings_output[1] = image[lucky_row][lucky_col][1];
		trainings_output[2] = image[lucky_row][lucky_col][2];

		train(nn, trainings_input, trainings_output);

		/*
		if(runs % OUTPUT_IMAGE_REFRESH_INTERVAL == 0 || runs == 1) {
		
			printf("Writing result (run: %09d | %d)\n", runs, MAX_NUM_TRAINING_ROUNDS);

			char fname[10];
			sprintf(fname, "%09d.ppm",runs);
			FILE* res_file = fopen(fname, "w");
			fprintf(res_file, "P3\n%d\n%d\n255\n", width, height);
			double* out;
			for(int row = 0; row < height; row++) {
				for(int col = 0; col < width; col++) {
					trainings_input[0] = inputs[row][col][0];
					trainings_input[1] = inputs[row][col][1];

					set_input_vector(nn, trainings_input);
					fire(nn);
					out = get_output_vector(nn);
					int r = min(255,max(0,(out[0] * 2 + 120)*1));
					int g = min(255,max(0,(out[1] * 2 + 120)*2));
					int b = min(255,max(0,(out[2] * 2 + 120)*2));
					free(out);
		
					fprintf(res_file, "%d\n%d\n%d\n",r,g,b);
				}
			}
		
			fclose(res_file);
			printf("Done!\n");
		}
		*/
	}


	/*
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


	// End of testing area
	*/
	free(trainings_input);
	free(trainings_output);


	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			free(image[i][j]);
			free(inputs[i][j]);
		}
		free(image[i]);
		free(inputs[i]);
	}
	free(image);
	free(inputs);

	free_neural_net(nn);
	free_activation_functions();
	return EXIT_SUCCESS;
}
