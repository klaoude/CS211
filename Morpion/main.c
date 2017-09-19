#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

//#define DEBUG 1

#define false 0
#define true 1

typedef int SOCKET; 
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

typedef char bool;

unsigned char map[3][3];

typedef struct vec2 vec2;
struct vec2
{
	unsigned char x : 3; //3bit for handle '\n'
	unsigned char y : 3;
};

enum STATE
{
	MAINMENU,
	MULTIMENU,
	PLAYING,
	MULTI,
	QUITTING
};

enum STATE state = MAINMENU;

bool isServer = false;
bool myTurn = false;
SOCKET ssock;
SOCKET csock;

void init()
{
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			map[i][j] = ' ';
}

void menu()
{
	while(state == MAINMENU)
	{
		system("clear");
		puts("---------------------------\n|                         |\n|         MORPION         |\n|                         |\n---------------------------\n");
		puts("       [MAIN MENU]\n");
		puts("[1] YOU vs IA");
		puts("[2] MULTIPLAYER");
		puts("[9] QUIT");

		unsigned char input;
		scanf("%c", &input);

		switch(input)
		{
			case 0x31:
				state = PLAYING;
				break;
			case 0x32:
				state = MULTIMENU;
				break;
			case 0x39:
				exit(0);
				return;
				break;
			default:
				break;
		}
	}
}

void createServer()
{
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sin = {0};
	sin.sin_family = AF_INET;
	sin.sin_port = 1337;

	bind(sock, (SOCKADDR*)&sin, sizeof sin);

	puts("Waiting for someone to connect ...");

	listen(sock, 1);

	SOCKADDR_IN csin = {0};

	int sinsize = sizeof csin;
	csock = accept(sock, (SOCKADDR*)&csin, &sinsize);

	puts("Client found !");

	isServer = true;
	myTurn = true;

	state = MULTI;
}

void joinServer()
{
	puts("Enter IP :");
	char ip[255];
	scanf("%s", ip);
	printf("Connecting to %s\n", ip);

	ssock = socket(AF_INET, SOCK_STREAM, 0);

	struct hostent *host = NULL;
	host = gethostbyname(ip);
	if(host == NULL)
	{
		printf("Unknown host %s\n", ip);
		exit(1);
	}

	SOCKADDR_IN sin = {0};

	sin.sin_addr = *(IN_ADDR*) host->h_addr;
	sin.sin_port = 1337;
	sin.sin_family = AF_INET;

	while(connect(ssock, (SOCKADDR*)&sin, sizeof(SOCKADDR)) == -1) ;

	printf("Connected to %s\n", ip);

	state = MULTI;
}

void multiMenu()
{	
	while(state == MULTIMENU)
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
				createServer();
				break;
			case 0x32:
				joinServer();
				break;
			case 0x39:
				state = MAINMENU;
				break;
			default:
				break;
		}
	}
}

void printMap()
{
#ifndef DEBUG
	system("clear");
#endif

	puts("-------------");
	for(int i = 0; i < 3; i++)
	{
		printf("|");
		for(int j = 0; j < 3; j++)
		{
			printf(" %c |", map[i][j]);
		}
		puts("\n-------------");
	}
	puts("\n");
}

vec2 char2Vec(char c)
{
	vec2 ret;
	switch(c)
	{
		case '1':
			ret.x = 0;
			ret.y = 2;
			break;
		case '2':
			ret.x = 1;
			ret.y = 2;
			break;
		case '3':
			ret.x = 2;
			ret.y = 2;
			break;
		case '4':
			ret.x = 0;
			ret.y = 1;
			break;
		case '5':
			ret.x = 1;
			ret.y = 1;
			break;
		case '6':
			ret.x = 2;
			ret.y = 1;
			break;
		case '7':
			ret.x = 0;
			ret.y = 0;
			break;
		case '8':
			ret.x = 1;
			ret.y = 0;
			break;
		case '9':
			ret.x = 2;
			ret.y = 0;
			break;
		default:
			ret.x = 3;
			ret.y = 3;
			break;
	}
	return ret;
}

bool place(vec2 pos, char id)
{
	if(pos.x == 3 || pos.y == 3)
		return 0;

#ifdef DEBUG
	printf("%d try to place at (%d, %d)\n", id, pos.x, pos.y);
#endif

	if(map[pos.y][pos.x] == ' ')
	{
		if(!id)
			map[pos.y][pos.x] = 'X';
		else
			map[pos.y][pos.x] = 'O';
	}
	else
		return 0;
	return 1;

}

void IAplay()
{
	srand(time(NULL));
	vec2 pos;

	do
	{
		pos.x = rand() % 3;
		pos.y = rand() % 3;
	} while(!place(pos, 1));
}

bool win()
{
	if(map[0][0] == map[0][1] && map[0][1] == map[0][2] && map[0][2] != ' ')
		return 1;
	if(map[1][0] == map[1][1] && map[1][1] == map[1][2] && map[1][2] != ' ')
		return 1;
	if(map[2][0] == map[2][1] && map[2][1] == map[2][2] && map[2][2] != ' ')
		return 1;
	if(map[0][0] == map[1][0] && map[1][0] == map[2][0] && map[2][0] != ' ')
		return 1;
	if(map[0][1] == map[1][1] && map[1][1] == map[2][1] && map[2][1] != ' ')
		return 1;
	if(map[0][2] == map[1][2] && map[1][2] == map[2][2] && map[2][2] != ' ')
		return 1;
	if(map[0][0] == map[1][1] && map[1][1] == map[2][2] && map[2][2] != ' ')
		return 1;
	if(map[2][0] == map[1][1] && map[1][1] == map[0][2] && map[0][2] != ' ')
		return 1;

	return 0;
}

void play()
{
	printMap();
	char c;
	do
	{
		printf("[1-9]\n> ");
		c = getchar();
	} while(!place(char2Vec(c), 0));

	printMap();

	if(win())
	{
		printMap();
		printf("You Win !!!\n");
		state = QUITTING;
		return;
	}

	IAplay();

	if(win())
	{
		printMap();
		printf("You lose :(\n");
		state = QUITTING;
		return;
	}
	
	printMap();
}

void multiplay()
{
#ifdef DEBUG
	printf("i'm %d and csock = %d, ssock = %d and it's turn %d\n", isServer, csock, ssock, myTurn);
#endif

	if(myTurn)
	{
		printMap();
		char c;
		do
		{
			printf("[1-9]\n> ");
			c = getchar();
		} while(!place(char2Vec(c), 0));

		bool w = win();
		char buffer[2] = {c, w};

		send(isServer ? csock : ssock, buffer, sizeof(buffer), 0);

		printMap();

		if(w)
		{
			printMap();
			printf("You Win !!!\n");
			state = QUITTING;
			return;
		}

		myTurn = !myTurn;
	}
	else
	{
		char buffer[2];
		bool rec = false;

		while(!recv(isServer ? csock : ssock, buffer, 2, 0) < 0) ;	

		place(char2Vec(buffer[0]), 1);

		if(buffer[1])
		{
			printMap();
			printf("You lose :(\n");
			state = QUITTING;
			return;
		}

		myTurn = !myTurn;
	}
}

int main(int argc, char const *argv[])
{	
	init();

	while(state != QUITTING)
	{
		switch(state)
		{
			case MAINMENU:
				menu();
				break;
			case PLAYING:
				play();
				break;
			case MULTIMENU:
				multiMenu();
				break;
			case MULTI:
				multiplay();
				break;
		}
	}	

	return 0;
}