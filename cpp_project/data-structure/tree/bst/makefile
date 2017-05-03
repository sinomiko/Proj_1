CC = gcc
CCFLAGS = -g -Wall -std=c99
LDFLAGS = -pthread 

bst: bst.o
	$(CC) $(CCFLAGS) -o bst bst.o -pthread

bst.o: bst.c
	$(CC) $(CCFLAGS) -c bst.c -pthread

clean : 
	- rm  *.o
	- rm bst
