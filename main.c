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

int main(int argc, char** argv) {


	return EXIT_SUCCESS;
}
