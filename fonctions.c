#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(){return 1;}

int max(){return 2;}

int avg(){return 3;}

int sum(){return 4;}

int odd(){return 5;}

int recherche_operation(char* ch)
{
	if (!strcmp(ch,"min"))
		return 0;
	if (!strcmp(ch,"max"))
		return 1;
	if (!strcmp(ch,"avg"))
		return 2;
	if (!strcmp(ch,"sum"))
		return 3;
	if (!strcmp(ch,"odd"))
		return 4;
	return 5;
}

int fonction(int indice_operation,int tab[],int taille)
{
	if (indice_operation==0)
		return min();
	if (indice_operation==1)
		return max();
	if (indice_operation==2)
		return avg();
	if (indice_operation==3)
		return sum();
	else 
		return odd();

}

/*
 void* recherche(void* arg)
{
	struct inf* info_thr = (struct inf*) arg;
	info_thr->retour = 0;
	int i;
	for (i = info_thr->debut ; i < info_thr->fin ; i++)
	{
		if (tab[i] > info_thr->retour)
			info_thr->retour = tab[i];
	}
}
maximum utilisée par le prof.
*/
