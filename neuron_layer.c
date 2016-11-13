// Author .......... Felix Brei
// Creation Date ... 2016/11/12
// Last changed .... 2016/11/13

// Description
// -----------
// This file contains the actual code for the neuron layers

// System includes
#include <stdlib.h>

// Local includes
#include "neuron_layer.h"
#include "neuron.h"
#include "wire.h"

// START

struct _NeuronLayer {
	Neuron** neurons;
	int num_neurons;
};

NeuronLayer* alloc_neuron_layer(int num_neurons, ActFunction* act) {

	NeuronLayer* nl = malloc(sizeof(NeuronLayer));
	nl->neurons = malloc( num_neurons * sizeof(Neuron*) );

	for(int i = 0; i < num_neurons; i++) {
		nl->neurons[i] = alloc_neuron();
		set_activation_function(nl->neurons[i], act);
	}

	nl->num_neurons = num_neurons;

	return nl;
}

void free_neuron_layer(NeuronLayer* nl) {

	for(int i = 0; i < nl->num_neurons; i++) {
		free_neuron(nl->neurons[i]);
	}
	free(nl->neurons);

	free(nl);

}

void connect_layers(NeuronLayer* src, NeuronLayer* dest) {

	int num_src_neurons = src->num_neurons;
	int num_dest_neurons = dest->num_neurons;

	for(int i = 0; i < num_src_neurons; i++) {
		for(int j = 0; j < num_dest_neurons; j++) {
			connect(src->neurons[i], dest->neurons[j]);
		}	
	}

}

NeuronLayer* create_input(int num_neurons, int inputs_per_neuron, ActFunction* act) {

	NeuronLayer* nl = malloc(sizeof(NeuronLayer));
	nl->neurons = malloc( num_neurons * sizeof(Neuron*) );
	nl->num_neurons = num_neurons;

	for(int i = 0; i < num_neurons; i++) {
		Neuron* n = alloc_neuron();
		set_activation_function(n,act);
		for(int j = 0; j < inputs_per_neuron; j++) {
			Wire* w = alloc_wire();
			add_dendrite(n,w);
		}
		nl->neurons[i] = n;
	}

	return nl;
}

NeuronLayer* create_output(int num_neurons, ActFunction* act) {

	NeuronLayer* nl = malloc(sizeof(NeuronLayer));
	nl->neurons = malloc( num_neurons * sizeof(Neuron*) );
	nl->num_neurons = num_neurons;

	for(int i = 0; i < num_neurons; i++) {
		Neuron* n = alloc_neuron();
		set_activation_function(n,act);
		Wire* w = alloc_wire();
		add_synapse(n,w);
		nl->neurons[i] = n;
	}

	return nl;
}
