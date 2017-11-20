#include "fat.h"

void initialise_fat()
{
	//initialisation du tableau FAT en déclarant tous les blocs libres.
	for(int i = 0; i < BLOCNUM; i++)
		FAT[i] = 0xFFFF;

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

Objet* creer_objet(char* nom, unsigned short auteur, unsigned int taille, char *data)
{
	if(strlen(nom) >= NAMELEN)
		return NULL;

	Objet* objet = malloc(sizeof(Objet));

	objet->nom = nom;
	objet->auteur = auteur;
	objet->taille = taille;
	objet->next = NULL;

	unsigned int nbBlocUsed = taille / BLOCSIZE + 1;
	
	unsigned int compteur = 0;
	unsigned int old = 0, curr = 0, next = 0;
	while(compteur != nbBlocUsed+1)
	{
		//find first freeblock
		for(int i = old; i < BLOCNUM; i++)
		{
			if(FAT[i] == 0xffff)
			{
				curr = i;
				break;
			}
		}

		//set objet->index to ptr to first block
		if(compteur == 0)
			objet->index = curr;

		if(compteur == nbBlocUsed-1)
		{
			FAT[curr] = 0xfffe;
			//copy data to volume
			memcpy(volume + curr * 512, data, 512);
			data = data+512;
			compteur = nbBlocUsed+1;
			break;
		}

		//find second next free
		for(int i = curr+1; i < BLOCNUM; i++)
		{
			if(FAT[i] == 0xffff)
			{
				next = i;
				break;
			}
		}

		//curr point to next
		FAT[curr] = next;

		//copy data to volume
		memcpy(volume + curr * 512, data, 512);
		data = data+512;
		
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

int supprimer_objet(char *nom)
{
	if(nom == NULL)
		return -1;

	if(obj == NULL)
		return -1;

	Objet* tmp = obj;
	Objet* prev;
	unsigned short ind;

	while(tmp != NULL)
	{
		prev = tmp;
		if(strcmp(tmp->nom, nom) == 0)
		{
			Objet* suiv = tmp->next; 
			tmp->next = NULL;
			ind = tmp->index;

			for(int i = 0; i < tmp->taille / BLOCSIZE + 1; i++)
			{
				int next = FAT[ind];
				FAT[ind] = 0xffff;
				if(next == 0xfffe)
					break;
				ind = next;
			}

			obj = suiv;
			free(tmp);

			return 0;
		}

		tmp = tmp->next;
	}	
	return -1;
}

void supprimer_tout()
{
	while(obj != NULL)
	{
		supprimer_objet(obj->nom);
	}
}

int lire_objet(Objet* o, char** data)
{
	if(o == NULL || obj == NULL)
		return -1;

	int index = o->index;
	*data = malloc(o->taille);

	for(int i = 0; i < o->taille / BLOCSIZE + 1; i++)
	{
		memcpy((*data) + i * BLOCSIZE, volume + BLOCSIZE * index, o->taille < BLOCSIZE ? o->taille : BLOCSIZE);
		if(index == 0xfffe)
			break;
		index = FAT[index];
	}

	return 0;
}