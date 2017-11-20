CC = gcc
CFLAGS = -std=c99 -g
LDFLAGS = -lm
EXEC = TP2

all: $(EXEC)

$(EXEC): main.o fat.o
	$(CC) -o $(EXEC) fat.o main.o $(LDFLAGS)

fat.o : fat.c
	$(CC) -o fat.o -c fat.c $(CFLAGS)

main.o : main.c fat.h
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o