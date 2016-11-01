CC=gcc
CFLAGS=-std=c99
OUTFILE=s-ann

all:
	$(CC) $(CFLAGS) -o $(OUTFILE) main.c
