#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bitmap.h"

void exo1(const char* srcPath, const char* dstPath)
{
	FILE* src = fopen(srcPath, "rb");
	FILE* dst = fopen(dstPath, "wb");

	if(src == NULL || dst == NULL) perror("[-] Cannot find transporteur.txt or create original.txt !");

	char curr;
	unsigned char i = 0, buf = 0;

	do
	{
		if(i > 7)
		{
			fputc(buf, dst);
			i = buf = 0;
		}

		curr = fgetc(src);

		if(isalpha(curr))
		{
			buf = buf << 1;
			buf += (isupper(curr) > 0);
			i++;
		}
	} while(curr != EOF);

	fclose(src);
	fclose(dst);
}

void exo2(const char* srcPath, const char* dstPath)
{
	FILE* src = fopen(srcPath, "rb");
	FILE* dst = fopen(dstPath, "wb");

	if(src == NULL || dst == NULL) perror("[-] Cannot find transporteur.bmp or create original.bmp !");

	BMP bmp;

	fread(&(bmp.fileHeader), sizeof(fichierEntete), 1, src);
	bmp.fileHeader.signature = ((bmp.fileHeader.signature & 0xff) << 8) + ((bmp.fileHeader.signature & 0xff00) >> 8);
	fread(&(bmp.imageHeader), sizeof(imageEntete), 1, src);

	printf("[*] fileHeader [ tag : 0x%x, size : 0x%x, res : 0x%x, offset : 0x%x ]\n", bmp.fileHeader.signature, bmp.fileHeader.tailleFichier, bmp.fileHeader.reserve, bmp.fileHeader.offset);
	printf("[*] imageHeader [ sizeHeader : 0x%x, width : 0x%x, height : 0x%x, plan : 0x%x, depth : 0x%x, compres : 0x%x, imgSize : 0x%x, Hres : 0x%x, Vres : 0x%x, nbColor : 0x%x, nmImpColor : 0x%x ]\n", bmp.imageHeader.tailleEntete, bmp.imageHeader.largeur, bmp.imageHeader.hauteur, bmp.imageHeader.plan, bmp.imageHeader.profondeur, bmp.imageHeader.compression, bmp.imageHeader.tailleImage, bmp.imageHeader.resolutionHorizontale, bmp.imageHeader.resolutionVerticale, bmp.imageHeader.nombreCouleurs, bmp.imageHeader.nombreCouleursImportantes);

	char curr;
	unsigned char j = 0, buf = 0;

	for(int i = 0; i < bmp.imageHeader.tailleImage; i++)
	{
		curr = fgetc(src);
		if(j > 7)
		{
			fputc(buf, dst);
			j = buf = 0;
		}

		buf = buf << 1;
		buf += (curr & 0x1);
		
		j++;
	}

	fclose(src);
	fclose(dst);
}

void mask(const char* srcPath, const char* originPath, const char* dstPath)
{
	FILE* src = fopen(srcPath, "rb");
	FILE* origin = fopen(originPath, "rb");
	FILE* dst = fopen(dstPath, "wb");

	if(src == NULL || dst == NULL || origin == NULL) 
	{
		printf("[-] Cannot open %s or %s or write to %s\n", srcPath, originPath, dstPath);
		exit(-1);
	}

	BMP srcBmp;

	fread(&(srcBmp.fileHeader), sizeof(fichierEntete), 1, src);
	srcBmp.fileHeader.signature = ((srcBmp.fileHeader.signature & 0xff) << 8) + ((srcBmp.fileHeader.signature & 0xff00) >> 8);
	fread(&(srcBmp.imageHeader), sizeof(imageEntete), 1, src);

	fseek(origin, 0, SEEK_END);
	unsigned int size = ftell(origin);
	fseek(src, 0, SEEK_SET);
	fseek(origin, 0, SEEK_SET);

	for(int i = 0; i < 0x36; i++)
		fputc(fgetc(src), dst);

	for(int i = 0; i < size; i++)
	{
		unsigned char enc = fgetc(origin);

		for(int j = 0; j < 8; j++)
		{
			unsigned char org = fgetc(src);
			unsigned char bit = (enc >> (7-j)) & 0x1;
			fputc(org | bit, dst);
		}
	}

	printf("[+] %s is created with %s masked in %s !\n", dstPath, originPath, srcPath);

	fclose(src);
	fclose(dst);
	fclose(origin);	
}

int main(int argc, char** argv)
{
	if(argc < 3 || (argc == 4 && !strcmp(argv[1], "mask")))
	{
		printf("Usage : ./TP1 [1,2,mask] [src] [dst] [transport]\n");		
		exit(-3);
	}
	if(!strcmp(argv[1], "1"))
		exo1(argv[2], argv[3]);
	else if(!strcmp(argv[1], "2"))
		exo2(argv[2], argv[3]);
	else if(!strcmp(argv[1], "mask"))
		mask(argv[2], argv[3], argv[4]);

	return 0;
}