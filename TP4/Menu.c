#include "Menu.h"

void menu(STATE* state)
{
	system("clear");
	puts("---------------------------\n|                         |\n|       MORPION TP4       |\n|                         |\n---------------------------\n");
	puts("       [MAIN MENU]\n");
	puts("[1] YOU vs IA");
	puts("[2] MULTIPLAYER");
	puts("[9] QUIT");

	unsigned char input;
	scanf("%c", &input);

	switch(input)
	{
		case 0x31:
			*state = CHOSING;
			break;
		case 0x32:
			*state = MULTIMENU;
			break;
		case 0x39:
			exit(0);
			return;
			break;
		default:
			break;
	}
}

void multiMenu(STATE* state, NetworkData* data)
{
	system("clear");
	puts("---------------------------\n|                         |\n|         MORPION         |\n|                         |\n---------------------------\n");
	puts("       [MULTIPLAYER MENU]\n");
	puts("[1] CREATE SERVER");
	puts("[2] JOIN SERVER");
	puts("[9] GO BACK");

	unsigned char input;
	scanf("%c", &input);

	switch(input)
	{
		case 0x31:
			CreateServer(data);
			*state = MULTI;
			break;
		case 0x32:
			JoinServer(data);
			*state = MULTI;
			break;
		case 0x39:
			*state = MAINMENU;
			break;
		default:
			break;
	}
}

void choseMenu(STATE* state, char* currPlayer)
{
	system("clear");
	puts("---------------------------\n|                         |\n|         MORPION         |\n|                         |\n---------------------------\n");
	puts("       [MULTIPLAYER MENU]\n");
	puts("[1] BEGIN");
	puts("[2] LET IA BEGIN");
	puts("[9] GO BACK");

	unsigned char input;
	scanf("%c", &input);

	switch(input)
	{
		case 0x31:
			*currPlayer = P1;
			*state = PLAYING;
			break;
		case 0x32:
			*currPlayer = P2;
			*state = PLAYING;
			break;
		case 0x39:
			*state = MAINMENU;
			break;
	}
}