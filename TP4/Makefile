CC = gcc
CFLAGS = -std=c99 -g
LDFLAGS = 
EXEC = TP4

all: $(EXEC)

$(EXEC): main.o Menu.o Morpion.o IA.o Multi.o
	$(CC) -o $(EXEC) *.o $(LDFLAGS)

Menu.o : Menu.c
	$(CC) -o $@ -c $< $(CFLAGS)

Morpion.o: Morpion.c
	$(CC) -o $@ -c $< $(CFLAGS)

IA.o: IA.c
	$(CC) -o $@ -c $< $(CFLAGS)

Multi.o: Multi.c
	$(CC) -o $@ -c $< $(CFLAGS)

main.o : main.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
