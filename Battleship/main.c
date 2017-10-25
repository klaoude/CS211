#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CHARBOAT 0x23

enum GAMETYPE
{
	IA,
	MULTI
};

enum STATE
{
	MAINMENU,
	MULTIMENU,
	PLACING,
	PLAYING,
	QUITTING
};

enum STATE state = MAINMENU;
enum GAMETYPE gt;

unsigned char map[10][10];
unsigned char IAmap[10][10];
unsigned char touchMap[10][10];
unsigned char IAtouchMap[10][10];

const char SIZE[] = {2, 3, 3, 4, 5};

char** split(const char* toSplit, char split)
{
	char** ret;

	int size = 1;
	for(int i = 0; i < strlen(toSplit); i++)
	{
		if(toSplit[i] == split)
			size++;
	}

	ret = malloc(size);
	for(int i = 0; i < size; i++)
		ret[i] = malloc(10);

	for(int i = 0, j = 0, k = 0; i < strlen(toSplit); i++)
	{
		if(toSplit[i] != split)
		{
			ret[j][k] = toSplit[i];
			k++;
		}
		else
		{
			j++;
			k=0;
		}
	}
	return ret;
}

void initMap()
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			IAmap[i][j] = 0x30;
			map[i][j] = 0x30;
			touchMap[i][j] = 0x30;
			IAtouchMap[i][j] = 0x30;
		}
	}
}

void printMap()
{
	system("clear");
	puts("   0 1 2 3 4 5 6 7 8 9 ");
	puts(" |---------------------|");
	for(int i = 0; i < 10; i++)
	{
		printf("%d| ", i);
		for(int j = 0; j < 10; j++)
			printf("%c ", map[i][j]);
		puts("|");
	}
	puts(" |---------------------|\n");
}

void printIAMap()
{
	system("clear");
	puts("   0 1 2 3 4 5 6 7 8 9 ");
	puts("  |---------------------|");
	for(int i = 0; i < 10; i++)
	{
		printf("%d| ", i);
		for(int j = 0; j < 10; j++)
			printf("%c ", IAmap[i][j]);
		puts("|");
	}
	puts("  |---------------------|\n");
}

void printPlayMap()
{
	system("clear");

	puts("   0 1 2 3 4 5 6 7 8 9 ");
	puts(" |---------------------|");
	for(int i = 0; i < 10; i++)
	{
		printf("%d| ", i);
		for(int j = 0; j < 10; j++)
			printf("%c ", map[i][j]);
		puts("|");
	}
	puts(" |---------------------|         0 1 2 3 4 5 6 7 8 9 ");
	puts("                               |---------------------|");
	for(int i = 0; i < 10; i++)
	{
		printf("                               %d| ", i);
		for(int j = 0; j < 10; j++)
			printf("%c ", touchMap[i][j]);
		puts("|");
	}
	puts("                               |---------------------|");	
}

void setup()
{
	puts("---------------------------\n|                         |\n|          Battle         |\n|           Ship          |\n|                         |\n---------------------------\n");
	
	while(state == MAINMENU)
	{
		puts("       [MAIN MENU]\n");
		puts("[1] YOU vs IA");
		puts("[2] MULTIPLAYER");
		puts("[9] QUIT");

		unsigned char input;
		scanf("%c", &input);

		switch(input)
		{
			case 0x31:
				state = PLACING;
				gt = IA;
				break;

			case 0x32:
				state = MULTIMENU; 
				break;

			case 0x39:
				state = QUITTING;
				return;
				break;

			default:
				break;
		}
	}	
}

void setupIA()
{
	srand(time(NULL));
	int x, y, dir;
	for(int i = 0; i < 5; i++)
	{
		do
		{			
			x = rand() % 10;
			y = rand() % 10;
			dir = rand() % 2;
		} while(dir ? y+SIZE[i]>=10 : x+SIZE[i]>=10);

		if(dir)
		{
			for(int j = 0; j < SIZE[i]; j++)
			{
				if(IAmap[y][x+j] == CHARBOAT)
				{
					i--;
					break;
				}				
			}
			for(int j = 0; j < SIZE[i]; j++)
			{
				IAmap[y][x+j] = CHARBOAT;
			}
		}
		else
		{
			for(int j = 0; j < SIZE[i]; j++)
			{
				if(IAmap[y+j][x] == CHARBOAT)
				{
					i--;
					break;
				}				
			}
			for(int j = 0; j < SIZE[i]; j++)
			{
				IAmap[y+j][x] = CHARBOAT;
			}
		}
	}

	printIAMap();
}

void placing()
{
	char* input = malloc(255);
	int x=0, y=0, dir=0;
	char** splited;

	for(int i = 0; i < 5; i++)
	{
		printMap();

		do
		{
			printf("Ou placer ce bateau %dx1 ? [x,y,pos] ou pos=0 vertical et pos=1 horizontal\n", SIZE[i]);
			
			scanf("%s", input);

			splited = split(input, ',');
			
			x = atoi(splited[0]);
			y = atoi(splited[1]);
			dir = atoi(splited[2]);
		} while(dir ? y+SIZE[i]-1>=10 : x+SIZE[i]-1>=10);
		

		if(dir)
		{
			for(int j = 0; j < SIZE[i]; j++)
			{
				if(map[y][x+j] == CHARBOAT)
				{
					puts("Boat already here !");
					i--;
					break;
				}				
			}
			for(int j = 0; j < SIZE[i]; j++)
			{
				map[y][x+j] = CHARBOAT;
			}
		}
		else
		{
			for(int j = 0; j < SIZE[i]; j++)
			{
				if(map[y+j][x] == CHARBOAT)
				{
					puts("Boat already here !");
					i--;
					break;
				}				
			}
			for(int j = 0; j < SIZE[i]; j++)
			{
				map[y+j][x] = CHARBOAT;
			}
		}
	}

	printMap();
	setupIA();
	state = PLAYING;	

	free(input);
}

void shooting()
{
	char* input = malloc(255);
	char** splited;

	int x, y;

	do
	{
		printf("Ou Tirer ? (x,y)\n");
		scanf("%s", input);

		splited = split(input, ',');

		x = atoi(splited[0]);
		y = atoi(splited[1]);
	} while(x > 9 || y > 9);

	if (IAmap[y][x] == CHARBOAT)
		touchMap[y][x] = 0x58;
	else if(IAmap[y][x] == 0x30)
		touchMap[y][x] = 0x70;
	else
	{
		free(input);
		shooting();
	}	
	free(input);
}

void IAplay()
{
	srand(time(NULL));
	int x = rand()%10;
	int y = rand()%10;

	if (map[y][x] == CHARBOAT)
		IAtouchMap[y][x] = 0x58;
	else if(map[y][x] == 0x30)
		IAtouchMap[y][x] = 0x70;
	else
	{
		IAplay();
	}	
}

void gameLoop()
{
	while(state == PLACING || state == PLAYING)
	{
		if(gt == IA)
		{
			switch(state)
			{
				case PLACING:
					placing();
					break;
				case PLAYING:
					printPlayMap();
					shooting();
					IAplay();
					break;
				default:
					break;
			}
		}		
	}
}

int main(int argc, char* argv[])
{
	setup();
	initMap();

	if(state != QUITTING)
		gameLoop();

	return 0;
}