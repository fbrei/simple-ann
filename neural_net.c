// Author .......... Felix Brei
// Creation Date ... 2016/11/28

// Description
// -----------
// This file contains the functionality of the neural net

// System includes
#include <stdlib.h>				// Contains useful constants

// Local includes
#include "neural_net.h"
#include "neuron_layer.h"
#include "net_config.h"

struct _NeuralNet {

	NeuronLayer* in;
	NeuronLayer* out;

	NeuronLayer** hidden;

	int NUM_INPUTS;
	int NUM_OUTPUTS;

	int NUM_HIDDEN_LAYERS;
	int NUM_NEURONS_PER_LAYER;

	double BACKPROP_STEP_SIZE;

	ActFunction* ACT_FUNCTION;
};

// START

NeuralNet* alloc_neural_net(NetConfig* conf) {

	NeuralNet* nn = malloc(sizeof(NeuralNet));

	nn->NUM_INPUTS = get_num_inputs(conf);
	nn->NUM_OUTPUTS = get_num_outputs(conf);

	nn->NUM_HIDDEN_LAYERS = get_num_hidden_layers(conf);
	nn->NUM_NEURONS_PER_LAYER = get_num_neurons_per_layer(conf);

	nn->BACKPROP_STEP_SIZE = get_backprop_step_size(conf);

	nn->in = create_input(get_num_inputs(conf), get_act_function(conf));
	nn->out = create_output(get_num_outputs(conf), get_output_function(conf));

	nn->hidden = malloc( nn->NUM_HIDDEN_LAYERS * sizeof(NeuronLayer*));
	for(int i = 0; i < nn->NUM_HIDDEN_LAYERS; i++) {
		nn->hidden[i] = alloc_neuron_layer(get_num_neurons_per_layer(conf), get_act_function(conf));
	}

	connect_layers(nn->in, nn->hidden[0]);
	for(int i = 1; i < nn->NUM_HIDDEN_LAYERS; i++) {
		connect_layers(nn->hidden[i-1], nn->hidden[i]);
	}
	connect_layers(nn->hidden[nn->NUM_HIDDEN_LAYERS-1], nn->out);

	return nn;
}

void free_neural_net(NeuralNet* nn) {
	int num_layers = nn->NUM_HIDDEN_LAYERS;

	for(int i = 0; i < num_layers; i++) {
		free_neuron_layer(nn->hidden[i]);
	}
	free(nn->hidden);

	free_neuron_layer(nn->in);
	free_neuron_layer(nn->out);

	free(nn);
}

void set_input_vector(NeuralNet* nn, double* in) {
	set_input(nn->in, in);
}

double* get_output_vector(NeuralNet* nn) {
	return get_output(nn->out);
}

void fire(NeuralNet* nn) {
	int num_layers = nn->NUM_HIDDEN_LAYERS;

	fire_all(nn->in);
	for(int i = 0; i < num_layers; i++) {
		fire_all(nn->hidden[i]);
	}
	fire_all(nn->out);
}

void backprop(NeuralNet* nn, double* err) {
	int num_layers = nn->NUM_HIDDEN_LAYERS;
	double step_size = nn->BACKPROP_STEP_SIZE;

	set_initial_gradient(nn->out,err);
	backprop_all(nn->out, step_size);
	for(int i = num_layers; i > 0; i--) {
		backprop_all(nn->hidden[i-1], step_size);
	}
	backprop_all(nn->in, step_size);
}

void train(NeuralNet* nn, double* target) {
	int num_outputs = nn->NUM_OUTPUTS;

	fire(nn);

	double* out = get_output(nn->out);
	double* err = malloc(num_outputs * sizeof(double));
	for(int i = 0; i < num_outputs; i++) {
		err[i] = target[i] - out[i];
	}

	backprop(nn,err);

	free(out);
	free(err);
}
