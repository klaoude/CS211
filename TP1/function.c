#include "function.h"

int intFromFile(FILE* file)
{
	unsigned char tmp[4];
	tmp[0] = fgetc(file);
	tmp[1] = fgetc(file);
	tmp[2] = fgetc(file);
	tmp[3] = fgetc(file);
	return (tmp[3] << 24) + (tmp[2] << 16) + (tmp[1] << 8) + tmp[0];
}

short shortFromFile(FILE* file)
{
	unsigned char tmp[2];
	tmp[0] = fgetc(file);
	tmp[1] = fgetc(file);
	return (tmp[1] << 8) + tmp[0];
}

void printHeader(fichierEntete header)
{
	puts("-----HEADER-----");
	printf("Signature : %x\nTaille : %x\nReserve : %x\nOffset : %x\n", header.signature, header.tailleFichier, header.reserve, header.offset);
	puts("----------------\n");
}

void printDIB(imageEntete DIB)
{
	puts("------DIB------");
	printf("DIB header size : %x\nImage Width : %x\nImage Height : %x\nPlanes : %x\nBits per pixel : %x\nCompression : %x\nImage size : %x\nX pixel per Meter : %x\nY pixel per Meter : %x\nColor in colorTable : %x\nImportant color count  : %x\n", 
			DIB.tailleEntete, DIB.largeur, DIB.hauteur, DIB.plan, DIB.profondeur, DIB.compression, 
			DIB.tailleImage, DIB.resolutionHorizontale, DIB.resolutionVerticale, DIB.nombreCouleurs, 
			DIB.nombreCouleursImportantes);
	puts("---------------\n");
}

void printBMP(BMP bmp)
{
	printHeader(bmp.header);
	printDIB(bmp.DIB);
}

BMP fileToStruct(FILE* file)
{
	BMP bmp;

	if(file == NULL) exit(1337);

	fichierEntete header;	
	header.signature = shortFromFile(file);
	header.tailleFichier = intFromFile(file);
	header.reserve = intFromFile(file);
	header.offset = intFromFile(file);

	imageEntete DIB;
	DIB.tailleEntete = intFromFile(file);
	DIB.largeur = intFromFile(file);
	DIB.hauteur = intFromFile(file);
	DIB.plan = shortFromFile(file);
	DIB.profondeur = shortFromFile(file);
	DIB.compression = intFromFile(file);
	DIB.tailleImage = intFromFile(file);
	DIB.resolutionHorizontale = intFromFile(file);
	DIB.resolutionVerticale = intFromFile(file);
	DIB.nombreCouleurs = intFromFile(file);
	DIB.nombreCouleursImportantes = intFromFile(file);

	bmp.header = header;
	bmp.DIB = DIB;

	return bmp;
}

char* stringcat(char* str1, char* str2)
{
	char* ret = malloc(strlen(str1) + strlen(str2) + 1);
	strcpy(ret, str1);
	strcat(ret, str2);
	return ret;
}

FILE* getModifiedFile(char* path)
{
	//building "sed 's/\xFF/\xFD/g' " + path  + " > temp"
	char* cmd = stringcat(stringcat("sed 's/\xFF/\xFD/g' ", path), " > temp");

	system(cmd);
	
	free(cmd);
	
	return fopen("temp", "r");
}