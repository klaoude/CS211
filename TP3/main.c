#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 

#include "AlgoGenetique.h" 

int main(int argc, char *argv[]) 
{	
	srand(time(NULL));

	int opt,nbgeneration=0;
 	groupe population,parents; 

	// les valeurs par defaut. 	
	population.nombre=NBPOPULATION; 
	parents.nombre=NBPARENTS; 
	
 	while ((opt = getopt(argc, argv, "p:P:")) != -1) 
	{
	    switch (opt) 
	    {
			case 'p':
				population.nombre=atoi(opt);
				break;
			case 'P':
				parents.nombre = atoi(opt);
				break;
			default:
				fprintf(stderr, "Usage: %s [-p nbpopulation] [-P nbparents] \n",argv[0]);
				exit(EXIT_FAILURE);
       }
    }
	// test et allocation mémoire. 
	if (parents.nombre > population.nombre) 
		exit(EXIT_FAILURE);  

	if (( population.membres = malloc(sizeof(serpent) * population.nombre) ) == NULL) 
		exit(EXIT_FAILURE);
	if (( parents.membres = malloc(sizeof(serpent) * parents.nombre) ) == NULL) 
		exit(EXIT_FAILURE);

	// creation de la premiere génération 
	generationAleatoire(&population);


	while (evaluation(&population)) 
	{
		printf("Generation %d\n", nbgeneration); 
		selection(&population, &parents); 
		reproduction(&population, &parents); 
		mutation(&population);
		nbgeneration++;
	}

	printf("Generation %d\n",nbgeneration);
	free(population.membres); 
	free(parents.membres); 
}