#ifndef MORPION_H
#define MORPION_H

#include <stdio.h>
#include <stdlib.h>

#define P1 0x01
#define P2 0x10

typedef int Map[3][3];

void PrintMap(Map* map);
char end(Map* map);
char place(Map* map, int pos, char player);

#endif