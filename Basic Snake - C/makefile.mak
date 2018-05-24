CC=gcc
FLAGS=-I
DEPENDENCIES = header.h

%.o: %.c %(DEPENDENCIES)
	$(CC) -c -o $@ $< $(FLAGS)
	
csnake: main.o functions.o
	gcc -o csnake main.o functions.o -I