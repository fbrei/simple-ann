// Author .......... Felix Brei
// Creation Date ... 2016/11/28

// Description
// -----------
// This file contains the neural net api that is to be used in the main program

// The usual header guard

#ifndef NEURAL_NET_H_
#define NEURAL_NET_H_

// Local includes
#include "typedefs.h"

// START

// Allocate and free a neural net
NeuralNet* alloc_neural_net(NetConfig*);
void free_neural_net(NeuralNet* nn);

// Controlling what goes in and what comes out
void set_input_vector(NeuralNet*, double*);
double* get_output_vector(NeuralNet*);

void fire(NeuralNet*);

// After setting an input vector, train a network towards an output vector (once)
void train(NeuralNet*, double*);

#endif
