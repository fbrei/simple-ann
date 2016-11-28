// Author .......... Felix Brei
// Creation Date ... 2016/11/28

// Description
// -----------
// This file contains the functions to maintain the config object

// The usual header guard

#ifndef NET_CONFIG_H_
#define NET_CONFIG_H_

// Local includes
#include "typedefs.h"

// START

// Allocate and free a config object
NetConfig* alloc_net_config();
void free_net_config(NetConfig* nc);

// Getters and setters

void set_num_inputs(NetConfig*,int);
int get_num_inputs(NetConfig*);

void set_num_outputs(NetConfig*,int);
int get_num_outputs(NetConfig*);

void set_num_hidden_layers(NetConfig*,int);
int get_num_hidden_layers(NetConfig*);

void set_num_neurons_per_layer(NetConfig*,int);
int get_num_neurons_per_layer(NetConfig*);

void set_backprop_step_size(NetConfig*,double);
double get_backprop_step_size(NetConfig*);

void set_act_function(NetConfig*,ActFunction*);
ActFunction* get_act_function(NetConfig*);

void set_output_function(NetConfig*, ActFunction*);
ActFunction* get_output_function(NetConfig*);

#endif
