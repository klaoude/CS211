CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm
EXEC = TP1

all: $(EXEC)

TP1: main.o function.o
	$(CC) -o TP1 function.o main.o $(LDFLAGS)

function.o : function.c
	$(CC) -o function.o -c function.c $(CFLAGS)

main.o : main.c function.h
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o
