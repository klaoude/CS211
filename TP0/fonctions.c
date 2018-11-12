#include <stdio.h>
#include <stdlib.h>

#include "fonctions.h"

void affiche(int* a, int n)
{
	for (int i = 0 ; i < n ; i++)
		printf("%d ", a[i]);
	printf("\n\n");
}

int compare(int* a, int *b, int n)
{
	for(int i = 0; i < n ; i++)
	{
		if (a[i] != b[i])
		{
			printf("Comparison FAILED at index %d\n\n", i);
			return i;
		}
	}
	printf("Comparison OK\n\n");
	return -1;	
}

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int BubbleSort(int* tab, int n)
{
	int ret = 0;
	int swapNum = 1;
	while(swapNum != 0)
	{
		swapNum = 0;
		for(int i = 0; i < n - 1; i++)
		{
			if(tab[i] > tab[i+1])
			{
				swap(tab + i, tab + i + 1);
				swapNum++;
			}
			ret++;
		}
	}
}