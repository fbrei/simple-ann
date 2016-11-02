CC=gcc
CFLAGS=-std=c99 -O0 -ggdb -lm
OUTFILE=s-ann

all:
	$(CC) $(CFLAGS) -o $(OUTFILE) main.c neuron.c wire.c
