CC = gcc
CFLAGS = -std=c99 -Wall -g
LDFLAGS = -lm
EXEC = TP1

all: $(EXEC)

TP1: main.o
	$(CC) -o TP1 main.o $(LDFLAGS)

main.o : main.c bitmap.h
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o