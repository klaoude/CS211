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

	if(nom == NULL)
		return NULL;

	if(rechercher_objet(nom) != NULL)
		return NULL;

	Objet* objet = malloc(sizeof(Objet));

	objet->nom = malloc(strlen(nom)+1);
	strcpy(objet->nom, nom);
	objet->auteur = auteur;
	objet->taille = taille;
	objet->next = NULL;

	unsigned int nbBlocUsed = taille / BLOCSIZE + 1; //nb de bloc utilisé par le fichier
	
	unsigned int compteur = 0; //conte le nombre de bloc traversé
	unsigned int old = 0; //bloc derierre le bloc courant
	unsigned int curr = 0; //current cut index
	unsigned int next = 0;
	while(compteur != nbBlocUsed + 1)
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
			freeblocks--;
			//copy data to volume
			memcpy(volume + curr * 512, 
					data, 
					taille - (nbBlocUsed-1)*512);
			*(volume + curr*512 + taille - (nbBlocUsed-1)*512 + 1) = 0x00;
			
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

		freeblocks--;

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

		if(tmp->next == NULL && strcmp(tmp->nom, nom) == 0)
		{
			ind = tmp->index;
			obj = NULL;
			for(int i = 0; i < tmp->taille / BLOCSIZE + 1; i++)
			{
				int next = FAT[ind];
				FAT[ind] = 0xffff;
				freeblocks++;
				if(next == 0xfffe)
					break;
				ind = next;
			}

			free(tmp);

			return 0;
		}

	while(tmp->next != NULL)
	{
		if(strcmp(tmp->next->nom, nom) == 0)
		{
			prev = tmp;
			//surpime l'elements du milieu et link le precedent vers le suivant
			Objet* suiv = tmp->next->next; 
			prev->next = suiv;
			ind = tmp->next->index;

			//on libére les bloc FAT
			for(int i = 0; i < tmp->next->taille / BLOCSIZE + 1; i++)
			{
				int next = FAT[ind];
				FAT[ind] = 0xffff;
				freeblocks++;
				if(next == 0xfffe)
					break;
				ind = next;
			}

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
	{
		supprimer_objet(obj->nom);
	}
}

int lire_objet(Objet* o, char** data)
{
	if(o == NULL || obj == NULL)
		return -1;

	int index = o->index;
	*data = malloc(o->taille+1);

	for(int i = 0; i < o->taille / BLOCSIZE + 1; i++)
	{
		memcpy((*data) + i * BLOCSIZE, 
				volume + BLOCSIZE * index, 
				o->taille < BLOCSIZE ? o->taille : BLOCSIZE);
		if(index == 0xfffe)
			break;
		index = FAT[index];
	}

	return 0;
}