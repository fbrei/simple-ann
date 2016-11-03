// Author .......... Felix Brei
// Creation Date ... 2016/11/03
// Last changed .... 2016/11/03

// Description
// -----------
// This file contains a ready-to-use collection of popular activation functions

// System includes
#include <math.h>		// contains exp(x)

// START

#ifndef ACTIVATION_FUNCTIONS_H_
#define ACTIVATION_FUNCTIONS_H_

// The identity function
double id(double x) { return x; }

// Widely used sigmoid function ('squashing function')
double sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); }

// Jump function 0->1 at x = 0
double binary(double x) { return (x > 0.0) ? 1.0 : 0.0; }

double (*ID)(double) = &id;
double (*SIGMOID)(double) = &sigmoid;
double (*BINARY)(double) = &binary;

#endif
