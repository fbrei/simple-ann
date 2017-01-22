// Author .......... Felix Brei
// Creation Date ... 2016/11/01

// Description
// -----------
// This file contains the functionality of the neuron

// System includes
#include <stdlib.h>				// Contains useful constants

// Local includes
#include "neuron.h"
#include "wire.h"
#include "activation_function.h"

// START

struct _Neuron {
	// The incoming signals (dendrites)
	Wire** dendrites;
	int num_dendrites;

	// The weight vector
	double* weights;
	double* old_weights;

	// The learning rates
	double* learning_rates;

	// The outgoing connections
	Wire** synapses;
	int num_synapses;

	// The activation function and its threshold
	ActFunction* act;
	double theta;
	double old_theta;
};

// Allocates a neuron without any functionality or connections (default)
Neuron* alloc_neuron() {
	Neuron* n = malloc(sizeof(Neuron));

	n->dendrites = NULL;
	n->num_dendrites = 0;

	n->weights = NULL;
	n->old_weights = NULL;

	n->learning_rates = NULL;

	n->synapses = NULL;
	n->num_synapses = 0;

	n->act = NULL;
	n->theta = 0.0;
	n->old_theta = 0.0;

	return n;
}

// Frees a given neuron and destroys all its dendrites and synapes too, since they would be loose ends otherwise
void free_neuron(Neuron* n) {
	for(int i = 0; i < n->num_dendrites; i++) {
		remove_synapse(get_predecessor(n->dendrites[i]), n->dendrites[i]);
		free_wire(n->dendrites[i]);
	}
	for(int i = 0; i < n->num_synapses; i++) {
		remove_dendrite(get_successor(n->synapses[i]), n->synapses[i]);
		free_wire(n->synapses[i]);
	}

	free(n->dendrites);
	free(n->weights);
	free(n->old_weights);

	free(n->learning_rates);

	free(n->synapses);

	free(n);
}

// Sets the activation function of a given neuron
void set_activation_function(Neuron* n, ActFunction* act) {
	n->act = act;
}

// Sums up all the (weighed) inputs and plugs the result into the activation function. The result is stored in all synapses
void fire_neuron(Neuron* n) {
	double x = n->theta;

	int num_dendrites = n->num_dendrites;
	int num_synapses = n->num_synapses;

	for(int i = 0; i < num_dendrites; i++) {
		x += get_signal_strength(n->dendrites[i]) * n->weights[i];
	}

	double output = calculate_value(n->act, x);
	for(int i = 0; i < num_synapses; i++) {
		set_signal_strength(n->synapses[i],output);
	}
}

// Adds a dendrite (input) to a neuron
void add_dendrite(Neuron* n, Wire* w) {
	if(n->num_dendrites == 0) {
		n->dendrites = malloc(sizeof(Wire*));
		n->dendrites[0] = w;

		n->weights = malloc(sizeof(double));
		n->weights[0] = 0.1 * ((double) rand()) / RAND_MAX;
	
		n->learning_rates = malloc(sizeof(double));
		n->learning_rates[0] = rand() / (double) RAND_MAX + 0.5;
	} else {
		Wire** new_dendrites = malloc( (n->num_dendrites+1) * sizeof(Wire*));
		double* new_weights = malloc( (n->num_dendrites+1) * sizeof(double));
		double* new_learning_rates = malloc( (n->num_dendrites+1) * sizeof(double));

		for(int i = 0; i < n->num_dendrites; i++) {
			new_dendrites[i] = n->dendrites[i];
			new_weights[i] = n->weights[i];
			new_learning_rates[i] = n->learning_rates[i];
		}
		new_dendrites[n->num_dendrites] = w;
		new_weights[n->num_dendrites] = (((double) rand()) / RAND_MAX) - 0.5;
		new_learning_rates[n->num_dendrites] = rand() / (double) RAND_MAX + 0.5;

		free(n->weights);
		free(n->dendrites);
		free(n->learning_rates);

		n->weights = new_weights;
		n->dendrites = new_dendrites;
		n->learning_rates = new_learning_rates;
	}

	set_successor(w, n);
	set_gradient(w, 1.0);
	n->num_dendrites++;
}

void remove_dendrite(Neuron* n, Wire* w) {

	if(n == NULL)
		return;

	int num_dendrites = n->num_dendrites;

	if( num_dendrites == 1) {

		free(n->weights);
		n->weights = NULL;
		free(n->dendrites);
		n->dendrites = NULL;
		n->num_dendrites = 0;

	} else if ( num_dendrites > 1 ) {
	
		int offset = 0;

		Wire** new_dendrites = malloc( (num_dendrites-1) * sizeof(Wire*) );

		double* new_weights = malloc( (num_dendrites-1) * sizeof(double) );
		for(int i = 0; i < num_dendrites - 1; i++) {
			if( n->dendrites[i] == w ) {
				offset = 1;
			}

			new_dendrites[i] = n->dendrites[i+offset];
			new_weights[i] = n->weights[i+offset];
		}

		free(n->weights);
		free(n->dendrites);
		n->weights =  new_weights;
		n->dendrites = new_dendrites;
		n->num_dendrites--;
	
	}
}

// Adds a synapse (output) to a neuron
void add_synapse(Neuron* n, Wire* w) {
	if(n->num_synapses == 0) {
		n->synapses = malloc(sizeof(Wire*));
		n->synapses[0] = w;
	} else {
		Wire** new_synapses = malloc( (n->num_synapses+1) * sizeof(Wire*));
		for(int i = 0; i < n->num_synapses; i++) {
			new_synapses[i] = n->synapses[i];
		}
		new_synapses[n->num_synapses] = w;
		free(n->synapses);
		n->synapses = new_synapses;
	}


	set_predecessor(w,n);
	n->num_synapses++;
}

void remove_synapse(Neuron* n, Wire* w) {
	
	if(n == NULL)
		return;

	int num_synapses = n->num_synapses;

	if( num_synapses == 1 ) {
		free(n->synapses);
		n->synapses = NULL;
		n->num_synapses = 0;
	} else if ( num_synapses > 1 ) {
	
		int offset = 0;

		Wire** new_synapses = malloc( (num_synapses-1) * sizeof(Wire*));
		
		for(int i = 0; i < num_synapses - 1; i++) {
			if( n->synapses[i] == w) {
				offset = 1;
			}

			new_synapses[i] = n->synapses[i+offset];
		}

		free(n->synapses);
		n->synapses = new_synapses;
		n->num_synapses--;
	}
	
}

void connect(Neuron* src, Neuron* dest) {
	Wire* w = alloc_wire();
	add_dendrite(dest, w);
	add_synapse(src,w);
}

void backprop_neuron(Neuron* n, double STEP_SIZE) {

	// Make a backup of old values
	if(n->old_weights != NULL)
		free(n->old_weights);

	n->old_weights = malloc(n->num_dendrites * sizeof(double) );
	for(int i = 0; i < n->num_dendrites; i++) {
		n->old_weights[i] = n->weights[i];
	}
	n->old_theta = n->theta;


	double incoming_gradient = 0.0;

	for(int i = 0; i < n->num_synapses; i++) {
		incoming_gradient += get_gradient(n->synapses[i]);
	}

	double net = 0.0;
	for(int i = 0; i < n->num_dendrites; i++) {
		net += get_signal_strength(n->dendrites[i]);
	} 
	double local_grad = calculate_gradient(n->act, net);

	n->theta += incoming_gradient * STEP_SIZE;
	for(int i = 0; i < n->num_dendrites; i++) {
		double weight = n->weights[i];
		double signal = get_signal_strength(n->dendrites[i]);
		n->weights[i] += incoming_gradient * STEP_SIZE  * signal * local_grad * n->learning_rates[i];
		set_signal_strength(n->dendrites[i], get_signal_strength(n->dendrites[i]) + incoming_gradient * STEP_SIZE * weight * local_grad * n->learning_rates[i]);
		set_gradient(n->dendrites[i], weight * local_grad );
	}
}


void reset_neuron(Neuron* n) {
	free(n->weights);
	n->weights = malloc(n->num_dendrites * sizeof(double));
	for(int i = 0; i < n->num_dendrites; i++) {
		n->weights[i] = n->old_weights[i];
	}

	n->theta = n->old_theta;
}


int get_num_dendrites(Neuron* n) { return n->num_dendrites; }
Wire** get_dendrites(Neuron* n) { return n->dendrites; }

int get_num_synapses(Neuron* n) { return n->num_synapses; }
Wire** get_synapses(Neuron* n) { return n->synapses; }
