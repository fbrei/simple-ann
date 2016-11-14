CC=gcc
CFLAGS=-std=c99 -O0 -ggdb -lm
RUNFLAGS=-std=c99 -Ofast -lm 
OUTFILE=s-ann
SOURCEFILES=main.c neuron.c wire.c activation_function.c neuron_layer.c

all:
	$(CC) $(CFLAGS) -o $(OUTFILE) $(SOURCEFILES)

testrun: all
	valgrind --track-origins=yes --leak-check=full ./$(OUTFILE)

quickrun:
	$(CC) $(RUNFLAGS) -o $(OUTFILE) $(SOURCEFILES)
	strip $(OUTFILE)
	./$(OUTFILE)
