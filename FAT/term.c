#include "term.h"

const char* getUsername(int userID)
{
	const char* userList[] = {"root", "user"};
	return userList[userID];
}

void printHello()
{
	puts("              =======================================");
	puts("              |                                     |");
	puts("              |                                     |");
	puts("              |          FAT Simulator V2           |");
	puts("              |                                     |");
	puts("              |                                     |");
	puts("              =======================================");

	puts("How to use :");
	puts("		use 'help' to see all availible commands");
	puts("");
}

void afficher_Objet()
{
	if(obj == NULL)
		return;

	Objet* tmp = obj;

	do
	{
		printf("%d %d %s\n", tmp->auteur, tmp->taille, tmp->nom);
		tmp = tmp->next;
	} while(tmp != NULL);
}

void printFAT(int n)
{
	printf("0000 : ");
	for(int i = 0; i < n; i++)
	{
		printf("[%04x] ", FAT[i]);
		if(i % 0x10 == 0 && i != 0)
			printf("\n0x%04x : ", i);
	}
	puts("");
}

void printVolume(int s, int e)
{
	if(volume == NULL)
		return;

	printf("%08x : [ ", s);
	for(int i = s; i < e; i++)
	{
		printf("0x%02x ", volume[i]);
	}
	printf("]\n");
}

const char* handleCommande()
{
	printf("%s@FATemulator:%s$ ", getUsername(0), "/");
	char input[255];
	scanf("%254s", input);
	printf("%s\n", input);
}

int Run()
{
	const char* cmd = handleCommande();
	return 0;
}