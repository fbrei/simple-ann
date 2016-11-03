// Author .......... Felix Brei
// Creation Date ... 2016/11/01
// Last changed .... 2016/11/03

// Description
// -----------
// This file contains the neuron api that is to be used in the main program

// The usual header guard

#ifndef NEURON_H_
#define NEURON_H_

// Local includes
#include "typedefs.h"

// START

// Allocate and free a neuron
Neuron* alloc_neuron();
void free_neuron(Neuron* n);

// Define the activation function
void set_activation_function(Neuron*, double (*act)(double));

// 'Run' the neuron
void fire(Neuron*);

// Register dendrites (inputs) and synapses (outputs) at a neuron
void add_dendrite(Neuron*, Wire*);
void add_synapse(Neuron*, Wire*);

#endif
