CC = g++
CCFLAGS = -g -Wall -std=c++11
LDFLAGS = -pthread 

test: test.o
	$(CC) $(CCFLAGS) -o test test.o -pthread

test.o: test.cpp
	$(CC) $(CCFLAGS) -c test.cpp -pthread

clean : 
	- rm  *.o
	- rm test
