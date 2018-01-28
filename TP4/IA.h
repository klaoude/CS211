#ifndef IA_H
#define IA_H

#include "Morpion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIN 1000

typedef struct Pair
{
	int val;
	int id;
} Pair;

void IAPlay(Map* map);

#endif