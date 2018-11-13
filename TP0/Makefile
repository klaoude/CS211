CC = gcc
CFLAGS = -std=c99 -Wall -g
LDFLAGS =
EXEC = TP0

all: $(EXEC)

$(EXEC): fonctions.o main.o
	$(CC) -o $(EXEC) fonctions.o main.o $(LDFLAGS)

fonctions.o : fonctions.h
	$(CC) -o fonctions.o -c fonctions.c $(CFLAGS)

main.o : main.c fonctions.c
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o
