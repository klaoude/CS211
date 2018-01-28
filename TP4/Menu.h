#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>

#include "Multi.h"
#include "Morpion.h"

typedef enum STATE
{
	MAINMENU,
	MULTIMENU,
	PLAYING,
	MULTI,
	CHOSING,
	QUITTING
} STATE;

void menu(STATE* state);
void multiMenu(STATE* state, struct NetworkData* data);
void choseMenu(STATE* state, char* currPlayer);

#endif