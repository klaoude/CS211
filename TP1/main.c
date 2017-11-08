#include "function.h"

//Utilisation, 	./TP1 1 pour l'exo 1
//				./TP1 2 pour l'exo 2
// 				./TP1 mask [source] [origin] [dest] pour le masquage

void exo1()
{
	FILE* transporteur = fopen("transporteur.txt", "rb");
	FILE* origin = fopen("original", "wb");

	if(transporteur == NULL) exit(1);

	if(origin == NULL) exit(2);

	char currChar;
	unsigned char i = 0;
	unsigned char buffer = 0;
	do
	{
		if(i > 7)
		{
			fputc(buffer, origin);
			buffer = 0;
			i = 0;		
		}

		currChar = fgetc(transporteur);

		if(isalpha(currChar))
		{
			if(isupper(currChar))
			{
				buffer += pow(2, 7-i);
			}
			i++;
		}
	} while(currChar != EOF);

	if(fclose(transporteur)) exit(3);
	if(fclose(origin)) exit(4);
}

void exo2()
{
	//FILE* inputFile = getModifiedFile("transporteur.bmp");
	FILE* inputFile = fopen("transporteur.bmp", "rb");
	if(inputFile == NULL) exit(1);

	FILE* output = fopen("out.jpg", "wb");
	if(output == NULL) exit(2);

	fseek(inputFile, 0, SEEK_END);
	int size = ftell(inputFile);
	fseek(inputFile, 0, SEEK_SET); //J'utilise la size plutot que l'EOF car si dans notre fichier on a un byte a 0xFF, il sera considéré comme un EOF !
	printf("%d\n", size);

	char currChar;
	unsigned char i = 0;
	unsigned char buffer = 0;

	BMP info = fileToStruct(inputFile);

	printBMP(info);

	for(int j = 0; j < size - 0x36; j++) //offset de 0x36, taille de l'header
	{
		currChar = fgetc(inputFile);

		if(i > 7)
		{
			fputc(buffer, output);
			buffer = 0;
			i = 0;		
		}

		buffer += (currChar&1)*pow(2, 7-i);

		i++;
	}

	puts("Hey, Richard Stallman is cool !!!");

	if(fclose(inputFile)) exit(3);
	if(fclose(output)) exit(4);
}

void masquage(char* sourcePath, char* originelPath, char* destPath)
{
	FILE* source = fopen(sourcePath, "rb");
	FILE* originel = fopen(originelPath, "rb");
	FILE* dest = fopen(destPath, "wb");

	if(source == NULL) exit(1);
	if(originel == NULL) exit(2);
	if(dest == NULL) exit(5);

	int sourceSize, originelSize;

	//calcul de taille des fichiers
	fseek(source, 0, SEEK_END);
	fseek(originel, 0, SEEK_END);
	sourceSize = ftell(source);
	originelSize = ftell(originel);
	fseek(source, 0, SEEK_SET);
	fseek(originel, 0, SEEK_SET);

	if(sourceSize != originelSize)
	{
		printf("Erreur de masquage, sourceSize != originelSize !!\n");
		exit(42);
	}

	printf("Masking %s in %s.\n", sourcePath, destPath);

	//copy les même 0x36 premier bytes
	for(int i = 0; i < 0x36; i++)
		fputc(fgetc(originel), dest);

	char toEncode;
	//on chiffre
	for(int j = 0; j < sourceSize; j++)
	{
		toEncode = fgetc(source);
		printf("Encoding 0x%02x\n", toEncode);
		for(int i = 0; i < 8; i++)
		{			
			unsigned char org = fgetc(originel);
			unsigned char bit = (toEncode>>i)&1;
			if(org == 0xff && bit == 1)
				fputc(0xfe, dest);
			else
			{
				if((org & 1) == bit)
					fputc(org+1, dest);
				else
					fputc(org, dest);
			}			
		}
	}

	printf("Done !\n");

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
		else if(argc > 3 && !strcmp(argv[1], "mask"))
			masquage(argv[2], argv[3], argv[4]);
	}
	else
	{
		puts("Usage : ./TP1 [1/2/mask] [source] [origin] [dest]");
	}
	return 0;
}
