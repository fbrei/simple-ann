// Author .......... Felix Brei
// Creation Date ... 2016/11/28

// Description
// -----------
// This file contains the code to create a config object for the neural net

// System includes
#include <stdlib.h>				// Contains useful constants

// Local includes
#include "net_config.h"

struct _NetConfig {

	int NUM_INPUTS;
	int NUM_OUTPUTS;

	int NUM_HIDDEN_LAYERS;
	int NUM_NEURONS_PER_LAYER;

	double BACKPROP_STEP_SIZE;

	ActFunction* ACT_FUNCTION;
	ActFunction* OUTPUT_FUNCTION;
};


NetConfig* alloc_net_config() {
	return malloc(sizeof(NetConfig));
}

void free_net_config(NetConfig* nc) {
	free(nc);
}

void set_num_inputs(NetConfig* nc, int n) { nc->NUM_INPUTS = n; }
int get_num_inputs(NetConfig* nc) { return nc->NUM_INPUTS; }

void set_num_outputs(NetConfig* nc, int n) { nc->NUM_OUTPUTS = n; }
int get_num_outputs(NetConfig* nc) { return nc->NUM_OUTPUTS; }

void set_num_hidden_layers(NetConfig* nc, int n) { nc->NUM_HIDDEN_LAYERS = n; }
int get_num_hidden_layers(NetConfig* nc) { return nc->NUM_HIDDEN_LAYERS; }

void set_num_neurons_per_layer(NetConfig* nc, int n) { nc->NUM_NEURONS_PER_LAYER = n; }
int get_num_neurons_per_layer(NetConfig* nc) { return nc->NUM_NEURONS_PER_LAYER; }

void set_backprop_step_size(NetConfig* nc, double x) { nc->BACKPROP_STEP_SIZE = x; }
double get_backprop_step_size(NetConfig* nc) { return nc->BACKPROP_STEP_SIZE; }

void set_act_function(NetConfig* nc, ActFunction* act) { nc->ACT_FUNCTION = act; }
ActFunction* get_act_function(NetConfig* nc) { return nc->ACT_FUNCTION; }

void set_output_function(NetConfig* nc, ActFunction* act) { nc->OUTPUT_FUNCTION = act; }
ActFunction* get_output_function(NetConfig* nc) { return nc->OUTPUT_FUNCTION; }
