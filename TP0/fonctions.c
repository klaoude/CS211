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
			ret++;
			if(tab[i] > tab[i+1])
			{
				swap(tab + i, tab + i + 1);
				swapNum++;
			}
		}
	}

	return ret;
}

int insertionSort(int* tab, int n)
{
	int ret = 0;
	for(int i = 1; i < n; i++)
	{
		ret++;
		if(tab[i] < tab[i-1])
		{
			for(int j = 0; j < i; j++)
			{
				ret++;
				if(tab[j] > tab[i])
				{
					for(;j < i; j++)
					{
						swap(tab + j, tab + i);
						ret++;
					}
					continue;
				}
			}
		}
	}

	return ret;
}

void merge(int* tab, int* tmp, int left, int mid, int right, int* cnt)
{
	int cntr = 0, i = left, j = mid;

	while(cntr != (right - left) + 1)
	{
		if(i == mid)
		{
			tmp[cntr++] = tab[j++];
		}
		else if(j == right + 1)
		{
			tmp[cntr++] = tab[i++];
		}
		else if(tab[i] < tab[j])
		{
			tmp[cntr++] = tab[i++];
		}
		else if(tab[i] > tab[j])
		{
			tmp[cntr++] = tab[j++];
		}
		else
		{
			tmp[cntr++] = tab[i++];
		}

		(*cnt)++;
	}

	for(int k = 0; k < right - left + 1; k++)
	{
		tab[left + k] = tmp[k];
		(*cnt)++;
	}

}

int mergeSort(int* tab, int n)
{
	int* tmp = malloc(n * sizeof(int));
	int cntr = 0;

	for(int i = 1; i < n; i+=2)
	{
		if(tab[i] < tab[i-1])
		{
			swap(tab + i, tab + i - 1);
			cntr++;
		}
	}

	for(int i = 2; i < n; i+=2)
	{
		if(i == n-1)
			merge(tab, tmp, 0, n-1, n-1, &cntr);
		else
			merge(tab, tmp, 0, i, i+1, &cntr);
	}

	free(tmp);

	return cntr;
}
