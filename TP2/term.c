#include "term.h"

void printHello()
{
	puts("              =======================================");
	puts("              |                                     |");
	puts("              |                                     |");
	puts("              |           FAT Simulator             |");
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
		if(i % 10 == 0 && i != 0)
			printf("\n%04d : ", i);
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

int input(char*** tab)
{
	char* inp;
	char inputStr[255];
	unsigned int len;
	int ret = 0;
	
	gets(inputStr);

	if(inputStr == NULL)
		return 0;

	len = strlen(inputStr);

	if(len == 0)
		return 0;

	unsigned int compteurSplit = 1;
	for(int i = 0; i < len; i++)
	{
		if(inputStr[i] == ' ')
			compteurSplit++;
	}

	ret = compteurSplit;
	*tab = malloc(compteurSplit*sizeof(char*));

	unsigned int tailleMot = 0, compteurMot = 0;
	for(int i = 0; i < len; i++)
	{
		if(inputStr[i] == ' ' || i == len - 1)
		{
			if(i == len - 1)
				tailleMot++;

			(*tab)[compteurMot] = malloc(tailleMot+1);
			tailleMot = 0;
			compteurMot++;
			continue;
		}
		tailleMot++;
	}

	char buff[1024]; compteurMot = 0; unsigned int tmp = 0, j = 0;
	int compt = 0;
	for(int i = 0; i < len; i++)
	{
		if(inputStr[i] == ' ' || i == len - 1)
		{
			if(i == len - 1)
				buff[j] = inputStr[i];

			compt = i - tmp - 1;
			if(tmp == 0 || i == len - 1)
				compt++;
			if(tmp == 0 && i == len - 1)
				compt++;

			memcpy((*tab)[compteurMot], buff, compt);
			(*tab)[compteurMot][compt] = 0x0;
			tmp = i;
			j = 0;
			compteurMot++;
			continue;
		}
		buff[j] = inputStr[i];
		j++;
	}

	return ret;
}

char** inputTab;
int argCompteur;
int Run()
{
	printf("$ ");
		
	argCompteur = input(&inputTab);

	if(argCompteur == 0)
	{
		for(int i = 0; i < argCompteur; i++)
			free(inputTab[i]);
		free(inputTab);
		return 0;
	}

	if(!strcmp(inputTab[0], "ls"))
	{
		afficher_Objet();
	}
	else if(!strcmp(inputTab[0], "create") || !strcmp(inputTab[0], "c"))
	{
		if(argCompteur == 3)
		{
			if(creer_objet(inputTab[1], 10, strlen(inputTab[2]), inputTab[2]) != NULL)
				printf("File %s created !\n", inputTab[1]);
			else
				printf("File %s already exist or name is too long (MAX : %d)\n", inputTab[1], NAMELEN);
		}
		else if(argCompteur > 3)
		{
			int fullSize = 0;
			for(int i = 2; i < argCompteur; i++)
			{
				fullSize += strlen(inputTab[i]) + 1;
			}

			char *tmp = NULL;
			char* full = malloc(fullSize);
			for(int i = 2; i < argCompteur-1; i++)
			{
				if(tmp == NULL)
				{
					tmp = malloc(strlen(inputTab[i]) + strlen(inputTab[i+1]));
					tmp = strcat(inputTab[i], " ");
				}
				else
				{
					tmp = malloc(strlen(tmp) + strlen(inputTab[i+1]));
					tmp = strcat(tmp, " ");
				}				
				tmp = strcat(tmp, inputTab[i+1]);
				full = strcat(full, tmp);
				free(tmp);
			}

			if(creer_objet(inputTab[1], 10, strlen(full), full) != NULL)
				printf("File %s created !\n", inputTab[1]);
			else
				printf("File %s already exist or name is too long (MAX : %d)\n", inputTab[1], NAMELEN);

			free(full);
		}
		else
		{
			printf("usage: create nom data\n");
		}
	}
	else if(!strcmp(inputTab[0], "create-full") || !strcmp(inputTab[0], "c-f"))
	{
		if(argCompteur == 4)
		{
			char* tab = malloc(atoi(inputTab[3]));
			for(int i = 0; i < atoi(inputTab[3]); i++)
				memcpy(tab+i, inputTab[3], 1);

			creer_objet(inputTab[1], 10, atoi(inputTab[3]), tab);
			printf("File %s created !\n", inputTab[1]);
			free(tab);
		}
		else
		{
			printf("usage: create-full nom char size\n");
		}
	}
	else if(!strcmp(inputTab[0], "cat"))
	{
		if(argCompteur == 2)
		{
			char* data;
			Objet* obj = rechercher_objet(inputTab[1]);
			if(lire_objet(obj, &data) == -1)
			{
				printf("Error, file %s not found\n", inputTab[1]);
				free(data);
			}
			else
				printf("%s\n", data);
		}
		else
			printf("Usage : cat nom\n");
	}
	else if(!strcmp(inputTab[0], "rm"))
	{
		if(argCompteur == 2)
		{
			if(!strcmp(inputTab[1], "*"))
				supprimer_tout();
			else
			{
				if(supprimer_objet(inputTab[1]) == -1)
					printf("Error, file %s not found\n", inputTab[1]);
			}
		}
		else
			puts("Usage: rm nom");
	}
	else if(!strcmp(inputTab[0], "fat"))
	{
		if(argCompteur == 2)
		{
			printFAT(atoi(inputTab[1]));
		}
		else
			puts("Usage: fat size");
	}
	else if(!strcmp(inputTab[0], "quit") || !strcmp(inputTab[0], "q"))
	{
		for(int i = 0; i < argCompteur; i++)
			free(inputTab[i]);
		free(inputTab);
		exit(0);
		return 1;
	}
	else if(!strcmp(inputTab[0], "help"))
	{
		puts("    List of all availble commands :");
		puts("    ls : print all created files.\n        output : [author] [size] [name]\n");
		puts("    create/c : create a new file\n        create [nom] [data]\n");
		puts("    create-full/c-f : create a new file with n * data.\n        create-full [nom] [data] [size]\n");
		puts("    cat : show a file data's.\n        cat [fileName]\n");
		puts("    rm : remove a file.\n        rm [name]\n");
		puts("    fat : show the current fat state\n        fat [size]\n");
		puts("    quit : exit the program.\n");
	}
	else
		printf("Unknow command %s. Use help or ? for help\n", inputTab[0]);

	/*for(int i = 0; i < argCompteur; i++)
		if(inputTab[i] != NULL)
			free(inputTab[i]);
	free(inputTab);*/

	return 0;
}