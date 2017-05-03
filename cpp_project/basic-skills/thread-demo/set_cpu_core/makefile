CC = gcc
CCFLAGS = -g -Wall
LDFLAGS = -pthread 

main: main.o
	$(CC) $(CCFLAGS) -o main main.o -pthread

main.o: main.c
	$(CC) $(CCFLAGS) -c main.c -pthread

clean : 
	- rm  *.o
	- rm main
