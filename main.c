// Author .......... Felix Brei
// Creation Date ... 2016/11/01
// Last changed .... 2016/11/01

// Description
// -----------
// This file contains the main function and serves as the entry point to the program

// System includes
#include <stdlib.h>				// Contains useful constants
#include <stdio.h>				// printf

// Local includes
#include "neuron.h"


// START


int main(int argc, char** argv) {

	Neuron* n = alloc_neuron();

	free_neuron(n);

	return EXIT_SUCCESS;
}
