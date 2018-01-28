#include "Morpion.h"

void PrintMap(Map* map)
{
	printf("-------------\n");
	for(int i = 0; i < 9; i++)
	{
		switch((*map)[i/3][i%3]) 
		{
			case 0x00: printf("|   "); break; 
			case 0x01: printf("| x "); break; 
			case 0x10: printf("| o "); break; 
		}
		if(i%3 == 2 && i != 0)
			printf("|\n");
	}
	printf("-------------\n");
}

char end(Map* map)
{
	if( (*map)[0][0] == P1 && (*map)[0][1] == P1 && (*map)[0][2] == P1 || 
		(*map)[1][0] == P1 && (*map)[1][1] == P1 && (*map)[1][2] == P1 || 
		(*map)[2][0] == P1 && (*map)[2][1] == P1 && (*map)[2][2] == P1 || 
		(*map)[0][0] == P1 && (*map)[1][1] == P1 && (*map)[2][2] == P1 || 
		(*map)[2][0] == P1 && (*map)[1][1] == P1 && (*map)[0][2] == P1 || 
		(*map)[0][0] == P1 && (*map)[1][0] == P1 && (*map)[2][0] == P1 || 
		(*map)[0][1] == P1 && (*map)[1][1] == P1 && (*map)[2][1] == P1 || 
		(*map)[0][2] == P1 && (*map)[1][2] == P1 && (*map)[2][2] == P1)
		return 1;

	if( (*map)[0][0] == P2 && (*map)[0][1] == P2 && (*map)[0][2] == P2 || 
		(*map)[1][0] == P2 && (*map)[1][1] == P2 && (*map)[1][2] == P2 || 
		(*map)[2][0] == P2 && (*map)[2][1] == P2 && (*map)[2][2] == P2 || 
		(*map)[0][0] == P2 && (*map)[1][1] == P2 && (*map)[2][2] == P2 || 
		(*map)[2][0] == P2 && (*map)[1][1] == P2 && (*map)[0][2] == P2 || 
		(*map)[0][0] == P2 && (*map)[1][0] == P2 && (*map)[2][0] == P2 || 
		(*map)[0][1] == P2 && (*map)[1][1] == P2 && (*map)[2][1] == P2 || 
		(*map)[0][2] == P2 && (*map)[1][2] == P2 && (*map)[2][2] == P2)
		return 1;

	for(int i = 0; i < 9; i++)
		if((*map)[i/3][i%3] == 0)
			return 0;

	return 1;
}

char place(Map* map, int pos, char player)
{
	printf("place %d, %d\n", pos, player);
	if(pos >= 9)
		return 0;
	if((*map)[pos/3][pos%3] != 0)
		return 0;
	(*map)[pos/3][pos%3] = player;
	return 1;
}