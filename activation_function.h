// Author .......... Felix Brei
// Creation Date ... 2016/11/03
// Last changed .... 2016/11/11

// Description
// -----------
// This file contains a ready-to-use collection of popular activation functions

// The usual header guard

#ifndef ACTIVATION_FUNCTIONS_H_
#define ACTIVATION_FUNCTIONS_H_

// System includes

// Local includes
#include "typedefs.h"

// START

// Identity function (a.k.a. 'do nothing')
ActFunction* ID;

// Infamous sigmoid function ('squashing function')
ActFunction* SIGMOID;

// Initialize the default activation functions
void init_activation_functions();

// Clean up after you are done
void free_activation_functions();

// Calculate the value of a function
double calculate_value(ActFunction*, double);

// Calculate the gradient
double calculate_gradient(ActFunction*, double);

#endif
