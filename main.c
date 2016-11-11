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

	printf("sigmoid(1.0) = %f\n", calculate_value(SIGMOID, 1.0));
	printf("The gradient is: %f\n", calculate_gradient(SIGMOID, 1.0));

	free_activation_functions();

	return EXIT_SUCCESS;
}
