// Author .......... Felix Brei
// Creation Date ... 2016/11/01

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
void set_activation_function(Neuron*, ActFunction*);

// 'Run' the neuron
void fire_neuron(Neuron*);

// Register dendrites (inputs) and synapses (outputs) at a neuron
void add_dendrite(Neuron*, Wire*);
void add_synapse(Neuron*, Wire*);

// Remove a dendrite or synapse from a neuron
void remove_dendrite(Neuron*, Wire*);
void remove_synapse(Neuron*, Wire*);

// Connect source neuron to destination neuron (order important!)
void connect(Neuron* src, Neuron* dest);

// Adjust the weights of a neuron, scaled by step size
void backprop_neuron(Neuron*, double);

// Reset a given neuron to the last state
void reset(Neuron*);

// Allow access to inputs and outputs
int get_num_dendrites(Neuron*);
Wire** get_dendrites(Neuron*);

int get_num_synapses(Neuron*);
Wire** get_synapses(Neuron*);

#endif
