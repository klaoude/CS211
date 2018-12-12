#include "fat.h"

void initialise_fat()
{
	//initialisation du tableau FAT en déclarant tous les blocs libres.
	for(int i = 0; i < BLOCNUM; i++)
		FAT[i] = FREE;

	//initialisation de la variable freeblocks à BLOCNUM.
	freeblocks = BLOCNUM;

	//initialisation de la variable objet
	obj = NULL;
}

Objet* rechercher_objet(char *nom)
{
	Objet* tmp = obj;

    while(tmp != NULL)
    {
        if(strcmp(tmp->nom, nom) == 0)
            return tmp;

        tmp = tmp->next;
    }
    return NULL;
}

void free_FAT(unsigned short index, unsigned int size)
{
	for(int i = 0; i < size / BLOCSIZE + 1; i++)
	{
		int next = FAT[index];
		FAT[index] = FREE;
		freeblocks++;
		if(next == LAST_BLOC)
			break;
		index = next;
	}
}

Objet* creer_objet(char *nom, unsigned short auteur,unsigned int taille, char *data)
{
	if(strlen(nom) >= NAMELEN)
		return NULL;

	if(nom == NULL)
		return NULL;

	if(rechercher_objet(nom) != NULL)
		return NULL;

	Objet* objet = malloc(sizeof(Objet));

	objet->nom = malloc(strlen(nom) + 1);
	strcpy(objet->nom, nom);
	objet->auteur = auteur;
	objet->taille = taille;
	objet->next = NULL;

	unsigned int nbBlocUsed = taille / BLOCSIZE + 1; //nb de bloc utilisé par le fichier
	
	unsigned int compteur = 0; //compte le nombre de bloc traversé
	unsigned int old = 0; //bloc derière le bloc courant
	unsigned int curr = 0; //current cut index
	unsigned int next = 0;
	while(compteur != nbBlocUsed + 1)
	{
		//find first freeblock
		for(int i = old; i < BLOCNUM; i++)
		{
			if(FAT[i] == FREE)
			{
				curr = i;
				break;
			}
		}

		//set objet->index to ptr to first block
		if(compteur == 0)
			objet->index = curr;

		if(compteur == nbBlocUsed - 1)
		{
			FAT[curr] = LAST_BLOC;
			freeblocks--;
			//copy data to volume
			memcpy(volume + curr * BLOCSIZE, 
					data, 
					taille - (nbBlocUsed - 1) * BLOCSIZE);
			*(volume + curr * BLOCSIZE + taille - (nbBlocUsed - 1) * BLOCSIZE + 1) = 0x00;
			
			data = data + BLOCSIZE;
			compteur = nbBlocUsed + 1;
			break;
		}

		//find second next free
		for(int i = curr + 1; i < BLOCNUM; i++)
		{
			if(FAT[i] == FREE)
			{
				next = i;
				break;
			}
		}

		//curr point to next
		FAT[curr] = next;

		freeblocks--;

		//copy data to volume
		memcpy(volume + curr * BLOCSIZE, data, BLOCSIZE);
		data += BLOCSIZE;
		
		old = next;
		compteur++;
	}

	if(obj == NULL)
	{
		obj = objet;
		return objet;
	}
	else
	{
		objet->next = obj;
		obj = objet;
		return objet;
	}

	return NULL;
}

int supprimer_objet(char* nom)
{
	if(nom == NULL)
		return -1;

	if(obj == NULL)
		return -1;

	Objet* tmp = obj;
	Objet* prev;
	unsigned short ind;

	if(tmp->next == NULL && strcmp(tmp->nom, nom) == 0)
	{
		ind = tmp->index;
		obj = NULL;

		free_FAT(ind, tmp->taille);

		free(tmp);

		return 0;
	}

	while(tmp->next != NULL)
	{
		if(strcmp(tmp->next->nom, nom) == 0)
		{
			prev = tmp;

			Objet* suiv = tmp->next->next; 

			prev->next = suiv;
			ind = tmp->next->index;

			free_FAT(ind, tmp->taille);

			free(tmp->next);

			return 0;
		}

		tmp = tmp->next;
	}	
	return -1;
}

void supprimer_tout()
{
	while(obj != NULL)
		supprimer_objet(obj->nom);
}

int lire_objet(Objet* o, char** data)
{
	if(o == NULL || obj == NULL)
		return -1;

	int index = o->index;

	*data = malloc(o->taille + 1);

	for(int i = 0; i < o->taille / BLOCSIZE + 1; i++)
	{
		memcpy((*data) + i * BLOCSIZE, 
				volume + BLOCSIZE * index, 
				o->taille < BLOCSIZE ? o->taille : BLOCSIZE);

		if(index == LAST_BLOC)
			break;

		index = FAT[index];
	}

	return 0;
}