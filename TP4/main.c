#include "Menu.h"
#include "Morpion.h"
#include "IA.h"
#include "Multi.h"

STATE state = MAINMENU;

NetworkData nmData;

char currPlayer;

void playVSIA(Map* map)
{
	while(!end(map))
	{
		PrintMap(map);
		if(currPlayer == P1)
		{
			int move;
			do
			{
				printf("Enter move : ");
				scanf("%d", &move);
			} while(!place(map, move, P1));
			currPlayer = P2;
		}
		else
		{
			IAPlay(map);
			currPlayer = P1;
		}
	}
	PrintMap(map);
	state = MAINMENU;
}

void multiplay(Map* map)
{
#ifdef DEBUG
	printf("i'm %d and csock = %d, ssock = %d and it's turn %d\n", isServer, csock, ssock, myTurn);
#endif
	while(!end(map))
	{
		if(nmData.myTurn)
		{
			PrintMap(map);
			int move;
			do
			{
				printf("Enter move : ");
				scanf("%d", &move);
			} while(!place(map, move, P1));

			char buffer = move;

			send(nmData.imServer ? clientSocket : serverSocket, &buffer, sizeof(buffer), 0);

			nmData.myTurn = !nmData.myTurn;
		}
		else
		{
			char buffer;
			while(!recv(nmData.imServer ? clientSocket : serverSocket, &buffer, sizeof(buffer), 0) < 0) ;	

			place(map, buffer, P2);

			nmData.myTurn = !nmData.myTurn;
		}
	}
}

void resetMap(Map* map)
{
	for(int i = 0; i < 9; i++)
		(*map)[i / 3][i % 3] = 0;
}

void tests()
{
	Map t1 = { { P1, P1, P1 }, { 0, 0, 0 }, { 0, 0, 0 } };
	printf("Test 1 : ");
	end(&t1) != 1 ? printf("end() : FAILED ") : printf("end() : GOOD ");
	evaluate(&t1) != WIN ? printf("evaluate() : FAILED ") : printf("evaluate() : GOOD ");
	puts("");

	Map t2 = { { P2, P1, P1 }, { P1, P2, P1 }, { 0, 0, P2 } };
	printf("Test 2 : ");
	end(&t2) != 1 ? printf("end() : FAILED ") : printf("end() : GOOD ");
	evaluate(&t2) != -WIN ? printf("evaluate() : FAILED ") : printf("evaluate() : GOOD ");
	puts("");

	Map t3 = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
	printf("Test 3 : ");
	end(&t3) != 0 ? printf("end() : FAILED ") : printf("end() : GOOD ");
	evaluate(&t3) != 0 ? printf("evaluate() : FAILED ") : printf("evaluate() : GOOD ");
	puts("");	

	Map t4 = { { P1, 0, P1 }, { P1, 0, 0 }, { P1, 0, P2 } };
	printf("Test 4 : ");
	end(&t4) != 1 ? printf("end() : FAILED ") : printf("end() : GOOD ");
	evaluate(&t4) != WIN ? printf("evaluate() : FAILED ") : printf("evaluate() : GOOD ");
	puts("");

	Map t5 = { { P1, 0, P2 }, { 0, P2, 0 }, { P2, 0, 0 } };
	printf("Test 5 : ");
	end(&t5) != 1 ? printf("end() : FAILED ") : printf("end() : GOOD ");
	evaluate(&t5) != -WIN ? printf("evaluate() : FAILED ") : printf("evaluate() : GOOD ");
	puts("");

	Map t6 = { { P1, P1, P1 }, { P1, P1, P1 }, { P1, P1, P1 } };
	printf("Test 6 : ");
	end(&t6) != 1 ? printf("end() : FAILED ") : printf("end() : GOOD ");
	evaluate(&t6) != WIN ? printf("evaluate() : FAILED ") : printf("evaluate() : GOOD ");
	puts("");
}

int main(int argc, char** argv)
{
	if(argc >= 2)
	{
		tests();
		return 0;
	}

	Map map = { { 0, 0, 0 },{ 0, 0, 0 },{ 0, 0, 0 } };
	while(state != QUITTING)
	{
		switch(state)
		{
		case MAINMENU:
			resetMap(&map);
			menu(&state);
			break;
		case PLAYING:
			system("clear");
			playVSIA(&map);
			break;
		case MULTIMENU:
			multiMenu(&state, &nmData);
			break;
		case MULTI:
			multiplay(&map);
			break;
		case CHOSING:
			choseMenu(&state, &currPlayer);
			break;
		}
	}

	return 0;
}