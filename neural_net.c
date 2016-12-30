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

	NetConfig* config;
};

// START

NeuralNet* alloc_neural_net(NetConfig* conf) {

	NeuralNet* nn = malloc(sizeof(NeuralNet));

	nn->in = create_input(get_num_inputs(conf), get_act_function(conf));
	nn->out = create_output(get_num_outputs(conf), get_output_function(conf));
	nn->config = conf;

	int num_hidden = get_num_hidden_layers(conf);
	nn->hidden = malloc( num_hidden * sizeof(NeuronLayer*));
	for(int i = 0; i < num_hidden; i++) {
		nn->hidden[i] = alloc_neuron_layer(get_num_neurons_per_layer(conf), get_act_function(conf));
	}

	connect_layers(nn->in, nn->hidden[0]);
	for(int i = 1; i < num_hidden; i++) {
		connect_layers(nn->hidden[i-1], nn->hidden[i]);
		for(int j = 0; j < i; j++) {
			connect_layers(nn->hidden[j], nn->hidden[i]);
		}
	}
	connect_layers(nn->hidden[num_hidden-1], nn->out);

	return nn;
}

void free_neural_net(NeuralNet* nn) {
	int num_layers = get_num_hidden_layers(nn->config);

	for(int i = 0; i < num_layers; i++) {
		free_neuron_layer(nn->hidden[i]);
	}
	free(nn->hidden);

	free_neuron_layer(nn->in);
	free_neuron_layer(nn->out);

	free_net_config(nn->config);

	free(nn);
}

void set_input_vector(NeuralNet* nn, double* in) {
	set_input(nn->in, in);
}

double* get_output_vector(NeuralNet* nn) {
	return get_output(nn->out);
}

void fire(NeuralNet* nn) {
	int num_layers = get_num_hidden_layers(nn->config);

	fire_all(nn->in);
	for(int i = 0; i < num_layers; i++) {
		fire_all(nn->hidden[i]);
	}
	fire_all(nn->out);
}

void backprop(NeuralNet* nn, double* err, double step_size) {
	int num_layers = get_num_hidden_layers(nn->config);

	set_initial_gradient(nn->out,err);
	backprop_all(nn->out, step_size);
	for(int i = num_layers; i > 0; i--) {
		backprop_all(nn->hidden[i-1], step_size);
	}
	backprop_all(nn->in, step_size);
}

void reset(NeuralNet* nn) {
	int num_layers = get_num_hidden_layers(nn->config);
	reset_all(nn->in);
	for(int i = 0; i < num_layers; i++) {
		reset_all(nn->hidden[i]);
	}
	reset_all(nn->out);
}

void train(NeuralNet* nn, double* input, double* target) {
	int num_outputs = get_num_outputs(nn->config);
	double step_size = (get_backprop_step_size(nn->config));
	double reduction = get_step_size_reduction(nn->config);

	step_size *= (rand() % 100000) + 1.0;

	set_input_vector(nn,input);
	fire(nn);

	double* out = get_output(nn->out);
	double* err = malloc(num_outputs * sizeof(double));
	double initial_error = 0.0;
	double abs_error = 0.0;
	for(int i = 0; i < num_outputs; i++) {
		err[i] = target[i] - out[i];
		abs_error = (err[i] > 0) ? err[i] : -err[i];
		initial_error += abs_error * abs_error;
	}

	backprop(nn,err,step_size);
	free(out);

	double new_error = initial_error + 1.0;

	while(new_error > initial_error) {
		new_error = 0.0;
		set_input_vector(nn,input);
		fire(nn);
	
		out = get_output(nn->out);
		for(int i = 0; i < num_outputs; i++) {
			abs_error = target[i] - out[i];
			new_error += abs_error * abs_error;
		}

		if(new_error > initial_error) {
			reset(nn);
			step_size *= reduction;
			backprop(nn,err,step_size);
		}

		free(out);
	}
		
	free(err);
}
