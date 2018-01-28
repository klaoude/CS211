#include "IA.h"

#define INF 999999

int evaluate(Map* map)
{
	if( (*map)[0][0] == P1 && (*map)[0][1] == P1 && (*map)[0][2] == P1 || 
		(*map)[1][0] == P1 && (*map)[1][1] == P1 && (*map)[1][2] == P1 || 
		(*map)[2][0] == P1 && (*map)[2][1] == P1 && (*map)[2][2] == P1 || 
		(*map)[0][0] == P1 && (*map)[1][1] == P1 && (*map)[2][2] == P1 || 
		(*map)[2][0] == P1 && (*map)[1][1] == P1 && (*map)[0][2] == P1 || 
		(*map)[0][0] == P1 && (*map)[1][0] == P1 && (*map)[2][0] == P1 || 
		(*map)[0][1] == P1 && (*map)[1][1] == P1 && (*map)[2][1] == P1 || 
		(*map)[0][2] == P1 && (*map)[1][2] == P1 && (*map)[2][2] == P1)
		return WIN;

	if( (*map)[0][0] == P2 && (*map)[0][1] == P2 && (*map)[0][2] == P2 || 
		(*map)[1][0] == P2 && (*map)[1][1] == P2 && (*map)[1][2] == P2 || 
		(*map)[2][0] == P2 && (*map)[2][1] == P2 && (*map)[2][2] == P2 || 
		(*map)[0][0] == P2 && (*map)[1][1] == P2 && (*map)[2][2] == P2 || 
		(*map)[2][0] == P2 && (*map)[1][1] == P2 && (*map)[0][2] == P2 || 
		(*map)[0][0] == P2 && (*map)[1][0] == P2 && (*map)[2][0] == P2 || 
		(*map)[0][1] == P2 && (*map)[1][1] == P2 && (*map)[2][1] == P2 || 
		(*map)[0][2] == P2 && (*map)[1][2] == P2 && (*map)[2][2] == P2)
		return -WIN;

	return 0;
}

Pair maxx(int tab[])
{
	Pair p = { -999, 0 };
	for (int i = 0; i < 9; i++)
		if (tab[i] != -1)
			if (tab[i] > p.val)
			{
				p.id = i;
				p.val = tab[i];
			}
	return p;
}

Pair minn(int tab[])
{
	int tabb[9];
	memcpy(tabb, tab, 9 * sizeof(int));
	Pair p = { 999, 0 };
	for (int i = 0; i < 9; i++)
		if (tabb[i] != -1)
			if (tabb[i] < p.val)
			{
				p.id = i;
				p.val = tabb[i];
			}
	return p;
}

Pair minmax(Map* map, int joueur)
{
	Pair p;
	int score[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};

	if(end(map))
	{
		p.val = evaluate(map);
		return p;
	}		

	for(int i = 0; i < 9; i++)
	{
		if((*map)[i/3][i%3] == 0x00)
		{
			(*map)[i/3][i%3] = joueur;
			Pair sc = minmax(map, joueur == P1 ? P2 : P1);
			score[i] = sc.val;
			(*map)[i/3][i%3] = 0x00;
		}
	}

	if (joueur == P1)
		p = maxx(score);
	else
		p = minn(score);

	return p;
}

Pair minmaxAB(Map* map, int joueur, int alpha, int beta)
{
	Pair p;
	int score[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};

	if(end(map))
	{
		p.val = evaluate(map);
		return p;
	}		

	if(joueur == P1 && beta == WIN)
	{
		p.val = WIN;
		return p;
	}
	if(joueur == P2 && alpha == -WIN)
	{
		p.val = -WIN;
		return p;
	}

	for(int i = 0; i < 9; i++)
	{
		if((*map)[i/3][i%3] == 0x00)
		{
			(*map)[i/3][i%3] = joueur;
			
			Pair sc = minmaxAB(map, joueur == P1 ? P2 : P1, alpha, beta);
			score[i] = sc.val;
			
			if(joueur == P1 && score[i] < alpha)
				alpha = score[i];
			else if(joueur == P2 && score[i] > beta)
				beta = score[i];

			(*map)[i/3][i%3] = 0x00;
		}
	}

	if (joueur == P1)
		p = maxx(score);
	else
		p = minn(score);

	return p;
}

void IAPlay(Map* map)
{
	Pair p = minmaxAB(map, P2, -999999, 999999);
	printf("score = %d, move = %d\n", p.val, p.id);
	(*map)[p.id/3][p.id%3] = P2;
}