#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int* b);

int compare(int* a, int *b, int n);

void affiche(int* a, int n);

void merge (int* tab, int* tmp, int left, int mid, int right, int* cnt);

int BubbleSort(int* tab, int n, unsigned char (*func)(int, int));

int insertionSort(int* tab, int n);

void merge(int* tab, int* tmp, int left, int mid, int right, int* cnt);

int mergeSort(int* tab, int n);

unsigned char asc(int a, int b);
unsigned char desc(int a, int b);