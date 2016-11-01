// Author .......... Felix Brei
// Creation Date ... 2016/11/01
// Last changed .... 2016/11/01

// Description
// -----------
// This file contains the neuron api that is to be used in the main program


// START
// nothing yet

#ifndef NEURON_H_
#define NEURON_H_

typedef struct _Neuron Neuron;

Neuron* alloc_neuron();
void free_neuron(Neuron* n);

#endif
