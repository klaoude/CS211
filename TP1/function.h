#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#include "bitmap.h"

typedef struct 
{
	char R;
	char G;
	char B;
} Pixel;

typedef struct BMP {
	fichierEntete header;
	imageEntete DIB;
	couleurPallete color;
} BMP;

int intFromFile(FILE* file);
short shortFromFile(FILE* file);

void printHeader(fichierEntete header);
void printDIB(imageEntete DIB);
void printBMP(BMP bmp);

BMP fileToStruct(FILE* file);

char* stringcat(char* str1, char* str2);
FILE* getModifiedFile(char* path);