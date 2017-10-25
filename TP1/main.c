#include "function.h"

void exo1()
{
	FILE* transporteur = fopen("transporteur.txt", "r");
	FILE* origin = fopen("original", "w");

	if(transporteur == NULL) exit(1);

	if(origin == NULL) exit(2);

	char currChar;
	unsigned char i = 0;
	unsigned char decoded = 0;
	do
	{
		if(i > 7)
		{
			fputc(decoded, origin);
			decoded = 0;
			i = 0;		
		}

		currChar = fgetc(transporteur);

		if(isalpha(currChar))
		{
			if(isupper(currChar))
			{
				decoded += pow(2, 7-i);
			}
			i++;
		}
	} while(currChar != EOF);

	if(fclose(transporteur)) exit(3);
	if(fclose(origin)) exit(4);
}

void exo2()
{
	FILE* inputFile = getModifiedFile("transporteur.bmp");
	if(inputFile == NULL) exit(1);

	FILE* output = fopen("out.txt", "w");
	if(output == NULL) exit(2);

	char currChar;
	unsigned char i = 0;
	unsigned char decoded = 0;

	BMP info = fileToStruct(inputFile);

	do
	{
		currChar = fgetc(inputFile);

		if(i > 7)
		{
			fputc(decoded, output);
			decoded = 0;
			i = 0;		
		}

		decoded += (currChar&1)*pow(2, 7-i);

		i++;

	} while(currChar != EOF);

	puts("Hey, Richard Stallman is cool !!!");

	system("rm temp");

	if(fclose(inputFile)) exit(3);
	if(fclose(output)) exit(4);
}

void masquage(FILE* source, FILE* originel, FILE* dest)
{
	if(source == NULL) exit(1);
	if(originel == NULL) exit(2);
	if(dest == NULL) exit(5);

	//copy les même 0x36 premier bytes
	for(int i = 0; i < 0x36; i++)
		fputc(fgetc(originel), dest);

	char toEncode;

	//on chiffre
	do
	{
		toEncode = fgetc(source);
		for(int i = 0; i < 8; i++)
		{
			char org = fgetc(originel);
			char bit = toEncode & ((int)pow(2, 7-i));
			if((org & 1) != bit)
				fputc(org+1, dest);
		}

	} while(toEncode != EOF);

	//on copy les même dernier bytes une fois que notre fichier source est encodé
	do
	{
		toEncode = fgetc(originel);
		fputc(toEncode, dest);
	} while(toEncode != EOF);

	if(fclose(source)) exit(3);
	if(fclose(originel)) exit(4);
	if(fclose(dest)) exit(6);
}

int main(int argc, char** argv)
{
	if(argc >= 2)
	{
		if(!strcmp(argv[1], "1"))
			exo1();
		else if(!strcmp(argv[1], "2"))
			exo2();
		else if(argc > 3)
			masquage(fopen(argv[1], "r"), fopen(argv[2], "r"), fopen(argv[3], "w"));
	}
	else
	{
		puts("Usage : ./TP1 [1/2/source] [[originel] [destination]]");
	}
	return 0;
}
