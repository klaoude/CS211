#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Ici, on est obligé d'utiliser la notation struct xxx,
car la structure s'auto-référence!*/
typedef struct node 
{
	char data ;
	struct node *link ;
} Lnode ;

/* Insertion en "tête de liste" */
void insertionTete(Lnode **ph,char item)
{
	/* A compléter */
}


/* Insertion en "queue de liste" */
void insertionQueue(Lnode **ph,char item)	
{
	/* A compléter */
}

/* Suppression en "tête de liste" */
void suppressionTete(Lnode **ph)
{
	/* A compléter */
}

/* Suppression en "Queue" de liste" */
void suppressionQueue(Lnode **ph)
{
	/* A compléter */
}

/* Procédure d'affichage de la liste. Ne doit pas être modifiée!!! */
void listeAffiche(Lnode * ptr)
{
	if ( NULL == ptr )
		printf("Liste vide!") ;
	else 
		printf("Contenu de la liste : ") ;
	while ( NULL != ptr ) 	
	{
		printf("%c ",ptr->data);
		ptr = ptr->link ;
	}
	printf("\n") ;
}

/* Programme principal. Ne doit pas être modifié!!! */
int main(void)
{
	Lnode *tete = NULL ;

	listeAffiche(tete) ;
	insertionTete(&tete,'a') ;
	listeAffiche(tete) ;
	insertionTete(&tete,'c') ;
	listeAffiche(tete) ;
	insertionQueue(&tete,'t') ;
	listeAffiche(tete) ;
	insertionQueue(&tete,'s') ;
	listeAffiche(tete) ;
	suppressionTete(&tete) ;
	listeAffiche(tete) ;
	suppressionTete(&tete) ;
	listeAffiche(tete) ;
	suppressionQueue(&tete) ;
	listeAffiche(tete) ;
	suppressionTete(&tete) ;
	listeAffiche(tete) ;

	return EXIT_SUCCESS;
}	
