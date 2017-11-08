#include "function.h"

Pixel fgetPixel(FILE* file)
{
	Pixel ret;
	ret.R = fgetc(file);
	ret.G = fgetc(file);
	ret.B = fgetc(file);
	return ret;
}

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
	printf("Signature : 0x%08x\nTaille : 0x%08x\nReserve : 0x%08x\nOffset : 0x%08x\n", header.signature, header.tailleFichier, header.reserve, header.offset);
	puts("----------------\n");
}

void printDIB(imageEntete DIB)
{
	puts("------DIB------");
	printf("DIB header size : 0x%08x\nImage Width : 0x%08x\nImage Height : 0x%08x\nPlanes : 0x%08x\nBits per pixel : 0x%08x\nCompression : 0x%08x\nImage size : 0x%08x\nX pixel per Meter : 0x%08x\nY pixel per Meter : 0x%08x\nColor in colorTable : 0x%08x\nImportant color count  : 0x%08x\n", 
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
