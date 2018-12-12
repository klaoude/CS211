CC = gcc
CFLAGS = -std=c99 -g
LDFLAGS = 
EXEC = FAT

all: $(EXEC)

$(EXEC): main.o fat.o term.o
	$(CC) -o $(EXEC) fat.o main.o term.o $(LDFLAGS)

fat.o : fat.c
	$(CC) -o fat.o -c fat.c $(CFLAGS)

term.o : term.c
	$(CC) -o term.o -c term.c $(CFLAGS)

main.o : main.c fat.h
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o
