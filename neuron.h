// Author .......... Felix Brei
// Creation Date ... 2016/11/01
// Last changed .... 2016/11/01

// Description
// -----------
// This file contains the neuron api that is to be used in the main program

// Local includes
#include "wire.h"

// START

#ifndef NEURON_H_
#define NEURON_H_

typedef struct _Neuron Neuron;

Neuron* alloc_neuron();
void free_neuron(Neuron* n);

void set_activation_function(Neuron*, double (*act)(double));
double fire(Neuron*);

void add_dendrite(Neuron*, Wire*);

#endif
