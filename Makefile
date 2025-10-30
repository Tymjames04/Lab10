CC=g++
CFLAGS= -c -Wall

all: lab10

lab10: lab10.o
	$(CC) lab10.o -o lab10
	rm -rf *.o

lab10.o: lab10.cpp
	$(CC) $(CFLAGS) lab10.cpp

clean:
	rm lab10
