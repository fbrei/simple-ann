// Author .......... Felix Brei
// Creation Date ... 2016/11/12

// Description
// -----------
// This file contains the api for creating whole layers of neurons and connect them with other layers

// The usual header guard

#ifndef NEURON_LAYER_H_
#define NEURON_LAYER_H_

// System includes

// Local includes
#include "typedefs.h"

// START

// Takes the number of neurons and their activation functions as arguments
NeuronLayer* alloc_neuron_layer(int, ActFunction*);

// Create a designated input layer
NeuronLayer* create_input(int num_neurons, ActFunction*);

// Create a designated output layer (one output per neuron)
NeuronLayer* create_output(int num_neurons, ActFunction*);

// Frees a given neuron layer
void free_neuron_layer(NeuronLayer*);

// Fully connect two given layers
void connect_layers(NeuronLayer* src, NeuronLayer* dest);

// Fire all neurons in a layer
void fire_all(NeuronLayer*);

// Backprops through all neurons of a layer
void backprop_all(NeuronLayer*, double);
void reset_all(NeuronLayer*);

// Feed an input vector to an input layer. Assumes one input per neuron
void set_input(NeuronLayer*, double*);

// Combines the outputs of all neurons of a layer into a single vector
double* get_output(NeuronLayer*);

// Sets the initial gradient for the backpropagation
void set_initial_gradient(NeuronLayer*, double*);

#endif
