// Author .......... Felix Brei
// Creation Date ... 2016/11/12
// Last changed .... 2016/11/12

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

// Frees a given neuron layer
void free_neuron_layer(NeuronLayer*);

void connect_layers(NeuronLayer* src, NeuronLayer* dest);

#endif
