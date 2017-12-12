CC = gcc
CFLAGS = -std=c99 -g
LDFLAGS = 
EXEC = TP3

all: $(EXEC)

$(EXEC): main.o AlgoGenetique.o
	$(CC) -o $(EXEC) main.o AlgoGenetique.o $(LDFLAGS)

AlgoGenetique.o : AlgoGenetique.c
	$(CC) -o AlgoGenetique.o -c AlgoGenetique.c $(CFLAGS)

main.o : main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o
