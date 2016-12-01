// Author .......... Felix Brei
// Creation Date ... 2016/11/11

// Description
// -----------
// This file contains the functionality that is needed to store activation functions. Plus, it defines some of them

// System includes
#include <stdlib.h>
#include <math.h>		// double exp(double)

// Local includes
#include "activation_function.h"

// START

struct _ActFunction {
	double (*fnct)(double);
	double (*grad)(double);
};

// The identity function
double id(double x) { return x; }
double id_grad(double x) { return 1.0; }

// Widely used sigmoid function ('squashing function')
double sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); }
double sigmoid_grad(double x) { return exp(-x) / ( (1.0 + exp(-x)) * (1.0 + exp(-x)) ); }

// The tanh function (even more powerful). The basic function is already defined in the math library!
double tanh_grad(double x) { double tx = tanh(x); return 1.0 - tx * tx; }

void init_activation_functions() {

	ID = malloc(sizeof(ActFunction));
	ID->fnct = &id;
	ID->grad = &id_grad;

	SIGMOID = malloc(sizeof(ActFunction));
	SIGMOID->fnct = &sigmoid;
	SIGMOID->grad = &sigmoid_grad;

	TANH = malloc(sizeof(ActFunction));
	TANH->fnct = &tanh;
	TANH->grad = &tanh_grad;
}

void free_activation_functions() {
	free(ID);
	free(SIGMOID);
	free(TANH);
}

double calculate_value(ActFunction* act, double x) { return act->fnct(x); }

// Calculate the gradient
double calculate_gradient(ActFunction* act, double x) { return act->grad(x); }
